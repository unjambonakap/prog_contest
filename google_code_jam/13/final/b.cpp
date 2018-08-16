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
typedef pair<double,double> pdd;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const double eps=0e-10;
const int oo=1e9;
const int maxn=55555;
int tb[maxn];
int n;

double det(double a, double b, double c, double d){return a*d-b*c;}

int checkit(double v){
    vector<pair<double,int> > l,r;
    REP(i,n){
        while(l.size()>=2){
            pdd x,y;
            x=l[l.size()-2]; y=l.back();
            if (det(tb[i]-v-x.ST,i-x.ND,y.ST-x.ST,y.ND-x.ND)<-eps) break; 
            l.pop_back();
        }
        l.pb(MP(tb[i]-v,i));
    }

    REP(i,n){
        while(r.size()>=2){
            pdd x,y;
            x=r[r.size()-2]; y=r.back();
            if (det(tb[i]+v-x.ST,i-x.ND,y.ST-x.ST,y.ND-x.ND)>eps) break; 
            r.pop_back();
        }
        r.pb(MP(tb[i]+v,i));
    }

    double a1,b1,a2,b2;
    int p1,p2;
    p1=p2=-1;
    REP(i,n-1){

        if (l[p1+1].ND==i){
            ++p1;
            a1=(l[p1+1].ST-l[p1].ST)/(l[p1+1].ND-i);
            b1=l[p1].ST-a1*i;
        }
        if (r[p2+1].ND==i){
            ++p2;
            a2=(r[p2+1].ST-r[p2].ST)/(r[p2+1].ND-i);
            b2=r[p2].ST-a2*i;
        }

        if (a2*i+b2<a1*i+b1+eps) return 0;
    }
    return 1;

}


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n;
        REP(i,n) scanf(" %d",tb+i);
        double res=oo;

        double T=0, H=oo;
        REP(step,200){
            double M=(T+H)/2;
            if (checkit(M)) H=M;
            else T=M;
        }
        res=T;

        printf("Case #%d: ",ti+1);
        printf("%.15lf\n",res);
    }

    return 0;
}

