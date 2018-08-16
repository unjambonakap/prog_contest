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

const int maxr=55;
int r, c;
int ro, co;

int vx[]={-1, 0, 0, 1};
int vy[]={0, -1, 1, 0};
const int inf=1e5;

int mdist(int a, int b){return abs(a)+abs(b);}
int in(int a, int b){return a>=0 && a<r && b>=0 && b<c;}

int solve(int tb[][maxr], int a){
    if (tb[ro][co]==0) return a-1;
    
    int ntb[maxr][maxr];
    int fd=0;
    REP(k, 4) if (in(ro+vx[k], co+vy[k]) && tb[ro+vx[k]][co+vy[k]]){fd=1; break;}
    if (!fd)  return inf;

    
    memcpy(ntb, tb, sizeof(ntb));
    REP(i, r) REP(j, c) if (i!=ro || j!=co){
        int v=-1;
        int prev=-1;
        REP(k, 4){
            int ni=i+vx[k], nj=j+vy[k];
            if (in(ni, nj)){
                int val=tb[ni][nj];
                if (v==-1 || val>prev) v=k, prev=val;
            }
        }
        if (v!=-1) ntb[i+vx[v]][j+vy[v]]=max(0, ntb[i+vx[v]][j+vy[v]]-tb[i][j]);
    }


    int res=solve(ntb, a+1);
    REP(k, 4) if (in(ro+vx[k], co+vy[k])){

        int *u=&ntb[ro+vx[k]][co+vy[k]];
        if (*u!=0){
            int prev=*u;
            *u=max(*u-tb[ro][co], 0);
            checkmax(res, solve(ntb, a+1));
            *u=prev;
        }
    }
    return res;





}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>c>>r>>co>>ro;
        --ro; --co;
        int tb[maxr][maxr];
        REP(i, r) REP(j, c) cin>>tb[i][j];
        //if (ti!=22)continue;


        int res=solve(tb, 0);

        printf("Case #%d: ", ti);
        if (res>=inf) printf("forever\n");
        else printf("%d day(s)\n", res);
    }
    return 0;
}



