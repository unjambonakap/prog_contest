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
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=1111;

ll pos[maxn];
int sgn[maxn];
int n;
ll last[maxn];
ll tx;
int cnt[maxn];


struct event{
    ll t;
    int x;
    int type;
    int id;
    event(ll t, int x, int id):t(t), x(x), id(id), type(1){}
    event(ll t, int x):x(x),type(0), t(t){ } 

    bool operator<(const event &e)const{
        if (t!=e.t) return t>e.t;
        if (type!=e.type) return type>e.type;
        if (x!=e.x) return x<e.x;
        return id<e.id;

    }
};

void update(int x){ pos[x]+=(tx-last[x])*sgn[x]; last[x]=tx; }

void doit(int a, int b, priority_queue<event> &q){
    if (a<0 || b==n) return;
    update(a); update(b);
    if (sgn[a]==-1 || sgn[b]==1) return;
    ll m=pos[a]+pos[b];
    assert(m%2==0); m/=2;
    q.push(event(tx+m-pos[a], a));
}

int main(){
    int tn; cin>>tn;
    REP(ti, tn){
        cin>>n;
        priority_queue<event> q;
        REP(i, n) cin>>pos[i], pos[i]*=2;
        REP(i, n){
            cin>>sgn[i];
            sgn[i]=(sgn[i]?1:-1);
        }
        memset(cnt, 0, sizeof(cnt));
        memset(last, 0, sizeof(last));
        int nq;
        cin>>nq;
        vector<pair<int,ll> > res(nq);
        REP(i, nq){
            ll a, b;
            cin>>a>>b;
            assert(b>=0);
            q.push(event(2*b, a, i));
        }
        REP(i, n-1) doit(i, i+1, q);
        tx=0;
        while(!q.empty()){
            event e=q.top(); q.pop();
            tx=e.t;

            if (e.type==1){
                int x=e.x;
                pos[x]+=(tx-last[x])*sgn[x];
                last[x]=tx;
                assert(pos[x]%2==0);
                res[e.id]=MP(cnt[x], pos[x]/2);
                --nq;
                if (nq==0) break;
            }else{
                int x=e.x;
                ++cnt[x]; ++cnt[x+1];
                update(x); update(x+1);
                sgn[x]=-sgn[x];
                sgn[x+1]=-sgn[x+1];
                doit(x-1, x, q);
                doit(x+1, x+2, q);

            }
        }
        FE(it, res) cout<<it->ND<<" "<<it->ST<<endl;
    }

    return 0;
}




