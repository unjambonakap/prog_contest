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

typedef long double ld;
const int maxn=20;
ld p;
int cnk[maxn][maxn];
int vis[maxn][maxn];
ld dp[maxn][maxn];

ld v1,v2,v3;//game, tie break, set

ld go(int a, int b){
    if (a==6&&b==6) return v2;
    if (a>=6 && a-b>=2) return 1;
    if (b>=6 && b-a>=2) return 0;

    ld &r=dp[a][b];
    if (vis[a][b]) return r;
    vis[a][b]=1;
    return r=v1*go(a+1,b)+(1-v1)*go(a,b+1);
}


ld pw(ld u, int px){ld x=1; REP(i,px) x*=u; return x;}
ld tie(int x, ld p1,ld p2){ return pw(p1,x)/(1-2*(1-p2)*p2)*pw(1-p1,x)*cnk[2*x][x]*p2*p2; }

int main(){
    REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
    FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=cnk[i-1][j]+cnk[i-1][j-1];

    while(cin>>p,p>-0.5){
        v1=0;
        REP(i,3) v1+=pw(p,4)*pw(1-p,i)*cnk[3+i][i];
        v1+=tie(3,p,p);

        v2=0;
        REP(i,6) v2+=pw(p,7)*cnk[6+i][i]*pw(1-p,i);
        v2+=tie(6,p,p);


        memset(vis,0,sizeof(vis));
        v3=go(0,0);


        ld res=0;
        REP(i,2) res+=pw(v3,2)*pw(1-v3,i)*cnk[1+i][i];
        printf("%.15Lf %.15Lf %.15Lf\n",v1,v3,res);
    }
    return 0;
}

