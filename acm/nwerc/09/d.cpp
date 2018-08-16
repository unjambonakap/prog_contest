#include <vector>
#include<complex>
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


typedef complex<double> point;

const int maxn=111;
point lst[maxn];
point px[maxn];

double frac[maxn];
double sx[maxn];
double rx[maxn];
int n;
point res;

void go(int d, double F, point rot){
    if (d==0){
        res+=px[n-1]*rot*F;
        return;
    }

    REP(i,n-1) if (F<=frac[i+1]){
        double nf=(F-frac[i])/(frac[i+1]-frac[i]);
        res+=px[i]*rot;
        go(d-1,nf,rot*polar(sx[i],rx[i]));
        return;
    }
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n;
        int xo,yo; scanf(" %d%d",&xo,&yo);
        int xl=xo, yl=yo;
        px[0]=point(0,0);
        REP(i,n-1){
            int x,y; scanf(" %d%d",&x,&y);
            px[i+1]=point(x-xo,y-yo);
            lst[i]=point(x-xl,y-yl);
            xl=x; yl=y;
        }

        double l=0;
        REP(i,n-1) l+=abs(lst[i]);

        frac[0]=0;
        REP(i,n-1) frac[i+1]=frac[i]+abs(lst[i])/l;
        REP(i,n-1) sx[i]=abs(lst[i])/abs(px[n-1]);
        REP(i,n-1) rx[i]=arg(lst[i])-arg(px[n-1]);

        int d; double F;
        scanf(" %d%lf",&d,&F);

        res=point(xo,yo);
        point tmp=polar(1.,0.);
        go(d,F,tmp);
        printf("(%.12lf,%.12lf)\n",res.real(),res.imag());
    }

    return 0;
}


