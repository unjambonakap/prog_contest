#!/usr/bin/perl -w
use strict;

my ($str,$temp,$len,$d,$n,@w,@toFind,$a,$c,$par,$currentN,$match,$mPar,$count);


$temp = <>;

($len,$d,$n) = split(" ",$temp);
foreach(1..$d){
	$str = <>;
	chomp $str;
	push @w,[split ("",$str)];
}


foreach (1..$n){
	$str = <>;
	chomp $str;

	$count = 0;

	foreach $a (@w){
		$par = 0;
		$currentN = 0;
		$match = 1;
		foreach $c (split("",$str)){
			if ($currentN >= $len){
				$match = 0;
				last;
			}
			if ($c eq "("){
				$par = 1;
				$mPar = 0;
				next;

			}elsif($c eq ")"){
				$par = 0;

				if ($mPar == 0){
					$match = 0;
					last;
				}
				$currentN ++;

				next;

			}
			if ($par){
				next if ($mPar == 1);
				if ($a->[$currentN] eq $c){
					$mPar = 1;

				}


			}else{
				if ($a->[$currentN] ne $c){
					$match = 0;
					last;

				}
				$currentN ++;

			}

		}
		if ($match == 1){$count++;}
	}
	print "Case #$_: $count\n";


}






