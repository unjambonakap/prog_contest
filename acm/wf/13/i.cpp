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

const int maxn=555;
const int oo=2e9;

int n,m,a,b;
int h[maxn][maxn];
vector<pii> tb[maxn];

int best[maxn][maxn];

int main(){

    while(cin>>a>>b>>n>>m,!cin.eof()){

        REP(i,n) REP(j,m) scanf(" %d",h[i]+j);
        if (a>b) swap(a,b);
        REP(i,n) h[i][m]=0;
        ++m;
        memset(best,0,sizeof(best));

        REP(i,n){
            REP(j,n) tb[j].clear();

            REP(j,m){
                int V=oo;
                FOR(k,i,n){
                    V=min(V,h[k][j]);

                    int last=j;
                    while(tb[k].size() && tb[k].back().ST>=V){
                        pii x=tb[k].back(); tb[k].pop_back();
                        int u=j-x.ND, v=k-i+1;
                        last=min(last,x.ND);

                        if (u>v) swap(u,v);
                        u=min(u,a); v=min(v,b);
                        best[u][v]=max(best[u][v],x.ST);
                    }
                    tb[k].pb(MP(V,last));
                    if (j==m-1) assert(tb[k].size()==1);
                }
            }
        }

        ll res=0;
        --m;
        REP(i,a+1) REP(j,b+1){
            ll T=0, H=2e13;
            ll ans=0;
            while(T<=H){
                ll M=T+H>>1;
                ll need=1ll*M*n*m;
                ll have=1ll*(best[i][j]+M)*i*j;
                if (need<have) T=M+1, ans=M;
                else H=M-1;
            }
            res=max(res,1ll*i*j*(best[i][j]+ans));

        }
        cout<<res<<endl;

    }

    return 0;
}

