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

const int maxn=2222;
ll px[maxn];
ll h[maxn];
char a[maxn], b[maxn], c[maxn];
int A[maxn], B[maxn];

int go(int v){
    px[0]=1;
    int na=strlen(a), nb=strlen(b), nc=strlen(c);;
    FOR(i,1,na) px[i]=px[i-1]*v;
    h[0]=0;
    REP(i,na) h[i+1]=h[i]*v+a[i]-'a'+1;
    ll hb, hc;
    hb=hc=0;
    REP(i,nb) hb=hb*v+b[i]-'a'+1;
    REP(i,nc) hc=hc*v+c[i]-'a'+1;

    vector<ll> tb;
    REP(i,na-max(nb,nc)+1) if (hb==h[i+nb]-h[i]*px[nb]) A[i]=1;
    FOR(i,max(nb,nc), na+1) if (hc==h[i]-h[i-nc]*px[nc]) B[i]=1;
    REP(i,na-max(nb,nc)+1) FOR(j, i+max(nb,nc), na+1) if (A[i]&&B[j]) tb.pb(h[j]-h[i]*px[j-i]);
    sort(ALL(tb));
    return unique(ALL(tb))-tb.begin();
}
int main(){
    scanf("%s", a);
    scanf("%s", b);
    scanf("%s", c);


    printf("%d\n", go(103));
    return 0;
}


