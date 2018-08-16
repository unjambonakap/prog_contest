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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxr=30;
const int maxn=16;
const int nc=7;
int r, c;
int mp[maxr][maxr];
int id[maxr][maxr];

int graph[maxn][maxn];
int na[maxn];
int col[maxn];
int visited[maxn];
int used[nc+1][nc+1];
int cntc[nc];
int order[maxn];
int nx;
int res;
int build[maxn];


int vx[]={0, 1};
int vy[]={1, 0};
int solc[]={0, 1, 2, 3, 4, 0, 5, 2, 5, 6, 6, 1, 3, 4};
int n;

int geta(char c){
    if (c=='.') return -1;
    if (c>='a') return c-'a';
    return 26+c-'A';
}
void dfs(int a){
    if (visited[a]) return;
    visited[a]=1;
    order[nx++]=a;
    REP(i, na[a]) dfs(graph[a][i]);
}


inline void doit(int p){
    if (p==n){ if (res==0) memcpy(build, col, sizeof(build)); ++res; return;}

    
    

    int a=order[p];
    int can[nc];
    REP(i, nc) can[i]=cntc[i]<2 && (p!=0 || i==0) && (p!=1 || i==1) && (p!=2 || i==2);

    vi ne;
    REP(k, na[a]){
        int j=graph[a][k];
        if (j==a) REP(i, nc) can[i]&=!used[i][i];
        else if (col[j]!=-1) REP(i, nc) can[i]&=!used[i][col[j]];
    }

    REP(i, nc) if (can[i]){
        col[a]=i;
        ++cntc[i];
        int b;

        int ok=1;
        REP(j, na[a]) if ((b=col[graph[a][j]])!=-1){
            if (used[i][b]){ok=0; break;}
            used[i][b]=used[b][i]=1;
        }
        if (ok) doit(p+1);
        REP(j, na[a]) if ((b=col[graph[a][j]])!=-1) used[i][b]=used[b][i]=0;
        --cntc[i];
    }
    col[a]=-1;

}



int main(){
    cin>>r>>c;
    REP(i, r){
        string s; cin>>s;
        REP(j, c) mp[i][j]=geta(s[j]);
    }
    memset(id, -1, sizeof(id));
    n=0;
    REP(i, r) REP(j, c) if (id[i][j]==-1 && mp[i][j]>=0) id[i+1][j]=id[i+1][j+1]=id[i][j+1]=id[i][j]=n++;
    
    memset(na, 0, sizeof(na));
    REP(i, r) REP(j, c) if (mp[i][j]>=0) REP(k, 2){
        int x=i+vx[k], y=j+vy[k];
        if (mp[x][y]==mp[i][j]){
            int a=id[i][j], b=id[x][y];
            graph[a][na[a]++]=b; 
            if (a!=b) graph[b][na[b]++]=a;
        }
    }
    memset(visited, 0, sizeof(visited));
    nx=0;
    REP(i, n) if (!visited[i]) dfs(i);

    
    memset(col, -1, sizeof(col));
    memset(used, 0, sizeof(used));
    memset(cntc, 0, sizeof(cntc));
    res=0;
    doit(0);
    printf("%d\n", res*7*6*5);
    REP(i, r){

        REP(j, c){
            if (id[i][j]==-1) printf(".");
            else printf("%d", build[id[i][j]]);
        }
        printf("\n");

    }
    return 0;
}


