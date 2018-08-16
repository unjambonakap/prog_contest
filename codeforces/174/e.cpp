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

const int maxn=1<<18;
int x[maxn];
int n;
vi nd[maxn], st[maxn];


struct node{
    int t,h;
    node *l,*r;
    int have[2];
    int sw;
    void init(int a, int b);

    int get(int a){
        norm();
        if (!l) return have[1];
        return a<t+h>>1?l->get(a):r->get(a);
    }

    void update(int a, int b){
        if (b<=t || a>=h) return;
        if (a<=t&&b>=h){sw^=1; return;}
        norm();

        l->update(a,b);
        r->update(a,b);
        l->norm(); r->norm();
        REP(f,2) have[f]=l->have[f]+r->have[f];
    }

    void norm(){
        if (!sw) return;
        if (l) l->sw^=1;
        if (r) r->sw^=1;
        sw=0;
        swap(have[0],have[1]);
    }

}tb[maxn];
int pos;
node *getn(){return tb+pos++;}

void node::init(int a, int b){
    t=a; h=b;
    have[0]=b-a;
    if (a+1==b) return;

    l=getn(); r=getn();
    l->init(a,a+b>>1);
    r->init(a+b>>1,b);
}


int main(){
    while(cin>>n,cin){
        int nq; cin>>nq;
        REP(i,n) scanf(" %d",x+i);
        sort(x,x+n);

        REP(i,nq){
            int a,b; scanf(" %d%d",&a,&b);
            a=lower_bound(x,x+n,a)-x;
            b=lower_bound(x,x+n,b+1)-x;
            if (a<b) nd[a].pb(b), st[b].pb(a);
        }

        node *r=getn(); r->init(0,n);

        ll res=1ll*n*(n-1)*(n-2)/6;

        REP(i,n){
            REP(j,nd[i].size()) r->update(i,nd[i][j]);
            REP(j,st[i].size()) r->update(st[i][j],i);
            int xx=r->get(i);
            int c1=r->have[1]-xx;
            res-=1ll*c1*(c1-1)/2;
            r->update(i,i+1);
        }

        cout<<res<<endl;
        REP(i,n+1) st[i].clear(), nd[i].clear();
    }
    return 0;
}

