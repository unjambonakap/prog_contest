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

const int maxn=1e6+10;
char s[maxn];
int n;
char is[256];
int has[maxn];

ll go(int n, int a){
    --a;
    return 1ll*(n-a)*(n-a+1)/2;
}

int main(){
    for (int i=0; i<5; ++i) is["aeiou"[i]]=1;
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %s",s);
        n=strlen(s);
        int m; scanf(" %d",&m);
        REP(i,n) s[i]=is[s[i]];


        ll res=0;

        memset(has,0,sizeof(has));
        REP(i,n) if (!s[i]){
            int j;
            for (j=i; j<n && !s[j]; ++j);
            if (j-i>=m) for (; i<j; ++i) has[i]=1;
            i=j-1;
        }

        REP(i,n) if (!has[i]){
            int j;
            for (j=i; j<n && !has[j]; ++j);
            int lb=i?i-m+1:i;
            int ub=j==n?j-1:j+m-2;
            ub-=lb-1;

            res+=go(ub,m);

            i=j-1;
        }
        res=go(n,m)-res;

        printf("Case #%d: ",ti+1);
        cout<<res<<endl;
    }

    return 0;
}

