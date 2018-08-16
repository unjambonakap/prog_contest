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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxr=50;
int mp[maxr][maxr];
int r, c;
int proc_line(int l){
    int st;
    if (c%3==0) st=1;
    else st=0;
    int res=0;
    for (; st<c; st+=3) res+=mp[l][st];
    return res;
}

int solve(){
    int tb[maxr];
    REP(i, r) tb[i]=proc_line(i);
    int val[maxr];
    memset(val, -1, sizeof(val));
    int cnt=tb[0];
    
    for (int i=2; i<r; i+=3){
        val[i]=tb[i-1]-cnt;
        if (i+1<r) cnt=tb[i+1]-val[i];
    }

    cnt=tb[r-1];
    for (int i=r-3; i>=0; i-=3){
        val[i]=tb[i+1]-cnt;
        if (i-1<r) cnt=tb[i-1]-val[i];
    }
    int m=r/2;
    if (val[m]!=-1) return val[m];
    assert(val[m-1]!=-1 && val[m+1]!=-1);
    return tb[m]-val[m-1]-val[m+1];



}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>r>>c;
        REP(i, r) REP(j, c) cin>>mp[i][j];

        printf("Case #%d: %d\n", ti, solve());
        

    }
    return 0;
}

