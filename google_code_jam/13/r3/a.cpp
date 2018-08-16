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

const int N=37;
ll tb[N];
ll val[N];

double proc(){
    double res=0;

    ll mx=1e18;
    REP(j,N) mx=min(mx,val[j]);
    int cnt=0;
    REP(j,N) if (mx==val[j]) ++cnt;
    REP(j,N) if (val[j]==mx) res+=1.*(N-1)*(val[j]-tb[j])/cnt;
    return res;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        ll b;
        int n; cin>>b>>n;
        memset(tb,0,sizeof(tb));
        REP(i,n) scanf(" %Ld",tb+i);
        sort(tb,tb+N);
        double best=0;
        ll ob=b;
        
        memcpy(val,tb,sizeof(tb));
        int u=0;
        while(b>0){
            //on u, spend till reach nu

            int nu=u;
            for (; nu<N && tb[u]==tb[nu]; ++nu);
            if (nu==N) break;
            ll need=nu*(tb[nu]-tb[u]);
            ll tot=min(b,need);

            int last=b<need;
            ll nb=b-need;


            ll k=tot/nu;
            REP(j,nu) val[j]+=k, b-=k;

            int x=tot%nu;
            REP(j,x) val[nu-1-j]++, --b;

            REP(j,nu){
                if (j>tot) break;
                best=max(best,proc()-(ob-b));
                x=(x+nu-1)%nu;
                val[nu-1-x%nu]--;
                ++b;
            }

            if (last) break;

            b=nb;
            REP(j,nu) val[j]=tb[nu];



            u=nu;
        }

        printf("Case #%d: ",ti+1);
        printf("%.10lf\n",best);
    }
    return 0;
}



