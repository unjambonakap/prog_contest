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

const int maxn=111;
int n;
int x[maxn], y[maxn];

const double eps = 1e-7;
const double SM_INF = 1e6; // objective function coefficient for artificial variables
typedef vector<double> vd;
struct SimplexM{
    int startN, N;
    vd old_c,c,b,res;
    vector<vd> system;
    double value;
    SimplexM(vd c):N(c.size()),c(c){ } // objective function (minimize)
    void add(vd r,double v,int sgn=0){ // v >= 0
        for(;c.size()<r.size();c.pb(0));
        for(;r.size()<c.size();r.pb(0));
        if(sgn)r.pb(-sgn),c.pb(0);
        system.pb(r),b.pb(v);
    }
    void refresh_c_func(int pos,int row){
        double begin=c[pos];
        REP(i,N) c[i]-=begin*system[row][i];
    }
    void gauss(int row,int col){
        double v=system[row][col];
        REP(i,N) system[row][i]/=v;
        b[row]/=v;
        REP(i,system.size()) if(i!=row){
            v=system[i][col];
            REP(j,N) system[i][j]-=v*system[row][j];
            b[i]-=v*b[row];
        }
    }
    // -2 - NO SOLUTION
    // -1 - minimum is infinity (minimum does not exists)
    // 1 - OK
    int solve(){
        N=c.size(),old_c=c;
        int m=system.size();
        REP(i,m)system[i].resize(N);
        startN=N;
        vi base(m,-1);
        REP(i,N){
            int nm=0,pos=-1;
            REP(j,m) if(fabs(system[j][i])>eps) nm++,pos=j;
            if(nm==1 && fabs(system[pos][i]-1)<eps && base[pos]==-1)
                base[pos]=i;
        }
        REP(i,m) if(base[i]==-1){
            N++;
            c.pb(SM_INF);
            REP(j,m) system[j].pb(j==i?1:0);
            base[i]=N-1;
        }
        REP(i,m) refresh_c_func(base[i],i);
        while(1){
            int pos=-1,row=-1;
            REP(i,N) if(c[i]<-eps && (pos==-1 || c[i]<c[pos])) pos=i;
            if(pos==-1) break;
            double min_teta=0;
            REP(i,m)
                if(system[i][pos]>eps &&
                        (row==-1 || min_teta>b[i]/system[i][pos]))
                    row=i,min_teta=b[i]/system[i][pos];
            if(row==-1) return -1;
            base[row]=pos;
            gauss(row,pos);
            refresh_c_func(pos,row);
        }
        REP(i,m) if(base[i]>=startN && fabs(b[i])>eps) return -2;
        res.resize(startN,0);
        REP(i,m) if(base[i]<startN) res[base[i]]=b[i];
        value=0;
        REP(i,startN) value+=res[i]*old_c[i];
        return 1;
    }
};


int main(){
    cin>>n;
    REP(i,n) scanf(" %d%d",x+i,y+i);

    SimplexM s;
    s.k
    return 0;
}

