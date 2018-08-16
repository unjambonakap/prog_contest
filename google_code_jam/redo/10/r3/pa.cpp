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

const int maxd=1e6+1;
const int maxk=11;
vi plist;
int w[maxk];
int k;
int prime[maxd];

ll inv(ll a, int p){
    ll tmp=1;
    if (p==2) return a;
    int mod=p;
    p-=2;
    while(p){
        if (p&1) tmp=tmp*a%mod;
        p>>=1;
        a=a*a%mod;
    }
    return tmp;
}

int next(int p){
    if (k==1) return -1;
    if (k==2){
        if (w[0]==w[1]) return w[0];
        return -1;
    }

    ll tmpa, tmpb;
    tmpa=w[1]-w[0];
    tmpb=w[2]-w[1];
    if (tmpa<0) tmpa+=p;
    if (tmpb<0) tmpb+=p;
    ll a=tmpb*inv(tmpa, p);
    ll b=(w[1]-a*w[0])%p;
    if (b<0) b+=p;
    ll s=w[0];
    REP(i, k){
        if (s!=w[i]) return -1;
        s=(a*s+b)%p;
    }
    return s;
}

int main(){
    int tn;
    cin>>tn;
    memset(prime, 1, sizeof(prime));
    FOR(i, 2, maxd-1) if (prime[i]){
        plist.pb(i);
        int p=i+i;
        while(p<maxd) prime[p]=0, p+=i;
    }

    FOR(ti, 1, tn){
        int d;
        cin>>d>>k;
        REP(i, k) cin>>w[i];
        d=pow(10, d);
        int m=*max_element(w, w+k);

        int res=-1;
        FE(it, plist) if (*it>m){
            if (*it>d) break;
            int tmp=next(*it);
            if (tmp!=-1){
                if (res!=-1 && res!=tmp) {res=-1; break;}
                res=tmp;
            }
        }

        printf("Case #%d: ", ti);
        if (res==-1) printf("I don't know.\n");
        else printf("%d\n", res);
    }
    return 0;
}


