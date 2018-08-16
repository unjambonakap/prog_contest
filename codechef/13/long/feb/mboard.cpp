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

const int maxn=5e5+10;
const int leaf=1<<19;
int val[2][maxn], wh[2][maxn];
char buf[111];

int tx[2][2][2*leaf];

void update(int *a, int p, int v){ for (p+=leaf; p; p>>=1) a[p]+=v; }
int get(int *a, int p){
    int res=a[p+=leaf];
    for (; p>1; p>>=1) if (p&1) res+=a[p^1];
    return res;
}

int main(){
    int n,q; cin>>n>>q;
    update(tx[0][0],0,n);
    update(tx[1][0],0,n);
    
    int step=0;
    REP(i,q){
        int x;
        scanf(" %s %d",buf,&x);
        --x;
        int f1=buf[0]=='R', f2=buf[3]=='S';
        if (f2){
            ++step;
            int v; scanf(" %d",&v);
            update(tx[f1][val[f1][x]],wh[f1][x],-1);
            wh[f1][x]=step;
            val[f1][x]=v;
            update(tx[f1][v],wh[f1][x],1);
        }else{
            int res=tx[f1^1][val[f1][x]^1][1]-get(tx[f1^1][val[f1][x]^1],wh[f1][x]);
            if (!val[f1][x]) res=n-res;
            printf("%d\n",res);
        }
    }
    return 0;
}

