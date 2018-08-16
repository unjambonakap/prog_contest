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

const int maxn=2*1111111;
int A[maxn], B[maxn];
int rmpa[maxn], rmpb[maxn];
int can[maxn];
int done[maxn];

int main(){
    int na, nb;
    cin>>na>>nb;
    REP(i,na) scanf(" %d", A+i);
    REP(i,nb) scanf(" %d", B+i);
    REP(i,na) A[i+na]=A[i];
    REP(i,nb) B[i+nb]=B[i];

    memset(rmpa,-1,sizeof(rmpa));
    memset(rmpb,-1,sizeof(rmpb));
    REP(i,na) rmpa[A[i]]=i;
    REP(i,nb) rmpb[B[i]]=i;
    int j=-1, u=-1, last=-1;
    int best=0;
    for (int i=0; i<na;++i){
        if (rmpb[A[i]]==-1){j=-1, u=-1, last=-1; continue;}
        if (j==-1) j=i+1, last=rmpb[A[i]];
        u=rmpb[A[i]];
        if (last-u>=nb) last-=nb;
        for (; j-i<na; ++j){
            int x=rmpb[A[j]];
            if (x==-1) break;
            if (x<u) x+=nb;
            if (x<=last) break;
            if (u+nb<=x) break;
            last=x;
        }
        best=max(best,j-i);
    }

    cout<<best<<endl;



    return 0;
}


