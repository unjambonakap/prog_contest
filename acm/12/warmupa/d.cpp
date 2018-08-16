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

const int maxn=1<<19;
ll tree[maxn];
int H[maxn], T[maxn];
int addl[maxn], addr[maxn];
ll sum[maxn], tmp[maxn];
int clr[maxn];

void init(int p, int a, int b){
    H[p]=b; T[p]=a;
    tmp[p]=1ll*(b-a)*(b-a-1)/2;
    if (a+1!=b) init(2*p,a,(a+b)/2), init(2*p+1,(a+b)/2,b);
}

inline void update(int p){
    if (!clr[p]) return;
    clr[p]=0;
    addl[p]=addr[p]=0;
    sum[p]=0;

    tree[p]=0;
    if (T[p]+1!=H[p]) clr[2*p]=clr[2*p+1]=1;
}

inline void norm(int p){
    update(p);
    update(2*p);
    update(2*p+1);
    sum[2*p]+=sum[p];
    sum[2*p+1]+=sum[p];


    addl[2*p]+=addl[p];
    addl[2*p+1]+=addl[p];
    addr[2*p]+=addr[p];
    addr[2*p+1]+=addr[p];

    sum[2*p+1]+=1ll*addl[p]*(T[2*p+1]-T[p]);
    sum[2*p]+=1ll*addr[p]*(H[p]-H[2*p]);

    addl[p]=addr[p]=sum[p]=0;

}

inline ll getv(int p){ update(p); return tree[p]+1ll*(H[p]-T[p])*sum[p]+1ll*(addl[p]+addr[p])*tmp[p]; }


void A(int p, int a, int b){
    if (T[p]>=b||H[p]<=a) return;
    update(p);
    if (T[p]>=a&&H[p]<=b){
        ++addl[p];
        sum[p]+=T[p]-a+1;
        return;
    }
    A(2*p,a,b); A(2*p+1,a,b);
    tree[p]=getv(2*p)+getv(2*p+1);
}

void B(int p, int a, int b){
    if (T[p]>=b||H[p]<=a) return;
    update(p);
    if (T[p]>=a&&H[p]<=b){
        ++addr[p];
        sum[p]+=b-H[p]+1;
        return;
    }
    B(2*p,a,b); B(2*p+1,a,b);
    tree[p]=getv(2*p)+getv(2*p+1);

}

void C(int p, int a, int b, int x){
    if (T[p]>=b||H[p]<=a) return;
    if (T[p]>=a&&H[p]<=b){
        clr[p]=1;
        update(p);
        addl[p]=addr[p]=0;
        sum[p]=x;
        tree[p]=0;
        return;
    }
    norm(p);
    C(2*p,a,b,x); C(2*p+1,a,b,x);
    tree[p]=getv(2*p)+getv(2*p+1);
}

ll S(int p, int a, int b){
    if (T[p]>=b||H[p]<=a) return 0;
    if (T[p]>=a&&H[p]<=b) return getv(p);
    norm(p);
    ll res=S(2*p,a,b)+S(2*p+1,a,b);
    tree[p]=getv(2*p)+getv(2*p+1);
    return res;

}

long long data[250001];
void Aa( int st, int nd ) {
        for( int i = st; i <= nd; i++ ) data[i] = data[i] + (i - st + 1);
}
void Ba( int st, int nd ) {
        for( int i = st; i <= nd; i++ ) data[i] = data[i] + (nd - i + 1);
}
void Ca( int st, int nd, int x ) {
        for( int i = st; i <= nd; i++ ) data[i] = x;
}
long long Sa( int st, int nd ) {
        long long res = 0;
            for( int i = st; i <= nd; i++ ) res += data[i];
                return res;
}

const char *sx="ABCS";

int main(){
    int tn; cin>>tn;
    char c; int a, b, x;
    init(1,0,maxn>>1);
    srand(time(0));

    REP(i,tn){
        //c=sx[rand()%4]; b=rand()%100+1; a=rand()%b+1;
        while((c=getchar())<'A'); scanf(" %d %d", &a,&b);
        --a;
        if (c=='C'){
            scanf("%d", &x);
            C(1,a,b,x);
        }else if (c=='A') A(1,a,b);
        else if (c=='B') B(1,a,b);
        else{
            printf("%Ld\n", S(1,a,b));
        }
    }
    return 0;
}



