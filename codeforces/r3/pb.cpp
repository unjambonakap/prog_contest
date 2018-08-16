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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxn=1e5+10;
pii tb[maxn];
struct cmpA{ bool operator()(int a, int b)const{return tb[a].ND*tb[b].ST>tb[b].ND*tb[a].ST;}};

int main(){
    int n, v;
    cin>>n>>v;
    int perm[n];
    REP(i, n) perm[i]=i;
    REP(i, n) cin>>tb[i].ST>>tb[i].ND;
    sort(perm, perm+n, cmpA());


    set<int> lst;
    int last=-1;
    int i=0, c=0, r=0;
    while(i<n && c+tb[perm[i]].ST<=v){
        c+=tb[perm[i]].ST;
        r+=tb[perm[i]].ND;
        if (tb[perm[i]].ST==1) last=perm[i];
        lst.insert(perm[i]);
        ++i;
    }
    if (i<n && c<v){
        int j=i;
        int ra=r;
        if (last!=-1 && r<r-tb[last].ND+tb[perm[i]].ND){r=r-tb[last].ND+tb[perm[i]].ND; lst.erase(last); lst.insert(perm[i]);}
        while(++j<n) if (tb[perm[j]].ST==1 && r<ra+tb[perm[j]].ND){lst.insert(perm[j]); r=ra+tb[perm[j]].ND; ++i; break;}
    }
    printf("%d\n", r);

    FE(it, lst) printf("%d ", *it+1); printf("\n");

    return 0;

}

