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
typedef unsigned int uint;
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


const int maxn=111111;
const int maxh=3003;
int n;
int xa[maxn], ya[maxn], xb[maxn], yb[maxn];
int xl,yl,xh,yh;

int dp[maxh][maxh];
int vcut[maxh][maxh], hcut[maxh][maxh];
int mv[maxh][maxh], mh[maxh][maxh];
int perm[maxn];


int in(int a){return xa[a]>=xl&&ya[a]>=yl && xb[a]<=xh&&yb[a]<=yh;}

void markv(int x, int ya, int yb){ FOR(i,ya+1,yb) vcut[x][i]=1; }
void markh(int y, int xa, int xb){ FOR(i,xa+1,xb) hcut[y][i]=1; }

int checkit(){
    int area=(xh-xl)*(yh-yl);
    area-=dp[xh][yh]-dp[xh][yl]-dp[xl][yh]+dp[xl][yl];
    if (area) return 0;
    if (mv[xl][yl]<yh || mh[yl][xl]<xh) return 0;
    return 1;
}


int go(){
    memset(dp,0,sizeof(dp));
    REP(u,n) FOR(i,xa[u],xb[u]) FOR(j,ya[u],yb[u]) dp[i+1][j+1]=1;
    FOR(i,1,maxh) FOR(j,1,maxh) dp[i][j]+=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];

    memset(vcut,0,sizeof(vcut));
    memset(hcut,0,sizeof(hcut));
    REP(i,n) markv(xa[i],ya[i],yb[i]);
    REP(i,n) markv(xb[i],ya[i],yb[i]);
    REP(i,n) markh(ya[i],xa[i],xb[i]);
    REP(i,n) markh(yb[i],xa[i],xb[i]);

    REP(i,maxh){
        int best=maxh;
        for (int j=maxh-1; j>=0; --j){
            mv[i][j]=best;
            if (hcut[j][i]) best=j;
        }
    }
    REP(i,maxh){
        int best=maxh;
        for (int j=maxh-1; j>=0; --j){
            mh[i][j]=best;
            if (vcut[j][i]) best=j;
        }
    }

    vector<pair<pii,int> > tb;
    REP(i,n) tb.pb(MP(MP(xa[i]-ya[i],xa[i]),n+i)), tb.pb(MP(MP(xb[i]-yb[i],xb[i]),i));
    sort(ALL(tb));
    REP(i,tb.size()){
        int j=i;
        for (; j<tb.size() && tb[j].ST.ST==tb[i].ST.ST; ++j);
        vector<int> stk;

        for (; i<j; ++i){
            int px,py;
            if (tb[i].ND<n){
                xh=xb[tb[i].ND], yh=yb[tb[i].ND];

                while(stk.size()){
                    xl=xa[stk.back()], yl=ya[stk.back()];
                    if (checkit()){
                        if (mv[xh][yl]<yh || mh[yh][xl]<xh) break;
                        else return 1;
                    }else stk.pop_back();
                }
            }
            else stk.pb(tb[i].ND-n);
        }

        i=j-1;
    }

    return 0;

}

int main(){
    while(cin>>n,!cin.eof()){
        REP(i,n) scanf(" %d%d%d%d",xa+i,ya+i,xb+i,yb+i);
        if (go()){
            vi res;
            REP(i,n) if (in(i)) res.pb(i);
            printf("YES %d\n",(int)res.size());
            REP(i,res.size()) printf("%d%c",res[i]+1," \n"[i==res.size()-1]);

        }else puts("NO");
    }
    return 0;
}

