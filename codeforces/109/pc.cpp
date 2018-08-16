#include <vector>
#pragma stacksize 70m
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

const int maxn=1e6+10;
const ll mod=1234577;
vi e[maxn];
int vis[maxn];
int tb[maxn];
ll v[2*maxn];

int cmp(int a, int b){return e[a].size()<e[b].size();}
set<pii> has;

ll h[maxn][2];

int main(){
    int n, m; cin>>n>>m;

    //n=m=1e6;
    REP(i,n) e[i].pb(i);

    //srand(time(0));
    //REP(i,m){
    //    while(1){
    //        int a=rand()%n, b=rand()%n;
    //        if (a==b) b=(b+1)%n;
    //        if (a>b) swap(a,b);
    //        assert(a>=0 && b<n);

    //        if (!has.count(MP(a,b))){e[a].pb(b); e[b].pb(a); has.insert(MP(a,b)); break;}
    //    }
    //}
    //has.clear();

    //clock_t sta=clock();
    REP(i,m){ int a, b; scanf("%d%d",&a,&b); --a; --b; e[a].pb(b); e[b].pb(a); }
    REP(i,n) sort(ALL(e[i]));
    ll res=0;

    REP(i,n) tb[i]=i;
    sort(tb,tb+n,cmp);
    for (int i=0, j=0; i<n; i=j){
        while(j<n&&e[tb[j]].size()==e[tb[i]].size()) ++j;
        if (e[tb[i]].size()==1){res+=1ll*(j-i)*(j-i-1); continue;}
        int na=0;
        FOR(k,i,j){
            int a=tb[k];
            REP(u,e[a].size()){
                int b=e[a][u];
                h[a][0]=h[a][0]*mod+b+1;
                if (b!=a) h[a][1]=h[a][1]*mod+b+1;
            }
            v[na++]=h[a][0];
            v[na++]=h[a][1];
        }
        sort(v,v+na);
        FOR(k,i,j){
            int a=tb[k];
            REP(f,2) res+=upper_bound(v,v+na,h[a][f])-lower_bound(v,v+na,h[a][f])-1;
        }
    }

    //cout<<1.*(clock()-sta)/CLOCKS_PER_SEC<<endl;
    cout<<res/2<<endl;

    return 0;
}


