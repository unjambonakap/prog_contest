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

double x,p,q;
const int maxv=10000;
const double eps=1e-5;

struct matrix{
    double m[2][2];
    matrix(){REP(i,2) REP(j,2) m[i][j]=0;}
    void ident(){REP(i,2) REP(j,2) m[i][j]=i==j;}
    matrix(const matrix &a){memcpy(m,a.m,sizeof(m));}

    matrix operator*(const matrix &a)const{
        matrix res;
        REP(k,2) REP(i,2) REP(j,2) res.m[i][j]+=m[i][k]*a.m[k][j];
        return res;
    }
};

const int maxn=26000;
double dp[maxn][2];

matrix faste(matrix a, int p){
    matrix x; x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=x*a;
    return x;
}

double eval(int i, int j){
    double ca=(1-x)*(i-1), cb=j+1;

    //matrix a;
    //a.m[0][0]=1/q; a.m[0][1]=-p/q;
    //a.m[1][0]=1; a.m[1][1]=0;

    //matrix aa=faste(a,j-i+1);
    double va=dp[j-i+1][0], vb=dp[j-i+1][1];
    double v=(ca-cb*vb)/va;


    //aa=faste(a,j);
    va=dp[j][0], vb=dp[j][1];
    double val=va*v+vb*cb;
    return val;
}

int main(){

    while(scanf(" %lf%lf",&x,&p)>0){
        p/=100.;
        x/=100.;
        q=1-p;

        matrix a;
        a.m[0][0]=1/q; a.m[0][1]=-p/q;
        a.m[1][0]=1; a.m[1][1]=0;
        dp[0][0]=1; dp[0][1]=0;
        REP(j,maxn-1){
            dp[j+1][0]=dp[j][0]/q+dp[j][1];
            dp[j+1][1]=-dp[j][0]*p/q;
        }


        int l=0, r=0;
        if (0) REP(step,8){

            int T=0, H=maxv;
            int best=0;
            int fd=0;

            while(T<=H){
                int M=T+H>>1;
                if (eval(l,r+M+1)-eval(l,r+M)>eps) T=M+1, best=M+1;
                else H=M-1;
            }
            r+=best;
            fd+=best;



            T=0, H=maxv;
            best=0;
            while(T<=H){
                int M=T+H>>1;
                if (eval(l-M-1,r)-eval(l-M,r)>eps) T=M+1, best=M+1;
                else H=M-1;
            }
            fd+=best;
            l-=best;

        }

        double res=0;
        //FOR(i,-10,11) FOR(j,-10,11) if (l+i<=0 && r+j>=0) res=max(res,eval(l+i,r+j));

        int bi,bj;
        for (int i=-21000; i<=0; ++i) for (int j=0; j<2500; ++j){
            double v=max(res,eval(i,j));  
            if (res<v) res=v,bi=i, bj=j;
        }

        //cout<<eval(0,2000)<<endl;
        printf("%.9lf\n",res);
    }
    return 0;
}



