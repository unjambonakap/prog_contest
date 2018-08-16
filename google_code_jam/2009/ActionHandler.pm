package ActionHandler;

use strict;
use warnings;
use lib './perl';
use Utils;
use Action;

use MecheMode;
use SurvivalMode;
use WaitMode;
use AttackMode;
use HoleMode;
use TestMode;
use NoMode;
use PlantMode;

use LastChanceMode;

use constant {
	TEST_MODE => 1,# mode provided for testing
		SURVIVAL_MODE => 2, #mode when our player is harmed => objectif are defined in setMode()
		LAST_CHANCE_MODE => 3,
					WAIT_MODE => 4,
					NO_MODE => 5,
					MECHE_MODE => 6,
					ATTACK_MODE => 7,
					HOLE_MODE => 8,
					PLANT_MODE => 9,



					FAILURE_LACK_MECHE => 1,
					FAILURE_NORMAL => 2,
					FAILURE_HARMED => 4,
					FAILURE_UNKNOWN => 3,
					FAILURE_ESCAPED => 5,
					FAILURE_CHANGE_MODE => 6,

					TOP_LEFT => 1,
					TOP_RIGHT => 2,
					BOT_RIGHT => 3,
					BOT_LEFT => 4,
					UNREACHABLE_ROUND => Utils::LONGUEUR_MECHE_MAX+2*Utils::TAILLE_CARTE+1,

					END_MODE => 1,
					NO_END_MODE => 0,
					MODE_ERROR => -1,
					NEXT_MODE_CHOSEN => 2



};

my %ai_vars= (

		meche_case_bonus => 5,
		enemies_closeness => 2,
		movement_enable => 1,
		direction_enable => 3,
		expose_next_round => 1,
		shorter_path_bonus => 2,
		line_closeness_limit => 1,
		column_closeness_limit => 1,
		pathfinding_bonus_round => 2


		);
my @corners = (TOP_LEFT,TOP_RIGHT,BOT_RIGHT,BOT_LEFT);


sub lineDistance{
	my ($x,$y,$player) = @_;
	return abs($y-$player->{y});
}
sub columnDistance{
	my ($x,$y,$player) = @_;
	return abs($x-$player->{x});
}


