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

const int maxn=11111;
int isp[maxn];
int vis[maxn];
int a[maxn][3];
int pl[maxn], np;

void check(int p, int &a, int &b, int &c){
    if (isp[p]){
        a=1; b=-1; c=-1;
        return;
    }
    int na, nb, nc, v=p+1;
    check(p+1, b,c,a);
    if (a==-1) a=p;
    REP(i, np) if (p%pl[i]==0){
        check(p/pl[i],nb,nc,na);
        if (na==-1) na=p/pl[i];
        if (na<a || (na==a && p/pl[i]<v)) v=p/pl[i], a=na, b=nb, c=nc;
    }

}

int *go(int p){
    if (vis[p]) return a[p];
    vis[p]=1;
    int *r=a[p];
    if (isp[p]){
        r[0]=1; r[1]=-1; r[2]=-1;
        return r;
    }
    int *x=go(p+1);
    int tmp=p+1;
    int best=x[2]==-1?p+1:x[2];
    for (int i=0; i<np && pl[i]<=p; ++i) if (p%pl[i]==0){
        int *y=go(p/pl[i]);
        int nv=y[2]==-1?p/pl[i]:y[2];
        if (nv<best || (nv==best && p/pl[i]<tmp)) x=y, best=nv, tmp=p/pl[i];
    }
    r[1]=x[0]; r[2]=x[1];
    r[0]=best;
    return r;
}

int qw(int p, int b){
    if (p==1) return 1;
    int *x=go(p);
    if (x[b]==-1) return p;
    return x[b];
}

int main(){
    int n; cin>>n;

    np=0;
    memset(isp, 1, sizeof(isp));
    FOR(i, 2, maxn) if (isp[i]){
        for (int j=i*i; j<maxn; j+=i) isp[j]=0;
        pl[np++]=i;
    }
    memset(a, -1, sizeof(a));

    int res[3]={0};
    
    REP(i, n){
        string s; int v;
        cin>>s>>v;
        int st;
        if (s=="O") st=0;
        else st=s=="E"?1:2;
        REP(j,3) res[(j+st)%3]+=qw(v,j);
    }
    printf("%d %d %d\n", res[0], res[1], res[2]);
    return 0;
}


