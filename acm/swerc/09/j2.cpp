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

const int maxn=44444;
const int mod=1e9+7;
const int px=53;

char s[maxn];
int h[maxn];
int n,K;
int tb[maxn];
int pw[maxn];
int st;
int perm[maxn];


int checkit(int a){

    int nx=n-a+1;
    REP(i,nx) tb[i]=(mod+h[a+i]-1ll*h[i]*pw[a]%mod)%mod;
    sort(tb,tb+nx);
    for (int i=0; i<nx;){
        int j;
        for (j=i; j<nx && tb[i]==tb[j]; ++j);
        if (j-i>=K) return 1;
        i=j;
    }
    return 0;

}


int cmp(int a, int b){return tb[a]<tb[b];}
int checkit2(int a){

    int nx=n-a+1;
    REP(i,nx) tb[i]=(mod+h[a+i]-1ll*h[i]*pw[a]%mod)%mod;
    REP(i,nx) perm[i]=i;
    sort(perm,perm+nx,cmp);

    int res=0;
    for (int i=0; i<nx;){
        int j;
        int xp=0;
        for (j=i; j<nx && tb[perm[i]]==tb[perm[j]]; ++j) xp=max(xp,perm[j]);
        if (j-i>=K) res=max(res,xp);
        i=j;
    }
    return res;
}

int main(){
    pw[0]=1;
    REP(i,maxn-1) pw[i+1]=1ll*pw[i]*px%mod;

    while(scanf(" %d",&K),K){
        scanf(" %s",s);
        n=strlen(s);

        h[0]=0;
        REP(i,n) h[i+1]=(1ll*h[i]*px+s[i]-'a'+1)%mod;

        int T=0,H=n, best=0;
        while(T<=H){
            int M=T+H>>1;
            if (checkit(M)) T=M+1, best=M;
            else H=M-1;
        }
        if (!best) puts("none");
        else{
            int uu=checkit2(best);

            printf("%d %d\n",best,uu);
        }
    }
    return 0;
}

