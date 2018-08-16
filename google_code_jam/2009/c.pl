#!/usr/bin/perl -w

use strict;

sub solve{
	my($c,$n) = @_;
	my ($ret);
	$ret = 0;

	return $ret;
}


my ($t,$n,$c,$s);
$t = <>;
chomp $t;

for (1..$t){

	$s = <>;
	chomp $s;
	($c,$n) = split(" ",$s);


	print "Case #$_: ",solve($c,$n),"\n";


}







