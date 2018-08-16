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

int best;
vector<pii> e[maxn];
int n;
int seen[222222];
int rmp[222222];
int step;

int dfs(int a, int p=-1){
    int res=0;
    REP(i,e[a].size()){
        int b=e[a][i].ST;
        if (b==p) continue;
        int x=dfs(b,a)+e[a][i].ND;
        if (x>0) res+=x;
    }
    if (best<res) best=res;
    return res;
}

int main(){
    step=0;
    while(cin>>n,n){
        ++n;
        REP(i,n) e[i].clear();
        ++step;
        int cnt=0;
        REP(i,n-1){
            int a, b, c; scanf(" %d%d%d",&a,&b,&c);
            --a; --b;
            if (seen[a]!=step) seen[a]=step, rmp[a]=cnt++;
            if (seen[b]!=step) seen[b]=step, rmp[b]=cnt++;
            a=rmp[a]; b=rmp[b];

            e[a].pb(MP(b,c));
            e[b].pb(MP(a,c));
        }

        best=INT_MIN;
        dfs(0);
        cout<<best<<endl;
    }
    return 0;
}


