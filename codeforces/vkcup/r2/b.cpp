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

struct data{
    int m, v, id;
    bool operator<(const data &d)const{if (m!=d.m) return m<d.m; return v<d.v;}
};
data tb[111111];
vi res;
int n, k, h;

int checkit(double T){
    int pos=1;
    vi x;
    REP(i,n){
        if (h*pos<=T*tb[i].v){
            x.pb(tb[i].id+1);
            ++pos;
            if (pos==k+1){ res=x; return 1; }
        }
    }
    return 0;

}


int main(){
    cin>>n>>k>>h;
    REP(i,n) tb[i].id=i;
    REP(i,n) scanf(" %d", &tb[i].m);
    REP(i,n) scanf(" %d", &tb[i].v);
    sort(tb,tb+n);
    double T=0, H=1e10;
    REP(step,150){
        double M=(T+H)/2;
        if (checkit(M)) H=M;
        else T=M;
    }
    out(res);
    return 0;
}


