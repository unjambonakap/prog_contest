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


const int maxn=1e5+10;
const int mod=1e9+7;

int a[maxn];
int n;

int faste(int a, int p){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}


int main(){
    cin>>n;
    REP(i,n) scanf(" %d",a+i);
    sort(a,a+n);
    int res=0;
    FOR(i,1,a[n-1]+1){
        int ub=sqrt(i);
        int sq=ub*ub==i;
        vi tb,tb2;
        FOR(j,1,ub+1) if (i%j==0){
            tb.pb(j);
            tb2.pb(i/j);
        }
        if (sq) tb2.pop_back();
        while(tb2.size()) tb.pb(tb2.back()), tb2.pop_back();

        int l=n;
        int ans=1;
        for (int j=tb.size()-1; j>=0; --j){
            int v=tb[j];
            int T=0, H=l-1;
            int nl=l;
            while(T<=H){
                int M=T+H>>1;
                if (a[M]>=v) H=M-1, nl=M;
                else T=M+1;
            }

            if (j==tb.size()-1) ans=(mod+faste(j+1,l-nl)-faste(j,l-nl))%mod;
            else ans=1ll*ans*faste(j+1,l-nl)%mod;
            l=nl;
        }
        res=(res+ans)%mod;
    }

    cout<<res<<endl;
    return 0;
}

