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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=310, maxk=20, mod=9901;

int ta[maxk], tb[maxk];
int n, k;
int fact[maxn];

int parent[maxn], seen[maxn];
int root(int a){return (parent[a]==-1?a:parent[a]=root(parent[a]));}


int solve(int m){
    memset(parent, -1, sizeof(parent));
    if (count_bit(m)>n) return 0;

    int cnt=n;
    memset(seen, 0, sizeof(seen));
    REP(i, k) if (m&two(i)){

        int a=ta[i], b=tb[i];
        ++seen[a]; ++seen[b];
        if (seen[a]>2 || seen[b]>2) return 0;
        if (root(a)==root(b)) return (cnt==1?1:0);
        
        parent[root(a)]=root(b);
        --cnt;
    }

    int cnta=0;
    memset(seen, 0, sizeof(seen));
    REP(i, n) if (root(i)!=i && !seen[root(i)]) ++cnta, seen[root(i)]=1;
    if (cnt==1) return 1;
    return fact[cnt-1]*two(cnta)%mod;



}

int main(){
    int ti, tn;

    fact[1]=4951;
    fact[2]=1;FOR(i, 3, maxn-1) fact[i]=(fact[i-1]*i)%mod;

    cin>>tn;
    REP(ti, tn){
        int res=0;
        cin>>n>>k;
        REP(i, k) cin>>ta[i]>>tb[i];
        REP(i, k) --ta[i], --tb[i];


        REP(i, two(k)) res=(res+mod+solve(i)*(count_bit(i)&1?-1:1))%mod;
        
        
        printf("Case #%d: %d\n", ti+1, res);

    }


}


