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

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=15, maxk=15;;
int dp[two(maxn)][maxk];
int px[maxn], py[maxn];

int n, k;
inline int in(int p, int xa, int ya, int xb, int yb){ return (px[p]>=xa &&px[p]<=xb && py[p]>=ya && py[p]<=yb); }

int checkit(int d){
    memset(dp, 0, sizeof(dp));
    dp[two(n)-1][k]=1;
    REPV(j, k) REP(i, two(n)) if (dp[i][j+1]){
        dp[i][j]=1;
        REP(a, n) if (i&two(a)) REP(b, n) if (i&two(b)){
            int x, y;
            int xa, xb, ya, yb;
            xa=px[a]; xb=px[b]; ya=py[a]; yb=py[b];
            if (xb<xa) swap(xa, xb); 
            if (yb<ya) swap(ya, yb);

            int nd;
            
            nd=i; x=xa; y=ya;
            REP(l, n) if (i&two(l) && in(l, x, y, x+d, y+d)) nd^=two(l);
            dp[nd][j]=1;
            nd=i; x=xa; y=yb-d;
            REP(l, n) if (i&two(l) && in(l, x, y, x+d, y+d)) nd^=two(l);
            dp[nd][j]=1;
            nd=i; x=xb-d; y=yb-d;
            REP(l, n) if (i&two(l) && in(l, x, y, x+d, y+d)) nd^=two(l);
            dp[nd][j]=1;
            nd=i; x=xb-d; y=ya;
            REP(l, n) if (i&two(l) && in(l, x, y, x+d, y+d)) nd^=two(l);
            dp[nd][j]=1;
        }

    }


    return dp[0][0];


}

int main(){
    int ti, tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n>>k;
        REP(i, n) cin>>px[i]>>py[i];

        int H=1e6, T=0;
        int M;
        while(T+1<H){
            M=(H+T)/2;
            if (checkit(M)) H=M;
            else T=M;
        }
        printf("Case #%d: %d\n", ti, H);
    }
    return 0;


}
