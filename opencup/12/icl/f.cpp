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

const int mod=1e9+7;
const int maxb=11111;
int p;
char s[2222];
int na, n;
int A[maxb];
int dp[maxb][2][2][2][2];


int main(){
    freopen("oranges.in", "r", stdin);
    freopen("oranges.out", "w", stdout);
    cin>>p; scanf(" %s", s); na=strlen(s);
    REP(i,na) s[i]-='0';

    n=0;
    while(1){
        ll v=0;
        REP(i,na) v=v*10+s[i], v%=p;
        A[n++]=v;
        v=0;
        REP(i,na){
            v=v*10+s[i];
            int x=v/p;
            s[i]=x;
            v-=1ll*x*p;
        }
        int fd=0; REP(i,na) if (s[i]){fd=1; break;}
        if (!fd) break;
    }
    memset(dp,0,sizeof(dp));
    dp[0][0][0][0][0]=1;
    REP(a,n+1) REP(fa,2) REP(fb,2) REP(fc,2) REP(d,2){

        for (int i=-1; i<=1; ++i) for (int j=-1; j<=1; ++j){
            if (fa&&i!=0) continue;
            if (fb&&j!=0) continue;
            int x=i+j-fc;
            if ((x-A[a])%p) continue;
            dp[a+1][fa|i==1][fb|j==1][x<0][d|i!=j]+=dp[a][fa][fb][fc][d];
            dp[a+1][fa|i==1][fb|j==1][x<0][d|i!=j]%=mod;
        }
    }
    printf("%Ld\n", (1ll*dp[n+1][1][1][0][1]*(mod+1)/2)%mod);
    return 0;
}



