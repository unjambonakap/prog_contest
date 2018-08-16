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

const int maxn=1e5+10;
const int oo=1e9;

int k,n,maxb,t;
int a[maxn], b[maxn];
int dp[maxn], dp2[maxn];

int next[maxn];
int rmp[maxn];

int st[maxn];
int nd[maxn];

int ne;
int xx[maxn], last[maxn], prev[maxn];

int cmp(int u, int v){return a[u]!=a[v]?a[u]<a[v]:u<v;}

int main(){
    cin>>k>>n>>maxb>>t;
    REP(step,k){
        REP(i,n) scanf(" %d",a+i);
        memcpy(b,a,sizeof(b));
        sort(b,b+n);

        int ub=0;
        for (int i=0; i<n; ++i){
            int j=i;
            for (; j<n && b[i]==b[j]; ++j);
            rmp[b[i]]=ub++;
            i=j-1;
        }
        REP(i,n) a[i]=rmp[a[i]];
        memset(nd,-1,sizeof(nd));

        for (int i=n-1; i>=0; --i){
            st[a[i]]=i;
            nd[a[i]]=i;
            next[i]=nd[a[i]+1];
        }


        int res=0;
        int sz=sizeof(int)*ub;
        int UB=min(1ll*n*t,1ll*int(1e9));;
        memset(dp,0,sz);

        REP(i,ub){
            memset(dp2,-1,sizeof(dp2));

            memset(last,-1,sizeof(int)*n); ne=0;
            int aa=i?oo:0;
            REP(j,ub){
                dp2[j]=aa;
                if (aa<oo) xx[ne]=j, prev[ne]=last[aa%n], last[aa%n]=ne++;
                aa=min(aa,dp[j]);
            }

            memset(dp,0x7f,sz);
            memset(nd,-1,sz);
            int fd=0;

            for (int j=n-1; j>=0; --j){
                nd[a[j]]=j;
                for (int k=last[j]; k>=0; k=prev[k]){
                    int x=xx[k];
                    int pos=dp2[x];
                    pos-=j;
                    int uu=nd[x];
                    if (uu==-1) uu=st[x], pos+=n;
                    pos+=uu;
                    if (pos<UB) dp[x]=pos+1, fd=1;
                }
            }

            if (fd) res=i+1;
        }
        printf("%d\n",res);
    }
    return 0;
}

