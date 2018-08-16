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

int n, R;

int besta, bestc;
string bestb;

void go(int a, int b){
    vi x;
    int old=b;
    int cnt=0;
    int u=0;
    while(a>1 && b>0){
        ++u;
        int c=a-b;
        if (c<=b) a=b, b=c;
        else a=c, ++cnt;
        
    }
    if (a==1 && b==1 && u==n && cnt<besta) besta=cnt, bestc=old;
}


void build(int a, int b){
    vi x;
    while(a>1 && b>0){
        int c=a-b;
        if (c<=b) a=b, b=c, x.pb(1);
        else a=c, x.pb(0);
        
    }
    reverse(ALL(x));
    int f=0;
    REP(i,n) f^=x[i], bestb.pb(f?'B':'T');

}

int main(){
    cin>>n>>R;
    --n;
    besta=n+1;
    bestc=-1;
    FOR(i,1,R+1) go(R,i);

    if (bestc!=-1) build(R,bestc);

    if (besta==n+1) cout<<"IMPOSSIBLE"<<endl;
    else printf("%d\nT%s\n",besta,bestb.c_str());

    return 0;
}