sub new{
	my ( $class,$self,$champion);
	($class,$champion) = @_;


	$self = {};
	$self->{champion} = $champion;
	$self->{m} = $self->{champion}->{m};
	$self->{id} = $self->{champion}->{id};
	$self->{my_player} = $self->{m}->{my_player};

	
	$self->{mecheModeEnabled} = ($#{$self->{m}->{meche_cases}} == -1 )? 0 : 1;


	$self->{completedPlay} = 1;
	$self->{temporaryIncrease} = 5;
	$self->{strictMovement} = 0;
	$self->{destinationErrorAccepted} = 1;
	$self->{deplacementErrorAccepted} = 1;
	$self->{allowShortcut} = 1;
	$self->{extraRoundSearch} = 3;
	$self->{bonusShorterPath} = 5;
	$self->{exposeInfluenceCoeff} = 10;
	$self->{enemiesDistanceCoeff} = 0.4;
	$self->{enemiesDistanceStep} = 5;
	$self->{mecheLimit} = 40;
	$self->{enabledDirectionCoeff} = 3;
	$self->{nForesee} = 8;

#score - score mod 6 to not escape just to the next position
	$self->{exposeCoeff} = 2;


	$self->{failureThreshold} = 2;

	$self->{harmThreshold} = 10;

	$self->{restartCount} = 0;
	$self->{restartLimit} = 6;


	$self->{dieForSure} = 0;
	$self->{modeEnded} = MODE_ERROR;
	$self->{dataSet} = 0;
	$self->{nFailure} = 0;
	$self->{restartProcess} = 0;

	bless( $self, $class );

	$self->{&TEST_MODE} = TestMode->new($self);
	$self->{&MECHE_MODE} = MecheMode->new($self);
	$self->{&SURVIVAL_MODE} = SurvivalMode->new($self);
	$self->{&ATTACK_MODE} = AttackMode->new($self);
	$self->{&WAIT_MODE} = WaitMode->new($self);
	$self->{&NO_MODE} = NoMode->new($self);
	$self->{&HOLE_MODE} = HoleMode->new($self);
	$self->{&PLANT_MODE} = PlantMode->new($self);
	$self->{&LAST_CHANCE_MODE} = LastChanceMode->new($self);


	$self->{mode} = NO_MODE;
	$self->{currentMode} = $self->{&NO_MODE};
	$self->{mecheLimit} = 0 if ($self->{mecheModeEnabled} == 0 );

	return $self;

}

sub setData{
	my $self = shift;

	my ($i,$j,$case,$t,$distanceScore,$round,$tX,$tY,$enabledDirection);

	return if $self->{dataSet} == 1;


	$self->{workMap} = Map->new();
	$self->{workMap}->load();

	$self->{influenceMap} = [];
	foreach $i (0..Utils::TAILLE_CARTE-1){
		$self->{influenceMap}->[$i] = [];
		foreach $j (0..Utils::TAILLE_CARTE-1){

			$case = $self->{m}->{cases}->[$i][$j];
			if ($case->{type} != Utils::VIDE and ( $i != $self->{champion}->{x} or $j != $self->{champion}->{y}) or $self->{m}->isCaseExposed($i,$j,0)==1 ){
				$t = -1;
			}else{
				$round = Utils::manhattanLength($i,$j,$self->{champion}->{x},$self->{champion}->{y});

				$t = 0;

				$distanceScore = (Utils::TAILLE_CARTE-1)*2-$round;
				foreach (@{$self->{m}->{other_players}}){
					$distanceScore += int(Utils::manhattanLength($_->{x},$_->{y},$i,$j)*$self->{enemiesDistanceCoeff});

				}
				$distanceScore = $distanceScore - $distanceScore % $self->{enemiesDistanceStep};
				$t += $distanceScore;




				$enabledDirection = 1;
				foreach (@Utils::directions){
					($tX,$tY) = Utils::movement($_,$i,$j);
					next unless ( $self->{m}->{cases}->[$tX][$tY]->{type} == Utils::VIDE or $_== Utils::DIRECTION_STATIC);
					$enabledDirection ++;
#$count ++ if ($self->{m}->isCaseExposed($tX,$tY,$round+1) == 0);
				}
				$t += $enabledDirection*$self->{enabledDirectionCoeff};

				$enabledDirection = 1;
				foreach (@Utils::secondRoundVectors){
					($tX,$tY) = Utils::addVectors($_,[$i,$j]);
					next if ($tX < 0 or $tY < 0 or $tX >= Utils::TAILLE_CARTE or $tY >= Utils::TAILLE_CARTE);
					
					next unless ($self->{m}->{cases}->[$tX][$tY]->{type} == Utils::VIDE or $tX == $i and $tY == $j);

					$enabledDirection ++;
				}

				$t += $enabledDirection*$self->{enabledDirectionCoeff};
				$t -= $self->{exposeInfluenceCoeff}*$case->{nExpose};

				$t = 0 if ( $t < 0 );
			}
			$self->{influenceMap}->[$i][$j] = $t;

#the higher $t => safer case
		}
	}
#foreach $i (0..Utils::TAILLE_CARTE-1){
#		foreach $j (0..Utils::TAILLE_CARTE-1){
#			print " $self->{influenceMap}->[$j][$i] ";
#		}print "\n";
#	}

	$self->{dataSet} = 1;

}


sub setMode{
	my ($self,$mode,@data) = @_;
	my $fail = 0;

	print "$self->{mode}///$mode\n";
	return if ($self->{modeEnded} == NO_END_MODE  and $self->{mode} == $mode);
	$self->{mode} = $mode;
	$self->{modeEnded} = NO_END_MODE;

	if ($self->{mecheModeEnabled} == 0 and $mode == MECHE_MODE){
		$self->{mode} = WAIT_MODE;
		@data = (1);
	}

	print "-------------Start set mode-------------\n";
	$self->{dest_x} = $self->{dest_y} = undef;

	$self->{currentMode} = $self->{$mode};

#die "undefined current mode\n" if (not defined $self->{currentMode});

	$fail = $self->{currentMode}->setMode(@data);
	

	$self->{nFailure} = 0;
	print "-------------End set mode-------------\n";

	if ( $fail == -1 ){
		$self->{mode} = WAIT_MODE;
	
		$self->{currentMode} = $self->{&WAIT_MODE};
		$fail = $self->{currentMode}->setMode(-1);
#die "couldn't set wait mode\n" if ($fail == -1);

	}elsif($fail == -2){
		if ($self->deadForSure() == 1){
			$self->{mode} = LAST_CHANCE_MODE;
			$self->{currentMode} = $self->{&LAST_CHANCE_MODE};
			$fail = $self->{currentMode}->setMode();
#die "couldn't set last chance mode\n" if ($fail == -1);
		}else{
			$self->setMode(HOLE_MODE);
		}

	}
	return $fail;
}


sub isModeOver{
	my $self = shift;
	my $ret = 0;


	$ret = $self->{currentMode}->isModeOver();


	$self->{modeEnded} = $ret;
	return $ret;

}

sub harmed{

	my $self = shift;
	my $danger = $self->evaluateDanger($self->{champion}->{x},$self->{champion}->{y},0);
# if we do not move, what will happen next time?

	return 1 if ($danger == -1);
#return 1 if ( $danger == -1 or $danger >= $self->{harmThreshold} );


	return 0;

}



sub endMode{

#this method is called when a mode is completed ( that does not mean the result is as expected )
	my $self = shift;
	print "end mode\n";
	if ($self->{modeEnded} == NEXT_MODE_CHOSEN){
		$self->setMode($self->{currentMode}->{nextMode});
	}else{
		if ($self->{mode} == SURVIVAL_MODE ){
			$self->setMode(ATTACK_MODE)
		}elsif($self->{mode} == HOLE_MODE){
			$self->setMode(WAIT_MODE,1);
		}else{

			$self->chooseMode();

		}
	}
}




sub chooseMode{

	my $self = shift;
	print "choose mode\n";
	if ($self->{mode} == MECHE_MODE){
		$self->setMode(ATTACK_MODE);

	}elsif ($self->{mode} == ATTACK_MODE){
		$self->setMode(WAIT_MODE,1);
	}else{
		$self->setMode(ATTACK_MODE);
	}

	print "end choose mode\n";

}

sub think{

# this function does basic checks, and call a method which process the action to do in the current mode
	my $self = shift;


	print "///////////////Start thinking//////////////////////\n";


	if ( $self->isModeOver() != NO_END_MODE ){
		$self->endMode();
	}else{

		if ( $self->{nFailure} >= $self->{failureThreshold} ){
			$self->chooseMode();

		}else{
			if ($self->{restartProcess} == 1 ){
				if ($self->{failureReason} == FAILURE_HARMED and $self->{mode} != HOLE_MODE ){

					$self->setMode(SURVIVAL_MODE);

				}elsif ($self->{failureReason} == FAILURE_CHANGE_MODE ){


				}elsif($self->{failureReason} == FAILURE_LACK_MECHE){
					$self->setMode(MECHE_MODE) if ($self->{mecheModeEnabled} == 0);
					
				}else{
					if ($self->{currentMode}->handleFailure() == -1 ){
						$self->chooseMode();
					}

				}

			}

		}

	}
	if (($self->{mode} == WAIT_MODE or $self->{mode} == NO_MODE)){
		$self->setMode(MECHE_MODE) if ( $self->{champion}->{perso}->{meche} < $self->{mecheLimit} );

	}



	if ( $self->{dieForSure} == 1 ){
		$self->setMode(LAST_CHANCE_MODE);

	}

	if ($self->{mode} == NO_MODE ){
		$self->setMode(WAIT_MODE,-1);

	}


	print "///////////////End thinking//////////////////////\n";
}






sub act{

#this method is stupid, it just accomplishes the indiced action
	my $self = shift;
	my $ret = Utils::SUCCES;

	print "Start acting===========\n";

	$self->{action}->display();
	$self->{action}->completeAction();

	print "End acting==========\n";

	return $ret;


}



sub processActionSafeness{
	my $self = shift;
	my ($x,$y,$a,$tX,$tY);



	return 1 if ($self->{mode} == LAST_CHANCE_MODE);

	$a = $self->{action};

	$self->{m}->displayMap();

	($x,$y) = ($self->{champion}->{x},$self->{champion}->{y});
	if ( not defined $a ){ print "not defined => $self->{mode}\n";}
	elsif ($a->{type} == Utils::ACTION_PLANT ){
		($tX,$tY) = Utils::movement($a->{direction},$x,$y);
		$self->{workMap}->addBomb($tX,$tY,$a->{time_remaining},$self->{champion}->{id});

	}elsif ($a->{type} == Utils::ACTION_MOVE ){

		$self->{workMap}->{cases}->[$self->{champion}->{x}][$self->{champion}->{y}]->{type} = Utils::VIDE;
		($x,$y) = Utils::movement($a->{direction},$x,$y);
		$self->{workMap}->{cases}->[$x][$y]->{type} = Utils::JOUEUR;
	}



	@$self{"newX","newY"} = ($x,$y);
	print "action safeness: $x $y ";
	$a->display();
	print "\n";

	my $ret = $self->actionDanger($x,$y);
	print "ret: $ret\n";


	if ( $ret == -1 ){
		$self->{workMap}->{cases}->[$x][$y]->{type} = Utils::JOUEUR;
		$self->{workMap}->{cases}->[$self->{champion}->{x}][$self->{champion}->{y}]->{type} = Utils::VIDE;
		$self->{failureReason} = FAILURE_HARMED;



		if ($a->{type} == Utils::ACTION_PLANT ){
			$self->{workMap}->delBomb($tX,$tY);
		}
		$self->{workMap}->{cases}->[$x][$y]->{type} = Utils::JOUEUR;
		$self->{workMap}->{cases}->[$self->{champion}->{x}][$self->{champion}->{y}]->{type} = Utils::VIDE;
		return 0;

	}



	if ($self->{mode} != HOLE_MODE and $self->{mode} != SURVIVAL_MODE){
		$self->{workMap}->displayMap();
		$ret = $self->{&ATTACK_MODE}->mbCorridorAttack();
		$ret = 0;

		if ($ret == 1 or $ret == 2){
			$self->{failureReason} = FAILURE_CHANGE_MODE;
			$self->setMode(HOLE_MODE,$self->{&ATTACK_MODE}->{attackType});
			$self->{workMap}->{cases}->[$x][$y]->{type} = Utils::JOUEUR;
			$self->{workMap}->{cases}->[$self->{champion}->{x}][$self->{champion}->{y}]->{type} = Utils::VIDE;

			if ($a->{type} == Utils::ACTION_PLANT ){
				$self->{workMap}->delBomb($tX,$tY);
			}
			$self->{workMap}->{cases}->[$x][$y]->{type} = Utils::JOUEUR;
			$self->{workMap}->{cases}->[$self->{champion}->{x}][$self->{champion}->{y}]->{type} = Utils::VIDE;
			return 0;
		}


	}
	if ($a->{type} == Utils::ACTION_PLANT ){
		$self->{workMap}->delBomb($tX,$tY);
	}
	$self->{workMap}->{cases}->[$x][$y]->{type} = Utils::JOUEUR;
	$self->{workMap}->{cases}->[$self->{champion}->{x}][$self->{champion}->{y}]->{type} = Utils::VIDE;

	return 1;

}


sub play{
	my $self = shift;

	print "+++++++++++++++++++++++++++++ AI CONTROL STARTING++++++++++++++++++++++\n";
	print "Current mode: $self->{mode}\n";
	print "joue avant ",sdz::joue_avant(1,2),"\n";

	Utils::displayHash($self->{m}->{play_order});

	@$self{"x","y","id"} = @{$self->{champion}}{"x","y","id"};

	if ($self->{restartProcess} == 0){
		$self->{dataSet} = 0;
		$self->{restartCount} = 0;

	}
	$self->{action} = Action->new({type=>Utils::ACTION_NONE});
	$self->setData();
	$self->{completedLastPlay} = $self->{completedPlay};
	$self->{nFailure} ++ if ($self->{completedLastPlay} == 0 );

	$self->{mecheCaught} += $self->{champion}->{perso}->{meche} - $self->{champion}->{perso}->{previousMeche};
	print "NFailure: $self->{nFailure}\n";

#	my ($x,$y) = (3,4);
#	my $k;
#	$self->{workMap}->addBomb(21,15,3,1);
#	foreach(@{$self->{m}->{players}}){
#		print "START PLAYING $_->{id}\n";
#		print $self->{workMap}->isCaisseDestroyed(22,15,2,$_->{id}),"\n";
##		$self->{workMap}->displayExposeMap($_->{id},8);
#		print "ENDD PLAYER ================\n";
#	}
#	exit;


	if ( $self->{completedLastPlay} == 0 ){
		print "Couldn't complete last play ( exceed time limit or so )\n";

	}

	$self->think() if ( $self->{dieForSure} == 0 );

	$self->{restartProcess} = 0;
	$self->{completedPlay} = 0;
	$self->{failureReason} = FAILURE_UNKNOWN;


	$self->processMode();
	print "end process\n";


	if ( $self->{restartProcess} == 0 ){

		if ( $self->processActionSafeness() == 1 ){

			if ($self->act() == Utils::SUCCES){
				$self->{completedPlay} = 1;
				print "successful play\n";
				$self->{currentMode}->successfulPlay();
			}else{
				print "\n\n\n\nPlay failed\n\n\n\n\n\n";
				$self->{restartProcess} = 1;
			}
		}else{
			$self->{restartProcess} = 1;
			print "no action safeness\n";

		}

	}
	if ( $self->{restartProcess} == 1 and $self->{restartCount} <= $self->{restartLimit} ){# to prevent infinite loop ( to change )
# we want to restart the process => redo everything

		$self->{completedPlay} = $self->{completedLastPlay};
		$self->{restartCount} ++;
		$self->play();


	}elsif( $self->{restartProcess} == 1 ){
		$self->{workMap}->displayMap();
		print "too much restart process, doing nothing\n";
		$self->{restartProcess} = 0;


	}
# do not write anything after that ======================

	print "+++++++++++++++++++++++++++++ END OF AI CONTROL++++++++++++++++++++++\n";


}


sub processMode{

# we can call this the heart of the ai, it will settle the action to do following the current mode of the ai

	print "Start Process mode\n";
	my $self = shift;
	my $ret = 0;


	$ret = $self->{currentMode}->processMode();


	if ($ret == -1 ){
		$self->{restartProcess} = 1;
	}
	print "End process mode\n";
}




sub completePath{
	my $self = shift;
	my ($nextDest,$currentDest) =(0,0);

	if ( $#{$self->{temporaryPath}} == -1){
		$nextDest = 1;

	}else{
		my $tempDist = Utils::manhattanLength($self->{champion}->{x},$self->{champion}->{y},
				$self->{simplePath}->[$self->{temporarySteps}]->{x},$self->{simplePath}->[$self->{temporarySteps}]->{y});

		if ($self->{completedLastPlay} == 0 and $tempDist <= $self->{destinationErrorAccepted}){

			$nextDest = 1;
# movement failed, but close to temporary destination => go to the next temporary destination

		}
		elsif ($self->{completedLastPlay} == 0){
			$currentDest = 1;

#movement failed
		}elsif ( $self->{completedLastPlay} == 1 ){

			my $danger = $self->evaluateDanger($self->{temporaryPath}->[0]->{x},$self->{temporaryPath}->[0]->{y},1);
			if ($danger == -1 ){
				if ($tempDist <= $self->{destinationErrorAccepted}){
					$nextDest = 1;
				}else{
					$currentDest = 1;
				}

			}

		}
	}


	if ($nextDest == 0 and $currentDest == 0 ){
		$currentDest = 1 if ($self->evaluateDanger(Utils::movement($self->{temporaryPath}->[0]->{direction},$self->{champion}->{x},$self->{champion}->{y}),1) == -1 );

	}

	if ($nextDest == 1 ){

		$self->{temporarySteps} += $self->{temporaryIncrease};
		$self->{temporarySteps} = $#{$self->{simplePath}} if ($self->{temporarySteps} > $#{$self->{simplePath}});

#		print "ici => $self->{temporarySteps} / $#{$self->{simplePath}}\n";

		$self->{temporaryPath} = [$self->getSafePath($self->{champion}->{x},$self->{champion}->{y},
				$self->{simplePath}->[$self->{temporarySteps}]->{x},$self->{simplePath}->[$self->{temporarySteps}]->{y})];
		if ($#{$self->{temporaryPath}} == -1){
			$self->{temporarySteps} ++;
			$self->{temporarySteps} = $#{$self->{simplePath}} if ($self->{temporarySteps} > $#{$self->{simplePath}});
			$self->{temporaryPath} = [$self->getSafePath($self->{champion}->{x},$self->{champion}->{y},
					$self->{simplePath}->[$self->{temporarySteps}]->{x},$self->{simplePath}->[$self->{temporarySteps}]->{y})];

		}

		foreach (@{$self->{temporaryPath}}){
			print "$_->{x}, $_->{y} => $Utils::direction_str{$_->{direction}}\n";
		}		

	}elsif ($currentDest == 1 ){

		$self->{temporaryPath} = [$self->getSafePath($self->{champion}->{x},$self->{champion}->{y},
				$self->{simplePath}->[$self->{temporarySteps}]->{x},$self->{simplePath}->[$self->{temporarySteps}]->{y})];
		if ($#{$self->{temporaryPath}} == -1){
			$self->{temporarySteps} ++;
			$self->{temporarySteps} = $#{$self->{simplePath}} if ($self->{temporarySteps} > $#{$self->{simplePath}});
			$self->{temporaryPath} = [$self->getSafePath($self->{champion}->{x},$self->{champion}->{y},
					$self->{simplePath}->[$self->{temporarySteps}]->{x},$self->{simplePath}->[$self->{temporarySteps}]->{y})];
		}
		foreach (@{$self->{temporaryPath}}){
			print "$_->{x}, $_->{y} => $Utils::direction_str{$_->{direction}}\n";
		}		

	}else{

	}

}


sub evaluateDanger{
	my ($self,$x,$y,$round,$playerId) = @_;
	my ($tX,$tY,$count,$danger,$enabledDirection);

	$enabledDirection = $count = 0;
	$danger = 0;
	$playerId = $self->{m}->{my_player}->{id} if (not defined $playerId);


# the following code checks that in the case ($x,$y) at round $round is safe for the $self->{nForesee} next rounds
# it re-uses mostly all the code from canGo subroutine, but adapting it to its needs


	my ($i,$j,$k,$map,$tempMap,$enabledPos,@enabledPosArr,$t,$case);

	$map->[$x][$y] = 1;

	for (my $k=$round;$k<$round+$self->{nForesee};$k ++ ){
		$tempMap = [];

		$enabledPos = 0;
		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				next if (not defined $map->[$i][$j] or $map->[$i][$j] == 0);


				foreach (@Utils::directions){
					($tX,$tY)=Utils::movement($_,$i,$j);
					next if ( Utils::inMap($tX,$tY) == 0 );

					next if (defined $tempMap->[$tX][$tY]);

					$case = $self->{m}->{cases}->[$tX][$tY];
					if ( $self->{m}->isCaseExposed($tX,$tY,$k,$playerId) == 0 ){
#die "Undef" if ( $case->{type} == Utils::CAISSE and not defined $case->{destroyed});
#die "Undef bomb" if ($case->{type} == Utils::BOMBE and not defined $case->{bomb}->{time_remaining}  );

						if ( $case->{type} == Utils::VIDE or ( $case->{type} == Utils::CAISSE and $self->{m}->isCaisseDestroyed($tX,$tY,$k,$playerId) )
								or ($case->{type} == Utils::BOMBE and $self->{m}->isBombDestroyed($tX,$tY,$k,$playerId) )
								or ($case->{type} == Utils::JOUEUR and ($k >= 1 or $tX == $self->{champion}->{x} and $tY == $self->{champion}->{y} )) ){
							$tempMap->[$tX][$tY]=1;

							$enabledPos ++;
						}
						else{
							$tempMap->[$tX][$tY] = 0;

						}
					}

				}

			}
		}
#		print "map at round $k\n";
#		for $i (0..Utils::TAILLE_CARTE-1){
#			for $j (0..Utils::TAILLE_CARTE-1){
#				if ( not defined $tempMap->[$j][$i] ){print "0";}
#				else{print "$tempMap->[$j][$i]";}
#			}print "\n";
#		}

#return -1 if ($enabledPos == 0 );
		if ($enabledPos == 0 ){
			return -1;
		}
		push @enabledPosArr, $enabledPos;

		$map = $tempMap;
	}
	foreach(0..$#enabledPosArr){
#die "$x $y $round" if ( not defined $Utils::posNumber[$round+$_+1]);
		$t = int(($Utils::posNumber[$round+$_+1]-$enabledPosArr[$_])/$Utils::posNumber[$round+$_+1]/($_+$round+1)*10);
# quite a complicated expression, that exprimes the danger at round $_, following the position that can be taken at that round
		$t = 0 if ($t < 0 );
		$danger += $t;
	}

