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

const int maxn=111111;
const int maxv=1e6;

ll a[maxn];
int n;
int cnt[maxv];

int dp[maxv];

int main(){
    while(scanf(" %d",&n)>0){
        REP(i,n) scanf(" %I64d",a+i);
        sort(a,a+n);

        memset(cnt,0,sizeof(cnt));
        int ub=1,lb=1;
        FOR(i,4,maxv){
            while(1ll*lb*lb*lb*lb<i) --cnt[dp[lb]], ++lb;
            while(1ll*ub*ub<=i) ++cnt[dp[ub]], ++ub;
            assert(lb<i);
            assert(ub<i);
            int pos=0;
            for (; cnt[pos]; ++pos);
            dp[i]=pos;
        }

        memset(cnt,0,sizeof(cnt));
        ub=1,lb=1;
        int res=0;
        REP(i,n) if (a[i]>3){
            int val=0;
            while(1ll*lb*lb*lb*lb<a[i]) --cnt[dp[lb]], ++lb;
            while(1ll*ub*ub<=a[i]) ++cnt[dp[ub]], ++ub;
            int pos=0;
            for (; cnt[pos]; ++pos);
            assert(pos<=1111);
            val=pos;
            res^=val;
        }

        puts(res?"Furlo":"Rublo");
    }
    return 0;
}

