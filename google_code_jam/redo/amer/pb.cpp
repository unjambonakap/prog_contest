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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}
const int maxn=1010;
const int mod=10007;
int s[maxn];
int n;
int ck[two(10)];

int solve(int *s, int n){
    if (n<=1) return -1;
    int sa=s[0];
    int sb=s[1];
    int fa=1, fb=1;
    for (int i=2; i<n; i+=2) if (s[i]!=sa){fa=0; break;}
    for (int i=3; i<n; i+=2) if (s[i]!=sb){fb=0; break;}
    if (!(fa^fb)) return -1;

    if (fa){
        if (n%2==0) return sa; 
        for (int i=1; i<n; i+=2) s[i/2]=s[i];
        return solve(s, n/2);
    }else{
        if (n%2) return sb;
        for (int i=0; i<n; i+=2) s[i/2]=s[i];
        return solve(s, ceil(n/2.));

    }





}


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        REP(i, n) cin>>s[i];

        int v;
        int last=s[n-1];
        REP(i, n-1) s[i]=(mod+s[i+1]-s[i])%mod;
        v=solve(s, n-1);

        printf("Case #%d: ", ti);
        if (v==-1) printf("UNKNOWN\n");
        else printf("%d\n", (last+v)%mod);
    }
    return 0;
}





