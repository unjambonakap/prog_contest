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

const int mod=1000200013;
const int maxn=2555;

int cnk[maxn][maxn];
int fact[maxn];

int n,m;
int aa[maxn*maxn];

int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};

int cnt[11];

set<vector<vi> > lst;
void dfs(vector<vi>& tb){
    if (lst.count(tb)) return;
    lst.insert(tb);
    int has=0;
    REP(i,n) REP(j,m) if (tb[i][j]!=0) ++has;
    ++cnt[has];
    if (0&&has==3){
        REP(i,n) out(tb[i]);
        puts("");
    }

    REP(i,n) REP(j,m) if (tb[i][j]!=0){
        REP(k,4){
            int nx=i+vx[k], ny=j+vy[k];
            if (nx>=0 && nx<n && ny>=0 && ny<m){
                vector<vi> tmp=tb;
                tmp[i][j]=0;
                tmp[nx][ny]=tb[i][j];
                dfs(tmp);
            }
        }
    }
}



int main(){
    REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
    FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

    fact[0]=1;
    FOR(i,1,maxn) fact[i]=1ll*fact[i-1]*i%mod;

    n=m=2;
    vector<vi> tb(n,vi(m));
    REP(i,n) REP(j,m) tb[i][j]=i*m+j+1;
    dfs(tb);
    //printf("%d\n",lst.size());
    //out(cnt,5);

    while(cin>>n>>m,!cin.eof()){
        if (n>m) swap(n,m);
        int res=0;
        if (n==1){
            REP(i,m) res=(res+1ll*cnk[m][i]*cnk[m][i])%mod;
        }else if (m==2){
            res=137;
            //REP(i,1){
            //    res=res+1ll*cnk[4][i]*cnk[4][i];
            //}
            //FOR(i,1,4) res=res+1ll*cnk[4][i]*fact[4-i]*cnk[4][4-i], cout<<res<<endl;
        }else{
            REP(i,n*m) res=(res+1ll*cnk[n*m][i]*fact[i]*cnk[n*m][i])%mod;
        }
        cout<<res<<endl;

    }

    return 0;
}

