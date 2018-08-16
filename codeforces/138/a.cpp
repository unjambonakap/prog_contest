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
char s[maxn];
char os[maxn];
int n;
const char *rmp="([)]";

int dp[maxn];
int match[maxn];


int main(){
    scanf(" %s", s);
    memcpy(os,s,sizeof(s));
    n=strlen(s);
    REP(i,n) REP(j,4) if (rmp[j]==s[i]) s[i]=j;
    memset(match,-1,sizeof(match));
    vi stk;
    REP(i,n){
        if (s[i]<2) stk.pb(i);
        else{
            if (!stk.size()) continue;
            int a=stk.back();
            stk.pop_back();
            if (s[i]!=(s[a]^2)) stk.clear();
            else match[i]=a, match[a]=i;
        }
    }
    pii best=MP(0,n);
    for (int i=n-1; i>=0; --i) if (s[i]<2 && match[i]!=-1){
        if (s[i]&1) ++dp[i];
        dp[i]+=dp[match[i]+1]+dp[i+1];
        best=max(best,MP(dp[i],i));
    }
    cout<<best.ST<<endl;
    int a=best.ND, b=a;
    while(match[b]!=-1 && dp[b]>0) b=match[b]+1;
    FOR(i,a,b) printf("%c",os[i]); puts("");
    return 0;
}

