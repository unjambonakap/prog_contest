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

const int n=1000;
const int p=10;
const int maxd=4;
const int maxt=10000;
const double oo=1e100;


double x[n][p];
double y[n];

int tree[maxt][2<<maxd];
double tree2[maxt][2<<maxd];

double f[n];
double r[n];
double val[n];
int tmp[n];
int cmpd;

int cmp(int a, int b){ return x[a][cmpd]<x[b][cmpd]; }


double F[maxn], F2[maxn];

void disp(int a, int b){

}


double sq(int a, int b){
    double mean=(F[b]-F[a])/(b-a);
    return F2[b]-F2[a]+(b-a)*mean*mean-2*mean*(F[b]-F[a]);
}


void grow(int wt, int pos, int *lst, int n, int d){
    if (n<=5 || d==maxd){//average
        double mean=0;
        REP(i,n) mean+=y[lst[i]];
        mean/=n;
        tree[wt][pos]=-1;
        tree2[wt][pos]=mean;
    }
    double best=oo;
    int sd=-1, spos=-1;

    REP(j,d){
        cmpd=j;

        sort(lst,lst+n,cmp);
        REP(i,n){
            double ya=y[lst[i]];
            F[i+1]=F[i]+ya;
            F2[i+1]=F2[i]+ya*ya
        }
        for (int i=0; i<n-1;){
            for (; i<n-1 && x[lst[i]][j]+eps>x[lst[i+1][j]]; ++i);
            double score=sq(0,i+1)+sq(i+1,n);
            if (score<best) score=best, sd=j,spos=i;
        }
    }

    assert(sd!=-1);

    cmpd=sd;
    sort(lst,lst+n,cmp);
    grow(wt,2*pos,lst,spos,d+1);
    grow(wt,2*pos+1,lst+spos,n-spos,d+1);

    tree[wt][pos]=sd;
    tree2[wt][pos]=(x[lst[spos]]+x[lst[spos+1]])/2;
}


int go(){
    int step=0;
    memset(f,0,sizeof(f));

    for (; step<maxt; ++step){
        REP(i,n) r[i]=y[i]-f[i];
        REP(i,n) tmp[i]=i;

        grow(step,1,tmp,n,0);

        REP(i,n) f[i]+=val[i];
    }
    return step;
}


int main(){
    REP(i,n){
        scanf(" %lf",y+i);
        REP(j,p) scanf(" %lf",x[i]+j);
    }
    int res=go();

    printf("%d\n",res);
    REP(i,res) disp(i,0);
    

    return 0;
}

