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
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<""; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=two(10);
char mp[maxn][maxn];
int parent[maxn*maxn];
int c[maxn*maxn];

int root(int a){return parent[a]==-1?a:parent[a]=root(parent[a]);}
int vx[]={-1, 0, 1, 0}, vy[]={0, 1, 0, -1};
int main(){
    int n, m;
    cin>>n>>m;
    char mp[n][m];
    REP(i, n){
        string s; cin>>s;
        REP(j, m) mp[i][j]=s[j];
    }
    memset(parent, -1, sizeof(parent));
    int c=0;
    REP(i, n) REP(j, m-1) if (mp[i][j]=='.' && mp[i][j+1]=='.') mp[i][j]=mp[i][j+1]='0'+i%4+c*4, parent[i*maxn+j+1]=i*maxn+j, ++j, c^=1;
    REP(j, m) REP(i, n-1) if (mp[i][j]=='.' && mp[i+1][j]=='.') mp[i][j]=mp[i+1][j]='8'+c, parent[i*maxn+maxn+j]=i*maxn+j, ++i, c^=1;
    int ok=1;
    REP(i, n) REP(j, m) if (mp[i][j]=='.'){

        ok=0;
        REP(k, 4){
            int ni=i+vx[k], nj=j+vy[k];
            if (ni>=0 && nj>=0 && ni<n && nj<m && mp[ni][nj]!='#'){
                mp[i][j]=mp[ni][nj];
                parent[i*maxn+j]=ni*maxn+nj;
                ok=1;
                break;
            }
        }
        if (!ok) goto out;
    }
out:
    if (!ok) printf("-1\n");
    else REP(i, n) out(mp[i], m);
    return 0;
}

