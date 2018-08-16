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

typedef long double ld;
const int maxn=201;
const ld eps=1e-11;
int w, l, u, g;
vector<pii> lp;
vector<pii> up;
ld la[maxn], ua[maxn];
ld mem[maxn];


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>w>>l>>u>>g;

        lp=vector<pii>(l); up=vector<pii>(u);
        REP(i, l) cin>>lp[i].ST>>lp[i].ND;
        REP(i, u) cin>>up[i].ST>>up[i].ND;

        vi line;
        set<int> tmp;
        REP(i, l) tmp.insert(lp[i].ST);
        REP(i, u) tmp.insert(up[i].ST);
        line=vi(ALL(tmp));

        int n=line.size();
        la[0]=lp[0].ND; ua[0]=up[0].ND;
        la[n-1]=lp.back().ND; ua[n-1]=up.back().ND;


        int p=0;
        FOR(i, 1, n-2){
            int x=line[i];
            if (lp[p+1].ST<x) ++p;

            if (lp[p].ST==x) la[i]=lp[p].ND;
            else{
                assert(p<lp.size());
                ld f=ld(x-lp[p].ST)/(lp[p+1].ST-lp[p].ST);
                la[i]=lp[p].ND+f*(lp[p+1].ND-lp[p].ND);
            }
        }
        p=0;
        FOR(i, 1, n-2){
            int x=line[i];
            if (up[p+1].ST<x) ++p;

            if (up[p].ST==x) ua[i]=up[p].ND;
            else{
                assert(p<up.size());
                ld f=ld(x-up[p].ST)/(up[p+1].ST-up[p].ST);
                ua[i]=up[p].ND+f*(up[p+1].ND-up[p].ND);
            }
        }
        ld area=0.;
        REP(i, n-1){
            ld va=ua[i]-la[i], vb=ua[i+1]-la[i+1];
            mem[i]=(va+vb)/2.*(line[i+1]-line[i]);
            area+=mem[i];
        }


        printf("Case #%d:\n", ti);
        ld ask=area/g;
        ld rem=ask;

        int k=g-1;
        ld tmpx=mem[0];
        ld pos=0.;
        ld ya=la[0], yb=ua[0];
        int i=0;
        while(1){
            if (rem>tmpx){
                rem-=tmpx;
                ++i;
                tmpx=mem[i];
                pos=line[i];
                ya=la[i]; yb=ua[i];
                continue;
            }
            ld nya=la[i+1], nyb=ua[i+1];
            ld T=pos, H=line[i+1];
            ld c, d;
            while(H-T>eps){
                ld M=(H+T)/2.;
                ld a=0.;
                ld f=(M-pos)/(line[i+1]-pos);
                c=ya+(nya-ya)*f;
                d=yb+(nyb-yb)*f;
                a=(M-pos)*(d-c+yb-ya)/2.;

                if (a>rem) H=M;
                else T=M;
            }
            pos=T;
            ya=c;
            yb=d;
            tmpx-=rem;

            printf("%.10Lf\n", pos);
            rem=ask;

            if (--k==0) break;


        }

    }
    return 0;

}



