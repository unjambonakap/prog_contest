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
vi e[maxn];
int rmp[maxn];
int n, m;
int par[maxn];

int root(int a){return par[a]<0?a:par[a]=root(par[a]);}
struct edge{
    int a, b, c;
    edge(int a, int b, int c):a(a), b(b), c(c){}
    bool operator<(const edge &e)const{
        if (c!=e.c) return c<e.c;
        return a!=e.a?a<e.a:b<e.b;
    }
};
char s[maxn];

int join(int a, int b){
    a=root(a); b=root(b);
    if (a==b) return 0;
    if (a<b) swap(a,b);
    par[b]+=par[a];
    par[a]=b;
    return 1;
}

int main(){
    int tn; cin>>tn;
    REP(ti, tn){
        cin>>n>>m;
        scanf("%s", s);
        int pos=1;
        REP(i, n) if (s[i]=='H') rmp[i]=pos++; else rmp[i]=0;
        n=pos;
        vector<edge> e;
        memset(par, -1, sizeof(int)*n);
        ll ans=0;
        REP(i, m){
            int a, b, c;
            scanf(" %d %d %d\n", &a, &b, &c);
            a=root(rmp[a-1]); b=root(rmp[b-1]);
            if (c<0){ 
                ans+=c;
                join(a,b);
            }else e.pb(edge(a,b,c));
        }
        sort(ALL(e));
        REP(i, e.size()){
            int a=root(e[i].a), b=root(e[i].b);
            if (join(a,b)) ans+=e[i].c;
        }
        cout<<ans<<endl;



    }
    return 0;
}


