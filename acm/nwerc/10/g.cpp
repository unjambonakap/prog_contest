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

const int maxn=1111;
int a[maxn][maxn];
char buf[maxn];
int t[maxn][maxn];
int n,m;
int res[4*maxn];

int stk[maxn], stk2[maxn];
int h[maxn], px[maxn];

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>m;
        REP(i,n){
            scanf(" %s",buf);
            REP(j,m) a[n-i-1][m-j-1]=buf[j]=='#';
        }
        memset(t,0,sizeof(t));
        for (int i=n-1; i>=0; --i) REP(j,m) if (!a[i][j]) t[i][j]=t[i+1][j]+1;
        memset(res,0,sizeof(res));
        REP(i,n){
            int sz=0, sh=0;
            int add=0;
            h[sh]=0; px[sh]=m; ++sh;

            for (int j=m-1; j>=0; --j){
                if (a[i][j]){px[0]=j; sh=1; sz=0; add=0; continue;}
                add+=2;
                while(sh && h[sh-1]>=t[i][j]) --sh;
                assert(sh);
                int last=px[sh-1];
                h[sh]=t[i][j]; px[sh]=j; ++sh;

                int c=2*(last-j)+2*t[i][j];


                while(sz && stk[sz-1]>=t[i][j]) --sz;
                if (!sz || stk2[sz-1]+add<c){stk[sz]=t[i][j]; stk2[sz]=c-add; ++sz;}

                //printf("ON %d %d >> %d %d\n",i,j,stk[sz-1], stk2[sz-1]+add);
                ++res[stk2[sz-1]+add];
            }
        }

        REP(i,4*maxn) if (res[i]) printf("%d x %d\n",res[i],i);
    }
    return 0;
}

