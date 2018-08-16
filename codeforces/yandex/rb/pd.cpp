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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=2e5+10;
int cnt[maxn];
int a[maxn], oa[maxn];
int n, t, m;
pii q[maxn];


struct cmpa{
    bool operator()(int a, int b)const{
        if (q[a].ST/m!=q[b].ST/m) return q[a].ST<q[b].ST;
        return q[a].ND<q[b].ND;
    }
};


int main(){
    cin>>n>>t;
    REP(i, n){ cin>>oa[i]; a[i]=oa[i];}
    REP(i, t) cin>>q[i].ST>>q[i].ND;
    REP(i, t) --q[i].ST, --q[i].ND;


    
    sort(oa, oa+n);
    m=ceil(sqrt(n));
    REP(i, n) a[i]=lower_bound(oa, oa+n, a[i])-oa;


    int perm[t];
    REP(i, t) perm[i]=i; sort(perm, perm+t, cmpa());
    ll res[t];
    ll ans=0;
    memset(cnt, 0, sizeof(cnt));

    pii p=q[perm[0]];
    pii prev=MP(0, -1);
    REP(i, t){
        p=q[perm[i]];
        if (prev.ND<=p.ND) while(prev.ND!=p.ND) ++prev.ND, ans+=oa[a[prev.ND]]*(1+2*cnt[a[prev.ND]]++);
        else while(prev.ND!=p.ND) ans+=oa[a[prev.ND]]*(1-2*cnt[a[prev.ND]]--), --prev.ND;
        
        if (prev.ST<=p.ST) while(prev.ST!=p.ST) ans+=oa[a[prev.ST]]*(1-2*cnt[a[prev.ST]]--), ++prev.ST;
        else while(prev.ST!=p.ST) --prev.ST, ans+=oa[a[prev.ST]]*(1+2*cnt[a[prev.ST]]++);


        res[perm[i]]=ans;
    }
    REP(i, t) cout<<res[i]<<endl;
    return 0;

}


