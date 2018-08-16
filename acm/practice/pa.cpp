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

const int maxn=1001;
int mp[maxn][maxn];
int dp[maxn][maxn];
int vis[maxn][maxn];
int n;
int vx[]={1,0,-1,0};
int vy[]={0,1,0,-1};



int go(){

    queue<pii> q;
    q.push(MP(0,0));
    while(!q.empty()){
        int a=q.front().ST, b=q.front().ND;
        q.pop();
        if (a==n-1 && b==n-1) return 1;
        REP(k, 2){
            int nx=a+vx[k], ny=b+vy[k];
            if (nx>=0 && ny>=0 && nx<n && ny<n && !mp[nx][ny] && !vis[nx][ny]){vis[nx][ny]=1; q.push(MP(nx,ny)); }
        }

    }
    return 0;

}

int gob(){ 

    queue<pii> q;
    q.push(MP(0,0));
    while(!q.empty()){
        int a=q.front().ST, b=q.front().ND;
        q.pop();
        if (a==n-1 && b==n-1) return 1;
        REP(k, 4){
            int nx=a+vx[k], ny=b+vy[k];
            if (nx>=0 && ny>=0 && nx<n && ny<n && !mp[nx][ny] && !vis[nx][ny]){vis[nx][ny]=1; q.push(MP(nx,ny)); }
        }

    }
    return 0;
}

int main(){
    cin>>n;
    getchar();
    int mod=INT_MAX;
    assert(n<maxn);
    REP(i, n){
        string s; cin>>s;
        assert(s.size()==n);
        REP(j, n) mp[i][j]=s[j]=='#';
    }
    assert(n<maxn);
    memset(vis,0,sizeof(vis));
    if (!go()){
        memset(vis,0,sizeof(vis));
        if (!gob()) cout<<"INCONCEIVABLE"<<endl;
        else cout<<"THE GAME IS A LIE"<<endl;
        return 0;
    }
    assert(n<maxn);

    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    REP(i,n) REP(j,n) if (dp[i][j]){
        if (j<n-1 && !mp[i][j+1]) dp[i][j+1]=(1ll*dp[i][j+1]+dp[i][j])%mod;
        if (i<n-1 && !mp[i+1][j]) dp[i+1][j]=dp[i][j];
    }
    assert(n<maxn);
    cout<<dp[n-1][n-1]<<endl;


    return 0;
}

