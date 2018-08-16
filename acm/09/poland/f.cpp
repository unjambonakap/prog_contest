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

const int maxn=333;
int n, na;

ll m[maxn][maxn/64];
ll u[maxn][maxn/64];
int id[maxn];
ll v[maxn][maxn/64];
ll tmp[3][maxn][maxn/64];

char buf[maxn];
int dep;

int go1(){
    memcpy(u,m,sizeof(u));
    REP(i,n) id[i]=i;

    memset(v,0,sizeof(v));
    REP(i,n) v[i][i>>6]=two(i&0x3f);

    REP(i,n){
        int p=-1;
        int x=i>>6, y=i&0x3f;
        FOR(j,i,n) if (u[i][x]>>y&1){p=j; break;}
        if (p==-1){dep=i; return 0;}
        swap(id[i],id[p]);
        REP(j,na) swap(u[p][j],u[i][j]);
        FOR(j,i+1,n) if (u[j][x]>>y&1){
            REP(k,na) u[j][k]^=u[i][k];
            REP(k,na) v[id[j]][k]^=v[id[i]][k];
        }
    }
    return 0;
}


int doit(int r, int c, int a){
    int res=0;

    int lba=n-2, lbb=n-1;
    REP(i,n-2){
        int p=-1;
        int x=i>>6, y=i&0x3f;
        FOR(j,i,n-2) if (u[i][x]>>y&1){p=j; break;}
        if (p==-1){ lba=i; break; }

        REP(j,na) swap(u[p][j],u[i][j]);
        FOR(j,i+1,n-2) if (u[j][x]>>y&1) REP(k,na) u[j][k]^=u[i][k];
        
    }
    return res;

}


int go2(){
    memcpy(tmp[0],m,sizeof(m));
    REP(i,na) swap(tmp[0][n-1][i],tmp[0][p][i]), swap(tmp[0][0][i],tmp[0][n-2][i]);
    return doit(0,0,0);
}

int main(){
    int tn; cin>>tn; 
    REP(ti,tn){
        cin>>n;
        na=(n+63)/64;
        memset(m,0,sizeof(m));
        memset(buf,0,sizeof(buf));
        REP(i,n){
            scanf(" %s", buf);
            REP(j,na){
                int v=0;
                REP(k,64) if (buf[j*64+k]=='1') v|=two(k);
                m[i][j]=v;
            }
        }
        FOR(i,n,na*64) m[i][i/64]|=two(i%64);
        n=na*64;
        int x=go1();
        if (x) puts("NO");
        else{
            x=id[dep];
            ll y[na]; memset(y,0,sizeof(y));
            ll vx[na]; REP(j,na) vx[j]=v[x][j];

            REP(i,n) if (vx[i>>6]>>(0x3f)&1){
                REP(j,na) y[j]^=m[i][j];
            }
            REP(j,na) assert(!y[j]);

            if (!(vx[x][0]&1)){
                REP(j,na) swap(m[0][j],m[x][j]);
                vx[0]^=1; vx[x>>6]^=two(x&0x3f);
            }
            int sum[maxn]; memset(j,0,sizeof(j));
            REP(i,n) if (vx[i>>6]&two(x&0x3f)) REP(j,n) if (m[i][j>>6]&two(j&0x3f)) ++sum[j];
            REP(j,na) m[0][j]=0;
            REP(j,n) if (sum[j]>>1&1) m[0][j>>6]^=two(j&0x3f);

            int res=go1();
            FOR(j,1,n) if (vx[j>>6]&two(j&0x3f)) res^=go2(j); 
            if (res&1) puts("NO");
            else puts("YES");


        }
    }
    return 0;
}


