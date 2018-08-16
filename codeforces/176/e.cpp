#include <vector>
#include<complex>
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

typedef complex<double> point;
const int maxn=1<<21;
const double pi=acos(-1);

int n,m;
int rev[maxn];
int is[maxn];
point ca[maxn],cb[maxn],cc[maxn];

void dft(point *tb, point w, int nb){
    point wl[nb+1];
    wl[0]=1;
    wl[1]=w;
    FOR(i,1,nb) wl[i+1]=wl[i]*wl[i];
    int n=1<<nb;
    for (int i=1, x=nb; x>0; i<<=1, --x){
        point ww=wl[x];
        assert(2*i<=n);
        for (int j=0; j<n; j+=2*i){
            point u=1;
            for (int k=j; k<j+i; ++k){
                point tmp=u*tb[k+i];
                tb[k]+=tmp;
                tb[k+i]=tb[k]-2.*tmp;
                u*=ww;
            }
        }
    }
}

vi mul(vi a, vi b){
    int nb=0;
    for (; 1<<nb<m+1; ++nb);
    ++nb;


    FOR(i,1,1<<nb){
        int lb=i&-i;
        rev[i]=rev[i^lb]|(1<<nb)/lb/2;
    }

    point w=point(cos(2*pi/(1<<nb)),sin(2*pi/(1<<nb)));

    REP(i,1<<nb) ca[i]=0, cb[i]=0;

    REP(i,a.size()) ca[rev[i]]=point(a[i],0);
    REP(i,b.size()) cb[rev[i]]=point(b[i],0);
    


    dft(ca,w,nb);
    dft(cb,w,nb);
    REP(i,1<<nb) cc[rev[i]]=ca[i]*cb[i];
    dft(cc,conj(w),nb);

    vi res;
    REP(i,m+1) res.pb(abs(cc[i])/(1<<nb)+0.5);
    return res;
}

int main(){
    while(cin>>n>>m,!cin.eof()){
        vi tb(m+1,0);
        memset(is,0,sizeof(is));
        REP(i,n){
            int a;
            scanf(" %d",&a);
            tb[a]=1;
            is[a]=1;
        }

        vi res=mul(tb,tb);
        int ok=1;
        FOR(i,1,m+1) if (res[i]&&(!tb[i]&&!is[i])){ok=0; break;}
        if (!ok) puts("NO");
        else{
            puts("YES");

            vi ans;
            REP(i,m+1) if (tb[i]&&!res[i]) ans.pb(i);
            printf("%d\n",ans.size());
            REP(i,ans.size()) printf("%d ",ans[i]);
            puts("");
        }
    }
    return 0;
}

