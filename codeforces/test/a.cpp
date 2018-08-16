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

const int maxn=5e5+10;
int n, k;
int vis[maxn];
int u[maxn][2], v[maxn][2];
char s[maxn];
char res[maxn];

void go(int a){
    if (vis[a]) return;
    vis[a]=1;
    if (!a){
        u[0][0]=0; u[0][1]=s[0];
        v[0][0]=1; v[0][1]=(s[0]+1)%k;
        return;
    }
    go(a-1);
    u[a][0]=v[a][0]=maxn;
    REP(i,k){
        int c=(u[a-1][1]==i?v[a-1][0]:u[a-1][0])+(i==s[a]?0:1);
        if (c<u[a][0]) v[a][1]=u[a][1], v[a][0]=u[a][0], u[a][1]=i, u[a][0]=c;
        else if (c<v[a][0]) v[a][1]=i, v[a][0]=c;
    }
}

void build(int a, int f){
    int *x;
    if (f==u[a][1]) x=v[a];
    else x=u[a];
    res[a]=x[1];
    if (!a) return;
    build(a-1,x[1]);
}

int main(){
    cin>>n>>k;

    scanf(" %s", s);
    REP(i,n) s[i]-='A';
    res[n]=0;
    go(n-1);
    build(n-1,k);


    cout<<u[n-1][0]<<endl;
    REP(i,n) res[i]+='A';
    res[n]=0;
    printf("%s\n",res);
    return 0;
}

