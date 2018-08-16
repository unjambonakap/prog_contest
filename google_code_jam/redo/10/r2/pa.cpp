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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxk=55;
int mp[2*maxk+10][2*maxk+10];
int k;

int ok(int x, int y, int v){
    if (x<0 || y<0 || x>2*k || y>2*k || mp[x][y]==-1) return 1;
    return mp[x][y]==v;
}

int checkita(int a){
    REP(i, 2*k+1) REP(j, 2*k+1) if (mp[i][j]!=-1){
        if (!ok(2*a-i, j, mp[i][j])) return 0;
    }
    return 1;
}
int checkitb(int a){
    REP(i, 2*k+1) REP(j, 2*k+1) if (mp[i][j]!=-1){
        if (!ok(i, 2*a-j, mp[i][j])) return 0;
    }
    return 1;
}
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>k;
        memset(mp, -1, sizeof(mp));
        FOR(i, 1, k) FOR(j, 1, i) cin>>mp[i][k-1-i+j*2];
        
        FOR(i, k+1, 2*k-1) FOR(j, 1, 2*k-i) cin>>mp[i][i-1-k+2*j];
        int va=INT_MAX;
        int vb=INT_MAX;
        FOR(i, 1, 2*k+1) if (checkita(i)) checkmin(va, abs(i-k));
        FOR(i, 1, 2*k+1) if (checkitb(i)) checkmin(vb, abs(i-k));
        assert(va<INT_MAX);
        assert(vb<INT_MAX);
        int m=k+va+vb;
        int tmp=k*(k+1)/2+k*(k-1)/2;
        int res=m*(m+1)/2+m*(m-1)/2-tmp;
        printf("Case #%d: %d\n", ti, res);
    }
    return 0;
}



