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

int isleap(int a){
    if (a%4) return 0;
    if (a%100) return 1;
    if (a%400) return 0;
    return 1;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        string s; int a, b;
        string t; int u, v;
        cin>>s>>a; getchar();cin>>b;
        cin>>t>>u; getchar(); cin>>v;
        if (s=="January" || s=="February");
        else ++b;

        if (t=="January" || t=="February"&&u<29) --v;
        while(b%4) ++b;
        while(v%4) --v;
        int ans=0;
        if (b<=v) ans+=(v-b)/4+1;
        while(b%100) ++b;
        while(v%100) --v;
        if (b<=v) ans-=(v-b)/100+1;
        while(b%400) ++b;
        while(v%400) --v;
        if (b<=v) ans+=(v-b)/400+1;
        printf("Case %d: %d\n", ti+1, ans);


    }
    return 0;
}


