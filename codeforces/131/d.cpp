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


const double pi=acos(-1);
double ca=cos(2*pi/5), cb=cos(pi/5);
double sa=sin(2*pi/5), sb=sin(pi/5);
int order[]={1,3,2,0};


double xo[]={-sa,-sb,sb,0};
double yo[]={ca,-cb,-cb,1};
double dist(double a, double b){return sqrt(a*a+b*b);}

int main(){
    int n; cin>>n;
    double side=dist(xo[0]-xo[1],yo[0]-yo[1]);
    REP(i,4) xo[i]*=10/side, yo[i]*=10/side;
    sa*=10/side;

    cout<<4*n+1<<endl;


    double x=sa;
    REP(i,n){
        REP(j,4) printf("%.15lf %.15lf\n", xo[j]+x,yo[j]);
        x+=2*sa;
    }
    printf("%.15lf %.15lf\n", xo[0]+x,yo[0]);
    REP(i,n){int u=4*i+1; printf("%d %d %d %d %d\n", u,u+1,u+2,u+4,u+3);}
    REP(i,n+1) printf("%d ", 4*i+1);
    for (int i=n-1; i>=0; --i) REP(j,4) printf("%d ", 4*i+order[j]+1);
    puts("");
    return 0;
}


