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


const int maxn=1e5+10;
const int maxa=101;

double prob[maxn][maxa];
int na[maxn];
int org[maxn];
int picked[maxn];
int n;
double px[6];

double P[5*maxn+110][6];

double tmp[maxa];

double cnk(double n, double k){
    double res=1;
    REP(i,k) res*=(n-i)/(i+1);
    return res;
}


int main(){
    cin>>n;
    REP(i,n){ scanf(" %d",na+i); org[i]=na[i]; prob[i][0]=1;}

    int ub=5*maxn+110;



    int nq; cin>>nq;
    double res=0;
    REP(i,n) res+=prob[i][org[i]];
    REP(step,nq){
        int u,v,k; scanf(" %d%d%d",&u,&v,&k); --u; --v;


        res-=prob[u][org[u]];

        memset(tmp,0,sizeof(tmp));
        int x=min(picked[u],org[u]);
        for (int i=x; i>=0; --i){
            int rem=org[u]-i;
            REP(kk,k+1) if (i+kk<=org[u] && na[u]-rem>=k-kk){
                //already picked i, now pick kk => have rem

                tmp[i+kk]+=prob[u][i]*cnk(rem,kk)*cnk(na[u]-rem,k-kk)/cnk(na[u],k);
            }
        }
        memcpy(prob[u],tmp,sizeof(tmp));
        res+=prob[u][org[u]];

        na[v]+=k;
        na[u]-=k;
        picked[u]+=k;
        printf("%.10lf\n",res);
    }

    return 0;
}

