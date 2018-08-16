#!/usr/bin/perl -w

no warnings 'recursion';

use strict;

sub solve{
	my ($t,$m,$c,$u,$set,$l) = @_;
	my ($r);

	return if ($u > $t);


	$c = ($c+$u)% $l;


	if (not defined $m->{$set->[$c]-1}){

		$m->{$set->[$c]-1} = $u;
		splice(@$set,$c,1);
		$r = solve($t,$m,$c-1,$u+1,$set,$l-1);
		return;

	}else{
		die "not normal\n";

	}
	die "not normal 2\n";



}



my ($n,$t,$l,$s,$r,$m,$set);
$n = <>;
chomp $n;

for (1..$n){

	$t = <>;
	chomp $t;

	$s = <>;
	chomp $s;
	$l = [split(" ",$s)];
	shift @$l;
	foreach $r (0..$#$l){
		$l->[$r] --;

	}




	$m = {};
	$set = [1..$t];
	solve($t,$m,-1,1,$set,$t);
	foreach $r (@$l){
#		print "$r => $m->{$r} || ";

	}
	print "Case #$_: ",join(" ",@$m{@$l}),"\n";


}
