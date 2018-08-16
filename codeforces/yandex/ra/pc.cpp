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
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=1e5+10;
const int maxm=1e5+10;

int parent[maxn];
int nx[maxn];
vi e[maxn];
int key[maxn];
int tb[maxm];
int n, m;
int sa[maxn][2];

int mz[maxn];
int nv[maxn];
int d[maxn];

struct cmpA{ bool operator()(int a, int b)const{return tb[a]<tb[b];} };


ll ex;
int no;
void dfs(int a, int dx, int v){
    d[a]=dx;

    mz[a]=v;
    if (nx[a]==0){
        sa[a][0]=sa[a][1]=key[a];
        return;
    }

    REP(i, 2){
        int x=e[a][i];
        dfs(x, dx+1, i?v:key[a]);
        sa[a][i]=sa[x][i];
    }
}

int dfsa(int a, int v){
    if (mz[a]<v){ex-=nv[d[a]-1]; return dfsa(parent[a], v);}
    if (nx[a]==0) return a;
    int y=key[a]<v;
    nv[d[a]]=sa[e[a][y^1]][y];
    ex+=nv[d[a]];
    return dfsa(e[a][y], v);
}


int main(){
    cin>>n;
    REP(i, n) cin>>parent[i]>>key[i];

    int root;
    REP(i, n) if (parent[i]!=-1) e[--parent[i]].pb(i); else root=i;
    REP(i, n) if ((nx[i]=e[i].size()) && key[e[i][0]]>key[e[i][1]]) swap(e[i][0], e[i][1]);

    dfs(root, 0, INT_MAX);
    cin>>m;
    REP(i, m) cin>>tb[i];
    int perm[m];
    REP(i, m) perm[i]=i;
    sort(perm, perm+m, cmpA());
    double res[m];

    int pos=root;
    ex=0;
    REP(i, m){
        pos=dfsa(pos, tb[perm[i]]);
        assert(pos!=root);
        res[perm[i]]=double(ex)/d[pos];
    }
    REP(i, m) printf("%.10lf\n", res[i]);
    return 0;



}


