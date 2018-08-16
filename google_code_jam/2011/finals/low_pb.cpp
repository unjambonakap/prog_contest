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

const int maxr=21;
const int maxn=maxr*maxr;;
int r, c, n;
int vx[]={-1, 0, 1, 0}, vy[]={0, 1, 0, -1};

ll m;
int next[maxn][4];
ll mp[maxn];
ll wl[maxn];
int ne;
int el[4*maxr-4];
int visited[maxn];


int in(int x, int y){return x>=0 && y>=0 && x<r && y<c;}

int doit(){
    
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
    memset(visited, 0, sizeof(visited));
    memset(wl, -1, sizeof(wl));
    visited[n]=1; wl[n]=0;

    REP(i, ne) q.push(MP(wl[el[i]]=mp[el[i]], el[i])), visited[el[i]]=1;

    while(!q.empty()){
        pii pa=q.top(); q.pop();
        int p=pa.ND;
        visited[p]=1;
        if (mp[p]>pa.ST){
            q.push(MP(wl[p]=mp[p], p));
            continue;
        }

        REP(k, 4){
            int a=next[p][k];
            if (!visited[a] && (wl[a]==-1 || wl[a]>wl[p])) q.push(MP(wl[a]=wl[p], a));
        }
    }
    int fd=0;
    printf("<< map level (%Ld\n", m);
    REP(i, r){
        REP(j, c) printf("%Ld\t", mp[i*c+j]);
        printf("\n");
    }
    printf("xx %d %d\n", fd, n);
    REP(i, r){
        REP(j, c) printf("%Ld\t", wl[i*c+j]);
        printf("\n");
    }
    printf("\n\n");
    sleep(1);

    REP(i, n){
        ll v=wl[i];
        REP(k, 4) checkmin(v, wl[next[i][k]]);
        mp[i]-=min(wl[i]-v, m);
        if (mp[i]) fd=1;
    }


        
    return fd;

}


ll solve(){
    int fd=0;
    REP(i, n) if (mp[i]){fd=1; break;}
    if (!fd) return 0;
    ll cnt=1;
    while(doit()) ++cnt;
    return cnt;
}

int main(){
    int tn, ti;
    cin>>tn;

    for (ti=1; ti<=tn; ++ti){
        cin>>r>>c>>m;
        n=r*c;
        mp[n]=0;
        REP(i, r) REP(j, c){
            int id=i*c+j;
            cin>>mp[id];
            REP(k, 4) next[id][k]=in(i+vx[k], j+vy[k])?(i+vx[k])*c+j+vy[k]:n;
        }
        if (ti!=6) continue;
        ne=0;
        REP(i, r) el[ne++]=i*c, el[ne++]=i*c+c-1;
        REP(i, c-2) el[ne++]=i+1, el[ne++]=r*c-c+i+1;

        ll res=solve();

        printf("Case #%d: %Ld\n", ti, res);
    }
    return 0;


}


