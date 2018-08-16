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

const int maxn=222222;
char a[maxn], b[maxn];
int n;
vi lst[26];

int main(){
    cin>>n;
    scanf(" %s",a);
    scanf(" %s",b);
    REP(i,n) a[i]-='A', b[i]-='A';

    double res=0;
    REP(i,26){
        vi la, lb;
        vector<pii> el;
        ll sa=0, sb=0;
        REP(j,n) if (a[j]==i) sa+=n-j, el.pb(MP(j,0));
        REP(j,n) if (b[j]==i) sb+=n-j, el.pb(MP(j,1));
        sort(ALL(el));
        REP(j,el.size()){
            int p=el[j].ST;
            if (el[j].ND==0) res+=1ll*(p+1)*sb, sa-=n-p;
            else res+=1ll*(p+1)*sa, sb-=n-p;
        }
    }
    ll den=0;
    FOR(i,1,n+1) den+=1ll*i*i;
    res/=den;



    printf("%.10lf\n",res);
    return 0;
}


