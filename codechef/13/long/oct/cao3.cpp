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



const int maxn=22;
char s[maxn][maxn];
int r,c;
int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};

int is[maxn][maxn];

int in(int a, int b){return a>=0&&b>=0&&a<r&&b<c;}

const char *str[]={"Kirito","Asuna"};

int dp[maxn][maxn][maxn][maxn];

int go(int xl, int xh, int yl, int yh){
    int &r=dp[xl][xh][yl][yh];
    if (r!=-1) return r;
    r=0;

    set<int> mex;
    FOR(i,xl,xh) FOR(j,yl,yh) if (is[i][j]){
        mex.insert(
                go(xl,i,yl,j)^
                go(xl,i,j+1,yh)^
                go(i+1,xh,j+1,yh)^
                go(i+1,xh,yl,j)
                );
    }

    for (; mex.count(r); ++r);
    return r;
}


int main(){

    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %d%d",&r,&c);
        REP(i,r) scanf(" %s",s[i]);

        memset(is,0,sizeof(is));
        REP(i,r) REP(j,c) if (s[i][j]=='^'){
            int best=10;
            REP(k,4){
                int x=i,y=j;
                int cnt=0;
                for (; in(x,y) && s[x][y]=='^'; x+=vx[k], y+=vy[k], ++cnt);
                best=min(best,cnt);
            }
            is[i][j]=best>=3;
        }

        memset(dp,-1,sizeof(dp));
        printf("%s\n",str[go(0,r,0,c)>0]);
    }

    return 0;
}

