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

const int maxn=1<<18+1;
vi e[maxn];
int h[maxn];
int n;

vector<pii> xt[maxn];
vi ql[maxn];

int cnt[maxn];
int cost[maxn];

int res[maxn];

int get(int *tb, int a){ int res=0; for (++a; a; a&=a-1)  res+=tb[a]; return res; }
void update(int *tb, int a, int v){ for (++a; a<maxn; a+=a&-a) tb[a]+=v; }

int go(int a){

    int b=1<<17;
    int u=0, have=0;
    for (b=17; b>=0; --b) if (have+cost[u+(1<<b)]<h[a]) have+=cost[u+=1<<b];
    if (a) update(cnt,u+1,1);

    REP(i,xt[a].size()) update(cost,xt[a][i].ST,xt[a][i].ND);

    REP(i,ql[a].size()) res[ql[a][i]]=get(cnt,ql[a][i]);


    int cc=0;
    REP(i,e[a].size()) cc+=go(e[a][i]);

    REP(i,ql[a].size()) res[ql[a][i]]+=cc-get(cnt,ql[a][i]);


    REP(i,xt[a].size()) update(cost,xt[a][i].ST,-xt[a][i].ND);

    return cc+1;
}

int main(){
    cin>>n; ++n;
    h[0]=-1;
    REP(i,n-1){
        int a; scanf(" %d%d",h+i+1,&a);
        e[a].pb(i+1);
    }


    int nq; cin>>nq;


    REP(i,nq){
        int a,b; scanf(" %d%d",&a,&b);
        if (a==1){
            int c; scanf(" %d",&c);
            xt[b].pb(MP(i+1,c));
        }else ql[b].pb(i+1);
    }
    memset(res,-1,sizeof(res));
    go(0);


    REP(i,nq+1) if (res[i]!=-1) printf("%d\n",res[i]);

    return 0;
}

