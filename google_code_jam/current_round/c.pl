#!/usr/bin/perl -w
use strict;


sub cross{
	my ($a,$b,$k) = @_;
	my $a_inf_b = ($a->{price}->[$k-1] < $b->{price}->[$k-1])?1:0;
	my $a_inf_b_next = ($a->{price}->[$k] < $b->{price}->[$k])?1:0;
	return 1 if ($a->{price}->[$k] == $b->{price}->[$k]);

	return 1 if ($a_inf_b != $a_inf_b_next);
	return 0;

}


sub solve{
	my($n,$k,$p) = @_;
	my($i,$j);

	my ($ret);
	$ret = 0;
	foreach(1..$k-1){

		foreach $i(0..$n-1){
			next if ($p->[$i]->{stored} == 1);

			foreach $j($i+1 .. $n-1){
				next if defined $p->[$i]->{conflicts}->{$j};

				if (cross($p->[$i],$p->[$j],$_) == 1){
					$p->[$i]->{conflicts}->{$p->[$j]} = 1;
					$p->[$j]->{conflicts}->{$p->[$i]} = 1;
					$p->[$j]->{nC} ++;
					$p->[$i]->{nC} ++;

				}


			}
		}
	}

	my @cList = ();

	$ret = 1;
	while(1){
		my ($max,$t);

		print "delete @cList\n";
		foreach $i (@cList){
			foreach(keys %{$i->{conflicts}}){
				next if $_->{stored} == 1;
				
				delete $_->{conflicts}->{$i};
				$_->{nC} --;
			die "go to hell "if (not defined $p->[$_] or not defined $p->[$_]->{nC} or not defined $p->[$_]->{stored});
			}
		}
		$t = [];
		foreach(@$p){
			die if (not defined $_ or not defined $_->{nC} or not defined $_->{stored});
			push @$t, $_ if ($_->{stored} == 0 and $_->{nC} > 0);
		}

		$p = [sort {$a->{nC} <=> $b->{nC}} @$t];
		foreach(@$p){
			die "there\n" if (not defined $_ or not defined $_->{nC} or not defined $_->{stored});
		}
		last if ($#$p == -1);

		my $e = $p->[$#$p];

		@cList = ($e);
		$e->{stored} = 1;

		
		for ($i=$#$p-1;$i >= 0;$i--){

			my $fine = 1;
			foreach(@cList){
				if (defined $p->[$i]->{conflicts}->{$e}){
					$fine = 0;
					last;
				}
			}
			next if( $fine == 0);

			$p->[$i]->{stored} = 1;
			push @cList, $p->[$i];
		}
		last if ($#cList == $#$p);

		$ret ++;

	}

	return $ret;

}









my ($nStuff);


$nStuff = <>;
chomp $nStuff;


for(1..$nStuff){
	my ($s,$nT,$nK,$price,$i,$j);
	$price = [];

	$s = <>;
	chomp $s;
	($nT,$nK) = split(" ",$s);
	foreach $i(0..$nT-1){
		$s = <>;
		chomp $s;
		$price->[$i]->{stored} = 0;
		$price->[$i]->{nC} = 0;
		$price->[$i]->{id} = $i;
		$price->[$i]->{conflicts} = {};
		foreach $j(split(" ",$s)){
			push @{$price->[$i]->{price}},$j;

		}
	}

	print "Case #$_: ",solve($nT,$nK,$price),"\n";
}




