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

const int n=44;
int g[n][n];
int da[n], db[n];
char s[1111];
int vis[n];
int na;

int leet(char c, int f){
    if (!f) return c-'a'+10;
    if (c=='o') return 0;
    if (c=='i') return 1;
    if (c=='e') return 3;
    if (c=='a') return 4;
    if (c=='s') return 5;
    if (c=='t') return 7;
    if (c=='b') return 8;
    if (c=='g') return 9;
    return c-'a'+10;
}


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        memset(g,0,sizeof(g));
        int tmp; cin>>tmp;
        scanf(" %s", s);
        na=strlen(s);
        memset(g,0,sizeof(g));
        REP(i,na-1) REP(f,4) g[leet(s[i],f&1)][leet(s[i+1],f&2)]=1;
        int res=1;
        memset(da,0,sizeof(da));
        memset(db,0,sizeof(db));
        int res2=0;
        REP(i,n) REP(j,n) res+=g[i][j], da[i]+=g[i][j], db[j]+=g[i][j];
        REP(i,n) res2+=fabs(da[i]-db[i]);
        if (res2>=2) res2-=2;
        res+=res2/2;

        printf("Case #%d: %d\n", ti+1,res);
    }
    return 0;
}


