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

const int maxn=1<<19;


struct data{
    int l,r,t;
    data(){}
    data(int l, int r, int t):l(l),r(r),t(t){}
    bool operator<(const data &d){return t<d.t;}
};

int n,m;
int st[maxn];

data tb[maxn];
vector<data> tb2;
int in[maxn];

ll A[maxn], B[maxn];

ll get(int p, ll *a){
    ll res=0;
    for (++p; p; p&=p-1) res+=a[p];
    return res;
}
void update(int p, int v, ll *a){ for (++p; p<maxn; p+=p&-p) a[p]+=v; }


struct cmp{
    bool operator()(int a, int b){return tb[b]<tb[a];}
};


void add(int a, int b, int v, ll *tb){
    if (a>=b) return;
    update(a,v,tb);
    update(b,-v,tb);
}

int main(){
    while(cin>>n>>m,!cin.eof()){

        memset(in,0,sizeof(in));
        tb2.clear();

        vector<pii> el;
        REP(i,m){
            int a,b,c; scanf(" %d%d%d",&a,&b,&c);
            tb[i]=data(a,b,c);
            el.pb(MP(a,i+1));
            el.pb(MP(b,-i-1));
        }
        REP(i,n) scanf(" %d",st+i);

        sort(ALL(el));
        priority_queue<int,vi,cmp> q;
        int prev=0;

        REP(i,el.size()){
            int a=el[i].ND;
            while(q.size() && !in[q.top()]) q.pop();

            if (q.size() && prev!=el[i].ST) tb2.pb(data(prev,el[i].ST,tb[q.top()].t));
            
            prev=el[i].ST;

            if (a<0) in[-a-1]=0;
            else in[a-1]=1, q.push(a-1);
        }

        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));

        REP(i,tb2.size()){
            int t1=tb2[i].t-tb2[i].r;
            int t2=tb2[i].t-tb2[i].l;

            int a=lower_bound(st,st+n,t1)-st;
            int b=lower_bound(st,st+n,t2)-st;
            add(a,b,-t1,A);
            add(a,b,1,B);
            add(b,n,t2-t1,A);
        }

        REP(i,n){
            ll xa=get(i,A), xb=get(i,B);
            int res=xa+st[i]*xb;
            printf("%d\n",res);
        }
    }
    return 0;
}

