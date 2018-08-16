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


const int maxn=35;
int mp[maxn][maxn];
int n, m;
set<pii> f;
int parent[maxn*maxn];
int dist[maxn][maxn];
int visited[maxn][maxn];

int vx[]={0, 0, 1, -1};
int vy[]={-1, 1, 0, 0};

struct state{
    int x, y;
    int c;
    state(int x, int y, int c):x(x), y(y), c(c){}
    bool operator<(const state &s)const{return c>s.c;}

};

int in(int x, int y){return x>=0 && y>=0 && x<n && y<m;}

int solve(){

    f.erase(MP(0, 0));
    vector<pii> fa;
    fa.pb(MP(0, 0));
    memset(visited, 0, sizeof(visited));
    visited[0][0]=1;
    int ans=0;

    while(!f.empty()){

        priority_queue<state> q;
        memset(dist, -1, sizeof(dist));
        FE(it, fa) q.push(state(it->ST, it->ND, 0)), dist[it->ST][it->ND]=0, parent[it->ST*m+it->ND]=-1;
        while(!q.empty()){
            state s=q.top(); q.pop();
            if (dist[s.x][s.y]!=s.c) continue;
            if (f.count(MP(s.x, s.y))){
                pii pa=MP(s.x, s.y);
                fa.pb(pa);
                f.erase(pa);
                int p=s.x*m+s.y;
                int d=s.c;
                while(parent[p]!=-1){
                    if (!visited[p/m][p%m]){
                        ans+=d;
                        visited[p/m][p%m]=1;
                    }
                    --d;
                    p=parent[p];
                }
                break;
            }
            REP(k, 4){
                int nx=s.x+vx[k], ny=s.y+vy[k];
                if (in(nx, ny) && mp[nx][ny] && (dist[nx][ny]==-1 || dist[nx][ny]>s.c+1)){
                    dist[nx][ny]=s.c+1;
                    parent[nx*m+ny]=s.x*m+s.y;
                    q.push(state(nx, ny, s.c+1));
                }
            }
        }
    }

    priority_queue<state> q;
    memset(dist, -1, sizeof(dist));
    FE(it, fa) q.push(state(it->ST, it->ND, 0)), dist[it->ST][it->ND]=0;
    while(!q.empty()){
        state s=q.top(); q.pop();
        if (dist[s.x][s.y]!=s.c) continue;
        if (!visited[s.x][s.y]) ans+=s.c;

        REP(k, 4){
            int nx=s.x+vx[k], ny=s.y+vy[k];
            if (in(nx, ny) && mp[nx][ny] && (dist[nx][ny]==-1 || dist[nx][ny]>s.c+1)){
                dist[nx][ny]=s.c+1;
                parent[nx*m+ny]=s.x*m+s.y;
                q.push(state(nx, ny, s.c+1));
            }
        }
    }



    return ans;

}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n>>m;
        f.clear();
        REP(i, n){ 
            string s;
            cin>>s;
            REP(j, m){
                if (s[j]=='T') s[j]='#', f.insert(MP(i, j));
                mp[i][j]=s[j]=='#';
            }
        }
        printf("Case #%d: %d\n", ti, solve());

    }

    return 0;
}



