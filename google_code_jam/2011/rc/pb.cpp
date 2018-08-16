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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxc=1010;
int n, l, c;
ll t;
int a[maxc];
ll b[maxc];

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>l>>t>>n>>c;
        REP(i, c) cin>>a[i];
        b[0]=0;
        REP(i, c) b[i+1]=b[i]+a[i];

        int nc=n%c, nr=n/c;
        ll tot=(ll(nr)*b[c]+b[nc])*2;
        ll rem=0;

        ll sround=t/2/b[c];
        map<int, int> mv;
        if (sround<nr){
            int na=nr-sround-1;
            REP(i, c) mv[a[i]]+=na;
            ll tmp=t-sround*b[c]*2;
            int p=0;
            while(2*b[p+1]<tmp) ++p;
            tmp-=b[p]*2;
                assert(tmp%2==0);
            ++mv[a[p]-tmp/2];
            FOR(i, p+1, nc+c-1) ++mv[a[i%c]];



        }else if (sround==nr){
            ll tmp=t-sround*b[c]*2;
            int p=0;
            while(b[p+1]*2<tmp) ++p;
            tmp-=b[p]*2;
            if (p<nc){
                
                assert(tmp%2==0);
                ++mv[a[p]-tmp/2];
                for (++p; p<nc; ++p) ++mv[a[p]];
            }
        }

        FEV(it, mv) if (l>0){
            int nb=min(l, it->ND);
            rem+=nb*it->ST;
            l-=it->ND;
        }

        printf("Case #%d: %Ld\n", ti, tot-rem);
        
    }
    return 0;
}

