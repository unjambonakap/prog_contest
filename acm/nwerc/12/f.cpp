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

const int maxn=1026;
const int maxb=11;

int g[maxn][maxn];
char buf[maxn];
int n;
int A[maxn], B[maxn];
int na, nb;
int ta[maxn], tb[maxn];

int vis[maxn];
int with[maxn];
int U;
int nna,nnb;

int vis2[maxn];

int dfs(int a){
    if (vis[a]==U) return 0;
    vis[a]=U;
    REP(i,nb) if (g[A[a]][B[i]] && (with[i]==-1 || dfs(with[i]))){
        with[i]=a;
        return 1;
    }
    return 0;
}

void match(int a, int b){
    printf("%d %d\n",a+1,b+1);
    vis2[a]=vis2[b]=1;

    if (!a) assert(g[0][b]);
    else{
        int vx=g[a][b]?a:b; 
        if (g[0][vx]) ta[nna++]=vx;
        else tb[nnb++]=vx;
    }
}

int main(){
    while(scanf(" %d",&n)>0){
        REP(i,n){
            scanf(" %s",buf);
            REP(j,n) g[i][j]=buf[j]-'0';
        }

        na=nb=0;
        FOR(i,1,n) if (g[0][i]) A[na++]=i; else B[nb++]=i;

        int nx=n;
        while(nx>1){
            nna=nnb=0;
            memset(vis,0,sizeof(vis));
            memset(with,-1,sizeof(with));

            U=1;
            REP(i,na) if (!dfs(i)){
                ++U;
                dfs(i);
            }
            memset(vis2,0,sizeof(vis2));
            REP(i,nb) if (with[i]!=-1) match(A[with[i]],B[i]);
            
            vi rema, remb;
            REP(i,na) if (!vis2[A[i]]) rema.pb(A[i]);
            REP(i,nb) if (!vis2[B[i]]) remb.pb(B[i]);



            while(remb.size()>=2){
                int x=remb.back(); remb.pop_back();
                int y=remb.back(); remb.pop_back();
                match(x,y);
            }
            assert(rema.size());
            match(0,rema.back());
            rema.pop_back();
            while(rema.size()>=2){
                int x=rema.back(); rema.pop_back();
                int y=rema.back(); rema.pop_back();
                match(x,y);
            }

            assert((rema.size()+remb.size())%2==0);
            if (rema.size() && remb.size()) match(rema[0],remb[0]);


            na=nna; nb=nnb;
            memcpy(A,ta,sizeof(A));
            memcpy(B,tb,sizeof(B));
            nx/=2;
        }

    }
    return 0;
}

