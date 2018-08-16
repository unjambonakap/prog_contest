#!/usr/bin/perl -w
use strict;




sub solve{
	my ($n,$t) = @_;
	my ($ret,$i,$moved,$start,$dest,$j);
	$ret = 0;

	$moved = 1;
	while($moved == 1){
		$moved = 0;
		foreach $i (0..$#$t){
			print "$i -> $t->[$i]\n";
			

			if ($i < $t->[$i]){
				$start = $t->[$i];
				foreach $j( $i .. $start-1){
					print "$t->[$j] = $t->[$j+1]\n";
					$t->[$j] = $t->[$j+1];
				}	
				print "in $i to $t->[$i]\n";
				$t->[$start] = $start;
				$moved = 1;
				$ret += $start - $i;
				last;
					

			}
		}
		exit if $ret > 10;
	}



	return $ret;

}









my ($nStuff);


$nStuff = <>;
chomp $nStuff;


for(1..$nStuff){
	my ($n,$t,$s,$a);
	$t = [];
	$n = <>;
	chomp $n;
	for (0..$n-1){
		$s = <>;
		chomp $s;
		$a = rindex ($s,"1");
		print "$s => $a\n";
		push @$t,$a;
	}


	print "Case #$_: ",solve($n,$t),"\n";
}




