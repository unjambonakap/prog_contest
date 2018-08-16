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

const int maxm=88;
int mod,np,n;
int f[maxm];

int is0[maxm];
int is[maxm], tmp[maxm], tmp2[maxm];
int st[maxm], nd[maxm];
int fix[maxm];

struct matrix{
    int m[maxm][maxm];
    matrix(){memset(m,0,sizeof(m));}
    matrix(const matrix &b){memcpy(m,b.m,sizeof(m));}
    void ident(){REP(i,n) m[i][i]=1;}

    matrix operator*(const matrix &b)const{
        matrix r;
        REP(i,n) REP(j,n){
            int x=0;
            REP(k,n) x=(x+m[i][k]*b.m[k][j])%mod;
            r.m[i][j]=x;
        }
        return r;
    }

};

matrix faste(matrix a, int p){
    matrix x; x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=x*a;
    return x;
}


int main(){
    while(cin>>n,n){
        REP(i,n+1) scanf(" %d",f+i);
        cin>>np>>mod;
        matrix x;
        int fd=0;
        REP(i,n){
            int a=f[i], b=f[i+1];
            if (a==i && b==i+1){fd=1; break;}
            if (a>b) swap(a,b);
            FOR(j,a,b) x.m[i][j]=1;
        }
        if (fd){puts("Infinity"); continue;}

        x=faste(x,np);
        int res=0;
        REP(i,n) res+=x.m[i][i];
        res%=mod;

        REP(i,n+1){
            int u=i;
            REP(j,np) u=f[u];
            fix[i]=u==i;
        }

        memset(is,0,sizeof(is));
        REP(i,n) if (abs(f[i]-f[i+1])==1) is[i]=f[i]<f[i+1]?1:-1;
        memcpy(is0,is,sizeof(is));
        REP(step,np-1){
            memset(tmp,0,sizeof(tmp));
            REP(j,n) if (is0[j] && is[f[j]-(is0[j]==-1)]) tmp[j]=is0[j]*is[f[j]-(is0[j]==-1)];
            memcpy(is,tmp,sizeof(is));
        }

        REP(i,n) if (is[i]==1 && fix[i]){fd=1; break;}

        if (fd){puts("Infinity"); continue;}

        memset(st,0,sizeof(st)); memset(nd,0,sizeof(nd));
        REP(i,n){
            if (f[i]<f[i+1]) st[i]=1, nd[i+1]=1;
            if (f[i]>f[i+1]) st[i]=-1, nd[i+1]=-1;
        }

        REP(step,np-1){
            memset(tmp,0,sizeof(tmp)); memset(tmp2,0,sizeof(tmp2));
            REP(i,n){
                if (f[i]<f[i+1]){
                    tmp[i]=st[f[i]];
                    tmp2[i+1]=nd[f[i+1]];
                }else if (f[i]>f[i+1]){
                    tmp[i]=nd[f[i]]*-1;
                    tmp2[i+1]=st[f[i+1]]*-1;
                }
            }
            memcpy(st,tmp,sizeof(st)); memcpy(nd,tmp2,sizeof(nd));
        }
        REP(i,n) if (st[i]<=0&&fix[i]) ++res;
        REP(i,n) if (nd[i+1]<=0&&fix[i+1]) ++res;
        FOR(i,1,n) if (fix[i]) --res;


        res=(res+mod)%mod;
        printf("%d\n",res);

    }
    return 0;
}

