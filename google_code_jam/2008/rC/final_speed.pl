#!/usr/bin/perl -w
use strict;
no warnings "recursion";

my $posHash;

my $mod = 1000000007;
sub solve{
	my($n,$speed,$sortedSpeed) = @_;
	my ($sum,$add,$i,%h,$priorSpeed,$e,$j);


	$sum = 0;
	for $i($n-1..0){


		print "$i $#$sortedSpeed\n";

		$add = 1;
		for ($j = $posHash->{$speed->[$i]};$j >= 0;$j --){
			if (defined $h{$sortedSpeed->[$j]}){
				$add = ($h{$sortedSpeed->[$j]} + $add)% $mod;
				last;

			}

		}
		for ($j = $posHash->{$speed->[$i]}+1;$j <= $#$sortedSpeed;$j ++){
			$h{$sortedSpeed->[$j]} = 0 if not defined $h{$sortedSpeed->[$j]};
			$h{$sortedSpeed->[$j]} = ($add + $h{$sortedSpeed->[$j]})% $mod;
		}
#foreach(keys %h){
#			print "$_ => $h{$_}\n";
#
#		}




		$sum = ($sum + $add)% $mod;

	}

#return $h{$sortedSpeed->[$#$sortedSpeed]};
	return $sum;

}








my ($nCase,$s,$i,$c,$speed,%h,$sortedSpeed,$finalSpeed,$k,$tempSpeed);

$nCase = <>;
chomp $nCase;

for (1..$nCase){
	$s = <>;
	chomp $s;
	my ($n,$m,$x,$y,$z) = split(" ",$s);
	$c = [];
	$speed = [];

	for $i(0..$m-1){
		$s = <>;
		chomp $s;
		$c->[$i] = $s;
	}

	for $i (0..$n-1){
		$speed->[$i] = {v=>$c->[$i % $m],id=>$i};
		$c->[$i % $m] = ($x*$c->[$i % $m] + $y*($i+1))% $z;
	}

	$tempSpeed = [sort {$a->{v} <=> $b->{v}} @$speed];

	%h = ();
	$k = 0;

	$finalSpeed->[$tempSpeed->[0]->{id}] = $k;
	$h{$k} ++;
	for $i(1..$#$tempSpeed){
		$k ++ if ($tempSpeed->[$i-1]->{v} < $tempSpeed->[$i]->{v});
		$finalSpeed->[$tempSpeed->[$i]->{id}] = $k;
		$h{$k} ++;
	}

	$sortedSpeed = [sort {$a <=> $b} keys %h];
	$posHash = {};
	foreach $i(0..$#$sortedSpeed){
		$posHash->{$sortedSpeed->[$i]} = $i;
	}

#	foreach $i(@$speed){
#		print "$i  => ";
#
#	}

	print "Case #$_: ",solve($n,$finalSpeed,$sortedSpeed) % $mod,"\n";


}
