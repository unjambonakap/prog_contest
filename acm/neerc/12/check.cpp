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

const int maxn=1555;
int r,c;
int A[maxn][maxn];
char buf[maxn];
int vis[maxn][maxn];
int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};

int in(int a, int b){return a>=0&&b>=0&&a<r&&b<c;}
void bfs(){
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(0);
    while(q.size()){
        int a=q.front(); q.pop();
        int x=a%r, y=a/r;
        REP(k,4){
            int nx=x+vx[k],ny=y+vy[k];
            if (in(nx,ny) && !A[nx][ny] && !vis[nx][ny]) vis[nx][ny]=1, q.push(nx+ny*r);
        }
    }
}



int main(int argc, char **argv){
    if (argc<4){fprintf(stderr,"need 3 args\n"); return 1;}
    FILE *fa=fopen(argv[2],"r"), *fb=fopen(argv[3],"r");
    freopen(argv[1],"r",stdin);
    assert(fa); assert(fb);

    cerr<<argv[2]<<endl;
    cin>>c>>r;
    REP(i,r){
        scanf(" %s",buf);
        REP(j,c) A[i][j]=buf[j]=='#';
    }

    int sa,sb;
    int aa,bb;
    aa=fscanf(fa," %d",&sa);
    bb=fscanf(fb," %d",&sb);
    if (aa!=bb){
        fprintf(stderr,"diff result >> %d %d\n",aa,bb);
        return 1;
    }
    if (aa>0 && bb>0){
        if (sa!=sb){
            fprintf(stderr,"err size >> %d %d\n",sa,sb);
            return 1;
        }
        int x,y;
        fscanf(fa," %d%d",&y,&x);
        fprintf(stderr, "REQDING %d %d %d\n",sa,x,y);
        --y; --x;
        REP(i,sa) REP(j,sa) assert(!A[x+i][y+j]);
        REP(i,sa) REP(j,sa) A[x+i][y+j]=1;
        bfs();
        assert(!A[r-1][c-1]);
        assert(!A[0][0]);
        assert(!vis[r-1][c-1]);

    }
    return 0;
}

