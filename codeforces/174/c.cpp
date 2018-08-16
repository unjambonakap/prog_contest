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


const int maxn=333;
const int maxv=1e5+10;
const int mod=1e9+7;

int next[maxn];
int n,q; ll t;
int in[maxn];
int a[maxn];

ll dp[maxv];

int main(){
    while(cin>>n>>q>>t){
        memset(in,0,sizeof(in));
        memset(next,-1,sizeof(next));

        REP(i,n) scanf(" %d",a+i);

        REP(i,q){
            int a, b; scanf(" %d%d",&a,&b);
            --a; --b;
            next[a]=b;
            in[b]=1;
        }
        if (q==n){puts("0"); continue;}
        REP(i,n) if (!in[i]){
            int s=0;
            int u=i;
            while(next[u]!=-1){
                t-=s;
                s=a[u]+=s;
                u=next[u];
                --q;
            }
            t-=s;
            a[u]+=s;
        }
        if (t<0 || q) puts("0");
        else{
            memset(dp,0,sizeof(dp));
            dp[0]=1;
            REP(i,n) REP(j,t+1) if (j+a[i]<=t) dp[j+a[i]]=(dp[j+a[i]]+dp[j])%mod;
            printf("%d\n",dp[t]);
        }

    }
    return 0;
}

