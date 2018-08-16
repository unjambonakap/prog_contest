#!/usr/bin/perl -w

use strict;



my ($n,$s,$nK,$mK,$l,@occ,$r,$e);


$n = <>;
chomp $n;


for(1..$n){
	$s = <>;
	chomp $s;
	($mK,$nK,$l) = split(" ",$s);
	$s = <>;
	chomp $s;

	@occ = split(" ",$s);
	@occ = sort {$b <=> $a} @occ;
	$r = 0;
	foreach $e(0..$#occ){
		$r += (int($e / $nK)+1) * $occ[$e];

	}

	print "Case #$_: $r\n";

}
