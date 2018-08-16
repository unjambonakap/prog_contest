#include <vector>
#include<ctime>
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
const int maxc=3013;
int n;
int xa[maxn], ya[maxn], xb[maxn], yb[maxn];
int x1,y1,x2,y2;
int dp1[maxc][maxc];
int dp2[maxc][maxc];
int is[maxc][maxc];

int in(int a){return xa[a]>=x1&&xb[a]<=x2&&ya[a]>=y1&&yb[a]<=y2;}

int checkit(){
    int a=(x2-x1+1)*(y2-y1+1);
    REP(i,n) if (in(i)) a-=(xb[i]-xa[i]+1)*(yb[i]-ya[i]+1);
    return a==0;
}

int go(){
    memset(dp2,0,sizeof(dp2));
    memset(dp1,0,sizeof(dp1));
    memset(is,0,sizeof(is));

    REP(i,n) xa[i]+=2,ya[i]+=2,++xb[i],++yb[i];
    REP(i,n){
        int u=rand();
        dp1[xa[i]][ya[i]]+=u;
        dp1[xb[i]][yb[i]]-=u;
        is[xa[i]][ya[i]]=1;
        dp2[xb[i]][yb[i]]=(xb[i]-xa[i]+1)*(yb[i]-ya[i]+1);
    }
    REP(i,maxc-1) REP(j,maxc-1) dp1[i+1][j+1]+=dp1[i+1][j]+dp1[i][j+1]-dp1[i][j];
    REP(i,maxc-1) REP(j,maxc-1) dp2[i+1][j+1]+=dp2[i+1][j]+dp2[i][j+1]-dp2[i][j];

    REP(i,n){
        int xh=xb[i], yh=yb[i];

        int d=max(xh-xa[i],yh-ya[i]);
        int ub=min(xh,yh);
        for (int j=d; j<ub; ++j){
            x2=xh; y2=yh; x1=xh-j; y1=yh-j;
            if (!is[x1][y1]) continue;

            int v1=dp1[x2][y2]-dp1[x1-1][y2]-dp1[x2][y1-1]+dp1[x1-1][y1-1];
            if (v1) continue;

            int v2=dp2[x2][y2]-dp2[x1-1][y2]-dp2[x2][y1-1]+dp2[x1-1][y1-1];
            if (v2==(j+1)*(j+1) && checkit()) return 1;
        }
    }
    return 0;
}


int main(){
    srand(1235267);
    while(cin>>n,!cin.eof()){
        REP(i,n) scanf(" %d%d%d%d",xa+i,ya+i,xb+i,yb+i);
        if (go()){
            vi res;
            REP(i,n) if (in(i)) res.pb(i);
            printf("YES %d\n",res.size());
            REP(i,res.size()) printf("%d%c",res[i]+1," \n"[i==res.size()-1]);
            
        }else puts("NO");
    }
    return 0;
}

