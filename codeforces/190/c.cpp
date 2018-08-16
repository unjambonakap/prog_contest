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


const int maxn=1e5+10;
vi e[maxn];
int block[maxn];
int res[maxn];
int n;

int cnt[maxn];
int N;


int dfs1(int a, int p=-1){
    cnt[a]=1;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (!block[b] && b!=p) cnt[a]+=dfs1(b,a);
    }
    return cnt[a];
}

int dfs2(int a, int p=-1){
    int mx=N-cnt[a];
    int uu=-1;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (!block[b] && b!=p && mx<cnt[b]) mx=cnt[b], uu=b;
    }
    if (mx<=N/2) return a;
    return dfs2(uu,a);
}

void go(int a, int x){
    N=dfs1(a);

    int pick=dfs2(a);
    res[pick]=x;
    block[pick]=1;
    REP(i,e[pick].size()){
        int b=e[pick][i];
        if (!block[b]) go(b,x+1);
    }
}


int main(){
    cin>>n;
    REP(i,n-1){
        int a,b; scanf(" %d%d",&a,&b); --a; --b;
        e[a].pb(b);
        e[b].pb(a);
    }
    go(0,0);

    REP(i,n) printf("%c%c",res[i]+'A'," \n"[i==n-1]);
    return 0;

}

