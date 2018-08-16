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

const int mod=1e9+7;
const int maxn=1e5+10;
int x[maxn], y[maxn];
int n;

pii z;
int ans;
int M;
int parent[maxn], c[maxn];
int tmp[maxn];


int root(int a){
    int i, b;
    for (i=0, b=a; parent[b]!=-1; ++i, b=parent[b]) tmp[i]=b;
    tmp[i]=b;
    for (--i; i>=0; --i) c[tmp[i]]^=c[tmp[i+1]], parent[tmp[i]]=b;
    return b;
}
inline int dist(int a, int b){
    int c=x[a]-x[b];
    int d=y[a]-y[b];
    if (c<0) c=-c;
    if (d<0) d=-d;
    return c+d;
}

void join(int a, int b, int d){
    assert(c[a]==0 && c[b]==0);
    parent[b]=a;
    assert(a!=b);
    c[b]=d;

}





pii checkit(){
    REP(i, n) parent[i]=-1, c[i]=0;

    REP(i, n){
        int ra=root(i);
        REP(j, i) if (dist(i, j)>M){
            int rb=root(j);

            if (ra==rb){ if (c[i]==c[j]) return MP(0, 0); }
            else join(ra, rb, c[i]==c[j]);
        }
    }

    int cnt=1;
    REP(i, n) if (root(i)==i) cnt=cnt*2%mod;
    //out(parent, n);
    //out(c, n);
    //out(nv, n);
    return MP(1, cnt);
}


int main(){
    cin>>n;
    REP(i, n) cin>>x[i]>>y[i];

    int T=0, H=2*maxn;

    while(T<H){
        M=(T+H)/2;
        pii res=checkit();
        if (res.ST) H=M, ans=res.ND;
        else T=M+1;
    }
    M=T;
    printf("%d\n%d\n", T, ans);
    return 0;


}


