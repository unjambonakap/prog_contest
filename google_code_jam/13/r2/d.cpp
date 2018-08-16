#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
//#include <ext/hash_map>

#include"crypto.h"


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

bg W,H,n,m,v1,v2,xo,yo,vx,vy;
char s[111];

bg readbg(){
    scanf(" %s",s);
    return bg(s,10);
}

void disp(const bg &a){printf("%s",a.getstr(10).a);}

void cmin(bg &a, const bg &b){ if (b!=-1 && (a==-1|| b<a)) a=b; }
bignum geth(bignum a, const bignum &Y){ a=a%(Y*2); return a>=Y?Y*2-a:a; }
bignum dist(const bignum &a, const bignum &b){bignum c=a-b;return c<0?-c:c;}
bignum dist2(const bignum &a, const bignum &b, const bignum &Y){return dist(geth(a,Y),geth(b,Y));}

bg go2(bg a, bg m, bg s, bg t){
    assert(s<=t);
    if (s==0) return 0;
    if (a==0) return -1;
    if (a*2>m) return go2(m-a,m,m-t,m-s);
    bg tmp=(s+a-1)/a;
    if (tmp*a<=t) return tmp;
    assert(s%a<=t%a);

    tmp=(m+a-1)/a;
    bg na=tmp*a%m;
    bg res=go2(na,a,s%a,t%a);
    if (res==-1) return res;

    bg cost=res*tmp;
    bg u=res*na;

    if (s<=u && u<=t) return cost;

    if (u<s) cost=cost+(s-u+a-1)/a;
    else cost=cost-(u-s)/a;

    bg nx=cost*a%m;
    assert(nx<=t);
    assert(nx>=s);
    return cost;
}


bignum go(bg n, bg yo, bg dy, bg Y, bg ya, bg yb){
    bg M=Y*2;
    if (ya>yb) return -1;

    if (ya<=yo && yo<=yb) return 0;
    ya=(ya+M-yo)%M;
    yb=(yb+M-yo)%M;
    bg res=go2(dy,M,ya,yb);
    return res;
}

bignum eval(const bignum &a, const bg &b, const bg &c){ return dist(geth(a,c),geth(a+b,c)); }

bg proc(bg n, bg yo, bignum Y, bignum dy, bignum period, bignum v){

    bignum dv=v*n*period;
    if (dv>=Y) return -1;
    yo=yo%(Y*2);
    dy=dy%(Y*2);

    bignum res=-1;
    bignum dyn=dy*n%(Y*2);

    vector<bignum> tb;
    bignum to=0, th;


    while(to<=Y*2){

        bignum nxt=(to+dyn)%(Y*2);
        bignum dst=min(Y-to%Y,Y-nxt%Y);
        if (dist2(to,nxt,Y)>dist2(to+1,nxt+1,Y)) dst=min(dst,dist2(to,nxt,Y)/2);
        th=to+dst;



        bg da=eval(to,dyn,Y);
        bg db=eval(th,dyn,Y);
        bg dc=eval((to+th)/2,dyn,Y);
        assert(min(da,db)<=dc && dc<=max(da,db));

        bignum T=to, H=th;
        if (eval(T,dyn,Y)>eval(H,dyn,Y)){
            bignum best=to-1;
            while(T<=H){
                bignum M=(T+H)/2;
                if (eval(M,dyn,Y)>dv) T=M+1, best=M;
                else H=M-1;
            }
            cmin(res,go(n,yo,dy,Y,to,best));
        }else{
            bignum best=th+1;
            while(T<=H){
                bignum M=(T+H)/2;
                if (eval(M,dyn,Y)>dv) H=M-1, best=M;
                else T=M+1;
            }


            cmin(res,go(n,yo,dy,Y,best,th));
        }

        to=th+1;
        if (res!=-1) assert(eval(yo+res*dy,dyn,Y)>=dv);
    }
    return res==-1?-1:res+n;
}

void solve(){
    bg a,b;
    if (vx>0){
        a=proc(n,vx*yo+(W*2-xo)*vy,H*vx,W*2*vy,W*2,v1);
        b=proc(m,vx*yo+(W-xo)*vy,H*vx,W*2*vy,W*2,v2);

        if (a==-1 && b==-1) printf("DRAW");
        else if (a==-1) printf("LEFT "), disp(b);
        else if (b==-1) printf("RIGHT "), disp(a);
        else if (b<=a) printf("LEFT "), disp(b);
        else if (a<=b) printf("RIGHT "), disp(a);
        puts("");
    }else{
        vx=-vx;
        a=proc(n,vx*yo+(W-xo)*vy,H*vx,W*2*vy,W*2,v1);
        b=proc(m,vx*yo+(W*2-xo)*vy,H*vx,W*2*vy,W*2,v2);

        if (a==-1 && b==-1) printf("DRAW");
        else if (a==-1) printf("LEFT "), disp(b);
        else if (b==-1) printf("RIGHT "), disp(a);
        else if (a<=b) printf("RIGHT "), disp(a);
        else if (b<=a) printf("LEFT "), disp(b);
        puts("");
    }


}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        H=readbg();
        W=readbg();
        n=readbg();
        m=readbg();
        v1=readbg();
        v2=readbg();
        yo=readbg();
        xo=readbg();
        vy=readbg();
        vx=readbg();


        printf("Case #%d: ",ti+1);
        solve();
    }
    return 0;
}


