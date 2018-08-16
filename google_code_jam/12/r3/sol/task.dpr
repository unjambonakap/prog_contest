{$R+,S+,Q+,I+,O-}
{R-,S-,Q-,I-,O+}
var
  tt,qq,i,j,n: longint;
  ll,rr,mid,q,v,min,m,f,low,high,days,ans,tmp: int64;
  ok: array [0..210] of boolean;
  p,s: array [0..210] of int64;

function get(days,mul:int64):int64;
var
  res,need: int64;
  i: longint;
begin
  if mul = 0 then
  begin
    get:=0;
    exit;
  end;
  res:=0;
  for i:=1 to n do
  begin
    if s[i]-s[i-1] > days then need:=days
    else need:=s[i]-s[i-1];
    if res+1.0*need*p[i] > 2e18 then
    begin
      res:=round(2e18);
      break;
    end;
    res:=res+need*p[i];
    days:=days-need;
    if days = 0 then break;
  end;
  if days > 0 then res:=round(2e18) else
  if 1.0*res*mul > 2e18 then res:=round(2e18)
  else res:=res*mul;
  get:=res;
end;

function count(cnt,days:int64):int64;
var
  res: int64;
begin
  res:=get(days div cnt,cnt-days mod cnt)+get(days div cnt+1,days mod cnt);
  if res+1.0*f*cnt > 2e18 then res:=round(2e18)
  else res:=res+f*cnt;
  count:=res;
end;

begin
  assign(input,'in'); reset(input);
  assign(output,'out'); rewrite(output);
  read(tt);
  for qq:=1 to tt do
  begin
    read(m,f,n);
    for i:=1 to n do read(p[i],s[i]);
    for i:=1 to n-1 do
      for j:=i+1 to n do
        if (s[i] > s[j]) or (s[i] = s[j]) and (p[i] < p[j]) then
        begin
          tmp:=p[i]; p[i]:=p[j]; p[j]:=tmp;
          tmp:=s[i]; s[i]:=s[j]; s[j]:=tmp;
        end;
    for i:=1 to n do ok[i]:=True;
    min:=round(2e18);
    for i:=n downto 1 do
      if p[i] >= min then ok[i]:=False
      else min:=p[i];
    j:=0;
    for i:=1 to n do
      if ok[i] then
      begin
        inc(j);
        p[j]:=p[i];
        s[j]:=s[i];
      end;
    n:=j;
    s[0]:=-1;
    low:=0; high:=m;
    while low < high do
    begin
      days:=(low+high+1) shr 1;
      ll:=(days+s[n]) div (s[n]+1);
      rr:=days;
      ans:=count(ll,days);
      while ll < rr do
      begin
        mid:=(ll+rr) shr 1;
        q:=count(mid,days);
        if q < ans then ans:=q;
        v:=count(mid+1,days);
        if v < ans then ans:=v;
        if v < q then ll:=mid+1
        else rr:=mid;
      end;
      if ans <= m then low:=days
      else high:=days-1;
    end;
    writeln('Case #',qq,': ',low);
  end;
  close(input);
  close(output);
end.