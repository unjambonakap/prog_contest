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

const int maxn=1<<18;
int n;
int a[maxn];

struct node{
    vector<ll> st, nd;
    ll S;
    node *l, *r;

    ll query(ll v){
        if (!l){
            assert(st.size()==1);
            return st[0]>=v;
        }
        ll res=l->query(v)+r->query(v);
        vector<ll> &ua=l->nd, &ub=r->st;

        REP(i,ua.size()){
            int best=-1;
            int T=0, H=ub.size()-1;
            while(T<=H){
                int M=T+H>>1;
                if (ua[i]+ub[M]>=v) best=M, T=M+1;
                else H=M-1;
            }
            res+=best+1;
        }
        return res;

    }


};

node *init(int l, int r){
    node *x=new node();
    x->l=x->r=0;
    if (l+1==r){ x->S=a[l]; x->st.pb(a[l]); x->nd.pb(a[l]); return x; }

    x->l=init(l,l+r>>1);
    x->r=init(l+r>>1,r);
    x->S=x->l->S+x->r->S;

    x->st=x->l->st;
    vector<ll> &tmpa=x->r->st;
    REP(i,tmpa.size()) x->st.pb(tmpa[i]+x->l->S);
    sort(ALL(tmpa),greater<ll>());

    x->nd=x->r->nd;
    vector<ll> &tmpb=x->l->nd;
    REP(i,tmpb.size()) x->nd.pb(tmpb[i]+x->r->S);
    sort(ALL(tmpb),greater<ll>());
    return x;
}


int main(){
    ll k; cin>>n>>k;
    //n=1e5;
    //REP(i,n) a[i]=rand()%1000000000-500000000;
    //k=n*(n-1)/2-100;

    REP(i,n) scanf(" %d", a+i);
    node *root=init(0,n);


    ll T=-1e15, H=1e15;
    ll best=T;
    while(T<=H){
        ll M=(T+H)/2;
        if (root->query(M)>=k) T=M+1, best=M;
        else H=M-1;
    }
    cout<<best<<endl;


    return 0;
}

