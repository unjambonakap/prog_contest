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
int a[maxn], b[maxn];
int id[maxn], idb[maxn];

int cmp(int u, int v){return a[u]<a[v];}
int cmpb(int u, int v){return b[u]<b[v];}

int main(){
    int n,m,x,y; cin>>n>>m>>x>>y;
    REP(i,n) scanf(" %d", a+i);
    REP(i,m) scanf(" %d", b+i);
    REP(i,n) id[i]=i;
    REP(i,m) idb[i]=i;
    sort(id,id+n,cmp);
    sort(idb,idb+m,cmpb);

    int j=0;
    vector<pii> res;
    REP(i,n){
        int p=a[id[i]];
        while(j<m && b[idb[j]]<p-x) ++j;
        if (j<m && b[idb[j]]<=p+y) res.pb(MP(id[i],idb[j])), ++j;
    }

    printf("%d\n", res.size());
    REP(i,res.size()) printf("%d %d\n", res[i].ST+1, res[i].ND+1);
    return 0;
}


