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

const int maxn=111;
const int rate=10;
const int inf=1e8;
int n, m; 
int F[maxn][maxn], C[maxn][maxn];
int H;
int vis[maxn][maxn];
int dist[maxn][maxn];

int vx[]={-1,0,1,0};
int vy[]={0,1,0,-1};
int in(int a, int b){return a>=0&&b>=0&&a<n&&b<m;}

struct state{
    int a, b, t;
    state(){}
    state(int a, int b, int t):a(a),b(b),t(t){}
    bool operator<(const state &s)const{ return t>s.t; }
};

int can(int a, int b, int c, int d, int H){
    int u=max(F[c][d],max(H,F[a][b]));
    if (u+50>C[c][d]) return 0;
    if (F[c][d]+50>C[a][b]) return 0;
    return 1;
}

int getl(int a, int b, int c, int d){ return C[c][d]-50; }

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>H>>n>>m;
        REP(i,n) REP(j,m) scanf(" %d", C[i]+j);
        REP(i,n) REP(j,m) scanf(" %d", F[i]+j);

        memset(vis,0,sizeof(vis));
        queue<state> qa;
        qa.push(state(0,0,0));
        vis[0][0]=1;
        while(!qa.empty()){
            state s=qa.front(); qa.pop();
            REP(k,4){
                int x=s.a+vx[k], y=s.b+vy[k];
                if (in(x,y) && can(s.a,s.b,x,y,H) && !vis[x][y])  vis[x][y]=1, qa.push(state(x,y,0));
            }
        }


        double res;
        priority_queue<state> q;
        REP(i,n) REP(j,m) if (vis[i][j]) q.push(state(i,j,0));

        REP(i,n) REP(j,m) dist[i][j]=inf;

        while(!q.empty()){
            state s=q.top(); q.pop();
            if (s.a==n-1 && s.b==m-1){res=s.t; break;}
            if (s.t>dist[s.a][s.b]) continue;

            REP(k,4){
                int x=s.a+vx[k], y=s.b+vy[k];
                if (in(x,y)){
                    int nt=max(s.t,H-getl(s.a,s.b,x,y));
                    if (!can(s.a,s.b,x,y,H-nt)) continue;

                    if (H-nt>=20+F[s.a][s.b]) nt+=10;
                    else nt+=100;
                    if (nt<dist[x][y]) dist[x][y]=nt, q.push(state(x,y,nt));
                }
            }
        }

        printf("Case #%d: %.1lf\n", ti+1, res/rate);

    }
    return 0;
}




