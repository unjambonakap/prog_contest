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

const int maxn=111111;
const int oo=1e9;

vi e[maxn];
int a[maxn], b[maxn];
int n,m;
int H,T;

int res[2][111];
int U,V;


int build(int x, int y){
    int have1=0, have2=0;
    int i=0, j=0;
    int na=e[x].size(), nb=e[y].size();
    
    for (; i<na || j<nb;){
        int la=i<na?e[x][i]:oo;
        int lb=j<nb?e[y][j]:oo;
        if (la==y){++i; continue;}
        if (lb==x){++j; continue;}


        if (la<lb){
            ++i;
            if (have1<H) res[0][have1++]=la;
        }else if (la>lb){
            ++j;
            if (have2<T) res[1][have2++]=lb;
        }else{
            ++i; ++j;
            if (have1<H) res[0][have1++]=la;
            else if (have2<T) res[1][have2++]=lb;
        }
    }

    return have1==H && have2==T;
}

int checkit(int x, int y){
    int i=0, j=0;
    int na=e[x].size(), nb=e[y].size();

    vi ta,tb,tc;
    
    for (; i<na || j<nb;){
        int la=i<na?e[x][i]:oo;
        int lb=j<nb?e[y][j]:oo;
        if (la==y){++i; continue;}
        if (lb==x){++j; continue;}


        if (la<lb) ta.pb(la), ++i;
        else if (la>lb) tb.pb(lb), ++j;
        else tc.pb(la), ++i,++j;
    }

    int have1=min(H,(int)ta.size());
    int have2=min(T,(int)tb.size());
    if (tc.size()<H+T-have1-have2) return 0;


    REP(i,have1) res[0][i]=ta[i];
    REP(i,have2) res[1][i]=tb[i];

    int px=0;
    REP(i,H-have1) res[0][have1+i]=tc[px++];
    REP(i,T-have2) res[1][have2+i]=tc[px++];
    return 1;
}
int main(){
    cin>>n>>m>>H>>T;
    int sw=0;
    if (H>T) sw=1, swap(H,T);

    REP(i,m){int x, y; scanf(" %d%d",&x,&y); --x; --y; e[x].pb(y); e[y].pb(x); a[i]=x; b[i]=y;}

    REP(i,n) sort(ALL(e[i]));
    U=-1;
    REP(i,m){
        int x=a[i], y=b[i];
        int sw2=0;
        if (e[x].size()>e[y].size()) swap(x,y), sw2=1;
        int na=e[x].size()-1, nb=e[y].size()-1;

        if (na<H || nb<T) continue;

        if (na>=T+H){//work for sure
            U=x; V=y;
            assert(build(x,y));
            break;
        }

        if (checkit(x,y)){
            U=x; V=y;
            break;
        }
    }

    if (U==-1) puts("NO");
    else{
        puts("YES");
        int aa=0, bb=1;
        if (sw) swap(U,V), swap(aa,bb), swap(H,T);
        printf("%d %d\n",U+1,V+1);
        REP(i,H-1) printf("%d ",res[aa][i]+1);
        printf("%d\n",res[aa][H-1]+1);

        REP(i,T-1) printf("%d ",res[bb][i]+1);
        printf("%d\n",res[bb][T-1]+1);
    }


    return 0;
}