#	print "count 2 $count / $enabledDirection \n";
#	return -1 if ($count==0);
#
#		$danger += $enabledDirection-$count;


	return $danger;

}

sub actionDanger{
	my ($self,$x,$y,$playerId) = @_;
	my $round = 0;

	$playerId = $self->{m}->{my_player}->{id} if (not defined $playerId);

# it completely re-uses the evaluateDanger function, but uses the map workMap, to foresee movements of our/others player(s)
	my ($tX,$tY,$count,$danger,$enabledDirection);

	$enabledDirection = $count = 0;
	$danger = 0;

	print "case directly exposed?\n";
	return -1 if ($self->{workMap}->isCaseExposed($x,$y,0,$playerId));
	print "no\n";

# the following code checks that in the case ($x,$y) at round $round is safe for the $self->{nForesee} next rounds
# it re-uses mostly all the code from canGo subroutine, but adapting it to its needs


	my ($i,$j,$k,$map,$tempMap,$enabledPos,@enabledPosArr,$t,$case);

	$map->[$x][$y] = 1;

	$self->{workMap}->displayExposeMap(undef,8);
	for (my $k=$round+1;$k<$round+$self->{nForesee};$k ++ ){
		$tempMap = [];

		$enabledPos = 0;
		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				next if (not defined $map->[$i][$j] or $map->[$i][$j] == 0);


				foreach (@Utils::directions){
					($tX,$tY)=Utils::movement($_,$i,$j);
					next if (Utils::inMap($tX,$tY) == 0);

					next if (defined $tempMap->[$tX][$tY]);

					$case = $self->{workMap}->{cases}->[$tX][$tY];
					if ( $self->{workMap}->isCaseExposed($tX,$tY,$k,$playerId) == 0 ){
#die "Undef" if ($case->{type} == Utils::CAISSE and not defined $case->{destroyed});
#die "Undef bomb" if ($case->{type} == Utils::BOMBE and not defined $case->{bomb}->{time_remaining});

						if ( $case->{type} == Utils::VIDE or ( $case->{type} == Utils::CAISSE and $self->{m}->isCaisseDestroyed($tX,$tY,$k,$playerId) )
								or ($case->{type} == Utils::BOMBE and $self->{m}->isBombDestroyed($tX,$tY,$k,$playerId))
								or ($case->{type} == Utils::JOUEUR and ($k >= 1 or $tX == $self->{champion}->{x} and $tY == $self->{champion}->{y} )) ){
							$tempMap->[$tX][$tY]=1;

							$enabledPos ++;
						}else{
							$tempMap->[$tX][$tY] = 0;

						}
					}else{
						$tempMap->[$tX][$tY] = 0;
					}



				}

			}
		}
