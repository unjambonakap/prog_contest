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

const int maxn=505;
const int oo=1e8;
int n;
int dp[maxn][maxn];
int tb[maxn];
int seen[maxn];

int dp2[maxn];

int rank[maxn];
int ma[maxn], mb[maxn];


int go(int a, int b){
    if (a+1==b) return 0;
    assert(a<b);

    int &r=dp[a][b];
    if (r!=-1) return r;
    r=oo;
    FOR(i,a,b-1) go(a,i+1), go(i+1,b);

    memset(rank,0,sizeof(rank));

    FOR(i,a,b) rank[tb[i]]=1;
    ma[a]=oo;
    FOR(i,a,b) ma[i+1]=min(ma[i],tb[i]);
    mb[b]=oo;
    for (int i=b-1; i>=a; --i) mb[i]=min(mb[i+1],tb[i]);
    for (int i=maxn-2; i>=0; --i) rank[i]+=rank[i+1];

    FOR(i,a,b-1) r=min(r,go(a,i+1)+go(i+1,b)+rank[max(ma[i+1],mb[i+1])]);
    
    
    assert(r!=-1);
    return r;
}


int main(){
    while(cin>>n,!cin.eof()){
        REP(i,n) scanf(" %d",tb+i);
        memset(dp,-1,sizeof(dp));

        dp2[n]=0;
        REPV(i,n){
            memset(seen,0,sizeof(seen));
            int mx=0;
            int x=oo;

            FOR(j,i,n){
                if (seen[tb[j]]) break;
                seen[tb[j]]=1;
                mx=max(mx,tb[j]);
                if (mx==j-i+1) x=min(x,go(i,j+1)+dp2[j+1]);
            }
            dp2[i]=x;
        }

        int res=dp2[0];

        if (res==oo) printf("impossible\n");
        else printf("%d\n",res);
    }

    return 0;
}

