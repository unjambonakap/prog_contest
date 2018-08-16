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

const int maxc=27;
const int maxn=202;
const int oo=1e9;

int rmp[256];
char mp[maxc];
int k;
char buf[maxn];
int n;
int dp[maxn][maxn][maxc];
int g[maxc][maxc], t[maxc][maxc];
int done[maxn][maxn][maxc];


int main(){
    int uu=0;
    while(cin>>k,k){
        if (uu++) puts("");

        char c;
        memset(rmp,-1,sizeof(rmp));
        REP(i,k){
            scanf(" %s",buf), c=buf[0], rmp[c]=i, mp[i]=c;
        }
        int oldk=k;
        REP(i,k) REP(j,k){
            int x;
            scanf("%d-%c",&x,&c);
            assert(rmp[c]!=-1);
            g[i][j]=rmp[c]; t[i][j]=x;
        }

        int nq; cin>>nq;
        REP(ii,nq){
            scanf(" %s",buf); n=strlen(buf);
            assert(n<=200);
            assert(k<=26);
            REP(i,n) assert(rmp[buf[i]]!=-1);

            REP(i,n) REP(j,n) REP(kk,k) dp[i][j][kk]=oo;
            memset(done,0,sizeof(done));
            REP(i,n) dp[i][i][rmp[buf[i]]]=0;
            REP(i,n) REP(kk,k) done[i][i][kk]=1;

            for (int i=n-2; i>=0; --i) FOR(j,i+1,n){
                FOR(u,i,j) REP(ka,k) REP(kb,k){
                    assert(done[i][u][ka]);
                    assert(done[u+1][j][kb]);
                    int dst=g[ka][kb];
                    done[i][j][dst]=1;
                    int nc=dp[i][u][ka]+dp[u+1][j][kb]+t[ka][kb];
                    if (dp[i][j][dst]>nc) dp[i][j][dst]=nc;
                }
                REP(kk,k) done[i][j][kk]=1;
            }
            assert(k==oldk);


            pii best=MP(oo,0);
            REP(i,k) best=min(best,MP(dp[0][n-1][i],i));
            assert(best.ST<oo);
            printf("%d-%c\n",best.ST,mp[best.ND]);
        }
    }

    return 0;
}

