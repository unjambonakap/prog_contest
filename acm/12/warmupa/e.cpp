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
const int maxp=18;
vi e[maxn];
int vis[maxn];
pii na[maxn];//subtree sz, longest path
int id[maxn];
int rmq[maxn][maxp];
int pos;
int n, m;
int res, cnt;


int dfs(int a, int p){
    ++cnt;
    vis[a]=1;
    int x=0, y=0;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        int z=dfs(b,a)+1;
        if (z>x) y=x, x=z;
        else if (z>y) y=z;
    }
    checkmax(res,x+y);
    return x;
}


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>m;
        REP(i,n) e[i].clear();
        REP(i,m){
            int a, b; scanf("%d%d", &a,&b);
            --a; --b;
            e[a].pb(b); e[b].pb(a);
        }
        pos=0;
        memset(vis,0,sizeof(vis));
        REP(i,n) if (!vis[i]){
            res=-1;
            cnt=0;
            dfs(i,-1);
            na[pos++]=MP(cnt,res);
        }


        sort(na,na+pos);
        REP(i,pos) rmq[i][0]=na[i].ND;
        FOR(i,1,maxp) REP(j,pos) rmq[j][i]=max(rmq[j][i-1],rmq[min(pos-1,j+(1<<i-1))][i-1]);


        printf("Case %d:\n", ti+1);
        int nq; cin>>nq;
        REP(i,nq){
            int k; scanf("%d", &k);
            --k;
            int a=lower_bound(na,na+pos,MP(k+1,0))-na;
            if (a==pos) puts("impossible");
            else{
                int x=floor(log(pos-a)/log(2));
                printf("%d\n", 2*k-min(k,max(rmq[a][x],rmq[pos-x][x])));


            }
        }
    }
    return 0;
}


