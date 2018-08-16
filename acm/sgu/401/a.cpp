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
typedef unsigned int uint;
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

const int maxn=55;
const int oo=1e5;
int n,u,t;
int w[maxn], v[maxn];
double ans[maxn];
double res;

double eval(int v, int d, double t){ return v+u*u*t/sqrt(u*u*t*t-d*d); }
double eval2(int v, int d, double t){return v*t+sqrt(u*u*t*t-d*d);}

pair<double,double> go(int v, int d, double fx){
    pair<double,double> res=MP(0.,0.);
    double T=1.*d/u, H=oo;

    REP(step,200){
        double M=(T+H)/2;
        if (eval(v,d,M)<=fx) H=M;
        else T=M;
    }
    res.ST=T;
    res.ND=eval2(v,d,T);
    return res;
}

int checkit(double x){
    double tx=0;
    res=0;
    REP(i,n){
        pair<double,double> u=go(v[i],w[i],x);
        ans[i]=u.ST;
        tx+=ans[i];
        res+=u.ND;
    }

    return tx<=t;

}

int main(){
    while(cin>>n>>u>>t,!cin.eof()){
        int s=0;
        REP(i,n) scanf(" %d%d",w+i,v+i), s+=w[i];

        if (u*t<s) puts("-1");
        else{
            if (u*t==s){
                REP(i,n) res+=1.*w[i]*v[i]/u;
                REP(i,n) ans[i]=1.*w[i]/u;
            }else{
                double T=0, H=oo;

                REP(step,200){
                    double M=(T+H)/2;
                    if (checkit(M)) H=M;
                    else T=M;
                }
                assert(T<oo-1);
            }

            res=sqrt(res*res+1.*s*s);
            printf("%.10lf\n",res);
            REP(i,n) printf("%.10lf%c",ans[i]," \n"[i==n-1]);
        }
    }

    return 0;
}

