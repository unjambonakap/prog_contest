#!/usr/bin/perl -w


use strict;

my $solveData;
my ($FDData,$FBData,$DBData);
my $layer = 0;

sub solveFMax{

	my ($f,$d,$b) = @_;
	my ($i,$ret);
	for ($i = ($f > $d )?$f+1:$d+1;$i <=4294967296;$i++){
		print "$i\n";
		$ret = solvable($i+1,$d,$b);
		return $i-1 if ($ret == 0);

	}
	return -1;

}

sub solveDMin{
	my ($f,$d,$b) = @_;
	my ($i,$ret);


	print "solveDMin\n";
	exit;
	for ($i = $d-1;$i > 0;$i--){
		$ret = solvable($f+1,$i,$b);
		return $i+1 if ($ret == 0);

	}
	return 1;
}
sub solveBMin{
	my ($f,$d,$b) = @_;
	my ($ret,$i);



	for ($i = $b-1;$i > 0;$i--){
		$ret = solvable($f+1,$d,$i);
		return $i+1 if ($ret == 0);

	}

	return 1;

}



sub solvable{
	my ($f,$d,$b) = @_;
	my ($i,$r);
		print "\n $layer solvable $f $d $b =>>>";
	if ($f == 1){
		$FDData->{$f}{$d}->{minSuccess} = $b;
		$FBData->{$f}{$b}->{minSuccess} = $d;
		print "ret 1*****";

		return 1;
	}
#	return 0 if (defined $FDData->{$f}{$d}->{maxFail} and $FDData->{$f}{$d}->{maxFail} >= $b);
#	return 0 if (defined $FBData->{$f}{$b}->{maxFail} and $FBData->{$f}{$b}->{maxFail} >= $d);
#	return 0 if (defined $DBData->{$d}{$b}->{maxFail} and $DBData->{$d}{$b}->{maxFail} <= $f);

	if (defined $FDData->{$f}{$d}->{maxFail} and $FDData->{$f}{$d}->{maxFail} >= $b){
		return 0;

	}
	if (defined $FBData->{$f}{$b}->{maxFail} and $FBData->{$f}{$b}->{maxFail} >= $d){
		print "laa\n";
		die "ici\n";
	}
	if (defined $DBData->{$d}->{$b}->{maxFail} and $DBData->{$d}->{$b}->{maxFail} <= $f){
		return 0;
	}
	return 1 if (defined $FDData->{$f}{$d}->{minSuccess} and $FDData->{$f}{$d}->{minSuccess} <= $b);
	return 1 if (defined $FBData->{$f}{$b}->{minSuccess} and $FBData->{$f}{$b}->{minSuccess} <= $d);
	return 1 if (defined $DBData->{$d}{$b}->{minSuccess} and $DBData->{$d}{$b}->{minSuccess} >= $f);
	print "process=>";

	if ($f == 2){
		if ($b == 0 or $d == 0){
			print "0 ? $f $d $b?";
			$FDData->{$f}{$d}->{maxFail} = $b;
			$FBData->{$f}{$b}->{maxFail} = $d;
			$DBData->{$d}{$b}->{maxFail} = $f;
			return 0;
		} else{

			print "1";
			$FDData->{$f}{$d}->{minSuccess} = $b;
			$FBData->{$f}{$b}->{minSuccess} = $d;
			$DBData->{$d}{$b}->{minSuccess} = $f;
			return 1;
		}
	}
	if ($b == 0 or $d == 0){
		$FDData->{$f}{$d}->{maxFail} = $b;
		$FBData->{$f}{$b}->{maxFail} = $d;
		$DBData->{$d}{$b}->{maxFail} = $f;

		print "0 !!";
		return 0;
	}
	for ( $i = 1;$i < $f; $i ++){
		$layer ++;

		print "\ntest $i : ";
		$r = (solvable($f-$i,$d-1,$b)==1 and solvable($i,$d-1,$b-1)==1);
		$layer --;
		if ($r){
			$FDData->{$f}{$d}->{minSuccess} = $b;
			$FBData->{$f}{$b}->{minSuccess} = $d;
			$DBData->{$d}{$b}->{minSuccess} = $f;

			print "<<1";
			return 1;

		}else{
			print "<temp0>";

		}

	}
	$FDData->{$f}{$d}->{maxFail} = $b;
	$FBData->{$f}{$b}->{maxFail} = $d;
	$DBData->{$d}{$b}->{maxFail} = $f;

	print "0 /$f $d $b/";
	return 0;


}







my ($n,$s,$f,$d,$b);


$n = <>;
chomp $n;

for (1..$n){
	$s = <>;
	chomp $s;
	($f,$d,$b) = split(" ",$s);

	print "Case #$_: ",join( " ", solveFMax($f,$d,$b),solveDMin($f,$d,$b),solveBMin($f,$d,$b)),"\n";


}

