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

const int maxn=222;
const int oo=1e9;

int dp[maxn][maxn][2];
int n[2],nx;
int At[2][maxn], Ad[2][maxn];

char buf[11];

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>nx;
        n[0]=n[1]=0;
        REP(i,nx){
            int t,d;
            scanf(" %s %d%d",buf,&t,&d);
            char c=buf[0]-'A';
            At[c][n[c]]=t; 
            Ad[c][n[c]]=d; ++n[c];
        }
        memset(dp,0x7f,sizeof(dp));
        dp[0][0][0]=dp[0][0][1]=0;
        REP(i,n[0]+1) REP(j,n[1]+1){
            int w=dp[i][j][1];
            int st=w-10,nd=w-10;
            FOR(k,i,n[0]){
                st=max(st+10,At[0][k]);
                nd=max(nd+10,st+Ad[0][k]);
                dp[k+1][j][0]=min(dp[k+1][j][0],nd);
            }
            w=dp[i][j][0];
            st=w-10; nd=w-10;
            FOR(k,j,n[1]){
                st=max(st+10,At[1][k]);
                nd=max(nd+10,st+Ad[1][k]);
                dp[i][k+1][1]=min(dp[i][k+1][1],nd);
            }
        }

        int res=min(dp[n[0]][n[1]][0],dp[n[0]][n[1]][1]);
        printf("%d\n",res);
    }
    return 0;
}

