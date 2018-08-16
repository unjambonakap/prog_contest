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

const int maxn=1e6+10;
const double inf=1e10;
int n;
vector<pii> l;
int ny;
int xp[maxn];
int rxp[maxn];
double best;

inline double dist(const pii &a, const pii &b){return sqrt(double(a.ST-b.ST)*(a.ST-b.ST)+double(a.ND-b.ND)*(a.ND-b.ND));}

struct cmpY{
    bool operator()(const pii &a, const pii &b)const{return a.ND<b.ND;}

};

void dc(int T, int H){
    if (T+1==H){
        double res=inf;
        FOR(i, xp[T], xp[H]-3) checkmin(best, (l[i].ND+l[i+2].ND)*2.);
        checkmin(best, res);
    }else{
        int M=(H+T)/2;
        dc(T, M); dc(M, H);
        double box=best/2;
        int mid=rxp[M];
        int a=lower_bound(rxp+T, rxp+M, mid-box)-rxp;
        int b=upper_bound(rxp+M, rxp+H, mid+box)-rxp;
        --b;
        deque<pii> sa, sb;
        FOR(i, (!a?0:xp[a-1]), xp[M-1]-1) sa.pb(l[i]);
        FOR(i, xp[M-1], xp[b]-1) sb.pb(l[i]);
        sort(ALL(sa), cmpY());
        sort(ALL(sb), cmpY());
        int ua, lb, ub;
        ua=0;
        lb=ub=0;
        int na, nb;
        na=sa.size(); nb=sb.size();
        REP(la, na){
            while(ub+1<nb && sb[ub+1].ND-sa[la].ND<box) ++ub;
            while(lb<nb && sa[la].ND-sb[lb].ND>box) ++lb;
            while(ua+1<na && sa[ua+1].ND-sa[la].ND<box) ++ua;

            FOR(i, lb, ub){
                FOR(j, la+1, ua) checkmin(best, dist(sa[la], sb[i])+dist(sa[la], sa[j])+dist(sb[i], sa[j]));
                FOR(j, lb, i-1) checkmin(best, dist(sa[la], sb[i])+dist(sa[la], sb[j])+dist(sb[i], sb[j]));
            }
            box=best/2;


        }


    }

}

void solve(){
    sort(ALL(l));
    int p=0;
    REP(i, n) if (i)  if (l[i].ST!=l[i-1].ST) xp[p]=i, rxp[p++]=l[i-1].ST;
    xp[p]=n, rxp[p++]=l[n-1].ST;
    best=inf;
    dc(0, p);



}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        l.resize(n);
        REP(i, n) cin>>l[i].ST>>l[i].ND;
        //REP(i, n) printf("%d %d\n", l[i].ST, l[i].ND);
        solve();
        printf("Case #%d: %.11lf\n", ti, best);

    }
    return 0;


}


