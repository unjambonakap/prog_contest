#!/usr/bin/perl -w

use strict;
use constant{
	SOUTH => 0,
		  WEST => 1,
		  NORTH => 2,
		  EAST => 3,
		  FORWARD => 1,
		  LEFT => 2,
		  RIGHT => 3

};
# cardinal points are clockwise crescent

my %dir_str = (&NORTH => "NORTH", &SOUTH => "SOUTH", &WEST => "WEST", &EAST => "EAST");

my @directions = reverse (NORTH,SOUTH,WEST,EAST);

sub nextPos{
	my($dir,$x,$y) = @_;
	return ($x,$y+1) if ($dir == SOUTH);
	return ($x,$y-1) if ($dir == NORTH);
	return ($x-1,$y) if ($dir == WEST);
	return ($x+1,$y) if ($dir == EAST);
}

sub oppositeDir{
	my($dir) = @_;
	return NORTH if ($dir == SOUTH);
	return SOUTH if ($dir == NORTH);
	return WEST if ($dir == EAST);
	return EAST;

}
sub getNewDir{
	my( $d,$cDir) = @_;

	return $cDir if ($d == FORWARD);
	return ($cDir+1) % 4 if ($d == RIGHT);
	return ($cDir-1) % 4;

}
sub baseToNumber{
	my ($n,$b) = @_;
	my (@a,%h,@c,$s);
	@a = split("",$b);
	@c = reverse split("",$n);

	foreach (0..$#a){
		$h{$a[$_]} = $_;
	}
	$s = 0;
	foreach (0..$#c){
		$s += $h{$c[$_]} * (($#a+1) ** $_);
	}
	return $s;




}

sub numberToBase{

	my ($n,$b) = @_;
	my ($l,$i,$t,$s,@a,%h);
	$l = length($b);

	@a = split("",$b);

	foreach (0..$#a){
		$h{$_} = $a[$_];
	}
	$i = $l;
	$s = "";
	while ($n > 0){
		$t = $n % $i;
		$s = $h{$t/($i/$l)}.$s;

		$n -= $t;


		$i *= $l;


		return $s;

	}
}
sub f{
	my($s,$cases,$r,$c,$i,$j,$ret);
	my ($startB,$endB,$t,$t2,$a,$rOffset,$cOffset,$tX,$tY,$currentDir,$d,%data,$minX,$maxX,$minY,$maxY,$first,@list);



	@data{"W","R","L"} = (FORWARD,RIGHT,LEFT);

	$startB = "01";
	$endB = "0123456789abcdef";

	$s = shift;
	$cases = {};
	$i = 0;
	$j = -1;




	$currentDir = SOUTH;

	foreach (split(" ",$s)){
		$first = 1;
		@list = split("",$_);
		foreach $a (0..$#list){
			$d = $data{$list[$a]};

			if ($d == FORWARD){
				($tX,$tY) = nextPos($currentDir,$i,$j);
				if ($first == 1){
						$minX = $tX if (not defined $minX or $tX < $minX);
						$maxX = $tX if (not defined $maxX or $tX > $maxX);
						$minY = $tY if (not defined $minY or $tY < $minY);
						$maxY = $tY if (not defined $maxY or $tY > $maxY);



				}else{
					$minX = $i if (not defined $minX or $i < $minX);
					$maxX = $i if (not defined $maxX or $i > $maxX);
					$minY = $j if (not defined $minY or $j < $minY);
					$maxY = $j if (not defined $maxY or $j > $maxY);
				}

				if ($first == 1 or $a == $#list){
					$first = 0;

					$cases->{$tX}{$tY}->{oppositeDir($currentDir)} = 1;
					($i,$j) = ($tX,$tY);

				}else{
					$cases->{$i}{$j}->{$currentDir} = 1;

					$cases->{$tX}{$tY}->{oppositeDir($currentDir)} = 1;
					($i,$j) = ($tX,$tY);
				}
			}else{
				$currentDir = getNewDir($d,$currentDir);

			}

		}
		$currentDir = oppositeDir($currentDir);
	}
	$cOffset = $minX;
	$rOffset = $minY;
	$r = $maxY - $rOffset + 1;
	$c = $maxX - $cOffset + 1;

	$ret = "";

	foreach $i (0..$r-1){
		foreach $j(0..$c-1){
			$t2 = "";
			foreach(@directions){
				if (defined $cases->{$j+$cOffset}{$i+$rOffset}->{$_}){
					$t2.="1";
				}else{
					$t2.="0";
				}

			}
			$t = baseToNumber($t2,$startB);
			$ret .= numberToBase($t,$endB);

		}
		$ret .= "\n";
	}
	return $ret;



}
my ($n,$s);


$n = <>;
chomp $n;

for (1..$n){
	$s = <>;
	chomp $s;

	print "Case #$_:\n";
	print f($s);


}



