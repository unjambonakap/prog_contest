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

const int inf=1e9;
const int maxn=1111;

int n, r;
vi e[maxn];
int c[maxn];
int u[maxn][maxn];
int dp[maxn][maxn];
int now;

vi A,B;
vi tmp;
int RES;


int go2(int a, int b){
    if (a==A.size() && b==B.size()) return 0;
    if (u[a][b]==now) return dp[a][b];
    u[a][b]=now;
    int &r=dp[a][b];
    r=inf;
    if (a<A.size()) r=min(r,c[A[a]]*(a+b+1)+go2(a+1,b));
    if (b<B.size()) r=min(r,c[B[b]]*(a+b+1)+go2(a,b+1));
    return r;
}

void build(int a, int b){
    if (a==A.size() && b==B.size()) return;
    int best=go2(a,b);
    if (a<A.size() && c[A[a]]*(a+b+1)+go2(a+1,b)==best)tmp.pb(A[a]), build(a+1,b);
    else tmp.pb(B[b]), build(a,b+1);
}



vi go(int a, int p=-1){
    vector<vi> lst;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b!=p) lst.pb(go(b,a));
    }
    A.clear();
    REP(i,lst.size()){
        B=lst[i];
        ++now;
        tmp.clear();
        build(0,0);
        RES=go2(0,0);
        A=tmp;
    }
    A.insert(A.begin(),a);
    return A;
}

int main(){
    while(cin>>n>>r,n){
        REP(i,n) e[i].clear();
        int s=0;
        REP(i,n) scanf(" %d", c+i), s+=c[i];
        REP(i,n-1){
            int a, b; scanf(" %d%d", &a,&b);
            --a; --b;
            e[a].pb(b); e[b].pb(a);
        }
        now=0;
        memset(u,0,sizeof(u));

        go(r-1);
        cout<<RES+s<<endl;



    }
    return 0;
}



