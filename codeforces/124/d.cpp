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


const int maxn=1<<20;
const int mul=31;

ll pw[maxn];
ll a[maxn], b[maxn];
int K, n;
int na, nb;
char s[maxn];

void update(ll *a, int p, ll v){++p; while(p<maxn) a[p]+=v, p+=p&-p;}
ll get(ll *a, int p){ll res=0; ++p; while(p) res+=a[p], p&=p-1; return res;}


int cmp(int pa, int pb, int n){
    ll va=get(a,pa+n)-get(a,pa),vb=get(b,pb+n)-get(b,pb);
    if (pa<pb) va*=pw[pb-pa];
    else vb*=pw[pa-pb];
    return va==vb;
}


int checkit(int p){
    if (p-2*na+1>=0 && cmp(p-2*na+1,n-1-p,na)) return 1;
    if (p-2*nb>=0 && cmp(p-2*nb,n-1-p,nb)) return 1;
    return 0;
}


void setpos(int i, char c, char pc=0){
    s[i]=c;
    update(a,i+1,(c-pc)*pw[i]), update(b,n-i,(c-pc)*pw[n-i-1]);
}

int add(int p){
    FOR(i,p+1,n) setpos(i,0,s[i]);
    while(p>=0){
        for (; p>=0; --p){
            setpos(p,(s[p]+1)%26,s[p]);
            if (s[p]){
                if (checkit(p)) break;
                else return 0;
            }
        }
    }
    return 1;
}



int main(){
    cin>>K;
    nb=K/2;
    na=nb+(K&1);

    scanf(" %s", s);
    if (K==1){ puts("Impossible"); return 0; }
    n=strlen(s);
    REP(i,n) s[i]-='a';

    pw[0]=1;
    REP(i,n) pw[i+1]=pw[i]*mul;

    REP(i,n) setpos(i,s[i],-1);
    int px=n-1;
    REP(i,n) if (checkit(i)){px=i; break;}


    if (add(px)) puts("Impossible");
    else{
        REP(i,n) if (checkit(i)){
            setpos(i,s[i]+1,s[i]);
            if (checkit(i)) setpos(i,s[i]+1,s[i]);
        }
        REP(i,n) s[i]+='a';
        printf("%s\n",s);
    }

    return 0;
}



