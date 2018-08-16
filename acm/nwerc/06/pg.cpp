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

const int maxp=10000;
int pl[2000];
int isp[maxp];
int np;

vi e[2000];
int dist[2000];

int main(){
    int tn; cin>>tn;
    np=0;
    int lb=-1;
    memset(isp, -1, sizeof(isp));
    FOR(i, 2, maxp){
        int fd=1;
        REP(j, np) if (i%pl[j]==0){fd=0; break;}
        if (fd){
            if (lb==-1 && i>=1000) lb=np;
            isp[i]=np;
            pl[np++]=i;

        }
    }
    FOR(i, lb, np-1){
        int p=1;
        REP(j, 4){
            int x=pl[i]-(pl[i]/p%10)*p;
            REP(k, 10){
                int nx=x+p*k;
                if (nx!=pl[i] && isp[nx]!=-1) e[i-lb].pb(isp[nx]-lb);
            }
            p=p*10;
        }
    }
    int n=np-lb;

    REP(ti, tn){
        int a, b;
        cin>>a>>b;
        a=isp[a]-lb; b=isp[b]-lb;
        priority_queue<pii,vector<pii>, greater<pii> > q;
        memset(dist, 0x7f, sizeof(dist));
        dist[a]=0;
        q.push(MP(0, a));
        int fd=0;
        while(!q.empty()){
            pii p=q.top(); q.pop();
            int x=p.ND;
            int A=pl[lb+x];
            if (dist[x]>p.ST) continue;
            if (x==b){fd=1; printf("%d\n", p.ST); break;}
            REP(i, e[x].size()){
                int y=e[x][i];
                if (dist[y]>dist[x]+1) q.push(MP(dist[y]=dist[x]+1, y));
            }
        }
        if (!fd) printf("Impossible\n");
    }
    return 0;
}

