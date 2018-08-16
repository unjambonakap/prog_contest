#!/usr/bin/perl 

use strict;
no warnings "recursion";


sub solve{
	my ($n,$list,$batchList) = @_;
	my ($ret,$t,$iW,$i);

	$ret = 0;

	for($i=0;$i<=$#$list;$i++){
		if ($list->[$i]->{nW} == 0){
			return -1 if ($list->[$i]->{m} == -1);

			if (not defined $batchList->[$list->[$i]->{m}]){
				$batchList->[$list->[$i]->{m}] = 1;
				foreach $t (@$list){
					if (defined $t->{w}->{$list->[$i]->{m}}){
						$t->{nW} --;
						undef  $t->{w}->{$list->[$i]->{m}};
					}
				}
				$i = -1;
			}
		}
	}
	
	
	return 0;
}


my ($n,$s,$t,$i,@a,$list,$temp,$j,$w,$m,$batchList,$ret,$nW);
$n = <>;
chomp $n;

for (1..$n){
	$t = <>;
	chomp $t;

	$batchList = [];


	$s = <>;
	chomp $s;

	$list = [];
	for $i (1..$s){
		$temp = <>;
		chomp $temp;
		@a = split(" ",$temp);
		shift @a;
		$w = {};
		$m = -1;
		$nW = 0;
		for ($j = 0; $j <= $#a;$j+=2){

			$a[$j] --;
			if ($a[$j+1] == 1){$m = $a[$j];}
			else{$w->{$a[$j]} = 1;$nW ++};
		}

		push @$list,{w=>$w,id=>$i,m=>$m,nW=>$nW};
	}
	
	$ret = solve($t,$list,$batchList);
	if ($ret == 0){
		@a = ();
		foreach $j (0..$t-1){
			if (defined $batchList->[$j] and $batchList->[$j] == 1){ push @a, "1";}
			else{ push @a,"0"};
		}
		$ret = join( " ",@a);
	}else{
		$ret = "IMPOSSIBLE";

	}

	print "Case #$_: $ret\n";


}







