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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int nx=10000;
const int maxv=20;
const double eps=1e-8;
double mem[nx][maxv];
int visited[nx][maxv];

int m, v, a;
int z;

double proc(int x, int y){
    if (y>=v) return 1.;
    if (y<=0) return 0.;
    if (x>=nx) return 0.;
    double &r=mem[x][y];
    if (visited[x][y]) return r;
    visited[x][y]=1;
    r=0.;
    FOR(i, 1, min(m, y)){
        double b=0.;
        double p=0.5;
        int j=i;
        for (; j<=m; j*=2, p*=0.5){
            b+=p*proc(x+1, y+i);
            double ans=b+p*proc(x+1, y-2*j+i);
            if (ans>=r-eps){ r=ans; if (x==0) z=i; }
        }
    }
    return r;

    

}
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>a>>m>>v;
        memset(visited, 0, sizeof(visited));
        double res=proc(0, a);
        printf("Case #%d: %.10lf %d\n", ti, res, z);
    }
    return 0;
}
