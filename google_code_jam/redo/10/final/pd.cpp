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

const int maxn=31;

int n;
ll f;
ll pos[maxn];
int mid;
vector<ll> sa, sb;

void reca(int p, int a, ll b){
    if (p==0){
        if (a==2) sa.pb(b);
        return;
    }
    if (a<=2*p) reca(p-1, a, b+a*(pos[p]-pos[p-1]));
    if (a>2) reca(p-1, a-2, b+(a-2)*(pos[p]-pos[p-1]));
    if (a+2<=2*p) reca(p-1, a+2, b+(a+2)*(pos[p]-pos[p-1]));

}


void recb(int p, int a, ll b){
    assert(p<=n-1);
    assert(p>=0);
    if (p==n-1){
        if (a==2) sb.pb(b);
        return;
    }
    if (a<=2*(n-p)) recb(p+1, a, b+a*(pos[p+1]-pos[p]));
    if (a>2) recb(p+1, a-2, b+(a-2)*(pos[p+1]-pos[p]));
    if (a+2<=2*(n-p)) recb(p+1, a+2, b+(a+2)*(pos[p+1]-pos[p]));

}


ll solve(){

    REP(i, n) if (pos[i]==0){mid=i; break;}
    ll res=0;

    for (int i=2; i<=n; i+=2){
        sa.clear();
        sb.clear();
        reca(n/2-1, i, 0);
        recb(n/2, i, (pos[n/2]-pos[n/2-1])*i);


        assert(sa.size());
        assert(sb.size());
        if (!sa.size() || !sb.size()) continue;
        sort(ALL(sa));
        sort(ALL(sb));
        sa.resize(unique(ALL(sa))-sa.begin());
        sb.resize(unique(ALL(sb))-sb.begin());


        int j=sb.size()-1;
        REP(k, sa.size()){
            while(j>0 && sa[k]+sb[j]>f) --j;
            if (sa[k]+sb[j]<=f) checkmax(res, sa[k]+sb[j]);
        }
    }
    return res;

}
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        REP(i, n) cin>>pos[i];
        cin>>f;
        sort(pos, pos+n);

        ll res=solve();
        printf("Case #%d: ", ti);
        if (res==0) printf("NO SOLUTION\n");
        else printf("%Ld\n", res);
    }

    return 0;
}



