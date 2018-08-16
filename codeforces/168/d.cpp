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


const int maxn=111111;
int n,m;
vi a[maxn];
int cnt[maxn];
int perm[maxn];
vector<pii> mx[maxn];
int pos[maxn];

int main(){
    cin>>n>>m;
    REP(i,n){
        a[i].resize(m);
        REP(j,m){
            scanf(" %d",&a[i][j]);
            if (a[i][j]!=-1) mx[i].pb(MP(a[i][j],j));
        }
        sort(ALL(mx[i]));
    }

    queue<int> q;
    REP(j,m){
        REP(i,n) if (a[i][j]!=-1 && a[i][j]!=mx[i][0].ST) ++cnt[j];
        if (!cnt[j]) q.push(j);
    }

    int step=0;
    while(q.size()){
        int j=q.front(); q.pop();
        perm[step++]=j+1;

        REP(i,n) if (a[i][j]!=-1){
            vector<pii> &tb=mx[i];
            int u=pos[i];
            if (u+1<tb.size() && tb[u].ST!=tb[u+1].ST){ 
                ++u;
                for (int x=u; x<tb.size() && tb[u].ST==tb[x].ST; ++x) if (!--cnt[tb[x].ND]) q.push(tb[x].ND);
            }
            ++pos[i];
        }


    }
    if (step!=m) puts("-1");
    else out(perm,m);

    return 0;
}

