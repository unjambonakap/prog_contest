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
const int maxn=1111;
int pw2[maxn], pw8[maxn];
int cnk[maxn][maxn];
int A[maxn][maxn];
int isl[maxn];
int lst[maxn], nl;

char sa[maxn], sb[maxn];

int go(char *s, int n){
    int cnt=0;
    REP(i,n) cnt+=isl[s[i]];
    int px=0;
    int res=0;
    if (isl[cnt]) ++res;

    REPV(i,n){
        cnt-=isl[s[i]];
        REP(j,s[i]) REP(k,nl) if (cnt+isl[j]<=lst[k]){
            res=(res+A[px][lst[k]-cnt-isl[j]])%mod;
        }
        ++px;
    }
    return res;
}

int checkit(char *sa, int na, char *sb, int nb){
    int a=0, b=0;
    REP(i,na) a=a*10+sa[i];
    REP(i,nb) b=b*10+sb[i];
    int res=0;
    FOR(i,a,b+1){
        int p=i;
        int cnt=0;
        while(p) cnt+=isl[p%10], p/=10;
        if (isl[cnt]) ++res;
    }
    return res;
}

int main(){
    int tn; cin>>tn;
    pw2[0]=1; REP(i,maxn-1) pw2[i+1]=pw2[i]*2%mod;
    pw8[0]=1; REP(i,maxn-1) pw8[i+1]=pw8[i]*8ll%mod;

    FOR(i,1,maxn){
        int p=i;
        isl[i]=1;
        while(p){ if (p%10!=4&&p%10!=7){isl[i]=0; break;} p/=10; }
        if (isl[i]) lst[nl++]=i;
    }

    REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
    FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

    REP(i,maxn) REP(j,i+1) A[i][j]=1ll*cnk[i][j]*pw2[j]%mod*pw8[i-j]%mod;

    REP(ti,tn){
        scanf(" %s %s", sa,sb);
        int na=strlen(sa);
        int nb=strlen(sb);
        REP(i,na) sa[i]-='0';
        REP(i,nb) sb[i]-='0';
        int res=go(sb,nb)-go(sa,na);
        int cnt=0;
        REP(i,na) if (isl[sa[i]]) ++cnt;
        if (isl[cnt]) ++res;
        res=(mod+res)%mod;
        cout<<res<<endl;
    }
    return 0;
}


