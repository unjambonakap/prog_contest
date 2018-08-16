#!/usr/bin/perl -w

use strict;


sub solve{
	my ($t,$s) = @_;
	my ($i,$c);

	return 1 if length($t) == 0;

	$c = 0;
	
	for ($i = 0;$i < $#$s-length($t)+2;$i++){
		if ( substr($t,0,1) eq $s->[$i]->{letter}){
			$c += $s->[$i]->{count}*solve(substr($t,1),[@$s[$i..$#$s]]);
		}
	}

	return $c;
}



my ($n,$s,$ret,$r,%set);
$r = "welcome to code jam";
foreach(split("",$r)){
	$set{$_} = 1;
}


$n = <>;
chomp $n;

for (1..$n){
	$s = <>;
	chomp $s;

	print "$s\n";
	my (@a,$previous);
	foreach(split("",$s)){
		if (defined $set{$_}){
			if (not defined $previous){
				$previous = {letter=>$_,count=>1};
			}elsif($previous->{letter} eq $_){
				$previous->{count} ++;
			}else{
				push @a,$previous;
				$previous = {letter=>$_,count=>1};
			}
		}
	}

	$ret = solve($r,[@a]);
	if ($ret < 10 ){ $ret = "000$ret";}
	elsif($ret < 100){$ret = "00$ret";}
	elsif($ret < 1000){$ret = "0$ret";}
	else{$ret = substr("$ret",length("$ret")-4);}

	print "Case #$_: $ret\n";


}
