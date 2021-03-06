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

const int maxc=1e6+10;
const int maxv=330;

int geta(int a){
    int res=0;
    REP(i,a+1) res+=i*i;
    return res;
}
int getb(int a){
    int res=0;
    for (int i=a; i>=0; i-=2) res+=i*i;
    return res;
}

int dp[maxc];
ll h[maxc];

int main(){

    vector<pair<int,pii> > tb;
    for (int i=2; ; ++i){
        int x=geta(i); if (x>maxc) break;
        tb.pb(MP(x,MP(0,i)));
    }for (int i=3; ; ++i){
        int x=getb(i); if (x>maxc) break;
        tb.pb(MP(x,MP(1,i)));
    }
    sort(ALL(tb));
    memset(dp,0x7f,sizeof(dp));
    dp[0]=0;
    h[0]=0;
    REPV(i,tb.size()) REPV(k,maxc-tb[i].ST){
        int x=k+tb[i].ST;
        if (dp[x]>dp[k]+1){dp[x]=dp[k]+1; h[x]=h[k]*maxv+i+1;}
        else if (dp[k+tb[i].ST]==dp[k]+1){
            ll nh=h[k]*maxv+i+1;
            if (nh>h[x]) h[x]=nh;
        }


    }



    int c;
    int tn=0;
    while(cin>>c, c){
        ++tn;
        printf("Case %d:", tn);
        int fd=0;
        if (dp[c]>7) printf(" impossible\n");
        else{
            ll v=h[c];
            vs ans;
            while(v){
                int val=v%maxv-1;
                v/=maxv;
                ans.pb(toStr(tb[val].ND.ND)+(tb[val].ND.ST?"L":"H"));
            }
            reverse(ALL(ans));
            FE(it,ans) cout<<' '<<*it;
            puts("");
        }
    }
    return 0;

}


