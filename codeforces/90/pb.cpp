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

const int maxn=111;
int a[maxn];
int used[maxn];
int n;

int A[maxn][maxn];
int B[maxn][maxn];

int go1(int p, int k){
    if (!k) return 0;
    if (p==n) return 11111;
    int &r=A[p][k];
    if (r!=-1) return r;
    r=go1(p+1,k);
    if (!used[p]) checkmin(r,go1(p+1,k-1)+a[p]);
    return r;
}
int go2(int p, int k){
    if (!k) return 0;
    if (p==n) return 0;
    int &r=B[p][k];
    if (r!=-1) return r;
    r=go2(p+1,k);
    if (!used[p]) checkmax(r,go2(p+1,k-1)+a[p]);
    return r;
}

int main(){
    int k;
    cin>>n>>k;
    int nk=n/k;
    REP(i,n) cin>>a[i];
    int q; cin>>q;
    double resa=1e5, resb=0.;
    REP(i,q){
        int res=0;
        REP(j,nk){
            int b; cin>>b; --b;
            used[b]=1;
            res+=a[b];
        }
        checkmin(resa, 1.*res/nk);
        checkmax(resb, 1.*res/nk);
    }
    int cnt=0;
    REP(i,n) if (!used[i]) ++cnt;

    if (cnt>n-nk*k){
        memset(A,-1,sizeof(A));
        memset(B,-1,sizeof(B));
        checkmin(resa, 1.*go1(0,nk)/nk);
        checkmax(resb, 1.*go2(0,nk)/nk);
    }
    printf("%lf %lf\n", resa, resb);

    return 0;
}



