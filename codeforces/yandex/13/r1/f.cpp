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
const int maxs=11111;
const int maxd=55;

const int oo=1e9;


int n,m,d;
int dp[maxs][maxn][maxn][2];
char s[maxs];
char s2[maxn][maxd];


int go(int a, int b, int p, int f){
    if (a==m) return p==d?0:oo;
    //if (a+d-p>m) return oo;
    int &r=dp[a][b][p][f];
    if (r!=-1) return r;
    r=oo;

    if (b==n){
        REP(i,n) REP(j,d) if ((f||j==0) && s[a]==s2[i][j]) r=min(r,go(a+1,i,j+1,f));
        ++r;
    }else{
        if (p==d) r=min(r,go(a,n,0,1));
        else r=min(r,go(a,n,0,0));
        if (p<d && s[a]==s2[b][p]) r=min(r,go(a+1,b,p+1,f|(p==d-1)));
    }

    return r;
}

int main(){
    while(cin>>n>>d,!cin.eof()){
        REP(i,n) scanf(" %s",s2+i);
        scanf(" %s",s);
        memset(dp,-1,sizeof(dp));

        m=strlen(s);
        REPV(i,m-d) go(i,n,0,0), go(i,n,0,1);
        int res=go(0,n,0,0);

        if (res<oo) printf("%d\n",res);
        else puts("NO");
    }

    return 0;
}

