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

const int maxa=12;
const int maxn=111111;
int fa[maxa][maxa];
double fb[maxa][maxa];

double x[maxn], y[maxn];
int n;

int main(){
    while(scanf(" %d",&n)>0){

        memset(fa,0,sizeof(fa));
        memset(fb,0,sizeof(fb));

        REP(i,n){
            scanf(" %lf%lf",x+i,y+i);
            int xx=x[i], yy=y[i];
            ++fa[xx][yy];
            fb[xx][yy]+=x[i]+y[i];
        }
        for (int i=10; i>=0; --i) for (int j=10; j>=0; --j){
            fa[i][j]+=fa[i+1][j]+fa[i][j+1]-fa[i+1][j+1];
            fb[i][j]+=fb[i+1][j]+fb[i][j+1]-fb[i+1][j+1];
        }
        double res=0;
        ll have=0;
        REP(i,n){
            int xx=x[i]+1, yy=y[i]+1;
            int u=fa[xx][yy];
            have+=u;
            res+=fb[xx][yy]-(x[i]+y[i])*u;
        }
        printf("%.8lf\n",res/have);

    }
    return 0;
}


