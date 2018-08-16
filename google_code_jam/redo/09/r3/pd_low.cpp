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

const ll mod=1e9+7;
ll A, B;
set<ll> pal;

int tb[7];
void gen(int pos, int n){
    if (pos==n){
        ll va=0, vb;
        REP(i, n) va=va*10+tb[i];
        vb=va;
        va=va*10+tb[n-1];
        REPV(i, n-1) va=va*10+tb[i], vb=vb*10+tb[i];
        pal.insert(va);
        pal.insert(vb);
        return;
    }

    for (int i=(pos?0:1); i<10; ++i){
        tb[pos]=i;
        gen(pos+1, n);
    }

}
int main(){
    int tn;
    cin>>tn;
    pal.clear();
    REP(i, 3) gen(0, i+1);
    pal.insert(0);
    ll i2=mod/2+1;

    FOR(ti, 1, tn){
        cin>>A>>B;
        A=10;
        B=11;
        ll cnta=0;
        set<ll>::iterator it=pal.lower_bound(A);

        ll p=A, np=*it;
        int step=0;
        while(1){
            checkmin(np, B+1);
            if (!step) cnta+=np-p;

            if (np==B+1) break;
            
            ++it;
            p=np;
            np=*it;
            step^=1;
        }
        cnta%=mod;
        ll cntb=(mod+B-A+1-cnta)%mod;
        printf("<< %Ld %Ld\n", cnta, cntb);
    
        
        printf("Case #%d: %Ld\n", ti, (mod+(cnta*(cnta+1)%mod)*i2%mod+(cntb*(cntb+1)%mod)*i2%mod-cntb)%mod);
        break;

    }
    return 0;

}
