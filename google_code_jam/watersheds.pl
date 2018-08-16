#!/usr/bin/perl -w
use strict;

use constant{
	NORTH=>1,
		SOUTH=>2,
		EAST=>3,
		WEST=>4

};

my @directions = (NORTH,WEST,EAST,SOUTH);

sub movement{
	my ($d,$x,$y) = @_;
	return ($x,$y-1) if ($d == NORTH);
	return ($x,$y+1) if ($d == SOUTH);
	return ($x+1,$y) if ($d == EAST);
	return ($x-1,$y) if ($d == WEST);
	print STDERR "NOT GOOD\n";
	die;
}
sub getNextCase{
	my($d,$x,$y,$m) = @_;
	my ($tX,$tY) = movement($d,$x,$y);
	return undef if ($tX < 0 or $tY < 0);

	return $m->[$tY][$tX];


}
sub solve{
	my($width,$height,$map) = @_;
	my ($i,$j,$alt,$a,$c,$minAlt,$minC,$nC);
	
	foreach $j(0..$height-1){
		foreach $i(0..$width-1){

			$map->[$j][$i] = {%{$map->[$j][$i]},x=>$i,y=>$j,id=>$i+$j*$width,sink=>-1};
			$a = $map->[$j][$i];
			$minAlt = $a->{alt} if ( not defined $minAlt or $a->{alt} < $minAlt);

			push @{$alt->[$a->{alt}]},$a;
		}
	}
	foreach $a (@$alt){
		foreach $c (@$a){
			if ($c->{alt} == $minAlt){
				$c->{sink} = $c->{id};
			}else{
				undef $minC;

				foreach(@directions){
					$nC = getNextCase($_,@$c{"x","y"},$map);
					next unless defined $nC;
# we already take care of directions if same altitude in @directions array

#next case is at a lower altitude than the current one
					$minC = $nC if ($nC->{alt} < $c->{alt} and (not defined $minC or $minC->{alt} > $nC->{alt}));
				}
				if (not defined $minC){
					$c->{sink} = $c->{id};
				}else{
					$c->{sink} = $minC->{sink};
				}
			}

		}
	}
	my $ret = "";
	my (%transf,$lastC);
	$lastC = ord('a');

	foreach $j(0..$height-1){
		foreach $i(0..$width-1){
			$a = $map->[$j][$i]->{sink};
			$transf{$a} = chr($lastC++) if ( not defined $transf{$a});
			$ret .= $transf{$a};
			$ret .= " " if ($i < $width-1);
		}
		$ret .= "\n";
	}
	return $ret;


}

my ($n,$width,$height,$s,$i,$j,$m);


$n = <>;
chomp $n;
for (1..$n){
	$s = <>;
	chomp $s;

	($height,$width) = split(" ",$s);

	$m = [];
	foreach $j(0..$height-1){
		$s = <>;
		chomp $s;

		$m->[$j] = [map {{alt=>$_}} split(" ",$s)];

	}
	print "Case #$_:\n",solve($width,$height,$m);


}

