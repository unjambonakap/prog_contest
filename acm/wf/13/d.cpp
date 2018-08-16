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

const int maxv=64;
const ull oo=(1ull<<63)+10;
int isp[maxv];
ull cnk[maxv][maxv];
double cnk2[maxv][maxv];
vi e[maxv];
ull pw[maxv][maxv];


ull res;

void go(ull n, int have, int last, int pos, ull val){
    if (val>=res) return;
    if (have && n==1) res=min(res,val);

    while(!isp[pos]) ++pos;
    double lb=val;

    REP(i,e[have].size()){
        int x=e[have][i];
        if (x>last) break;
        if (!pw[pos][x] || 1.*pw[pos][x]*val>oo) break;
        if (n>=cnk2[have+x][x] && n%cnk[have+x][x]==0) go(n/cnk[have+x][x],have+x,x,pos+1,val*pw[pos][x]);
    }
}


int main(){
    ull n;
    REP(i,maxv) cnk[i][i]=cnk[i][0]=1;
    FOR(i,1,maxv) FOR(j,1,i) cnk[i][j]=cnk[i-1][j]+cnk[i-1][j-1];

    REP(i,maxv) cnk2[i][i]=cnk2[i][0]=1;
    FOR(i,1,maxv) FOR(j,1,i) cnk2[i][j]=cnk2[i-1][j]+cnk2[i-1][j-1];

    FOR(i,1,maxv){
        pw[i][0]=1;
        FOR(j,1,maxv){
            if (1.*pw[i][j-1]*i>oo) break;
            pw[i][j]=pw[i][j-1]*i;
        }
    }

    memset(isp,1,sizeof(isp));
    FOR(i,2,maxv) for (int j=i*i; j<maxv; j+=i) isp[j]=0;

    while(scanf(" %Lu",&n)>0){
        res=oo;

        REP(i,maxv) e[i].clear();
        REP(i,maxv) FOR(j,1,maxv-i) if (n>=cnk2[i+j][j] && n%cnk[i+j][j]==0) e[i].pb(j);

        go(n,0,maxv,2,1);

        printf("%Lu %Lu\n",n,res);
    }

    return 0;
}