#		print "========> $k\n";
#		for $i (0..Utils::TAILLE_CARTE-1){
#			for $j (0..Utils::TAILLE_CARTE-1){
#				if (not defined $tempMap->[$j][$i]) {print "0";}
#				else{print "$tempMap->[$j][$i]";}
#			}print "\n";
#		}

		if ($enabledPos == 0 ){

			$self->{workMap}->displayMap();

			print "no enabled pos\n";
			return -1;
		}
		push @enabledPosArr, $enabledPos;

		$map = $tempMap;
	}
	foreach(0..$#enabledPosArr){
#die "$x $y $round" if ( not defined $Utils::posNumber[$round+$_+1]);
		$t = int(($Utils::posNumber[$round+$_+1]-$enabledPosArr[$_])/$Utils::posNumber[$round+$_+1]/($_+$round+1)*10);
# quite a complicated expression, that exprimes the danger at round $_, following the position that can be taken at that round
		$t = 0 if ($t < 0 );
		$danger += $t;
	}

	return $danger;




}



sub getPossiblePositions{

	my ($self,$x,$y,$round) = @_;
	my ($map,$tempMap,$i,$j,$tX,$tY,$ret,);

	$map = [];
	$ret = [];

	$map->[$x][$y] = 1;

	for (my $k=0;$k<$round;$k ++ ){
		$tempMap = [];

		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				next if (not defined $map->[$i][$j] or $map->[$i][$j] == 0);

				foreach (@Utils::directions){
					($tX,$tY)=Utils::movement($_,$i,$j);
					next if (Utils::inMap($tX,$tY) == 0);
					next if (defined $tempMap->[$tX][$tY]);

					my $case = $self->{champion}->{m}->{cases}->[$tX][$tY];
					if ( $self->{champion}->{m}->isCaseExposed($tX,$tY,$k) == 0 ){

						if ( $case->{type} == Utils::VIDE or ( $case->{type} == Utils::CAISSE and ( $case->{destroyed} != -1 and $case->{destroyed} < $k ) ) or ($case->{type} == Utils::JOUEUR and (( $x == $i and $y == $j ) or $k >= 1 ) ) or ($case->{type} == Utils::BOMBE and $case->{bomb}->{time_remaining} < $k )){
							$tempMap->[$tX][$tY]=1;
						}
					}
					$tempMap->[$tX][$tY] = 0 if ( not defined $tempMap->[$tX][$tY] );

				}
			}
		}

		push @$ret, [];

		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				push @{$ret->[$#{$ret}]}, [$i,$j] if (defined $tempMap->[$i][$j] and $tempMap->[$i][$j] == 1);
			}
		}

		$map = $tempMap;


	}

	return $ret;
}

