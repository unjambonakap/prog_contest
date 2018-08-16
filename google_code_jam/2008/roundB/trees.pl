#!/usr/bin/perl -w


use strict;




sub solve{
	my ($treeList) = @_;
	my ($i,$j,$k,$n,$xA,$xB,$yA,$yB,$nA,$nB,$nC,$t);

	$n = 0;
	foreach $i(0..$#$treeList){
		($xA,$yA,$nA) = @{$treeList->[$i]}{"x","y","n"};
		foreach $j($i..$#$treeList){
			next if ($i == $j and $nA == 1);
			$xB = $xA + $treeList->[$j]->{x};
			$yB = $yA + $treeList->[$j]->{y};
			$nB = $treeList->[$j]->{n};
			foreach $k($j..$#$treeList){
				next if ($i == $j and $j == $k and $nB <= 2);
				next if ($i == $j and $nB == 1);
				if ((($xB+$treeList->[$k]->{x}) % 3) == 0 and (($yB+$treeList->[$k]->{y}) % 3) == 0){

					if ($i == $j){
						if ($j == $k){
							$t = $nA*($nA-1)*($nA-2)/6;
						}else{
							$t = $nA*($nA-1)/2*$treeList->[$k]->{n};
						}
					}elsif($j == $k){
							$t = $nA*$nB*($nB-1)/2;
					}else{
						$t = $nA*$nB*$treeList->[$k]->{n};
					}

					$n += $t;
				}


			}
		}
	}






	return $n;
}









my ($n,$s,$i,$j);

$n = <>;
chomp $n;

for(1..$n){
	$s = <>;
	chomp $s;

	my ($nT,$a,$b,$c,$d,$x0,$y0,$m) = split(" ",$s);
	my (@treeList,$map);


	$map->{$x0}->{$y0} ++;

	for $i(1..$nT-1){
		$x0 = (($a * $x0+$b) % $m);
		$y0 = (($c * $y0+$d) % $m);
		$map->{$x0%3}->{$y0%3} ++;
	}
	foreach $i(keys %$map){
		foreach $j (keys %{$map->{$i}}){
			push @treeList,{x=>$i,y=>$j,n=>$map->{$i}->{$j}};
		}
	}

	print "Case #$_: ",solve([@treeList]),"\n";



}




