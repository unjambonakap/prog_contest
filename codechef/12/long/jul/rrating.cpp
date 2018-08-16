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


int tree[1<<20];
int query(int a, int b){
    if (a>=1<<19) return a-(1<<19);
    if (b>=tree[2*a]) return query(2*a+1,b-tree[2*a]);
    return query(2*a,b);
}

int main(){
    int nq; cin>>nq;
    vi l, lst;
    REP(i,nq){
        int a; scanf(" %d", &a);
        if (a==1){
            int b; scanf(" %d", &b);
            lst.pb(b); l.pb(b);
        }else lst.pb(-1);
    }
    sort(ALL(l));
    int n=0;
    REP(i,nq){
        if (lst[i]==-1){
            int p=n-n/3;
            if (p==n) puts("No reviews yet");
            else printf("%d\n", l[query(1,p)]);
        }else{
            int a=lower_bound(ALL(l),lst[i])-l.begin();
            a+=1<<19;
            while(a) ++tree[a], a>>=1;
            ++n;
        }
    }

    return 0;
}


