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

const int maxn=100001;
int isp[maxn];
int dc[maxn][5];

int m[5];
int pw[6];
int nxt[maxn];
int cntb[maxn];

int go(int n){
    if (!n) return cntb[m[n]];
    int st=m[n];
    int p=nxt[st];
    st+=pw[n+1];
    int res=0;
    while(p<st){
        REP(j,n) m[j]+=dc[p][j]*pw[n];
        res+=go(n-1);
        REP(j,n) m[j]-=dc[p][j]*pw[n];
        p=nxt[p];
    }
    return res;
}

int main(){
    memset(isp,1,sizeof(isp));
    isp[1]=isp[0]=0;
    FOR(i,2,maxn) if (isp[i]){for (ll j=1ll*i*i; j<maxn; j+=i) isp[j]=0; }
    REP(i,maxn) if (isp[i]){
        int x=i, j=0;
        while(x) dc[i][j++]=x%10, x/=10;
    }
    nxt[maxn-1]=maxn-1;
    for (int i=maxn-2; i>=0; --i){
        if (isp[i+1]) nxt[i]=i+1;
        else nxt[i]=nxt[i+1];
    }
    REP(i,maxn/10){
        int u=0;
        REP(j,10) if (isp[i*10+j]) ++u;
        cntb[i*10]=u;
    }


    pw[0]=1;
    REP(i,5) pw[i+1]=pw[i]*10;

    int tn; cin>>tn;
    REP(ti,tn){
        int p; cin>>p;
        int nd=0, x=p;
        while(x) ++nd, x/=10;
        REP(i,nd-1) m[i]=pw[nd-1]*dc[p][i];
        cout<<go(nd-2)<<endl;
    }


    return 0;
}

