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

const int maxn=88888;
int n;
vi e[maxn];
int par[maxn];
int sz[maxn];
ll sz2[maxn];

ll dp[maxn];



void dfs(int a, int p=-1){
    par[a]=p;
    sz[a]=1;

    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==par[a]){
            swap(e[a].back(),e[a][i]);
            e[a].pop_back();
            --i;
            continue;
        }
        dfs(b,a);
    }
    if (p!=-1) sz[p]+=sz[a];
    sz2[a]=1ll*sz[a]*(sz[a]-1)/2;
}


ll getsum2(int a){
    ll sum2=0;
    REP(i,e[a].size()) sum2+=sz2[e[a][i]];
    return sum2;
}

ll go(int a){//a in p1, p2 in a's subtree
    ll &res=dp[a];
    if (res!=-1) return res;
    res=0;

    ll sum2=getsum2(a);
    res+=sum2;//stopping p1 on a

    REP(i,e[a].size()){
        int b=e[a][i];
        res+=go(b);
        res+=sz[b]*(sum2-sz2[b]);//part here
    }

    return res;

}

ll solve(int a){//smallest subtree containing everything
    ll res=0;

    ll sum2=getsum2(a);

    //a is not visited => 2 diff subtrees
    REP(i,e[a].size()){
        int b=e[a][i];
        res+=sz2[b]*(sum2-sz2[b]);
    }
    //now a visited

    //a not chosen, p1 and p2 in diff subtree
    ll correct=1ll*(sz[a]-1)*(sz[a]-2)/2-sum2;

    res/=2;
    REP(i,e[a].size()){
        int b=e[a][i];
        res+=sz2[b]*(correct-1ll*(sz[a]-1-sz[b])*sz[b]);
    }

    //p1 and p2 in b's subtree
    REP(i,e[a].size()){
        int b=e[a][i];
        res+=go(b)*(sz[a]-sz[b]);
    }


    //a chosen, p1 and p2 in diff subtree
    REP(i,e[a].size()){
        int b=e[a][i];
        res+=sz2[b]*(sz[a]-1-sz[b]);
    }

    return res;
}


int main(){
    cin>>n;
    REP(i,n-1){
        int a, b; scanf(" %d%d",&a,&b);
        --a; --b;
        e[a].pb(b);
        e[b].pb(a);
    }
    dfs(0);

    ll res=0;
    memset(dp,-1,sizeof(dp));
    REP(i,n) res+=solve(i);

    cout<<2*res<<endl;
    return 0;
}

