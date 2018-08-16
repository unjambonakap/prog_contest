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

const int ns=15;
const int n=27;

char mp[ns][ns+1];
int vx[]={1,-1,0,0,0,0};
int vy[]={0,0,1,-1,0,0};
int vz[]={0,0,0,0,1,-1};
int x[n],y[n];

char res[5][5][5];
int can[27];

int lx[]={0,1,1,1};
int ly[]={0,0,1,1};
int lz[]={0,0,0,1};
char wx[n];



void disp(){
    REP(i,3){
        REP(j,3){
            REP(k,3) printf("%c",res[i+1][j+1][k+1]);
            printf("%c"," \n"[j==2]);
        }
    }
}

int go(int a, int x, int y, int z, int d){
    x+=vx[d]; y+=vy[d]; z+=vz[d];
    char &r=res[x][y][z];
    if (r!=-1) return 0;
    r=wx[a];

    if (a==n-1) return 1;
    

    if (!can[a]){
        if (go(a+1,x,y,z,d)) return 1;
    }else{
        int st=(d|1)+1;
        REP(k,4){
            int nd=(st+k)%6;
            if (go(a+1,x,y,z,nd)) return 1;
        }
    }
    r=-1;
    return 0;
}



int main(){
    freopen("folding.in","r",stdin);
    freopen("folding.out","w",stdout);
    while(1){

        REP(i,ns) if (scanf(" %s",mp[i])<=0) return 0;
        REP(i,ns) REP(j,ns) if (mp[i][j]=='A') x[0]=i, y[0]=j;

            REP(i,n){
                char c=i/2;
                if (i&1) c+='a';
                else c+='A';
                wx[i]=c;
            }

        REP(i,n-1){
            REP(k,4){
                int nx=x[i]+vx[k], ny=y[i]+vy[k];
                if (nx>=0 && nx<ns && ny>=0&&ny<ns && mp[nx][ny]==wx[i+1]){ x[i+1]=nx; y[i+1]=ny; break; }
            }
        }
        FOR(i,1,n-1) if (x[i]-x[i-1]!=x[i+1]-x[i] || y[i]-y[i-1]!=y[i+1]-y[i]) can[i]=1;

        REP(i,5) REP(j,5) REP(k,5) res[i][j][k]=-2;
        REP(i,3) REP(j,3) REP(k,3) res[i+1][j+1][k+1]=-1;
        REP(i,4){
            int x=lx[i]+1, y=ly[i]+1, z=lz[i]+1;
            res[x][y][z]=wx[0];
            REP(d,6) if (go(1,x,y,z,d)) goto out;
            res[x][y][z]=-1;
        } 

        assert(0);
out:
        disp();

    }

    return 0;
}

