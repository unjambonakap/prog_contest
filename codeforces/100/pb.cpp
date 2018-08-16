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

const int maxn=333;
int n;

int x[maxn];
int pref[maxn][maxn];
int res[maxn];
int send[maxn];
int sec[maxn];

int can(int a, int b){
    int u=-1, v=-1;
    if (a==b) return 0;
    REP(i, n){
        if (u==-1 || x[u]>x[i]) v=u, u=i;
        else if (v==-1 || x[v]>x[i]) v=i;
        if (u==b || (u==a && b==v)){res[a]=i+1; return 1;}
    }
    return 0;


}

int main(){
    cin>>n;
    REP(i, n){
        vi a(n);
        REP(j, n) cin>>a[j], pref[i][a[j]-1]=j;
    }
    vi a(n);
    REP(i, n) cin>>a[i], x[a[i]-1]=i;

    REP(i, n){
        int best=-1;
        REP(j, n) if ((best==-1 || pref[i][best]>pref[i][j]) && can(i, j)) best=j;
    }
    out(res, n);
    return 0;
}


