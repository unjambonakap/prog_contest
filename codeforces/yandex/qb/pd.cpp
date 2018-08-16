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

const int maxn=1e3+10;
int n;
int a[maxn];
int f[maxn];

int solve(int p){
    if (p==n) return n&1?a[n-2]:0;
    int &r=f[p];
    if (r!=-1) return r;
    r=INT_MAX;

    int op;
    if (p&1) op=--p-1;
    else op=p;

    int d=0;
    FOR(i, p+1, n-1){
        checkmin(r, max(a[op], a[i])+d+solve(i+1));
        if ((i-p)%2==0) d+=max(a[i], a[i-1]);
    }
    if (n&1) checkmin(r, a[op]+d);
    

    assert(r!=INT_MAX);
    return r;
}
void build(int p){
    if (p==n){
        if (n&1) printf("%d\n", n-1);
        return;
    }
    int ans=f[p];
    int op;
    if (p&1) op=--p-1;
    else op=p;

    int d=0;
    FOR(i, p+1, n-1){
        if (ans==max(a[op], a[i])+d+solve(i+1)){
            for (int j=p+1; j<i-1; j+=2) printf("%d %d\n", j+1, j+2);
            printf("%d %d\n", op+1, i+1);
            build(i+1);
            return;
        }
        if ((i-p)%2==0) d+=max(a[i], a[i-1]);
    }
    assert(n&1);
    for (int j=p+1; j<n; j+=2) printf("%d %d\n", j+1, j+2);
    printf("%d\n", op+1);
}

int main(){

    cin>>n;
    REP(i, n) cin>>a[i];
    memset(f, -1, sizeof(f));
    int res=solve(0);
    printf("%d\n", res);
    build(0);

    return 0;
}


