#!/usr/bin/perl -w
use strict;

my %primeHash;
sub setPrimeList{
	my $l = shift;
	my ($i,$root,$prime,$a);

	$i = 1;
	$root = 1;
	$primeHash{2} = 1;

	for($a=3;$a <=$l;$a+=2){
		$prime = 1;

		$root ++ if ($root * $root < $a);
		for ($i = 3;$i <= $root; $i += 2){
			if ($a % $i == 0){
				$prime = 0;
				last;
			}
		}
		$primeHash{$a} = 1 if ($prime == 1);
	}

}
sub isPrime{
	return (defined $primeHash{$_[0]})?1:0;

}

my $layer = 0;
sub parent{
#	if ($_[0]->[$_[1]] < 0){
#		return $_[1];
#
#	}else{
#		if ($layer > 30){
#			exit;
#
#		}
#		$layer ++;
#		my $t = parent($_[0],$_[0]->[$_[1]]);
#		$layer --;
#
#	}
#	
return ($_[0]->[$_[1]] < 0)?$_[1] : parent($_[0],$_[0]->[$_[1]]);

}
sub merge{
	my($set,$a,$b) = @_;
	$a = parent($set,$a);
	$b = parent($set,$b);
	return if ($a == $b);
# we will merge the higher into the lower
# we choose $b in $a
	($b,$a) = ($a,$b) if ($a > $b);
	$set->[$b] = $a;

}

sub solve{
	my($a,$b,$p) = @_;

	my ($start,$end,$previousSet,$found,$i,$set,$t);
	$start = $p;
	$end = int(($b-$a));
	
	$set = [];
	for($a..$b){
		$set->[$_-$a] = -1;
	}

	for ($start..$end){
		next if (isPrime($_) == 0);

	
		$t = ($a % $_ == 0 )? $a : $a + ($_ - $a % $_);
		$i = $t + $_;
		while($i <= $b){
			merge($set,$t-$a,$i-$a);
			$i += $_;
		}

	}
	$t = 0;
	for($a..$b){
		$t ++ if ($set->[$_-$a] < 0);
	}
	return $t;



}


my ($n,$p,$a,$b,$s);

$n = <>;
chomp $n;


setPrimeList(1000001);
for (1..$n){
	$s = <>;
	chomp $s;

	($a,$b,$p) = split(" ",$s);
	print "Case #$_: ",solve($a,$b,$p),"\n";





}