sub getPossiblePositionsWithParents{

	my ($self,$x,$y,$round) = @_;
	my ($map,$tempMap,$i,$j,$tX,$tY,$ret,$m,$n,$a,$commonParent);

	$map = [];
	$ret = [];

	$map->[$x][$y]->[$x][$y] = 1;

	for (my $k=0;$k<$round;$k ++ ){
		$tempMap = [];

		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				next if (not defined $map->[$i][$j]);

				foreach (@Utils::directions){
					($tX,$tY)=Utils::movement($_,$i,$j);
					next if (Utils::inMap($tX,$tY) == 0);

					my $case = $self->{champion}->{m}->{cases}->[$tX][$tY];
					if ( $self->{champion}->{m}->isCaseExposed($tX,$tY,$k) == 0 ){

						if ( $case->{type} == Utils::VIDE or ( $case->{type} == Utils::CAISSE and ( $case->{destroyed} != -1 and $case->{destroyed} < $k ) ) or ($case->{type} == Utils::JOUEUR and (( $x == $i and $y == $j ) or $k >= 1 ) ) or ($case->{type} == Utils::BOMBE and $case->{bomb}->{time_remaining} < $k )){
							$tempMap->[$tX][$tY] = [] if (not defined $tempMap->[$tX][$tY]);
							push @{$tempMap->[$tX][$tY]}, $map->[$i][$j];
						}
					}

				}
			}
		}
		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){

				next if (not defined $tempMap->[$i][$j]);
				$a = [];
				for $m (0..Utils::TAILLE_CARTE-1){
					for $n (0..Utils::TAILLE_CARTE-1){
						$commonParent = 1;
						foreach(@{$tempMap->[$i][$j]}){
							if ( not defined $_->[$m][$n]){
								$commonParent = 0;
								last;
							}
						}
						$a->[$m][$n] = 1 if ($commonParent == 1);
					}
				}
				$a->[$i][$j] = 1;
				$tempMap->[$i][$j] = $a;
			}
		}
		push @$ret, $tempMap;

		$map = $tempMap;


	}

	return $ret;
}

