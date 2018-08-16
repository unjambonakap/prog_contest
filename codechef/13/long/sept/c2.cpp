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
typedef unsigned int uint;
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

const int maxn=555;

char mp[maxn][maxn];
int r,c;

int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};
int v[maxn][maxn];
int tb[maxn][maxn];

int isp[maxn];
int cnt[maxn];

int in(int a, int b){return a>=0&&a<r&&b>=0&&b<c;}
int main(){

    memset(isp,1,sizeof(isp));
    int cx=0;
    for (int i=2; i<maxn; ++i){
        if (isp[i]){
            ++cx;
            for (int j=i*i; j<maxn; j+=i) isp[j]=0;
        }
        cnt[i]=cx;
    }



    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %d%d",&r,&c);
        REP(i,r) scanf(" %s",mp[i]);
        REP(i,r) REP(j,c) mp[i][j]=mp[i][j]=='^';

        memset(tb,0x7f,sizeof(tb));
        REP(k,4){
            int sx,dx,sy,dy;
            if (vx[k]==1) sx=r-1, dx=-1;
            else sx=0, dx=1;

            if (vy[k]==1) sy=c-1, dy=-1;
            else sy=0, dy=1;

            for (int i=sx; in(i,0); i+=dx)
                for (int j=sy; in(0,j); j+=dy){
                    int ni=i+vx[k], nj=j+vy[k];
                    v[i][j]=in(ni,nj)&&mp[ni][nj]?v[ni][nj]+1:0;
                }

            REP(i,r) REP(j,c) tb[i][j]=min(tb[i][j],v[i][j]);
        }
        int res=0;
        REP(i,r) REP(j,c) if (mp[i][j]) res+=tb[i][j]>=2;
        printf("%d\n",res);

    }

    return 0;
}

