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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

ll m, a, v;
ll z; 
long double px, py, df;
ll pos, npos;
const long double eps=1e-16;

void step(){
    if (pos+1>=npos) return;
    long double np;
    px+=(npos-pos-1)*df;
    py=px+df;
    pos=npos-1;
}


long double calc(ll x){
    if (x==0) return px;
    if (x==1) return py;
    return px+x*df; 
}



long double doit(){
    ll b=1;
    pos=0; py=1.; px=0.;
    df=1.;
    while(b*2<=m) b<<=1;

    long double ans=-1;

    if (a==1) ans=1.;
    ll low=0;

    set<ll> tmpz, tmpy;
    tmpy.insert(1); tmpz.insert(1);
    while(b>1){
        ll k=m/b;
        if (2*k>v) break;
        npos=k;
        if (a>=pos && a<=npos) ans=calc(a-pos);

        if (k*(2-2*b)<low) tmpz.insert(k);
        if (k*(2-2*b)<=low) low=k*(2-2*b), tmpy.insert(k);
        else{ b>>=1; continue; }
        step();

        npos=2*k;
        long double ndf=py/(2*b-1);
        //py=p_b, pz=p_{2*b}
        px=py;
        
        df=ndf/k;
        py+=df;
        ++pos;

        if (a>=pos && a<=npos) ans=calc(a-pos);

        py=px+ndf;
        px=py-df;



        pos=npos-1;

        b>>=1;
    }
    z=min(m, v-a);
    if (tmpy.count(a)) z=a;
    else{
        set<ll>::iterator it=tmpz.upper_bound(a);
        assert(it!=tmpz.begin());
        if (it!=tmpz.end()) checkmin(z, *it-a);
        --it;
        checkmin(z, a-*it); 
    }


    npos=v;
    if (a>=pos && a<=npos)ans=calc(a-pos);
    //printf("now on %lf %lf\n", px, py);
    //printf("%Ld %Ld\n", pos, npos);
    //printf("%Lf %Lf => %Ld %Lf\n", px, py, pos, 1/py);
    step();
    //printf("%Lf %Lf => %Ld %Lf\n", px, py, pos, 1/py);
    //must have p_v=1. => p_0=0, p_1=1/px

    assert(ans>=0.);
    return ans/py;

}


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>a>>m>>v;
        //if (ti!=12)continue;
        //checkmin(m, v);
        //printf("start at %Ld, max bet %Ld, to %Ld\n", a, m , v);
        long double res=doit();
        printf("Case #%d: %.9Lf %Ld\n", ti, res, z);
    }
    return 0;
}


