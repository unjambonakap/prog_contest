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
#include<sys/resource.h>

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


const int maxn=222;
int n;
char s[maxn];
double dp[maxn][maxn]; 
double p[maxn][maxn];

double cnk[maxn][maxn];
double pw[maxn][maxn][maxn];

int seen[maxn][maxn];
void go(int a, int b);

double getp(int a, int b){
    if (!seen[a%n][b%n]) go(a,b);
    return p[a%n][b%n];
}

double gete(int a, int b){
    if (!seen[a%n][b%n]) go(a,b);
    return dp[a%n][b%n];
}


void go(int a, int b){
    if (a>=n) a-=n;
    if (b>=n) b-=n;
    if (seen[a][b]) return;
    seen[a][b]=1;
    double &re=dp[a][b];
    double &rp=p[a][b];

    if (a>b) b+=n;

    re=rp=0;
    int x=0;

    int tot=0;
    FOR(i,a,b) if (!s[i%n]) ++tot;

    FOR(i,a,b) if (!s[i%n]){
        int d=i-a;
        double p2=1.*(d+1)/(b-a+1);
        double px=getp(a,i)*getp(i+1,b)*p2;
        px*=cnk[tot-1][x]*pw[d+1][b-a+1][x]*pw[b-i][b-a+1][tot-x-1];

        rp+=px;
        re+=px*((n-d/2.)+gete(a,i)+gete(i+1,b));
        ++x;
    }

    if (!tot) rp=1, re=0;
    re/=rp;

}
int main(){
    int tn; cin>>tn;

    REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
    FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=cnk[i-1][j]+cnk[i-1][j-1];

    REP(i,maxn){
        FOR(j,1,maxn){
            double x=1.*i/j;
            pw[i][j][0]=1;
            FOR(k,1,maxn) pw[i][j][k]=pw[i][j][k-1]*x;
        }
    }

    REP(ti,tn){
        memset(seen,0,sizeof(seen));
        scanf(" %s",s);
        n=strlen(s);
        REP(i,n) s[i]=s[i]=='X';

        memset(seen,0,sizeof(seen));
        int fd=0;
        double res=0;
        REP(i,n) if (!s[i]) res+=getp(i+1,i)*gete(i+1,i), fd=1;
        if (fd) res+=(n+1)/2.;


        printf("Case #%d: ",ti+1);
        printf("%.15lf\n",res);

    }
    return 0;
}



