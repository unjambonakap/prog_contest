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

const int maxn=111111;
const double oo=1e15;
const int leaf=1<<17;
const double eps=1e-9;

int n;
int x[maxn], y[maxn];

double best[maxn];
int perm[maxn];
int F[maxn];
int pos;
int da[maxn], db[maxn];

int cmp(int a, int b){return x[a]!=x[b]?x[a]<x[b]:y[a]<y[b];}

vector<pair<int,double> > e[maxn];
double dist(double a, double b){return sqrt(a*a+b*b);}


int X;
struct line{
    double a, b;
    int id;
    line(double a, double b, int id=0):a(a),b(b),id(id){}
    double eval(double X)const{return a*X+b;}
    bool operator<(const line &u)const{ double ea=eval(X), eb=u.eval(X); return fabs(ea-eb)>eps?ea<eb:id==-1||u.id==-1?0:eval(X+1)<u.eval(X+1);}
};
multiset<line> s;


void doit(int i, int j){
    FOR(k,i,j){
        int u=perm[k];

        multiset<line>::iterator it, it2;
        it2=s.lower_bound(line(0,y[u],-1));

        it=it2;
        if (it!=s.begin()){
            --it;
            for (; it!=s.begin() && (da[it->id]==u || db[it->id]==u); --it);
            if (!(da[it->id]==u || db[it->id]==u) && F[it->id]){
                int ua=da[it->id], ub=db[it->id];
                double yy=it->eval(x[u]);
                e[u].pb(MP(ua,dist(x[u]-x[ua],yy-y[ua])+fabs(yy-y[u])));
                e[u].pb(MP(ub,dist(x[u]-x[ub],yy-y[ub])+fabs(yy-y[u])));
            }
        }


        it=it2;
        for (; it!=s.end() && (da[it->id]==u || db[it->id]==u); ++it);
        if (it!=s.end() && !F[it->id]){
            int ua=da[it->id], ub=db[it->id];
            double yy=it->eval(x[u]);
            e[ua].pb(MP(u,dist(x[u]-x[ua],yy-y[ua])+fabs(yy-y[u])));
            e[ub].pb(MP(u,dist(x[u]-x[ub],yy-y[ub])+fabs(yy-y[u])));
        }
    }


}

int main(){

    int S,T;
    while(scanf(" %d",&n)>0){

        REP(i,n) scanf(" %d%d",x+i,y+i);
        REP(i,n) e[i].clear();
        cin>>S>>T;
        --S; --T;
        x[n]=x[0]; y[n]=y[0];


        REP(i,n) perm[i]=i;
        sort(perm,perm+n,cmp);

        pos=0;
        s.clear();

        for (int i=0; i<n;){
            int j;
            X=x[perm[i]];

            for (j=i; j<n && x[perm[j]]==x[perm[i]]; ++j);
            doit(i,j);

            for (j=i; j<n && x[perm[j]]==x[perm[i]]; ++j){
                int u=perm[j], va=(u+n-1)%n, vb=(u+1)%n;


                if (x[va]<x[u]) s.erase(line(0,y[u],-1));
                if (x[vb]<x[u]) s.erase(line(0,y[u],-1));

                multiset<line>::iterator ita=s.end(), itb=s.end(), it;
                if (x[va]>x[u]){
                    double ax=1.*(y[va]-y[u])/(x[va]-x[u]);
                    ita=s.insert(line(ax,y[u]-X*ax,pos));
                    da[pos]=u; db[pos]=va; ++pos;
                }

                if (x[vb]>x[u]){
                    double ax=1.*(y[vb]-y[u])/(x[vb]-x[u]);
                    itb=s.insert(line(ax,y[u]-X*ax,pos));
                    da[pos]=u; db[pos]=vb; ++pos;
                }

                if (ita!=s.end() && itb!=s.end() && *itb<*ita) swap(ita,itb);
                if (ita!=s.end()){
                    it=ita; --it;
                    if (ita==s.begin()) F[ita->id]=1;
                    else F[ita->id]=F[it->id]^1;
                }

                if (itb!=s.end()){
                    it=itb; --it;
                    if (itb==s.begin()) F[itb->id]=1;
                    else F[itb->id]=F[it->id]^1;
                }



                if (it==s.begin());
                else{
                }
            }

            doit(i,j);
            i=j;
        }




        REP(i,n){double d=dist(x[i]-x[i+1],y[i]-y[i+1]); e[i].pb(MP((i+1)%n,d)); e[(i+1)%n].pb(MP(i,d));}

        priority_queue<pair<double,int> > q;
        REP(i,n) best[i]=oo;
        best[S]=0;
        q.push(MP(-0.,S));
        while(q.size()){
            double d=-q.top().ST; 
            int a=q.top().ND;
            q.pop();

            if (a==T){printf("%.10lf\n",d); break;}
            if (d!=best[a]) continue;

            REP(i,e[a].size()){
                int b=e[a][i].ST;
                double nd=d+e[a][i].ND;
                if (best[b]>nd) best[b]=nd, q.push(MP(-nd,b));
            }
        }

    }
    return 0;
}

