#!/usr/bin/perl -w

no warnings "recursion";

use strict;
my $value;

# 4 ======= 104
# => 100 periodicity from u4
sub solve{

	my $n = shift;

	my ($i,$a,$b);
	
	
	$a = 2;
	$b = 6;
	for ($i = 2;$i <= $n; $i ++ ){
		($a,$b) = ($b%1000,1000+((6*$b-4*$a)%1000));
#		if (defined $value->{$a}->{$b}){
#			print "period $value->{$a}->{$b} ======== $i\n";
#			die;
#
#		}else{
#			$value->{$a}->{$b} = $i;
#
#		}

	}
	$b = ($b-1)%1000;

	if ($b < 10){ $b = "00$b"; }
	elsif($b < 100){ $b = "0$b";}
	else{$b = "$b";}

	return $b;


}


my ($n,$s);
$n = <>;
chomp $n;

for (1..$n){

	$s = <>;
	chomp $s;
	$s = ($s-4)%100 +4;


	print "Case #$_: ",solve($s),"\n";

}







