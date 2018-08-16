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

const int maxn=11;
int tb[maxn];
int x[maxn], y[maxn];
int best[maxn];
int val;
int n;
int xl[maxn], yl[maxn];

int go(){
    REP(i,n) xl[i]=x[tb[i]], yl[i]=y[tb[i]];

    xl[n]=x[tb[0]], yl[n]=y[tb[0]];
    int res=0;
    REP(i,n) res+=(xl[i]*yl[i+1]-yl[i]*xl[i+1]);
    return abs(res);
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n;
        REP(i,n) scanf(" %d%d",x+i,y+i);
        REP(i,n-1) tb[i+1]=i+1;
        val=0;
        do{
            int x=go();
            if (x>val) x=val, memcpy(best,tb,sizeof(best));
        }while(next_permutation(tb+1,tb+n));

        printf("Case #%d:",ti+1);
        REP(i,n) printf(" %d",best[i]);
        puts("");
    }
    return 0;
}



