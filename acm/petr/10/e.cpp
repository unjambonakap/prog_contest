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

const int maxd=4;
const int maxt=1300;
const double oo=1e100;
const double eps=1e-9;
const int maxn=1000;
const int maxp=11;

int n;
int p;

double x[maxn][maxp];
double y[maxn];

double x2[maxn][maxp];
double f2[maxn];
int n2;


int tree[maxt][2<<maxd];
double tree2[maxt][2<<maxd];

double f[maxn];
double r[maxn];
double val[maxn];
int tmp[maxn];
int cmpp;
int st;
double rate=0.1;

int cmp(int a, int b){ return x[a][cmpp]<x[b][cmpp]; }


double F[maxn], F2[maxn];

double sqr(double a){return a*a;}
void disp(int a, int b){
    if (st++) printf(" ");
    assert(b<2<<maxd);
    if (tree[a][b]==-1) printf("0 %lf",tree2[a][b]);
    else printf("%d %.12lf",tree[a][b]+1,tree2[a][b]), disp(a,2*b),disp(a,2*b+1);
}


double eval(int id, double *a){
    int u=1;
    
    for (;;){
        int pp=tree[id][u];
        if (pp==-1) return tree2[id][u];
        if (a[pp]<tree2[id][u]) u=2*u;
        else u=2*u+1;
    }
}

double sq(int a, int b){
    double mean=(F[b]-F[a])/(b-a);
    return F2[b]-F2[a]+(b-a)*mean*mean-2*mean*(F[b]-F[a]);
}

double geterr(int n){
    double res=0;
    REP(i,n) res+=sqr(y[i]-f[i]);
    return sqrt(res/n);
}

void read2(){
    FILE *f=fopen("easy.hidden_in","r");
    n2=1000;
    assert(f);
    REP(i,n2) REP(j,p+1) fscanf(f," %lf",x2+j);
    fclose(f);
}

void update2(int tt){ REP(i,n2) f2[i]+=eval(tt,x2[i]+1); }

double geterr2(){
    double res=0;
    REP(i,n2) res+=sqr(f2[i]-x2[i][0]);
    res=sqrt(res/n2);
    return res;
}

double checkit2(int nt){
    double res=0;
    REP(i,n2){
        double u=0;
        REP(j,nt) u+=eval(j,x2[i]+1);
        res+=sqr(u-x2[i][0]);
    }
    return sqrt(res/n2);
}

void grow(int wt, int pos, int *lst, int n, int d){

    //printf("GROWING %d %d %d %d\n",wt,pos,n,d);
    if (n<=20 || d==maxd-1){//average
        //printf("CHILD WITH SZ %d\n",n);
        double mean=0;
        REP(i,n) mean+=r[lst[i]];
        mean/=n;
        tree[wt][pos]=-1;
        mean*=rate;
        tree2[wt][pos]=mean;
        REP(i,n) val[lst[i]]=mean;
        return;
    }
    double best=oo;
    int sp=-1, spos=-1;

    REP(j,p){
        cmpp=j;

        sort(lst,lst+n,cmp);
        REP(i,n){
            double ya=r[lst[i]];
            F[i+1]=F[i]+ya;
            F2[i+1]=F2[i]+ya*ya;
        }
        for (int i=0; i<n-1;){
            for (; i<n-1 && x[lst[i]][j]+eps>x[lst[i+1]][j]; ++i);
            double score=sq(0,i+1)+sq(i+1,n);
            if (score<best) best=score, sp=j,spos=i+1;
            ++i;
        }
    }

    if (sp==-1){
        tree[wt][pos]=-1;
        tree2[wt][pos]=0;
        return;
        assert(sp!=-1);   

    }

    cmpp=sp;
    sort(lst,lst+n,cmp);
    
    tree[wt][pos]=sp;
    tree2[wt][pos]=(x[lst[spos-1]][sp]+x[lst[spos]][sp])/2;

    //printf("HERE %d %d // %d (( score %lf\n",sp,spos,n,best);
    grow(wt,2*pos,lst,spos,d+1);
    grow(wt,2*pos+1,lst+spos,n-spos,d+1);

}


int go(int n){
    int step=0;
    memset(f,0,sizeof(f));
    memset(f2,0,sizeof(f2));

    //printf("%lf\n",geterr(n)/n);
    for (; step<maxt; ++step){

        REP(i,n) r[i]=y[i]-f[i];
        REP(i,n) tmp[i]=i;

        grow(step,1,tmp,n,0);

        REP(i,n) f[i]+=val[i];
        //update2(step);

        //if (step%100==0) printf("%d >> %lf >> %lf\n",step,geterr(n),geterr2());
    }
    //printf("%lf\n",geterr(n));
    return step;
}


int main(){
    freopen("easy.in","r",stdin);
    freopen("easy.out","w",stdout);
    n=1000;
    p=10;
    REP(i,n){
        scanf(" %lf",y+i);
        REP(j,p) scanf(" %lf",x[i]+j);
    }

    //read2();
    int nt=go(1000);

    //cout<<checkit2(nt)<<endl;

    if (1){
        printf("%d\n",nt);
        REP(i,nt) st=0, disp(i,1), puts("");
    }

    return 0;
}

