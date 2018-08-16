#!/usr/bin/perl -w
use strict;



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

	}
	return $s;

}


my ($a,$k,$n,$startBase,$endBase,$t,$b);

$a = <>;
chomp $a;
for $k (1..$a){
	$b = <>;
	chomp $b;
	($n,$startBase,$endBase) = split (" ",$b);

	$t = baseToNumber($n,$startBase);

	$t = numberToBase($t,$endBase);
	print "Case #$k: $t\n";


}








