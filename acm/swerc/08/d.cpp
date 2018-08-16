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

const int maxn=111;
const int maxr=33;
const int oo=1e9;

int n, r;
int g[maxn][maxn];
char buf[maxn];
double dp[maxn][maxn*maxr];

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>r;
        REP(i,n){
            scanf(" %s",buf);
            REP(j,n) g[i][j]=buf[j]=='Y'?1:oo;
            g[i][i]=0;
        }
        REP(k,n) REP(i,n) REP(j,n) g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
        int nb=n*r+1;
        REP(i,nb) dp[0][i]=1.;
        REP(i,n){
            double s=0;
            REP(j,nb){
                if (j-r-1>=0) s-=dp[i][j-r-1];
                dp[i+1][j]=s/r;
                s+=dp[i][j];
            }
        }

        
        int nq; cin>>nq;
        printf("Case %d\n",ti+1);
        REP(step,nq){
            int a, b, m; scanf(" %d%d%d",&a,&b,&m);
            int x=g[a-1][b-1];
            m=min(m,r*x);
            printf("%.10lf\n",dp[x][m]);
        }

        puts("");
    }

    return 0;
}