sub canGo{
	my ($self,$startX,$startY,$destX,$destY,$playerId)=@_; 


	$playerId = $self->{m}->{my_player}->{id} unless defined $playerId;
	print "Can go,???: ";
	print "dest x $destX";
	print "dest y $destY";
	print "start x $startX";
	print "start y $startY\n";

	if ( not defined $destX or not defined $destY or not defined $startX or not defined $startY ){
		print "exiting cause undefined values in canGo\n";
#exit;
	}
	print "Can go $startX $startY $destX $destY\n";

#this function does not accept a destination to be a player, nor the possibilitie to go during the very next round to go on a player's case
	my ($map,$tempMap,$i,$j,$tX,$tY,$case,$played,$newPoint);
	$map = [];
	my $d = Utils::manhattanLength($startX,$startY,$destX,$destY);

	$case = $self->{m}->{cases}->[$destX][$destY];
	return 0 if ( $case->{type} == Utils::MUR or ( $case->{type} == Utils::CAISSE and $case->{destroyed} == -1 )
			or  ($case->{type} == Utils::JOUEUR and $d == 1 ));


	$map->[$startX][$startY] = 1;

	for (my $k=0;$k<UNREACHABLE_ROUND;$k ++ ){
		$tempMap = [];
		$newPoint = 0;

		$played = 0;
		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				next if (not defined $map->[$i][$j] or $map->[$i][$j] == 0);


				foreach (@Utils::directions){
					($tX,$tY)=Utils::movement($_,$i,$j);
					next if (Utils::inMap($tX,$tY) == 0);

					next if (defined $tempMap->[$tX][$tY] and $tempMap->[$tX][$tY]==1);

					$case = $self->{m}->{cases}->[$tX][$tY];
					if ( $self->{m}->isCaseExposed($tX,$tY,$k,$playerId) == 0 ){
#die "Undef" if ( $case->{type} == Utils::CAISSE and not defined $case->{destroyed} );
#die "Undef bomb" if ($case->{type} == Utils::BOMBE and not defined $case->{bomb}->{time_remaining}  );

						if ( $case->{type} == Utils::VIDE or ( $case->{type} == Utils::CAISSE and $self->{m}->isCaisseDestroyed($tX,$tY,$k,$playerId) )
								or ($case->{type} == Utils::BOMBE and $self->{m}->isBombDestroyed($tX,$tY,$k,$playerId) )
								or ($case->{type} == Utils::JOUEUR and $k >= 1) ){
							$tempMap->[$tX][$tY]=1;
							$played = 1;
							if ($newPoint == 0){
								if ($k > Utils::LONGUEUR_MECHE_MAX){
									$newPoint = 1 if (not defined $map->[$tX][$tY] or $map->[$tX][$tY] == 0);
								}else{
									$newPoint = 1;
								}
							}
						}
					}

				}

			}
		}
		return 0 if ($newPoint == 0);
		$map = $tempMap;
		return 1 if (defined $map->[$destX][$destY] and $map->[$destX][$destY] == 1);
		return 0 if ($played == 0);
	}
#normally never there
	return 0;


}




