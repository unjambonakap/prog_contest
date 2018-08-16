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
const int oo=1e9+10;
int a2[maxn], r2[maxn];
int a[maxn], r[maxn];
int perm[maxn], iperm[maxn];
int n;
int res[maxn];

int ub[maxn], lb[maxn];
int last[maxn];
int stk[maxn];
int ta[maxn], tb[maxn];
int N;
int u;
int ebp[maxn];

int cmp(int x, int y){return a2[x]<a2[y];}

void solve(){
    u=0;
    a[n]=2*oo;

    int m=0;
    N=0;
    REP(i,n+1){
        while(u>0 && ub[u]<a[i]){
            int p=tb[ebp[u]];

            do{
                res[stk[m]]=i-p;
            }while(stk[m--]!=last[u]);
            --u;
        }

        int nub=-oo;
        int j;
        for (j=u; j>0 && a[ta[ebp[j]]]>=a[i]-r[i]; --j) nub=max(nub,ub[j]);
        stk[++m]=i;

        if (j==u){
            //alone
            ++u;
            ub[u]=-oo; lb[u]=oo;
            last[u]=i;
            ta[N]=tb[N]=i; ebp[u]=N++;
        }else{
            //merge
            u=j+1;
            ub[u]=nub;
            N=ebp[u];
            ta[N++]=i;
        }
        lb[u]=min(lb[u],a[i]-r[i]);
        ub[u]=max(ub[u],a[i]+r[i]);
        for (j=N-1; j>=0; --j) if (a[ta[j]]<lb[u]) break;
        assert(j<N-1);

        ebp[u]=N=j+1;
        ta[N]=i;
        ++N;
    }
}

int main(){
    int ti=0;
    while(cin>>n,n){
        REP(i,n) scanf(" %d%d",a2+i,r2+i);
        REP(i,n) perm[i]=i;
        sort(perm,perm+n,cmp);

        REP(i,n) iperm[perm[i]]=i;
        REP(i,n) a[i]=a2[perm[i]];
        REP(i,n) r[i]=r2[perm[i]];


        solve();


        REP(i,n) printf("%d%c",res[iperm[i]]," \n"[i==n-1]);
    }
    return 0;
}

