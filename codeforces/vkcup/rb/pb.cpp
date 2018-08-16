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
const int maxn=1111;

int main(){
    int n, k; cin>>n>>k;
    int  shit;
    vector<pii> a, b;
    REP(i,n){
        int u ,v;
        scanf(" %d%d", &u,&v);
        if (v==2) b.pb(MP(u,i));
        else a.pb(MP(u,i));
    }
    sort(ALL(a));
    sort(ALL(b));
    reverse(ALL(a));


    ll v=0;
    REP(i,a.size()) v+=a[i].ST;
    REP(i,b.size()) v+=b[i].ST;
    v<<=1;

    vector<string> res;
    int na=min((int)a.size(),k-1);
    REP(i,na) v-=a[i].ST;
    if (na<a.size()) v-=b.size()?min(a.back().ST,b[0].ST):a.back().ST;


    cout<<(v>>1);
    if (v&1) printf(".5");
    else printf(".0");

    puts("");
    REP(i,na) printf("1 %d\n", a[i].ND+1);
    vector<int> rem;
    REP(i,b.size()) rem.pb(b[i].ND+1);
    FOR(i,na,a.size()) rem.pb(a[i].ND+1);
    REP(i,k-1-na) printf("1 %d\n", rem.back()), rem.pop_back();

    printf("%d", rem.size());
    REP(i,rem.size()) printf(" %d", rem[i]);
    puts("");


    return 0;
}


