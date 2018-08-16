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

const double eps=1e-9;
const int maxs=1<<13;
const int maxr=16;

struct state{
    vector<int> a;
    int b;
    bool operator<(const state &s)const{
        if (b!=s.b) return b<s.b;
        return a<s.a;
    }
    ll hash()const{
        ll h=b;
        REP(i,a.size()) h=h*1009+a[i];
        return h;
    }
};

int r, c; double p;
int nstate[maxr];
double pnext[4];


int next[maxr][maxr][maxs][4];
state inv[maxr][maxs];
map<int,int> rmp[maxr];
double dp[2][maxs];

int getid(const state &s){
    ll h=s.hash();
    if (rmp[r].count(h)) return rmp[r][h];
    inv[r][nstate[r]]=s;
    return rmp[r][h]=nstate[r]++;
}

double doit(int _r, int _c){
    r=_r; c=_c;
    if (nstate[r]==0){
        state s;
        REP(i,r) s.a.pb(two(i));
        s.b=0;
        getid(s);
    }
    pnext[0]=(1-p)*(1-p);
    pnext[2]=pnext[1]=p*(1-p);
    pnext[3]=p*p;

    int p=0, np=1;
    memset(dp,0,sizeof(dp));
    dp[p][0]=1.;

    REP(_c,c) REP(i,r) if (i||_c){
        memset(dp[np],0,sizeof(dp[np]));
        int na=nstate[r];
        REP(u,na){
            double px=dp[p][u];
            if (next[r][i][u][0]==-1){
                const state &s=inv[r][u];
                REP(f,4){

                    state ns; ns.a.pb(two(i));
                    ns.b=-1;
                    REP(j,s.a.size()){

                        if (((f&1)&&(s.a[j]&two(i))) || (i&&(f&2)&&(s.a[j]&two(i-1)))){
                            if (s.b==j) ns.b=0;
                            ns.a[0]|=s.a[j];
                        }else{ 
                            ns.a.pb(s.a[j]&(two(r)-1^two(i)));
                            if (ns.a.back()==0) ns.a.pop_back();
                            else if (s.b==j) ns.b=ns.a.size()-1;
                        }
                    }
                    if (ns.b==-1){next[r][i][u][f]=-2; continue;}
                    int x=ns.a[ns.b];
                    sort(ALL(ns.a));
                    REP(k,ns.a.size()) if (ns.a[k]==x){ns.b=k; break;}
                    int y=getid(ns);

                    next[r][i][u][f]=y;
                    dp[np][y]+=px*pnext[f];
                }
            }else REP(f,4) if (next[r][i][u][f]!=-2) dp[np][next[r][i][u][f]]+=px*pnext[f];
        }
        p=np; np^=1;
    }
    double res=0.;
    REP(i,nstate[r]) if (inv[r][i].a[inv[r][i].b]&two(r-1)) res+=dp[p][i];
    
    return res;
}

double faste(double a, ll p){
    double x=1.;
    for (; p; p>>=1, a=a*a) if (p&1) x*=a;
    return x;
}


int main(){
    int tn; cin>>tn;
    memset(next,-1,sizeof(next));
    int step=20;

    REP(ti,tn){
        int r;ll c;

        cin>>r>>c>>p;
        p=1-p;
        if (c<step) printf("%.15lf\n", doit(r,c));
        else{
            double a=doit(r,step), b=doit(r,step+1);
            if (b<eps) printf("%.15lf\n", b);
            else printf("%.18lf\n", a*faste(b/a,c-step));
        }

    }
    return 0;
}


