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
typedef long double ld;

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

const int maxn=1010;
int pl[maxn], tl[maxn];
const ld inf=1e9;
const ld eps=1e-10;
int n;

int checkit(ld v){
    ld va, vb;
    int qa, qe;
    ld t=-inf;
    ld pos=0.;
    multiset<ld> lst;


    
    ld np=-1;

    np=inf/2.;
    qe=0;
    qa=-1;
    while(1){
        if (qa!=-1){
            t=tl[qa];
            if (fabs(pl[qa]-pos)>eps+v) return 0;
            assert(lst.find(pl[qa])!=lst.end());
            lst.erase(lst.find(pl[qa++]));
            if (qa==n) return 1;
        }else ++qa;

        va=inf; vb=0;
        if (lst.size()) va=*lst.begin(), vb=*lst.rbegin();
        for (; qe<n; ++qe){
            ld nva, nvb;
            nva=min(va, (ld)pl[qe]);
            nvb=max(vb, (ld)pl[qe]);
            if (nvb-nva>eps+v*2) break;
            va=nva; vb=nvb;
            lst.insert(pl[qe]);
        }
        if (qe==n) np=vb-v;
        else{
            np=pl[qe];
            if (np>vb) np=va+v;
            else np=vb-v;
        }
        ld dt=fabs(np-pos);
        if (t+dt>tl[qa]){
            if (np>pos) pos+=tl[qa]-t;
            else pos-=tl[qa]-t;
        }else pos=np;
    }
}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        vector<pii> tmp(n);
        REP(i, n) cin>>tmp[i].ND>>tmp[i].ST;
        sort(ALL(tmp));
        REP(i, n) pl[i]=tmp[i].ND, tl[i]=tmp[i].ST;

        ld H, T, M;
        H=inf; T=0.;
        while(T+eps<H){
            M=(H+T)/2.;
            if (checkit(M)) H=M;
            else T=M;
        }
        printf("Case #%d: %.10Lf\n", ti, T);
    }
    return 0;
}



