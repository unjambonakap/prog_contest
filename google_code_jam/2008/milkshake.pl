#!/usr/bin/perl 

use strict;
no warnings "recursion";


sub solve{
	my ($n,$list,$batchList) = @_;
	my ($ret,$w,$ok,@posList,$c,$d,$t);
	$ret = 0;
	
	
	foreach $c (0..$#$list){
		$ok = 0;
		@posList = ();
		next if ($list->[$c]->{satisfiedBy} != -1);
		foreach $w (@{$list->[$c]->{w}}){
		
			if ( defined $batchList->[$w->{type}] and $w->{malted} == $batchList->[$w->{type}]){
# an existing batch already satisfied this client => no need to worry about him
#				print "$list->[$c]->{id} happy with $w->{type} $w->{malted}\n";
				$ok = 1;
				last;

			}elsif (not defined $batchList->[$w->{type}]){
				push @posList, $w;
# no batch have been done for this type => add it on the list
# no need to worry about the smallest number of malted batches, cause in $_->{w}, the unmalted milkshake are presented first
			}else{}
#last case, a batch exists on this type, but not malted correctly

		}

		next if ($ok == 1);
# client satisfied, no need to do a batch

		if ($#posList == -1){
# client not satisfied, so no need to go further, wrong way
#			print "not satisfaction possible for $list->[$c]->{id}\n";
			return -1;
		}
		foreach ( @posList){

			$batchList->[$_->{type}] = $_->{malted};
#setup a batch, to fill this possibility

			return 0 if ($c == $#$list);
print "choice $_->{type} $_->{malted} for personn $list->[$c]->{realId} classed in $c $list->[$c]->{nW} $list->[$c]->{nM}\n";

			foreach $d($c+1..$#$list){
				next if ($list->[$d]->{satisfiedBy} != -1 );
				if (defined $list->[$d]->{v}->{$_->{type}} and $list->[$d]->{v}->{$_->{type}} == $_->{malted}){
					$list->[$d]->{satisfiedBy} = $_->{type};
				}
			}
			$ret = solve($n,[@$list[$c+1..$#$list]],$batchList);

			return 0 if ($ret == 0);
#	print "choice $_->{type} $_->{malted} for personn $list->[$c]->{id}  classed in $c=> wrong guess\n";
			undef $batchList->[$_->{type}];
			
			foreach $d($c+1..$#$list){
				$list->[$d]->{satisfiedBy} = -1 if ($list->[$d]->{satisfiedBy} == $_->{type} );
			}

########################
			$t = ($_->{malted} == 1)?0:1;
				
				
			$batchList->[$_->{type}] = $t;
#setup a batch, to fill this possibility

			return 0 if ($c == $#$list);
#print "choice $_->{type} $_->{malted} for personn $list->[$c]->{id} classed in $c $list->[$c]->{nW} $list->[$c]->{nM}\n";

			foreach $d($c+1..$#$list){
				next if ($list->[$d]->{satisfiedBy} != -1 );
				if (defined $list->[$d]->{v}->{$_->{type}} and $list->[$d]->{v}->{$_->{type}} == $t){
					$list->[$d]->{satisfiedBy} = $_->{type};
				}

			}
			$ret = solve($n,[@$list[$c+1..$#$list]],$batchList);

			return 0 if ($ret == 0);
#	print "choice $_->{type} $_->{malted} for personn $list->[$c]->{id}  classed in $c=> wrong guess\n";
			undef $batchList->[$_->{type}];

			foreach $d($c+1..$#$list){
				$list->[$d]->{satisfiedBy} = -1 if ($list->[$d]->{satisfiedBy} == $_->{type} );
			}

			return -1;
#############################
		}
# no possibilities from there could satisfy the remaining clients= > wrong way
#			print " 3not satisfaction possible for $list->[$c]->{id}\n";
		return -1;
	}

	return 0;
}


my ($n,$s,$t,$i,@a,$list,$temp,$j,$w,$nW,$nM,$batchList,$ret,$cPos,$v);
$n = <>;
chomp $n;

for (1..$n){
	$t = <>;
	chomp $t;

	$batchList = [];


	$s = <>;
	chomp $s;

	$list = [];
	$cPos = {};
	for $i (1..$s){
		$temp = <>;
		chomp $temp;
		@a = split(" ",$temp);
		$nW = shift @a;
		$w = [];
		$v = {};
		$nM = 0;
		for ($j = 0; $j <= $#a;$j+=2){
			$nM ++ if ($a[$j+1] eq 1);
			$v->{$a[$j]-1} = $a[$j+1];

			push @$w, {type=>$a[$j]-1,malted=>$a[$j+1]};
			$cPos->{$a[$j]-1}++;
		}

		push @$list,{nW=>$nW,w=>$w,nM=>$nM,ok=>0,id=>$i,satisfiedBy =>-1,v=>$v};
	}
	for $i (0..$s-1){
		$list->[$i]->{w} = [sort {$a->{malted} <=> $b->{malted} || $cPos->{$a->{type}} <=> $cPos->{$b->{type}}} @{$list->[$i]->{w}}];

	}
	$list = [sort {$a->{nW} <=> $b->{nW} || $a->{nM} <=> $b->{nM}} @$list];
	for $i (0..$s-1){
		$list->[$i]->{realId} = $i;
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







