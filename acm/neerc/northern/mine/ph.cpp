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

const int maxn=55555;
const int M=5;
string dp[two(M)][maxn];

int main(){
    int n; cin>>n;

    int MASK=two(M)-1;
    REP(i,n) cin>>dp[MASK][i];
    REP(i,n) REP(j, two(M)-1){
        dp[j][i]="";
        REP(k, M) if (j&two(k)) dp[j][i]+=dp[MASK][i][k];
    }

    REP(j, two(M)) sort(dp[j], dp[j]+n);
    ll res[M+1], A[two(M)];
    memset(res, 0, sizeof(res));
    memset(A, 0, sizeof(A));
    REP(i, two(M)){
        int pos=0;
        while(pos<n){
            ll prev=pos;
            for (++pos; pos<n && dp[i][pos]==dp[i][pos-1]; ++pos);
            prev=pos-prev;
            A[i]+=prev*(prev-1)/2;
        }
    }


    REPV(i, M) REP(j, two(M)) if (count_bit(j)==i) REP(k, two(M)) if ((j&k)==j && j!=k) A[j]-=A[k];
    
    REP(i, two(M)) res[M-count_bit(i)]+=A[i];


    REP(i, M+1) printf("%Ld ", res[i]);
    return 0;
}


