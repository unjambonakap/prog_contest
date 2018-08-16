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

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=16;
const int mod=10000;
int n;
int mp[maxn][maxn];
int dp[two(maxn)];
int ne[two(maxn)];
int e[maxn];
int pt[maxn*maxn+1];

int main(){
    
    cin>>n;
    getchar();
    pt[0]=1;
    REP(i, n*n) pt[i+1]=pt[i]*2%mod;

    REP(i, n){
        string s; cin>>s;
        e[i]=0;
        REP(j, n) e[i]|=two(j)*(mp[i][j]=s[j]=='1');
    }


    REP(i, two(n)) if (i){
        int q=0;
        int rmp[maxn];
        ne[i]=0;
        REP(j, n) if (i&two(j)){
            ne[i]+=count_bit(e[j]&i);
            rmp[q++]=j;
        }
        ne[i]=pt[ne[i]/2];

        int cnt=0;
        REP(j, two(q-1)-1){
            int m=two(rmp[q-1]);
            REP(k, q-1) if (j&two(k)) m|=two(rmp[k]);
            cnt=(cnt+dp[m]*ne[i^m])%mod;

        }
        dp[i]=(mod+ne[i]-cnt)%mod;
    }
    printf("<< %d\n", dp[two(n)-1]);



    return 0;

}




