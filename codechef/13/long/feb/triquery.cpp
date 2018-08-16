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

const int maxn=333333+222222;
const int leaf=1<<19;

int x[maxn], y[maxn];
int d[maxn], vv[maxn];
int n,m,nq;
int tx[2*leaf], ty[2*leaf];

int id[maxn];
int res[maxn];

int get(int *tree, int a){int res=tree[a+=leaf]; for (; a>1; a>>=1) if (a&1) res+=tree[a^1]; return res;}
void update(int *tree, int a, int v){for (a+=leaf; a; a>>=1) tree[a]+=v;}

int cmp1(int a, int b){ return y[a]!=y[b]?y[a]<y[b]:x[a]<x[b]; }
int cmp2(int a, int b){return vv[a]<vv[b];}


int main(){
    cin>>n>>nq;
    REP(i,n) scanf(" %d%d",x+i,y+i);
    REP(i,nq) scanf(" %d%d%d",x+n+i,y+n+i,d+n+i);
    m=n+nq;
    REP(i,m) vv[i]=x[i]+y[i]+d[i];

    REP(i,nq) --y[n+i];

    REP(i,m) id[i]=i;
    sort(id,id+m,cmp1);
    REP(i,m){
        int a=id[i];
        if (a>=n) res[a-n]+=get(tx,x[a]-1);
        else update(tx,x[a],1);
    }

    REP(i,nq) ++y[n+i];
    memset(tx,0,sizeof(tx));

    sort(id,id+m,cmp2);
    int cnt=0;
    REP(i,m){
        int j=i;
        for (; j<m && vv[id[i]]==vv[id[j]]; ++j) if (id[j]<n) ++cnt, update(tx,x[id[j]],1), update(ty,y[id[j]],1);
        for (; i!=j; ++i) if (id[i]>=n){
            int a=id[i];
            res[a-n]+=cnt-get(tx,x[a]-1)-get(ty,y[a]-1);
        }
        --i;
    }

    REP(i,nq) printf("%d\n",res[i]);
    return 0;
}

