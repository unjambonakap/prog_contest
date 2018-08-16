#!/usr/bin/perl -w

use strict;
no warnings 'uninitialized';
use constant{
	NE=> 1,
		SE => 2,
		NW => 3,
		SW => 4,
		RIGHT=> 1,
		LEFT=>2,
		TOP=>3,
		BOT=>4,
		STAT=>5,
		
};
my @pos = (NE,SE,NW,SW);
my @dir = (RIGHT,LEFT,TOP,BOT,STAT);

sub getNewPos{
	my($x,$y,$int,$dir) = @_;
	if ($int == NE){
		if ($dir == RIGHT){return($x+1,$y,NW,1);}
		elsif ($dir == BOT){return($x,$y,SE,0);}
		elsif ($dir == TOP){return($x,$y-1,SE,1);}
		elsif ($dir == LEFT){return($x,$y,NW,0);}

	}elsif($int == SE){
		if ($dir == RIGHT){return($x+1,$y,SW,1);}
		elsif ($dir == BOT){return($x,$y+1,NE,1);}
		elsif ($dir == TOP){return($x,$y,NE,0);}
		elsif ($dir == LEFT){return($x,$y,SW,0);}
	}elsif($int == NW){

		if ($dir == RIGHT){return($x,$y,NE,0);}
		elsif ($dir == BOT){return($x,$y,SW,0);}
		elsif ($dir == TOP){return($x,$y-1,SW,1);}
		elsif ($dir == LEFT){return($x-1,$y,NE,1);}
	}elsif($int == SW){

		if ($dir == RIGHT){return($x,$y,SE,0);}
		elsif ($dir == BOT){return($x,$y+1,NW,1);}
		elsif ($dir == TOP){return($x,$y,NW,0);}
		elsif ($dir == LEFT){return($x-1,$y,SE,1);}
	}
}

sub getIntersectXY{
	my($x,$y,$int,$dir) = @_;
	return ($x,$y-1) if ($dir == RIGHT and $int == NE);
	return ($x,$y) if ($dir == RIGHT and $int == SE);
	return ($x-1,$y-1) if ($dir == LEFT and $int == NW);
	return ($x-1,$y) if ($dir == LEFT and $int == SW);

	return ($x,$y-1) if ($dir == TOP and $int == NE);
	return ($x-1,$y-1) if ($dir == TOP and $int == NW);
	return ($x,$y) if ($dir == BOT and $int == SE);
	return ($x-1,$y) if ($dir == BOT and $int == SW);
	

}
sub manhattanLength{
	my($a,$b,$c,$d,$e,$f) = @_;
	my $ret = 0;
	$ret += abs($a-$d)+abs($b-$e);
	if ($c == $f){
		$ret += 4 if ($ret != 0);
	}elsif(($c == NE or $c == NW) and ($f == SE or $f == SW)){
		$ret += 2;
	}elsif(($c == SE or $c == SW) and ($f == NE or $f == NW)){
		$ret += 2;
	}elsif(($c == NE or $c == SE) and ($f == NW or $f == SW)){
		$ret += 2;

	}elsif(($c == NW or $c == SW) and ($f == SE or $f == NE)){
		$ret += 2;
	}
	$ret ++;
	return $ret;
	
}


