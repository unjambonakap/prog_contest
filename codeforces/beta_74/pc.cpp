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
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=5002;
map<int, int> mp[maxn];
int n, m;
int p;
int d[maxn];
int next[maxn][4];
int nx[maxn][4];

int vx[]={-1, 0, 1, 0};
int vy[]={0, 1, 0, -1};
char dx[]={'U', 'R', 'D', 'L'};
map<char, int> mpd;
int dummy;
int main(){
    cin>>n>>m;
    REP(i, 4) mpd[dx[i]]=i;
    getchar();

    p=0;
    REP(i, n){
        string s; cin>>s;
        REP(j, m) if (s[j]!='.'){
            d[p]=mpd[s[j]];
            mp[i][j]=p;
            ++p;
        }
    }
    dummy=n*m;

    for (int k=0; k<4; k+=2){
        int ik=k^2;
        REP(j, m){
            int a=dummy;
            for (int i=(vx[k]>0?0:n-1); i>=0 && i<n; i+=vx[k]) if (mp[i].count(j)){
                int na=mp[i][j];
                next[a][k]=na;
                a=na;
            }
            next[a][k]=dummy;
        }
    }
    for (int k=1; k<4; k+=2){
        int ik=k^2;
        REP(i, n){
            int a=dummy;
            for (int j=(vy[k]>0?0:m-1); j>=0 && j<m; j+=vy[k]) if (mp[i].count(j)){
                int na=mp[i][j];
                next[a][k]=na;
                a=na;
            }
            next[a][k]=dummy;
        }
    }
    int ans, nc;
    ans=0, nc=0;
    REP(i, p){
        memcpy(nx, next, sizeof(next));
        int a=i;
        int res=0;
        while(a!=dummy){
            int na=nx[a][d[a]];
            REP(k, 4){
                nx[nx[a][k^2]][k]=nx[a][k];
                nx[nx[a][k]][k^2]=nx[a][k^2];
            }
            a=na;
            ++res;

        }

        if (res>ans) ans=res, nc=0;
        if (res==ans) ++nc;

    }
    printf("%d %d\n", ans, nc);
    return 0;



}
