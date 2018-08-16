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

int main(){
    int la, lb, ua, ub;
    cin>>la>>ua>>lb>>ub;
    vector<pii> a, b;
    a.pb(MP(la-1,ua-1));
    b.pb(MP(lb-1,ub-1));

    int res=0;
    for (int k=30; k; --k){
        int na=a.size(), nb=b.size();
        REP(i,na) REP(j,nb) checkmax(res,min(a[i].ND,b[j].ND)-max(a[i].ST,b[j].ST)+1);
        int fd=0;
        int sz=two(k)-1;

        REP(i,na) if (a[i].ND-a[i].ST+1==sz){fd=1; break;}
        REP(i,nb) if (b[i].ND-b[i].ST+1==sz){fd=1; break;}
        if (fd) break;
        vector<pii> ka, kb;

        int mid=two(k-1)-1;
        REP(i,na){
            if (a[i].ND<mid) ka.pb(a[i]);
            else if (a[i].ST>mid) ka.pb(MP(a[i].ST-mid-1,a[i].ND-mid-1));
            else ka.pb(MP(a[i].ST,mid-1)), ka.pb(MP(0,a[i].ND-mid-1));
        }
        REP(i,nb){
            if (b[i].ND<mid) kb.pb(b[i]);
            else if (b[i].ST>mid) kb.pb(MP(b[i].ST-mid-1,b[i].ND-mid-1));
            else kb.pb(MP(b[i].ST,mid-1)), kb.pb(MP(0,b[i].ND-mid-1));
        }


        a=ka; b=kb;

    }
    cout<<res<<endl;

    return 0;
}




