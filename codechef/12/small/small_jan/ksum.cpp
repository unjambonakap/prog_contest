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

const int maxn=11111;
int tb[maxn];
int A[maxn], B[maxn];
int S;
int n;

int doit(int a, int b, int k, vi &l, vi &r, vi &u){
    int na=b-a;
    if (k>=na*(na+1)/2){
        FOR(i, a, b) l.pb(A[i+1]-A[a]), r.pb(B[i]-B[b]);
        FOR(i, a, b) FOR(j, a, i+1) u.pb(A[i+1]-A[j]);
        sort(ALL(u));
        sort(ALL(l));
        sort(ALL(r));
        return u.size()<k?-1:u[k-1];
    }


    int m=(a+b)/2;
    int sl=A[m]-A[a], sr=A[b]-A[m];
    vi la, lb, ra, rb, ua, ub;
    doit(a, m, k, la, ra, u);
    doit(m, b, k, lb, rb, u);
    l=la;
    FE(it, lb) l.pb(*it+sl);
    r=rb;
    FE(it, ra) r.pb(*it+sr);
    sort(ALL(l));
    sort(ALL(r));
    if (l.size()>k) l.resize(k);
    if (r.size()>k) r.resize(k);

    priority_queue<pair<int,pii> > q;
    REP(i, ra.size()) q.push(MP(-ra[i]-lb[0], MP(i,0)));
    while(!q.empty() && u.size()<2*k){
        u.pb(-q.top().ST);
        pii p=q.top().ND; q.pop();
        if (p.ND==lb.size()-1) continue;
        q.push(MP(-ra[p.ST]-lb[p.ND+1], MP(p.ST, p.ND+1)));
    }
    sort(ALL(u));
    if (u.size()>k) u.resize(k);

    return u.size()<k?-1:u[k-1];
}

void solve(int *k){
    vi l,r,u;
    doit(0, n, k[2],l,r,u);
    REP(i, 3) printf("%d ", -u[k[i]-1]);
    puts("");

}

int main(){
    int tn; cin>>tn;
    REP(ti, tn){

        int k[3];
        cin>>n;
        REP(i, 3) cin>>k[i];
        REP(i, n) scanf(" %d", tb+i), tb[i]=-tb[i];

        S=0;
        REP(i, n) S+=tb[i];
        A[0]=0;
        REP(i, n) A[i+1]=A[i]+tb[i];
        B[n]=0;
        REPV(i, n) B[i]=B[i+1]+tb[i];

        solve(k);
    }
    return 0;
}


