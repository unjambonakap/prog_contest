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

const int maxn=2*111111;
int A[maxn], B[maxn], C[maxn], D[maxn];

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        memset(B,0x7f,sizeof(B)); B[0]=0;
        int n; cin>>n; REP(i,n) scanf(" %d", A+i);

        C[0]=1;
        FOR(i,1,n) C[i]=A[i]<=A[i-1]?1:C[i-1]+1;
        D[n-1]=1;
        for (int i=n-2; i>=0; --i) D[i]=A[i]>=A[i+1]?1:D[i+1]+1;
        int best=0;
        REP(i,n){
            int T=0, H=i+1;
            int bestx=0;
            while(T<=H){
                int M=(T+H)/2;
                if (B[M]>=A[i]) H=M-1;
                else T=M+1, bestx=M;
            }
            checkmax(best,bestx+D[i]);
            checkmin(B[C[i]],A[i]);
        }
        cout<<best<<endl;
    }

    return 0;
}


