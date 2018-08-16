#!/usr/bin/perl -w
use strict;
use constant{
	OP_MINUS=>0,
	OP_PLUS=>1

};

my $storeLimit = 100;
my $storedPos;
my $concatPos;
my $storedLayer;
my $singleStore;
my $uglyPos = {};
sub isUgly{
	my $a = shift;

	$uglyPos->{$a} = ($a % 2 and $a % 3 and $a % 5 and $a % 7)?0:1 if not defined $uglyPos->{$a};
	return $uglyPos->{$a};



}
sub solve{
	my ($i,$l,$previousElem,$lastOp,$currentElem,$layer) = @_;
	my ($sum,$cS);
#	print "$i $previousElem $lastOp $currentElem\n";


	
	$layer = 0 if not defined $layer;

	$sum = 0;
	if ($i == 0){
		if ($layer != 0 and not defined $singleStore->[$layer+2]){
			$singleStore->[$layer+2] = 1;
			push @{$storedPos->[$layer+2]},$currentElem;

		}
		if ($lastOp == OP_PLUS){
			$cS = $previousElem + $currentElem;
#			print "$cS = $previousElem + $currentElem ugly?\n";;
		
		}else{
			$cS = $previousElem - $currentElem;
#			print "$cS = $previousElem - $currentElem ugly?\n";
		}
		return 1 if (isUgly(abs($cS)));


		return 0;


	}else{
		if ($lastOp == OP_PLUS){
			$cS = $previousElem + $currentElem;
		}else{
			$cS = $previousElem - $currentElem;
		}
		if (not defined $storedPos->[$i+1]){


			$sum += solve($i-1,$l,$cS,OP_PLUS,$l->[$i-1],0);
#			print "try minus $cS $l->[$i-1]\n";
			$sum += solve($i-1,$l,$cS,OP_MINUS,$l->[$i-1],0);
			if ($i <= $storeLimit){

#				print "$i =>";
				$concatPos->[$i] = $l->[$i]*(10**$i)+$concatPos->[$i-1];
#				print "$concatPos->[$i] = $l->[$i]*10+$concatPos->[$i-1]\n";
				push @{$storedPos->[$i+1]},$concatPos->[$i];

			}	
			foreach(@{$storedPos->[$i]}){
#					print "for $i => $l->[$i]+$_, $l->[$i]-$_\n";
					
				push @{$storedPos->[$i+1]}, ($l->[$i]+$_,$l->[$i]-$_);


			}
		


		}else{
			foreach(@{$storedPos->[$i]}){
#print "check $cS + $_\n";
#				print "check $cS - $_\n";
				$sum ++ if (isUgly($cS+$_));
				$sum ++ if (isUgly($cS-$_));
				if ($layer > 0 and not defined $storedLayer->[$i]->{$i+$layer+1}){
#					print "push  for $i+$layer+1 $currentElem+$_,$currentElem-$_)\n";;
				$storedLayer->[$i]->{$i+$layer+1} = 1;
	push @{$storedPos->[$i+$layer+1]},($currentElem+$_,$currentElem-$_);
				}
			}
		}
		$sum += solve($i-1,$l,$previousElem,$lastOp,$currentElem*10+$l->[$i-1],$layer+1);

	}
#	print "$i => ret $sum\n";

	return $sum;



}










my ($n,$s,@r);

$n = <>;
chomp $n;
for (1..$n){
	$s = <>;
	chomp $s;
	@r = reverse split("",$s);
	$storedPos = [undef,[$r[0]]];
	$concatPos = [$r[0]];
	$storedLayer = [];
	$singleStore = [];
	print "Case #$_: ",solve($#r,[@r],0,OP_PLUS,$r[$#r]),"\n";

}
