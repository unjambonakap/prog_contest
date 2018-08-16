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

const int maxn=5555;

int par[maxn];
int root(int a){return par[a]<0?a:par[a]=root(par[a]);}
int join(int a, int b){a=root(a); b=root(b); if (a==b) return 0; par[a]+=par[b]; par[b]=a; return 1;}

vector<pair<int,pii> > ea, eb;

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        int n, na, nb; cin>>n>>na>>nb;
        ea.clear(); eb.clear();
        memset(par,-1,sizeof(par));
        REP(i,na){
            int a,b,c; scanf(" %d%d%d",&a,&b,&c);
            ea.pb(MP(c,MP(a,b)));
        }

        REP(i,nb){
            int a,b,c; scanf(" %d%d%d",&a,&b,&c);
            eb.pb(MP(c,MP(a,b)));
        }
        sort(ALL(ea));
        sort(ALL(eb));
        ll profit=0;
        for (int i=nb-1; i>=0; --i) if (join(eb[i].ND.ST,eb[i].ND.ND)) profit+=eb[i].ST;
        ll cost=profit;
        REP(i,na) if (join(ea[i].ND.ST,ea[i].ND.ND)) cost+=ea[i].ST;


        if (par[root(0)]!=-n) puts("Impossible");
        else printf("%Ld %Ld\n",profit,cost);
    }
    return 0;
}


