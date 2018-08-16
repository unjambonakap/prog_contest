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

const int maxn=111;
char a[maxn], b[maxn];
int K;
int n;
vector<vi> lst;
ull fact[maxn];


int main(){
    fact[0]=1;
    FOR(i,1,maxn) fact[i]=fact[i-1]*i;

    while(scanf(" %d",&K)>0){
        scanf(" %s",a);
        scanf(" %s",b);
        n=strlen(a);

        lst.clear();
        REP(i,K){
            vi tb;
            REP(j,K){
                int ok=1;
                for (int u=0; u<n; u+=K) if (a[u+i]!=b[u+j]){ok=0; break;}
                if (ok) tb.pb(j);

            }
            lst.pb(tb);
        }
        sort(ALL(lst));

        ull res=1;
        for (int i=0; i<lst.size();){
            int j=i;
            for (; j<lst.size() && lst[i]==lst[j]; ++j);
            
            int cnt=j-i;
            if (cnt!=lst[i].size()){res=0; break;}
            res=res*fact[cnt];
            i=j;
        }
        cout<<res<<endl;



    }
    return 0;
}

