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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}



const int maxn=1010;
const long double pi=acos(-1.);
const long double eps=1e-10;

long double dist(int a, int b){return sqrt(ll(a)*a+ll(b)*b);}
int n;
int x[maxn];
int y[maxn];
long double d[maxn][maxn];
long double ang[maxn][maxn];
map<long double, int> cycle[maxn][maxn];
int sang[maxn][maxn];

struct state{
    int a, b;
    long double v;
    bool operator<(const state &s)const{
        if (a!=s.a) return a<s.a;
        if (b!=s.b) return b<s.b;
        return v<s.v;
    }
    state(int a, int b, long double v):a(a), b(b), v(v){}

};
map<state, int> dp;


struct cmpA{
    int c;
    cmpA(int c):c(c){}
    bool operator()(int a, int b){
        if (fabs(ang[c][a]-ang[c][b])<eps) return d[c][a]>d[c][b];
        return ang[c][a]<ang[c][b];
    }

};

int findCycle(int a, int b, long double v, long double &va, int cnt, int st, int oa, int ob){
    if (!st && ob==b) return oa==a?cnt:0;
    int id=0;
    long double sa;

    sa=ang[a][b];
    while(id<n-1 && ang[b][sang[b][id]]<=sa) ++id;

    FOR(i, id, id+n-1){

        int ni=sang[b][i%(n-1)];

        if (d[b][ni]+eps<=v){
            va+=d[b][ni];
            return findCycle(b, ni, v-d[b][ni], va, cnt+1, 0, oa, ob);
        }
    }
    return 0;

}

int solve(int a, int b, long double v){
    long double sa;
    state s(a, b, v);
    if (dp.count(s)) return dp[s];
    int &r=dp[s];

    if (a!=-1) sa=ang[a][b];
    else sa=pi;

    r=0;


    if (a!=-1){
        long double ra=0.;
        int na=findCycle(a, b, v, ra, 0, 1, a, b);
        if (na){

            int nr=floor((v-eps)/ra);
            if (nr>=2){
                --nr;
                v-=nr*ra;
                r+=nr*na;
                return r+=solve(a, b, v);
            }
        }
    }

    int id=0;
    while(id<n-1 && ang[b][sang[b][id]]<=sa) ++id;
    //out(ang[b], n);
    //REP(i, n-1) printf("%lf ", ang[b][sang[b][i]]); printf("\n");
    //printf("pick %d\n", id);

    r=0;
    FOR(i, id, id+n-1){

        int ni=sang[b][i%(n-1)];

        if (d[b][ni]+eps<=v){
            //    printf("trying %d with %lf\n", ni, v);
            checkmax(r, 1+solve(b, ni, v-d[b][ni]));
            v=d[b][ni];
        }
    }
    return r;
}



int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int r;
        cin>>n>>r;
        REP(i, n) cin>>x[i]>>y[i];

        //out(x, n);
        //out(y, n);
        //printf("%d\n", r);
        REP(i, n) REP(j, n) d[i][j]=dist(x[i]-x[j], y[i]-y[j]);
        REP(i, n){
            REP(j, n) if (i!=j){
                sang[i][j-(j>i)]=j;
                ang[i][j]=atan2(y[j]-y[i], x[j]-x[i]);
            }
            sort(sang[i], sang[i]+n-1, cmpA(i));

        }

        REP(i, n) REP(j, n) cycle[i][j].clear();
        dp.clear();

        //long double ra;
        //int tmp=findCycle(4, 5, 114, ra, 0, 1, 4, 5);
        //printf("%d\n", tmp);
        //break;
        int res=(n==1?0:solve(-1, 0, r));

        printf("Case #%d: %d\n", ti, res);

    }

    return 0;
}



