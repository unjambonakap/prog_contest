#!/usr/bin/perl -w

use strict;

my $limit = 1000000000000000;
my $happyList = [];
my $secList = [];

sub solve{
	my ($b) = @_;
	my ($ret,$a,$elem,$c,$happy,$e,$reached,$i);
	for(2..$limit){
		print "$_\n";
		$happy = 1;
#		print "new\n";
		foreach $elem (@$b){
			$reached = {};
			if (defined $secList->[$elem]->{$_}){
				next if ($secList->[$elem]->{$_} == 1);
				$happy = 0;
				last;

			}

			$a = numberToBase($_,$elem);
#			print "base $elem =>$_ / $a\n";
			
			my @sec = ($_);
			
			while($a ne 0 and $a ne 1){
				$e = 0;
				foreach $c(split("","$a")){
					$e += $c*$c; 
				}
				if (defined $secList->[$elem]->{$e}){
					if ($secList->[$elem]->{$e} == 1){
						$a = 1;
						last;

					}
					$a = 0;
					last;
				}
				print "going here\n";
				$a = numberToBase($e,$elem);
				
				push @sec,$e;
#	print "new a =>($e) $a\n";
				if ($a ne 1 and $reached->{$a}++ >= 1){
					$a = 0;
					last;

				}
			}
			if ($a eq 0){
				foreach $i(@sec){$secList->[$elem]->{$i} = 0;}

				$happy = 0;
				last;
			}else{
				foreach $i(@sec){$secList->[$elem]->{$i} = 1;}

			}
		}
		return $_ if ( $happy == 1);


	}

	die "limit reached";
}


sub numberToBase{

	my ($n,$b) = @_;
	my $t;
	$t = "";
	while($n > 0){
		$t = ($n % $b).$t;
		$n = int ($n / $b);


	}
	return $t;

}



my ($n,$s,$bList);
$n = <>;
chomp $n;

for (1..$n){

	$s = <>;
	chomp $s;
	$bList = [split(" ",$s)];

	solve([2..10]);
	print "end solve\n";
	exit;


	print "Case #$_: ",solve($bList),"\n";

}







