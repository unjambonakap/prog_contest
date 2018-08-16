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

const int maxn=55;
int p, n;
int aa[maxn];
double dp[maxn][maxn][maxn][maxn];//last,num used, length, skip
int seen[maxn][maxn][maxn][maxn];


double go(int x, int a, int b, int c){
    if (x==n) return !a&&!b;
    if (a>n-x) return 0;
    if (c<0 || b<0) return 0;

    double &r=dp[x][a][b][c];
    if (seen[x][a][b][c]++) return r;
    r=0;
    double px=1.*a/(n-x);
    if (x==c) return r=(1-px)*go(x+1,a,b,c);
    r=px*go(x+1,a-1,b-aa[x],c)+(1-px)*go(x+1,a,b,c);
    return r;
}

int main(){
    cin>>n;
    int s=0;
    REP(i,n) scanf(" %d",aa+i), s+=aa[i];
    cin>>p;
    
    double res=0;
    if (s<=p) res=n;
    else{
        REP(i,n) REP(k,n) REP(j,p+1) if (aa[i]+j>p){
            res+=k*go(0,k,j,i)/(n-k);
        }
    }
    printf("%.10lf\n",res);
    return 0;
}