sub getCompletePath{
	my ($self,$startX,$startY,$destX,$destY) = @_;
	my ($cases,$tb,@openList,@closeList,$lowerF,$t,$newG,$movementCost,@v,$c);

# this function does not consider players

# here A* algorithm is used, cause we do not consider the time/rounds
	$movementCost = 1;


	if ( not defined $destX or not defined $destY or not defined $startX or not defined $startY ){
		print "exiting cause undefined values in getCompletePath\n";
		return ();
	}
	print "getCompletePath $startX $startY $destX $destY\n";

	$tb = [];
	for my $i (0..Utils::TAILLE_CARTE-1){
		$tb->[$i] = [];
		for my $j (0..Utils::TAILLE_CARTE-1){

			$tb->[$i][$j] = {x=>$i,y=>$j,g=>0,h=>Utils::manhattanLength($i,$j,$destX,$destY),inOpenList=>0,inCloseList=>0,openListId=>-1,closeListId=>-1,parent=>undef,case=>$self->{champion}->{m}->{cases}->[$i][$j],path_length=>0};

		}
	}

	push @openList,$tb->[$startX][$startY];
	$tb->[$startX][$startY]->{inOpenList} = 1;
	$tb->[$startX][$startY]->{direction} = Utils::DIRECTION_STATIC;
	$tb->[$startX][$startY]->{openListId} = 0;

	while ($#openList != -1 ){

		$lowerF = 0;
		for my $k (1..$#openList){
			next if (not defined $openList[$k]);

			$lowerF = $k if ($openList[$lowerF]->{g} == -1 or $openList[$lowerF]->{g}+$openList[$lowerF]->{h} >= $openList[$k]->{g}+$openList[$k]->{h});
		}

		$t = $openList[$lowerF];

		if ($t->{x} == $destX and $t->{y} == $destY ){
			my (@ret,$parent);

			unshift @ret,$t;
			$t->{direction} = Utils::DIRECTION_STATIC;
			$parent = $t->{parent};

			return @ret if ( not defined $parent );
			$parent->{direction} = $t->{t_direction};	

			unshift @ret,$parent;
			if ( not defined $parent->{x} or not defined $parent->{y} ){
				return ();

			}

			while($parent->{x} != $startX or $parent->{y} != $startY){
				$parent->{parent}->{direction} = $parent->{direction};
				$parent = $parent->{parent};
				unshift @ret,$parent;
			}

			return @ret;

		}

		splice @openList,$lowerF,1;
		$t->{inOpenList} = 0;

		push @closeList,$t;
		$t->{inCloseList} = 1;
		$t->{closeListId} = $#closeList;



		foreach (@Utils::directions){
			@v = Utils::movement($_,$t->{x},$t->{y});
			next if (Utils::inMap(@v) == 0);
			$c = $tb->[$v[0]][$v[1]];


			next if ($c->{case}->{type} == Utils::MUR or 
					($c->{case}->{type} == Utils::CAISSE and $self->{allowShortcut} == 1 and
					 ($c->{case}->{destroyed} == -1)
					));# the last condition set is used if this is a caisse case, and if it is destroyed
#next if ($c->{case}->{type} == Utils::MUR or $c->{case}->{type} == Utils::CAISSE);

				$newG = $t->{g}+$movementCost;

			if ( $c->{case}->{type} == Utils::CAISSE){
				if ($self->{m}->isCaisseDestroyed(@v[0..1],$t->{path_length}) == 1){
# the child we are considering will be destroyed => add a load to newG so that it will represent the wait of the caisse's destruction
					$newG += $movementCost * ($c->{case}->{destroyed} - $t->{path_length}-1) if ( $c->{case}->{destroyed} > $t->{path_length}+1);
				}else{
					next;
				}
			}
			if($self->{m}->isCaseExposed($v[0],$v[1],$t->{path_length})){
				$newG += $movementCost*5;
			}

			next if (($c->{inCloseList} == 1 or $c->{inOpenList} == 1) and $c->{g}<=$newG);
			$c->{g} = $newG;
			$c->{parent} = $t;
			$c->{t_direction} = $_;
			$c->{path_length} = $t->{path_length}+1;

			push @openList, $c if ($c->{inOpenList} == 0);
			splice @closeList,$c->{closeListId},1 if ($c->{inCloseList}==1);
		}


	}


	return ();

}



sub getCaseCost{
	my ($self,$x,$y,$round) = @_;
#the lower, the better
	my ($score,$case,$meche,$danger);

	$score = 10;
	$case = $self->{champion}->{m}->{cases}->[$x][$y];


	return -1 if ( $case->{type} == Utils::MUR or ( $case->{type} == Utils::BOMBE and $self->{m}->isBombDestroyed($x,$y,$round)==0)
			or ( $case->{type} == Utils::CAISSE and $self->{m}->isCaisseDestroyed($x,$y,$round)==0));

	return -1 if ( $case->{type} == Utils::JOUEUR and ($x != $self->{champion}->{x} or $y != $self->{champion}->{y}) and $round == 0 );
	return -1 if ($self->{champion}->{m}->isCaseExposed($x,$y,$round) == 1);


#$danger = $self->evaluateDanger($x,$y,$round);
#	return -1 if ($danger == -1);
#
#	$score += $danger;



	return $score;


}

sub getSafePath{

	my ($self,$startX,$startY,$destX,$destY) = @_;
	my ($i,$j,$k,$map,$tempMap,$cases,$newG,$currentG,$tCase,$foundRound,$pathRound,$c,$tX,$tY,$played);

	if ( not defined $destX or not defined $destY or not defined $startX or not defined $startY ){
		print "exiting cause undefined values in getSafePath\n";
		return ();
	}
	print "getSafePath $startX $startY $destX $destY\n";
	$self->{temp_dest_x} = $destX;
	$self->{temp_dest_y} = $destY;

#does not accept the possibilitie to, during the very next round, go on a player's case

	return () if ($self->canGo(@_[1..$#_]) == 0);

	print "$startX $startY to $destX $destY\n";
	$cases = $self->{m}->{cases};

	$map = [];

	for $i (0..Utils::TAILLE_CARTE-1){
		$map->[$i] = [];
		for $j (0..Utils::TAILLE_CARTE-1){
			$map->[$i][$j] = {openList=>0,g=>-1,path=>[],caseCost=>-2};
		}
	}
	$map->[$startX][$startY]->{openList} = 1;

	$foundRound = -1;
	for $k (0..UNREACHABLE_ROUND){
		$played = 0;

		$tempMap = [];
		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				$tempMap->[$i][$j] = {openList=>0,g=>-1,caseCost=>-2};
			}
		}
		$tempMap->[$destX][$destY] = $map->[$destX][$destY];
		$tempMap->[$destX][$destY]->{caseCost} = -2;


		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){


				next if ($map->[$i][$j]->{openList} == 0);

				$currentG = $map->[$i][$j]->{g};

#next if ( $i == $destX and $j == $destY );

				foreach (@Utils::directions){
					($tX,$tY) = Utils::movement($_,$i,$j);
					next if (Utils::inMap($tX,$tY) == 0);
					$c = $cases->[$tX][$tY];

					$tCase = $tempMap->[$c->{x}][$c->{y}];
					$tCase->{caseCost} = $self->getCaseCost($c->{x},$c->{y},$k) if ( $tCase->{caseCost} == -2 );

					if ( $tCase->{caseCost} == -1 and $tX == $destX and $tY == $destY ){
						print "impossible dest at round $k\n";

					}
					next if ( $tCase->{caseCost} == -1 );

					$played = 1;
					$newG = $tCase->{caseCost}+$currentG;
					if ($tX == $destX and $tY == $destY ){
						print "destination found\n";

						if ($foundRound == -1){
# first time we find  a path leading to the destination
							$foundRound = $k;

						}else{

							next if ($map->[$i][$j]->{g} <= $newG);
# this path leads to the end, but it ain't better than the one previously found
						}
						$pathRound = $k;

					}
					else{
						next if ( $tCase->{g} != -1 and $tCase->{g} <= $newG );
					}


					$tCase->{g} = $newG;
					$tCase->{openList} = 1;
					$tCase->{path} = [@{$map->[$i][$j]->{path}},{x=>$i,y=>$j,direction=>$_}];





				}

			}

		}
#		print "round $k\n";
#		for $i (0..Utils::TAILLE_CARTE-1){
#
#			for $j (0..Utils::TAILLE_CARTE-1){
#				print $tempMap->[$j][$i]->{openList};
#			}
#			print "\n";
#		}
#


		last if ($played==0);
		$map = $tempMap;



#
#		for $i (0..Utils::TAILLE_CARTE-1){
#			for $j (0..Utils::TAILLE_CARTE-1){
#				printf( " %3d ", $tempMap->[$j][$i]->{g});
#			}
#			print "\n";
#		}
#		print "\n\n\n";
#
#		die "not found\n" if ($k > 12);



		if ($foundRound != -1 and $k >= $foundRound+$self->{extraRoundSearch} ){
			print $map->[$destX][$destY]->{g};
#die "Error pathfinding"  if ( $#{$map->[$destX][$destY]->{path}} == -1 );
			return @{$map->[$destX][$destY]->{path}};
		}
	}
	print "fail founding path\n";
	return ();

}


