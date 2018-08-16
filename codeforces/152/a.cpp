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

double dist(double a, double b){return sqrt(a*a+b*b);}

int main(){
    int y1,y2,yw,xb,yb,r;
    cin>>y1>>y2>>yw>>xb>>yb>>r;
    xb=-xb;

    double T=xb, H=0;
    int ok=0;
    REP(step,100){
        double M=(T+H)/2;

        double rx=(yw-r-yb)/(M-xb);

        double yf=yw-r+M*rx;
        
        if (dist(M,yw-r-y2)<=r) H=M;
        else if (yf>y2-r) H=M;
        else{
            double aa=atan2(y2-yw+r,-M)-asin(r/dist(y2-yw+r,M));
            double bb=atan2(yf-yw+r,-M);
            if (bb>aa) H=M;
            else T=M;
        }
    }
    double xx=T;

    T=xb, H=0;
    REP(step,100){
        double M=(T+H)/2;

        double rx=(yw-r-yb)/(M-xb);

        double yf=yw-r+M*rx;
        if (yf>=y1+r) H=M;
        else T=M;
    }
    double yy=H;

    if (xx>=yy) printf("%lf\n",-(xx+yy)/2);
    else puts("-1");

    return 0;
}

