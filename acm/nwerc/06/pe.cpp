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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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

const int maxn=77;
const int maxv=2101;
int n;
int A[2][maxv][maxv];
pii X[maxn];

void doit(int &a, int b){
    if (a==-1) a=b;
    else checkmin(a, b);
}

int main(){
    int tn; cin>>tn;
    REP(ti, tn){
        cin>>n;
        int S=0;
        REP(i, n) cin>>X[i].ST>>X[i].ND, S+=X[i].ND;
        sort(X, X+n, greater<pii>());
        memset(A, -1, sizeof(A));
        int p, np;
        p=0, np=1;
        A[p][0][0]=0;
        int Y=S+1;
        REP(i, n){
            memset(A[np], -1, sizeof(A[np]));
            REP(j, Y) REP(k, Y) if (A[p][j][k]!=-1){
                int v=A[p][j][k];
                doit(A[np][j+X[i].ND][k], v+(j?0:X[i].ST));
                doit(A[np][j][k+X[i].ND], v+(k?0:X[i].ST));
                doit(A[np][j][k], v);
            }
            p=np; np^=1;
        }
        int ans=INT_MAX;
        REP(i, Y) REP(j, Y) if (i&&j&&A[p][i][j]!=-1){
            int k=max(max(i, j), S-i-j);
            checkmin(ans, (X[0].ST+A[p][i][j])*k);
        }
        printf("%d\n", ans);

    }
    return 0;
}



