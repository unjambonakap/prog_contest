#!/usr/bin/perl -w
use strict;
no warnings "recursion";

my $storedSpeed;

sub solve{
	my($n,$speed,$index,$currentSpeed) = @_;
	my ($sum,$i);


#print" defined at $index ($storedSpeed->[$index])\n" if defined $storedSpeed->[$index];
	return $storedSpeed->[$index] if defined $storedSpeed->[$index];
#print "index $index $currentSpeed\n";


	$sum = 1;
	for $i(0..$#$speed){
		next if ($speed->[$i] <= $currentSpeed);
#			print "new solve for $speed->[$i] at index ",$i+$index," ( current speed $currentSpeed, index $index\n";
		$sum += solve($n,[@$speed[$i+1..$#$speed]],$index+$i+1,$speed->[$i]);

	}

	$sum %= 1000000007;
	$storedSpeed->[$index] = $sum if ($index > 0);



	return $sum;

}








my ($nCase,$s,$i,$a,$speed);

$nCase = <>;
chomp $nCase;

for (1..$nCase){
	$s = <>;
	chomp $s;
	my ($n,$m,$x,$y,$z) = split(" ",$s);
	$a = [];
	$speed = [];

	for $i(0..$m-1){
		$s = <>;
		chomp $s;
		$a->[$i] = $s;
	}

	for $i (0..$n-1){
		$speed->[$i] = $a->[$i % $m];
		$a->[$i % $m] = ($x*$a->[$i % $m] + $y*($i+1))% $z;
	}
	$storedSpeed = [];
		foreach $i(@$speed){
			print "$i  => ";

		}
	print "Case #$_: ",(solve($n,$speed,0,-1)-1)%10000000007,"\n";
	if ($_ == 9){

	}



}
