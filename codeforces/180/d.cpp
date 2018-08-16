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

const int maxn=1111;
int w,h;
int a[maxn][maxn], b[maxn][maxn];
char buf[maxn];
char res[maxn][maxn];

int main(){
    int k;
    cin>>h>>w>>k;
    scanf(" %s",buf);
    int s=0;
    REP(i,w-1) s+=(a[0][i+1]=buf[i]=='N');

    REP(i,h-1){
        scanf(" %s",buf);
        REP(j,w) s+=(b[i+1][j]=buf[j]=='N');
        scanf(" %s",buf);
        REP(j,w-1) s+=(a[i+1][j+1]=buf[j]=='N');
    }
    int sw=0;
    if (h>w){
        REP(i,maxn) REP(j,maxn) swap(a[i][j],b[j][i]);
        swap(w,h);
        sw=1;
    }
    int tot=2*h*w-h-w;
    if (k==1){
        if (4*s>tot){puts("NO"); return 0;}
    }else{
        REP(i,w-1) res[0][i+1]=res[0][i]^a[0][i+1];
        FOR(i,1,h){
            if (w&1) res[i][0]=res[i-1][0]^b[i][0];
            for (int j=w&1; j<w; j+=2){
                int best=4;
                REP(x,2) REP(y,2){
                    int cost=(x^res[i-1][j]^b[i][j])+(y^res[i-1][j+1]^b[i][j+1])+(x^y^a[i][j+1]);
                    if (j) cost+=x^res[i][j-1]^a[i][j];
                    if (cost<best) best=cost, res[i][j]=x, res[i][j+1]=y;
                }
            }
        }
    }
    puts("YES");
    if (sw){
        swap(w,h);
        REP(i,maxn) REP(j,i) swap(res[i][j],res[j][i]);
    }
    REP(i,h) REP(j,w) printf("%d%c",res[i][j]+1," \n"[j==w-1]);

    return 0;
}

