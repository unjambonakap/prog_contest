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

const int maxn=1e8+10;

int tb[maxn];
int is[maxn];

int u[10];

int isp(ll x){
    int n=0;
    while(x) u[n++]=x%10, x/=10;
    REP(j,n/2) if (u[j]!=u[n-j-1]) return 0;
    return 1;
}


int main(){
    int tn; cin>>tn;
    
    FOR(i,1,maxn) is[i]=isp(i) && isp(1ll*i*i);
    
    REP(i,maxn) if (is[i]) printf(" %d >> %Ld\n",i,1ll*i*i);

    tb[0]=0;
    REP(i,maxn-1) tb[i+1]=tb[i]+is[i];
    REP(ti,tn){
        ll a,b; scanf(" %Ld%Ld",&a,&b);
        a=sqrt(a-1)+1, b=sqrt(b);

        int res=tb[b+1]-tb[a];

        printf("Case #%d: ",ti+1);
        printf("%d\n",res);
    }

    return 0;
}

