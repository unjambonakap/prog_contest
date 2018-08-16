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

const int maxn=1111;

double p[maxn][maxn];
int n;
int a[maxn];

int main(){
    int m;
    cin>>n>>m;
    REP(i,n) scanf(" %d",a+i);
    REP(i,n) REP(j,i) p[j][i]=a[j]>a[i];

    REP(i,m){
        int x,y; scanf(" %d%d",&x,&y);
        --x; --y;
        if (x>y) swap(x,y);
        p[x][y]=0.5;
        REP(j,x){
            double aa=p[j][x], bb=p[j][y];
            p[j][x]=0.5*aa+0.5*bb;
            p[j][y]=0.5*aa+0.5*bb;
        }
        FOR(j,y+1,n){
            double aa=p[x][j], bb=p[y][j];
            p[x][j]=0.5*aa+0.5*bb;
            p[y][j]=0.5*aa+0.5*bb;

        }
        FOR(j,x+1,y){
            double aa=p[x][j], bb=p[j][y];
            p[x][j]=0.5*aa+0.5*(1-bb);
            p[j][y]=0.5*bb+0.5*(1-aa);
        }
    }


    double res=0;
    REP(i,n) REP(j,i) res+=p[j][i];
    printf("%.10lf\n",res);
    return 0;
}