sub initPath{
	my ($self) = @_;

	$self->{simplePath} = [$self->getCompletePath($self->{champion}->{perso}->{x},$self->{champion}->{perso}->{y},$self->{dest_x},$self->{dest_y})];
	$self->{temporarySteps} = 0;
	$self->{temporaryPath} = [];


}	

sub onDest{
	my ($self) = @_;


	return 1 if (($self->{champion}->{x} == $self->{dest_x} and $self->{champion}->{y} == $self->{dest_y}) or
			($self->{m}->{cases}->[$self->{dest_x}][$self->{dest_y}]->{type} != Utils::VIDE 
			 and Utils::manhattanLength(@$self{"dest_x","dest_y"},@{$self->{champion}}{"x","y"}) <= $self->{destinationErrorAccepted}));

	return 0;
}

sub getPlantMap{

	my ($self,$x,$y,$round,$playerId) = @_;
	$playerId = $self->{m}->{my_player}->{id} unless defined $playerId;

	my ($map,$tempMap,$i,$j,$tX,$tY,$ret,$plantMap);
	$map = [];
	$ret = [];

	$map->[$x][$y] = 1;

	for (my $k=0;$k<$round;$k ++ ){
		$tempMap = [];
		$plantMap = [];

		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				next if (not defined $map->[$i][$j] or $map->[$i][$j] == 0);

				foreach (@Utils::directions){

					($tX,$tY)=Utils::movement($_,$i,$j);
					next if (Utils::inMap($tX,$tY) == 0);

					my $case = $self->{m}->{cases}->[$tX][$tY];
					if ( $self->{m}->isCaseExposed($tX,$tY,$k,$playerId) == 0 ){
						if ( $case->{type} == Utils::VIDE or ( $case->{type} == Utils::CAISSE and $self->{m}->isCaisseDestroyed($tX,$tY,$k,$playerId))
								or ($case->{type} == Utils::BOMBE and $self->{m}->isBombDestroyed($tX,$tY,$k,$playerId) )
								or ($case->{type} == Utils::JOUEUR and ( ($i == $x and $j ==$y) or $k >= 1 ) )){
							$tempMap->[$tX][$tY]=1;
							push @{$plantMap->[$tX][$tY]}, {plantX=>$i,plantY=>$j} if ($_ != Utils::DIRECTION_STATIC);
						}
					}
					$tempMap->[$tX][$tY] = 0 if ( not defined $tempMap->[$tX][$tY] );

				}



			}
		}
#for $i (0..Utils::TAILLE_CARTE-1){
#			for $j (0..Utils::TAILLE_CARTE-1){
#				if ( not defined $tempMap->[$j][$i] ){print "0";}
#				else{print "$tempMap->[$j][$i]";}
#			}print "\n";
#		}


		$map = $tempMap;


		push @$ret, $plantMap;

	}

	return $ret;
}

sub deadForSure{
	my ($self,$x,$y,$startRound,$endRound,$playerId,$workMap) = @_;

	$playerId = $self->{m}->{my_player}->{id} unless defined $playerId;
	($x,$y) = @{$self->{my_player}}{"x","y"} if (not defined $x or not defined $y);


	my ($map,$tempMap,$i,$j,$tX,$tY,$ret,$m,$alive,$k);

	$m = (not defined $workMap or $workMap == 0)?  $self->{m} : $self->{workMap};
	$map = [];
	$ret = [];

	$map->[$x][$y] = 1;

	$startRound = 0 if (not defined $startRound);
	$endRound = Utils::LONGUEUR_MECHE_MAX if (not defined $endRound);

	print "dead for sure from $x $y\n";
	for ($k=$startRound;$k<$startRound+$endRound;$k ++ ){
		$tempMap = [];
		$alive = 0;

		for $i (0..Utils::TAILLE_CARTE-1){
			for $j (0..Utils::TAILLE_CARTE-1){
				next if (not defined $map->[$i][$j] or $map->[$i][$j] == 0);

				foreach (@Utils::directions){
					($tX,$tY)=Utils::movement($_,$i,$j);
					next if (Utils::inMap($tX,$tY) == 0);
					next if (defined $tempMap->[$tX][$tY]);

					my $case = $m->{cases}->[$tX][$tY];

					if ( $m->isCaseExposed($tX,$tY,$k,$playerId) == 0 ){

						if ( $case->{type} == Utils::VIDE or ( $case->{type} == Utils::CAISSE and $m->isCaisseDestroyed($tX,$tY,$k,$playerId) )
								or ($case->{type} == Utils::BOMBE and $m->isBombDestroyed($tX,$tY,$k,$playerId) )
								or ($x == $tX and $y == $tY) ){
							$tempMap->[$tX][$tY]=1;
							$alive = 1;
						}
					}
					$tempMap->[$tX][$tY] = 0 if ( not defined $tempMap->[$tX][$tY] );

				}



			}
		}

		$map = $tempMap;
		if ($alive == 0){
			$self->{deathRound} = $k;
			print "dead at round $k\n";
			return 1;

		}
	}
	print "not dead\n";
	return 0;


}



1
