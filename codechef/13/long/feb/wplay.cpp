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

const int P=57, mod=1e9+9;
const int P2=37, mod2=1e9+7;

const int maxr=4;
const int maxn=maxr*maxr;

char buf[111];
int r,c,n;
set<int> lst, lst2;
int dp[1<<maxn];
int have[1<<maxn];

int go(int a){
    if (!a) return 0;
    int &r=dp[a];
    if (r!=-1) return r;
    r=0;
    for (int m=a; m; m=a&m-1) if (have[m] && !go(m^a)) return r=1;
    return r;
}

int main(){
    int nd;
    cin>>nd;
    REP(i,nd){
        scanf(" %s",buf);
        int m=strlen(buf);
        sort(buf,buf+m);
        int h=0, h2=0;
        REP(i,m) h=(1ll*h*P+buf[i]-'A'+1)%mod, h2=(1ll*h2*P2+buf[i]-'A'+1)%mod2;
        lst.insert(h);
        lst2.insert(h2);
    }
    cin>>r>>c;
    n=r*c;
    int tn; cin>>tn;
    REP(ti,tn){
        REP(i,r) scanf(" %s",buf+i*c);
        sort(buf,buf+n);
        int N=1<<n;

        memset(dp,-1,sizeof(int)*N);
        memset(have,0,sizeof(int)*N);
        FOR(i,1,N){
            int h=0, h2=0;
            REP(j,n) if (i>>j&1) h=(1ll*h*P+buf[j]-'A'+1)%mod, h2=(1ll*h2*P2+buf[j]-'A'+1)%mod2;
            have[i]=lst.count(h)&&lst2.count(h2);
        }
        puts(go(N-1)?"Alice":"Bob");
    }

    return 0;
}

