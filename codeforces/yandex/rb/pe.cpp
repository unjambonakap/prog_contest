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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(ll n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxk=50;
ll res[maxk]={
    3LL,
    5LL,
    9LL,
    20LL,
    33LL,
    68LL,
    250LL,
    485LL,
    711LL,
    1579LL,
    2599LL,
    4803LL,
    11872LL,
    16872LL,
    60025LL,
    78181LL,
    260036LL,
    346691LL,
    805533LL,
    1741380LL,
    2152343LL,
    6044816LL,
    10713889LL,
    27206403LL,
    63912017LL,
    95559823LL,
    165545255LL,
    296992181LL,
    730099714LL,
    1176868181LL,
    2811309472LL,
    6952528713LL,
    11338176021LL,
    18927809323LL,
    44286621048LL,
    75343025763LL,
    244792297742LL,
    435263110300LL,
    1067275519351LL,
    1443951289254LL,
    4380646641356LL,
    6759656859348LL,
    15685450827880LL,
    22137690048707LL,
    38132641857274LL,
    91434108032026LL,
    159670507020536LL,
    330527995056379LL,
    640307590638357LL

};


ll a[maxk];
ll m[maxk];
ll b[maxk];
char co[two(maxk/2+1)];
vector<ll> lst;
int k;
inline void mul(ll *x, ll *y, ll *z){
    REP(i, k){b[i]=0; REP(j, k) REP(l, k) b[i]^=(y[i]>>l&z[l]>>j&1)?twoll(j):0; }
    memcpy(x, b, sizeof(b));
}


int checkit(ll p){
    while(p){
        if (p&1) mul(a, a, m);
        p>>=1;
        mul(m, m, m);
    }
    REP(i, k) if (a[i]!=twoll(i)) return 0;
    return 1;
}
int checkitb(ll x){
    ll y=1;
    for (ll i=0; i<twoll(k)-1; ++i) y=(y<<1|count_bit(x&y)%2)&(twoll(k)-1);
    return y==1;
}

ll proc(){
    int nstep=1e5;
    REP(i, nstep){
        m[0]=twoll(k-1);
        REP(j, k-1) m[0]|=rand()%2?twoll(j):0;

        ll ans=m[0];
        REP(j, k-1) m[j+1]=twoll(j);
        REP(j, k) a[j]=twoll(j);

        if (checkit(twoll(k)-1)){
            FE(it, lst){
                m[0]=ans;
                REP(j, k-1) m[j+1]=twoll(j);
                REP(j, k) a[j]=twoll(j);

                if (checkit(*it)) goto fail;
            }
            //if (k<=20 && !checkitb(ans)){
            //    printf("fail b on %d (xx %Ld\n", k, ans);
            //    exit(0);
            //}
            return ans;
        }
fail:;

    }

    printf("xxxxxxx fail\n");
    exit(0);

}


int main(){
    //srand(time(0));

    //memset(co, 0, sizeof(char));
    //for (int i=2; i<=two(20); ++i) if (!co[i]) for (int j=i+i; j<=two(25); j+=i) co[j]=1;
    //for (k=2; k<=maxk; ++k){

    //    lst.clear();
    //    ll v=twoll(k)-1;
    //    for (int i=2; i<=two(25) && i<=sqrt(v); ++i) if (!co[i] && v%i==0) lst.pb(i), lst.pb(v/i);
    //    res[k]=proc();
    //    printf("%Ld,\n", res[k]);
    //}


    cin>>k;
    REP(i, k) printf("%d ", res[k-2]&twoll(i)?1:0); printf("\n");
    REP(i, k) printf("1 "); printf("\n");


    return 0;
}


