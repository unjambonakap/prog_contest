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


const int maxn=111111;
int n,m;
vector<pii> e[maxn];
vector<pii> tb[maxn];
int dist[maxn];


int main(){
    cin>>n>>m;
    REP(i,m){int a,b,c; scanf(" %d%d%d",&a,&b,&c); --a; --b; e[a].pb(MP(b,c)); e[b].pb(MP(a,c));}
    REP(i,n){
        int k; scanf(" %d",&k); 
        vi tmp;
        REP(j,k){int a; scanf(" %d",&a); tmp.pb(a);}
        for (int j=0; j<k;){
            int u=j+1;
            for (; u<k && tmp[u]-tmp[u-1]==1; ++u);
            tb[i].pb(MP(tmp[j],tmp[u-1]));
            j=u;
        }
    }

    memset(dist,0x7f,sizeof(dist));
    priority_queue<pii> q;
    q.push(MP(0,0));
    dist[0]=0;
    while(q.size()){
        int a=q.top().ND, d=-q.top().ST; q.pop();
        if (dist[a]!=d) continue;
        if (a==n-1){printf("%d\n",d); return 0;}

        vector<pii>::iterator it=lower_bound(ALL(tb[a]),MP(d+1,0));
        if (it!=tb[a].begin()){
            --it;
            d=max(it->ND+1,d);
        }

        REP(j,e[a].size()){
            int b=e[a][j].ST, nd=d+e[a][j].ND;
            if (dist[b]>nd) q.push(MP(-nd,b)), dist[b]=nd;
        }

    }
    puts("-1");
    return 0;
}

