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

const int mod=5e5+9;
const int maxn=2.25e6;
const int maxv=504735;

int ndiv[maxn];
int tmp[maxn];
int A[1111];
int B[maxn];



int main(){

    int lb=sqrt(maxn)+1;
    REP(i, maxn) ndiv[i]=1;
    FOR(i,2,maxn) if (ndiv[i]==1){
        tmp[i]=1;
        for (int j=i+i, cnt=2; j<maxn; j+=i, ++cnt) tmp[j]=1+(cnt%i==0?tmp[j/i]:0), ndiv[j]*=tmp[j]+1;
        //if (i<lb) for (ll k=1ll*i*i; k<maxn; k*=i) for (int j=k; j<maxn; j+=k) ++tmp[j];
        //for (int j=i+i; j<maxn; j+=i) ndiv[j]*=tmp[j]+1;
        ++ndiv[i];
    }

    B[1]=1;
    FOR(i, 2, maxn) B[i]=1ll*B[i-1]*++A[ndiv[i]]%mod;
    

    int tn; cin>>tn;
    REP(ti, tn){
        int n; scanf("%d", &n);
        if (n>=maxn) printf("%d\n", mod-1);
        else printf("%d\n", B[n]-1);
    }
    return 0;
}