sub solve{
	my($n,$m,$S,$W,$T) = @_;
	my ($ret,$x,$y,$map,$c);

	$ret = 0;
	my ($t,$newG,$found,$crossed,$tempMap);
	my ($destX,$destY,$destInt) = ($m,0,SW);

	$found = 0;

	for my $i (0..$m){
		for my $j (0..$n){
			foreach(@pos){
				$map->[$i][$j]->{$_} = {x=>$i,y=>$j,orientation=>$_,h=>manhattanLength($i,$j,$_,$destX,$destY,$destInt),inOpenList=>0,inCloseList=>0,openListId=>-1,closeListId=>-1};
			}
		}
	}

	my($startX,$startY,$startInt) = (0,$n,NE);
#print "$startX $startY\n";
	$map->[$startX][$startY]->{$startInt}->{g} = 0;

	my $count = 0;

	my $moved = 1;
	while($moved){
		$moved = 0;
		$tempMap = [];
#		print "\n\nnew start==========================\n";
		for my $i(0..$m){
			for my $j(0..$n){
				for my $currentInt (@pos){
					$t = $map->[$i][$j]->{$currentInt};
					next if (not defined $t->{g} or $t->{g} == -1);


					if ($t->{x} == $destX and $t->{y} == $destY and $t->{orientation} == $destInt){
						next;

					}

#print ">>>>>>>>>>>>>>>>>>>on ($t->{x},$t->{y}), ori $t->{orientation}, time: $t->{g}\n";


					foreach (@dir){
						my ($newX,$newY,$newInt,$crossed);
						$newG = $t->{g};


						if ($_ == STAT){
							($newX,$newY,$newInt) = @$t{"x","y","orientation"};
						}else{
							($newX,$newY,$newInt,$crossed) = getNewPos(@$t{"x","y","orientation"},$_);
#							print "direction $_ => $newX,$newY,$newInt,$crossed\n";
							next if ($newX < 0 or $newY < 0 or $newX > $m or $newY > $n);
							if ($crossed == 1){
#print "cross $newG direction $_\n";
								my ($tX,$tY) = getIntersectXY(@$t{"x","y","orientation"},$_);

								next if ($tX < 0 or $tY < 0 or $tX >= $m or $tY >= $n);

								my $time = $newG - $T->[$tY][$tX];
#$time = $newG if $time < 0;
								$time %= ($S->[$tY][$tX]+$W->[$tY][$tX]);

								$newG ++;

								if ($_ == TOP or $_ == BOT){
									$newG += ($S->[$tY][$tX]+$W->[$tY][$tX] - $time) if ($time >= $S->[$tY][$tX])
								}else{
									if ($time < $S->[$tY][$tX]){
										$newG += ($S->[$tY][$tX] - $time);
									}

								}
								$c = $map->[$newX][$newY]->{$newInt};

							}else{
								$newG += 2;
							}


						}
						$tempMap->[$newX][$newY]->{$newInt} = {} if not defined $tempMap->[$newX][$newY]->{$newInt};


						$c = $tempMap->[$newX][$newY]->{$newInt};
						
						@$c{"x","y","orientation"} = ($newX,$newY,$newInt);



#print "la $_\n";
						next if (defined $c->{g} and $c->{g}<=$newG);
					   	if(not defined $c->{g} and (defined $map->[$newX][$newY]->{$newInt}->{g} and $map->[$newX][$newY]->{$newInt}->{g} <= $newG)){
							$c->{g} = $map->[$newX][$newY]->{$newInt}->{g};
							next;

						}
						
#print "move $c->{x} $c->{y} $t->{x} $t->{y} $c->{g},dest orientation: $newInt $newG ,current G : $map->[$newX][$newY]->{$newInt}->{g}\n";

						$moved = 1 if ($_ != STAT);
#print "add ",@$c{"x","y","orientation"},", g=>  $newG, prior G: ",$c->{g},"\n";
						$c->{g} = $newG;



					}

				}

			}
		}
#print "moved $moved\n";
		$map = $tempMap;
	}


	return $map->[$destX][$destY]->{$destInt}->{g};
}


my ($t,$s,$i,$j,$a,$b,$c,$S,$W,$T);
$t = <>;
chomp $t;

for (1..$t){

	$s = <>;
	chomp $s;
	my($n,$m) = split(" ",$s);
	$S = [];
	$W = [];
	$T = [];
	for $i(0..$n-1){
		$s = <>;
		chomp $s;


		my @arr = split(" ",$s);
		while(){

			push @{$S->[$i]} , shift @arr;
			push @{$W->[$i]} , shift @arr;
			push @{$T->[$i]} , shift @arr;
			last if $#arr == -1;
		}

	}


	print "Case #$_: ",solve($n,$m,$S,$W,$T),"\n";


}







