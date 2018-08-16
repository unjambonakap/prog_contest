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

typedef int64_t ll;
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
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const double pi=acos(-1);
int n, m;
vector<pii> a, b, c;
map<int, pii> tb;

ll crossp(ll a, ll b, ll c, ll d){return a*d-c*b;}
void sum(){
    int ia, ib;
    ia=ib=0;
    REP(i, n) if (a[i].ND<a[ia].ND || (a[i].ND==a[ia].ND && a[i].ST<a[ia].ST)) ia=i;
    REP(i, m) if (b[i].ND<b[ib].ND || (b[i].ND==b[ib].ND && b[i].ST<b[ib].ST)) ib=i;
    
    c.clear();
    c.pb(MP(a[ia].ST+b[ib].ST, a[ia].ND+b[ib].ND));
    int i, j;
    i=j=0;
    while(i<n || j<m){
        int t;
        if (i==n) t=1;
        else if (j==m) t=0;
        else{
            int k=(ia+i)%n, nk=(k+1)%n;
            double va=atan2(a[nk].ND-a[k].ND, a[nk].ST-a[k].ST);
            k=(ib+j)%m, nk=(k+1)%m;
            double vb=atan2(b[nk].ND-b[k].ND, b[nk].ST-b[k].ST);
            if (va<0) va+=2*pi;
            if (vb<0) vb+=2*pi;
            t=(va>vb);
        }

        if (t){
            int k=(ib+j)%m, nk=(k+1)%m;
            c.pb(MP(b[nk].ST-b[k].ST+c.back().ST, b[nk].ND-b[k].ND+c.back().ND));
            ++j;
        }else{
            int k=(ia+i)%n, nk=(k+1)%n;
            c.pb(MP(a[nk].ST-a[k].ST+c.back().ST, a[nk].ND-a[k].ND+c.back().ND));
            ++i;
        }

    }
    a=c;
    a.pop_back();
    n=a.size();
}



int query(int x, int y){

    //REP(i, n) printf("%d %d\n", a[i].ST, a[i].ND);
    //printf("q %d %d\n", x, y);


    if (y<tb.begin()->ST) return 0;
    map<int, pii>::iterator it=tb.lower_bound(y);
    if (it==tb.end()) return 0;
    if (it->ST>y) --it;
    int i=it->ND.ST, j=i+1;
    assert(a[i].ND!=a[j].ND);

    if (crossp(ll(a[j].ST)-a[i].ST, ll(a[j].ND)-a[i].ND, ll(x)-a[i].ST, ll(y)-a[i].ND)>0) return 0;
    i=it->ND.ND-1, j=i+1;
    assert(a[i].ND!=a[j].ND);
    if (crossp(ll(a[j].ST)-a[i].ST, ll(a[j].ND)-a[i].ND, ll(x)-a[i].ST, ll(y)-a[i].ND)>0) return 0;

    return 1;


}


int main(){
    cin>>n;
    a.resize(n);
    REP(i, n) cin>>a[i].ST>>a[i].ND;


    cin>>m;
    b.resize(m);
    REP(i, m) cin>>b[i].ST>>b[i].ND;
    sum();


    cin>>m;
    b.resize(m);
    REP(i, m) cin>>b[i].ST>>b[i].ND;
    sum();

    tb.clear();
    REP(i, n) tb[a[i].ND]=MP(-1, -1);
    int va=tb.begin()->ST;
    int vb=(--tb.end())->ST;

    a.pb(a[0]);
    reverse(ALL(a));
    int i=0;
    FE(it, tb){
        while (a[i].ND<=it->ST && a[i].ND!=vb) ++i;
        it->ND.ST=i-1;
    }
    i=n-1;

    FE(it, tb){
        while (a[i].ND<=it->ST && a[i].ND!=vb) --i;
        it->ND.ND=i+1;
    }

    int k;
    cin>>k;
    REP(i, k){
        int x, y;
        cin>>x>>y;
        x*=3, y*=3;
        
        if (query(x, y)) printf("YES\n");
        else printf("NO\n");

    }









}
