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

const int maxn=1e5+100;
int c[maxn], v[maxn];
int n;
pair<ll,int> b1,b2;
int mul[2];
ll best[maxn];

int main(){
    int nq;
    scanf(" %d%d",&n,&nq);
    REP(i,n) scanf(" %d",v+i);
    REP(i,n) scanf(" %d",c+i);

    REP(qq,nq){
        scanf(" %d%d",mul,mul+1);
        b1=MP(0,-1);
        b2=MP(0,-2);
        REP(i,n) best[i+1]=-1e18;

        REP(i,n){
            ll nc=b1.ST+1ll*mul[b1.ND!=c[i]]*v[i];
            nc=max(nc,b2.ST+1ll*mul[b2.ND!=c[i]]*v[i]);

            nc=max(nc,best[c[i]]+1ll*mul[0]*v[i]);

            best[c[i]]=max(best[c[i]],nc);
            

            if (b1.ST<=nc){
                if (b1.ND!=c[i]) b2=b1;
                b1=MP(nc,c[i]);
            } else if (b2.ST<=nc && b1.ND!=c[i]) b2=MP(nc,c[i]);
            assert(b1.ND!=b2.ND);
        }
        printf("%I64d\n",b1.ST);
    }
    return 0;
}

