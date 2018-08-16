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

const int mod=1e6+3;
int main(){
    int n,m; 
    cin>>n>>m;
    getchar();

    vector<string> tb(n);
    int res=1;
    REP(i,n){
        cin>>tb[i];
        REP(j,m) if (tb[i][j]=='3') ++tb[i][j]; else if (tb[i][j]=='4') --tb[i][j];
        int fd=0;
        int prev=-1;
        REP(j,m){
            if (tb[i][j]!='.'){
                int val=tb[i][j]-'1'&2;
                if (!fd) prev=val;
                else if (val!=prev) res=0;
                
                fd=1;
            }
            prev^=2;
        }
        if (!fd) res=res*2%mod;
    }

    REP(i,m){
        int fd=0;
        int prev=-1;
        REP(j,n){
            if (tb[j][i]!='.'){
                int val=tb[j][i]-'1'&1;
                if (!fd) prev=val;
                else if (val!=prev) res=0;
                
                fd=1;
            }
            prev^=1;
        }
        if (!fd) res=res*2%mod;
    }

    printf("%d\n", res);
    return 0;
}

