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

const int maxn=111111;
ll px[22];
int take[maxn];

int main(){
    px[0]=1; REP(i,21) px[i+1]=px[i]*10;

    ll x; int n;
    cin>>x>>n;
    vector<pair<ll,pii> > tb;

    REP(i,n){
        ll q; int k;
        scanf(" %d%Ld",&k,&q);
        tb.pb(MP(px[k]*q,MP(k,i)));
    }
    sort(ALL(tb));
    reverse(ALL(tb));
    int cnt=0;
    int fd=0;

    int prec=18;
    REP(i,n){
        int j=i;
        int best=i;
        for (; j<n && tb[j].ST>=x; ++j) if (tb[best].ND.ST>tb[j].ND.ST) best=j;
        prec=min(prec,tb[best].ND.ST);
        take[tb[best].ND.ND]=1;
        ++cnt;
        if (j==i) x-=tb[i].ST, ++j;
        else x%=px[prec];
        if (!x) break;
        i=j-1;
    }


    if (x) puts("-1");
    else{
        printf("%d\n", cnt);
        int st=0;
        REP(i,n) if (take[i]){
            if (st++) printf(" ");
            printf("%d",i+1);
        }
        puts("");
    }
    return 0;
}

