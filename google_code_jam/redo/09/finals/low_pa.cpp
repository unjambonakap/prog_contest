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

const int maxm=55;
const int maxv=55;
int n, t;
int na[maxm];
int d[maxm][maxv];

ll gcd(ll a, ll b){ return b==0?a:gcd(b, a%b); }

struct data{
    ll k, a, b;
    data(ll b):b(b){a=k=0;}
    void add(ll na){a+=na; if (a>=b) k+=a/b, a%=b;}
    void reduce(){ll d=gcd(max(a, b), min(a, b)); a/=d; b/=d;}
};

data solve(){
    data res(ll(n)*n);
    REP(i, t) REP(a, na[i]){
        res.add(ll(n)*max(0, n-d[i][a]));
        REP(j, t) if (j!=i) REP(b, na[j]){
            res.add(max(0, min(n-d[i][a], n-d[j][b])));
        }



    }


    return res;
}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n>>t;
        REP(i, t){
            cin>>na[i];
            d[i][0]=0;
            REP(j, na[i]-1){
                cin>>d[i][j+1];
                --d[i][j+1];
            }
        }
        data res=solve();
        res.reduce();
        printf("Case #%d: %Ld+%Ld/%Ld\n", ti, res.k, res.a, res.b);

    }
    return 0;


}


