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

const int maxn=1111;
ll res=8e18;
int xi, yi;
int a[maxn][maxn];
int n, m;
int F[maxn][maxn];
ll F2[maxn];

void checkit(ll v, int i, int j){ if (v<res) res=v, xi=i, yi=j; }
int sqr(int a){return a*a;}

int main(){
    cin>>n>>m;
    REP(i,n) REP(j,m) scanf(" %d", a[i]+j);
    REP(i,n) REP(j,m) F[i][j+1]=F[i][j]+a[i][j];
    REP(i,n) REP(j,m+1) F2[j]+=F[i][j];
    ll sv=0;
    REP(i,n) REP(j,m) sv+=1ll*a[i][j]*(2+4*j)*(2+4*j);

    REP(i,n+1){
        ll v=sv;
        REP(j,n) v+=1ll*F[j][m]*sqr(j<i?2+(i-j-1)*4:2+(j-i)*4);
        checkit(v,i,0);
        ll sa=0, sb=0;
        REP(j,m) sa+=(2+4*j)*(F2[j+1]-F2[j]);

        REP(j,m){
            v+=16*(F2[m]-F2[j+1]+F2[j]);
            sa-=2*(F2[j+1]-F2[j]);
            v+=8*(sb-sa);
            sb+=2*(F2[j+1]-F2[j]);

            sa-=4*(F2[m]-F2[j+1]);
            sb+=4*F2[j];
            checkit(v,i,j+1);
        }
    }
    cout<<res<<endl;
    printf("%d %d\n",xi,yi);
    return 0;

}


