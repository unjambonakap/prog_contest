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

int a[12];
int n;
map<ll,int> mem[12][13];
ll px[13];
ll H;

ll geth(){
    ll h=0;
    REPV(i, n) h=43*h+a[i];
    return h;
}

int solve(int x, int y){
    if (H==0) return y;
    if (y==13) return 13;
    if (x>=y) return solve(0,y+1);
    if (mem[x][y].count(H)) return mem[x][y][H];
    int res=13;
    int fd=0;
    ll oh=H;
    REP(i, y) if (a[i] && x+i+1<=y){
        --a[i];
        H-=px[i];
        fd=1;
        checkmin(res, solve(x+i+2, y));
        H=oh;
        ++a[i];
    }
    if (!fd) res=solve(0,y+1);
    return mem[x][y][H]=res;
}



int main(){
    px[0]=1;
    REP(i, 12) px[i+1]=43*px[i];


    cin>>n;
    REP(i,n) cin>>a[i];
    H=geth();
    int res=solve(0,1);
    
    if (res>=13) printf("impossible\n");
    else cout<<res<<endl;
    return 0;
}

