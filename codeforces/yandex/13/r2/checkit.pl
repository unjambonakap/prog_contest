#!/usr/bin/perl -w

if ($#ARGV<0){
    die "need dir"
}
$b=$ARGV[0];
print $b,"\n";

for $i (1..400){
    #$z=$i;
    if ($i<10){$z="00$i";}
    elsif($i<100){$z="0$i";}
    else {$z="$i";}

    $x="$b/$z";
    $y="$b/$z.a";
    print $x,"\n";
    if (-e $x){
        #`cat $x > tmp.in`;
        `cat $x | /bin/time --format="%e" ./a.out  > res.out`;
        #`cat $y | head -n 1 > tmp.out`;
        #`cat $y >> res.out`;
        `diff --strip-trailing-cr res.out $y`;

        #`./check.out $x res.out $y`;
        
        #`cat tmp.in | ./b.out`;
        if ($?){
            print "failed $x\n";
            #die "failed on test $x"
        }
        #print "passed test $i\n";
    }else{
        print "cannot find $x","\n";
        last;
    }
}

print "test passed\n";


