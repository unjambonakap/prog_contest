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

const int maxn=1e6+10;
int a[maxn], b[maxn];
int lst[maxn];
int n,m;

int res[maxn];
int POS;

int go(int x, int v){
    for (int i=x; i<=n;){
        int is=POS<m && b[POS]==i;
        if (a[i]==v && !is){
            res[i]=-a[i];
            return i;
        } 
        if (is) ++POS;
        res[i]=a[i];
        i=go(i+1,a[i]);
        if (i==-1) return -1;
        ++i;

    }
    return -1;
}


int main(){
    while(cin>>n,cin.good()){

        REP(i,n) scanf(" %d",a+i);

        cin>>m;
        REP(i,m) scanf(" %d",b+i), --b[i];
        REP(i,n) lst[i]=a[i];
        sort(b,b+m);

        sort(lst,lst+n);
        REP(i,n) a[i]=lower_bound(lst,lst+n,a[i])-lst+1;
        REP(i,n/2) swap(a[i],a[n-i-1]);
        REP(i,m/2) swap(b[i],b[m-i-1]);
        REP(i,m) b[i]=n-b[i]-1;
        a[n]=n;

        POS=0;
        if (go(0,n)!=-1 && POS==m){
            puts("YES");
            REP(i,n) if (res[i]<0) res[i]=-lst[-res[i]-1]; else res[i]=lst[res[i]-1];
            REP(i,n) printf("%d ",-res[n-i-1]); puts("");
        }else puts("NO");
    }
    return 0;
}

