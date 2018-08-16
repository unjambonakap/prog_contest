#!/usr/bin/perl -w

use strict;

sub solve{
	my ($ret);
	$ret = 0;

	return $ret;
}


my ($n,$s);
$n = <>;
chomp $n;

for (1..$n){

	$s = <>;
	chomp $s;


	print "Case #$_: ",solve($s),"\n";

}







