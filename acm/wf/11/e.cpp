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

const int maxn=2010;

int A[maxn][maxn];
int b[maxn][maxn];

inline int getv(int a, int b){return a<0||b<0?0:A[min(a,maxn-1)][min(b,maxn-1)];}

int main(){
    int dx, dy, n, q;
    int tn=0;
    while(cin>>dx>>dy>>n>>q,dx|dy|n|q){
        printf("Case %d:\n", ++tn);
        vector<pii> tb;
        memset(b,0,sizeof(b));
        REP(i,n){
            int u, v; scanf("%d%d", &u,&v);
            b[u-v+1000][u+v]=1;
        }
        memset(A,0,sizeof(A));
        REP(i,maxn) REP(j,maxn) A[i][j]=getv(i-1,j)+getv(i,j-1)-getv(i-1,j-1)+b[i][j];
        REP(i,q){
            int M; cin>>M;
            int best=-1;
            pii res;
            REP(i,maxn) REP(j,maxn) if ((i+j)%2==0){
                int u=getv(i+M,j+M)-getv(i-M-1,j+M)-getv(i+M,j-M-1)+getv(i-M-1,j-M-1);
                if (u>=best){
                    pii pos=MP(j-i+1000>>1,i+j-1000>>1);
                    if (pos.ND<=0 || pos.ST<=0) continue;
                    if (u>best) best=u, res=pos;
                    else checkmin(res,pos);
                }
            }
            printf("%d (%d,%d)\n", best, res.ND, res.ST);
        }
    }
    return 0;
}

