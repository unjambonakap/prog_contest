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

short who[1<<26];
int res[11111];
int id[11111];
int nx;
int n, m;
char s[1111111];
char buf[33];


int a[33];


int main(){
    scanf(" %s", s);
    n=strlen(s);
    REP(i,n) s[i]-='a';
    cin>>m;
    nx=0;
    REP(i,m){
        scanf(" %s", buf);
        int x=strlen(buf);
        int u=0;
        REP(j,x) u|=1<<buf[j]-'a'; 
        if (!who[u]) who[u]=++nx;
        id[i]=who[u];
    }


    memset(a,-1,sizeof(a));
    for (int i=n-1; i>=0; --i){
        int st=26;
        REP(j,26) if (a[j]!=-1 && (a[j]&1<<s[i])){st=j; break;}
        REP(j,st-1) ++res[who[a[j]|1<<s[i]]];
        for (int j=st-1; j>=0; --j) a[j+1]=a[j]|1<<s[i];
        if (a[0]!=1<<s[i]) ++res[who[1<<s[i]]];
        a[0]=1<<s[i];
    }

    REP(i,m) printf("%d\n", res[id[i]]);
    return 0;
}


