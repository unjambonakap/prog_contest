#!/usr/bin/perl -w
use strict;


sub solve{
	my ($c,$d) = @_;
	my ($i,$ret,$j);
	$ret = 0;
	for ($i = 0; $i <= $#{$c->{positive}} and $i <= $#{$d->{negative}};$i++){
		$ret -= $c->{positive}->[$i]->{n}*$d->{negative}->[$i]->{n};
		$c->{positive}->[$i]->{used} = $d->{negative}->[$i]->{used} = 1;


	}
	for ($i = 0; $i <= $#{$d->{positive}} and $i <= $#{$c->{negative}};$i++){
		$ret -= $d->{positive}->[$i]->{n}*$c->{negative}->[$i]->{n};
		$d->{positive}->[$i]->{used} = $c->{negative}->[$i]->{used} = 1;
	}
	for ($i = 0; $i <= $#{$c->{null}};$i++){
		next if ($c->{null}->[$i]->{used} == 1);
		for ($j = 0;$j <= $#{$d->{all}};$j++){
			next if ( $d->{all}->[$j]->{used} == 1);
				
			$d->{all}->[$j]->{used} = 1;
			$c->{null}->[$i]->{used} = 1;
			last;

		}
#
#		next if ($c->{null}->[$i]->{used} == 1);
#		for ($j = 0;$j <= $#{$d->{negative}};$j++){
#			next if ( $d->{negative}->[$j]->{used} == 1);
#			$d->{negative}->[$j]->{used} = 1;
#			$c->{null}->[$i]->{used} = 1;
#			last;
#
#		}
#
#		next if ($c->{null}->[$i]->{used} == 1);
#		for ($j = 0;$j <= $#{$d->{null}};$j++){
#			next if ( $d->{null}->[$j]->{used} == 1);
#			$d->{null}->[$j]->{used} = 1;
#			$c->{null}->[$i]->{used} = 1;
#			last;
#
#		}
	}
	for ($i = 0; $i <= $#{$d->{null}};$i++){
		next if ($d->{null}->[$i]->{used} == 1);
		for ($j = 0;$j <= $#{$c->{all}};$j++){
			next if ( $c->{all}->[$j]->{used} == 1);
				
			$c->{all}->[$j]->{used} = 1;
			$d->{null}->[$i]->{used} = 1;
			last;

		}

#	next if ($d->{null}->[$i]->{used} == 1);
#		for ($j = 0;$j <= $#{$c->{negative}};$j++){
#			next if ( $c->{negative}->[$j]->{used} == 1);
#			$c->{negative}->[$j]->{used} = 1;
#			$d->{null}->[$i]->{used} = 1;
#			last;
#
#		}
#
#		next if ($d->{null}->[$i]->{used} == 1);
#		for ($j = 0;$j <= $#{$c->{null}};$j++){
#			next if ( $c->{null}->[$j]->{used} == 1);
#			$c->{null}->[$j]->{used} = 1;
#			$d->{null}->[$i]->{used} = 1;
#			last;
#
#		}
	}
	for ($i = 0; $i <= $#{$d->{negative}};$i++){
		next if ($d->{negative}->[$i]->{used} == 1);
		for ($j = $#{$c->{negative}};$j >= 0;$j--){
			next if ( $c->{negative}->[$j]->{used} == 1);
			$c->{negative}->[$j]->{used} = 1;
			$d->{negative}->[$i]->{used} = 1;
			$ret += $c->{negative}->[$j]->{n}*$d->{negative}->[$i]->{n};
			last;
		}
	}
	for ($i = 0; $i <= $#{$d->{positive}};$i++){
		next if ($d->{positive}->[$i]->{used} == 1);
		for ($j = $#{$c->{positive}};$j >= 0;$j--){
			next if ( $c->{positive}->[$j]->{used} == 1);
			$c->{positive}->[$j]->{used} = 1;
			$d->{positive}->[$i]->{used} = 1;
			$ret += $c->{positive}->[$j]->{n}*$d->{positive}->[$i]->{n};
			last;
		}
	}
	return $ret;

}





my ($n,$r,@v,$i,$s,$e,$t);

$n = <>;
chomp $n;

for (1..$n){

	$r = <>;
	chomp $r;
	@v = ();
	for $i(0..1){
		
		$s = <>;
		chomp $s;

		$t = {};
		$t->{positive} = [];
		$t->{negative} = [];
		$t->{null} = [];

		foreach $e (split(" ",$s)){
			push @{$t->{negative}}, {n=>abs($e),used=>0} if ($e < 0);
			push @{$t->{null}}, {n=>0,used=>0} if ($e == 0);
			push @{$t->{positive}}, {n=>$e,used=>0} if ($e > 0);
			
		}
		$t->{positive} = [sort {$b->{n} <=>$a->{n}} @{$t->{positive}}];
		$t->{negative} = [sort {$b->{n} <=>$a->{n}} @{$t->{negative}}];
		$t->{all} = [@{$t->{positive}},@{$t->{negative}},@{$t->{null}}];
		$t->{all} = [sort {$b->{n} <=> $a->{n}} @{$t->{all}}];

		push @v, $t;
	}
	print "Case #$_: ",solve(@v),"\n";

}


