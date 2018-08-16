program xlmj;
{$R-}
const
        maxn = 1000;
        maxy = 31;

var
        g              : array [0..maxn,0..maxn] of boolean;
        x,y            : array [0..maxn] of longint;
        left           : array [0..maxy] of longint;
        lab,q,c        : array [0..maxn] of longint;
        bo             : array [0..maxn] of boolean;
        n,m,i,j,t,test : longint;

procedure init;
var
        a,b : longint;
begin
        fillchar(g,sizeof(g),0);
        read(n);
        for i:=1 to n do read(x[i],y[i]);
end;

procedure sort;
var
        i,j,p : longint;
begin
        for i:=1 to n do
           for j:=i+1 to n do
              if x[i]<x[j] then
              begin
                 p:=x[i]; x[i]:=x[j]; x[j]:=p;
                 p:=y[i]; y[i]:=y[j]; y[j]:=p;
              end;
end;

procedure connect(a,b : longint );
begin
        if b=0 then exit;
        g[a,b]:=true; g[b,a]:=true;
end;

procedure prepare;
var
        i,j : longint;
begin
        fillchar(left,sizeof(left),0);
        for i:=1 to n do
        begin
           connect(i,left[y[i]-1]);
           connect(i,left[y[i]]);
           connect(i,left[y[i]+1]);
           left[y[i]]:=i;
        end;
end;

function check(i : longint ): boolean;
var
        first : longint;
begin
        first:=0;
        for j:=i+1 to n do
           if g[q[i],q[j]] then
              if first=0 then first:=q[j]
                 else if not g[first,q[j]] then exit(false);
        check:=true;
end;

procedure dye(i : longint );
begin
        for j:=i+1 to n do
           if g[q[i],q[j]] then bo[c[q[j]]]:=true;
        for j:=1 to t do
           if not bo[j] then break;
        if (t=0) or bo[j] then begin inc(t); j:=t; end;
        c[q[i]]:=j;
        for j:=1 to t do bo[j]:=false;
end;

procedure work;
var
        max,maxi : longint;
begin
        fillchar(lab,sizeof(lab),0);
        fillchar(q,sizeof(q),0);
        fillchar(c,sizeof(c),0);
        fillchar(bo,sizeof(bo),0);
        for i:=n downto 1 do
        begin
           max:=-1;
           for j:=1 to n do
              if not bo[j] and (lab[j]>max) then
              begin
                 max:=lab[j];
                 maxi:=j;
              end;
           bo[maxi]:=true; q[i]:=maxi;
           for j:=1 to n do
              if g[maxi,j] then inc(lab[j]);
        end;
        fillchar(bo,sizeof(bo),0); t:=0;
        for i:=n downto 1 do dye(i);
        writeln('Case #',test,': ',t);
end;

begin
        assign(input,'c.in'); reset(input);
        assign(output,'c.out'); rewrite(output);
        readln(test);
        for test:=1 to test do
        begin
           init;
           sort;
           prepare;
           work;
        end;
end.
