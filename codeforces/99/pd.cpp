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

const int maxn=25;
int A[2*maxn+1][2*maxn][2*maxn][2*maxn];
string mp[maxn]; int n, m;
int da[maxn][maxn], db[maxn][maxn];

int proca(int xa, int xb, int ya, int yb){
    if (xa+1>=xb || ya+1>=yb) return 0;
    int &r=A[xa][xb][ya][yb];
    if (r!=-1) return r;

    set<int> mex;
    REP(i, n) REP(j, m) if (i+j&1){
        int a=da[i][j], b=db[i][j];
        if (a>xa && a<xb && b>ya && b<yb){
            if (mp[i][j]=='R') mex.insert(proca(xa,xb,ya,b)^proca(xa,xb,b,yb));
            else if (mp[i][j]=='L') mex.insert(proca(xa,a,ya,yb)^proca(a,xb,ya,yb));
            else mex.insert(proca(xa, a, ya, b)^proca(xa,a,b,yb)^proca(a,xb,ya,b)^proca(a,xb,b,yb));
        }
    }


    int prev=-1;
    FE(it, mex) if (*it!=prev+1) return r=prev+1; else prev=*it;
    return r=prev+1;
}


int procb(int xa, int xb, int ya, int yb){
    if (xa+1>=xb || ya+1>=yb) return 0;
    int &r=A[xa][xb][ya][yb];
    if (r!=-1) return r;

    set<int> mex;
    REP(i, n) REP(j, m) if (!(i+j&1)){
        int a=da[i][j], b=db[i][j];
        if (a>xa && a<xb && b>ya && b<yb){
            if (mp[i][j]=='R') mex.insert(procb(xa,xb,ya,b)^procb(xa,xb,b,yb));
            else if (mp[i][j]=='L') mex.insert(procb(xa,a,ya,yb)^procb(a,xb,ya,yb));
            else mex.insert(procb(xa, a, ya, b)^procb(xa,a,b,yb)^procb(a,xb,ya,b)^procb(a,xb,b,yb));
        }
    }
    int prev=-1;
    FE(it, mex) if (*it!=prev+1) return r=prev+1; else prev=*it;
    return r=prev+1;
}

int main(){
    cin>>n>>m;
    REP(i, n) cin>>mp[i];
    memset(A, -1, sizeof(A));
    REP(i, n) REP(j, m){
        da[i][j]=i+j+1;
        db[i][j]=i-j+m;
    }

    int res=proca(0,n+m,0,n+m);
    memset(A, -1, sizeof(A));
    res^=procb(0,n+m,0,n+m);
    cout<<(res?"WIN":"LOSE")<<endl;
    return 0;
}


