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

const int maxq=1e5+10;
const int maxm=1e5+10;
const int maxn=1111;
int qtype[maxq];
int qa[maxq], qb[maxq], qc[maxq];
int n,m;
int a[maxm], b[maxm], c[maxm];
int nq;
int is[maxm];
int perm[maxm];
int par[maxn];
int ne;
int le[maxm];

int res[maxq];
int qperm[maxq];


int cmpq(int a, int b){return qc[a]>qc[b];}
int cmp(int a, int b){return c[a]>c[b];}
int root(int a){return par[a]<0?a:par[a]=root(par[a]);}

int main(){
    while(cin>>n>>m,n){
        REP(i,m) scanf(" %d%d%d",a+i,b+i,c+i), --a[i], --b[i];
        cin>>nq;
        memset(is,0,sizeof(is));

        REP(i,nq){
            scanf(" %lc %d %d",qtype+i,qa+i,qb+i);
            if (qtype[i]=='S') scanf(" %d",qc+i), --qa[i], --qb[i];
            else is[--qa[i]]=1;
        }

        REP(i,m) perm[i]=i;
        sort(perm,perm+m,cmp);

        memset(par,-1,sizeof(par));
        ne=0;

        REP(i,m){
            int e=perm[i];
            if (is[e]){le[ne++]=e; continue;}
            int x=root(a[e]), y=root(b[e]);
            if (x!=y) le[ne++]=e, par[x]=y;
        }

        REP(i,ne) perm[i]=le[i];

        REP(qq,nq){
            if (qtype[qq]=='S'){
                int j=qq;
                for (; j<nq && qtype[j]=='S'; ++j) qperm[j-qq]=j;
                int nx=j-qq;

                sort(qperm,qperm+nx,cmpq);
                sort(perm,perm+ne,cmp);

                int k=0;
                memset(par,-1,sizeof(par));
                REP(i,nx){
                    int xx=qperm[i];
                    for (; k<ne && c[perm[k]]>=qc[xx]; ++k){
                        int e=perm[k];
                        int x=root(a[e]), y=root(b[e]);
                        if (x!=y) par[x]=y;
                    }
                    res[xx]=root(qa[xx])==root(qb[xx]);
                }

                REP(i,nx) printf("%d\n",res[i+qq]);
                qq=j-1;
            }else c[qa[qq]]=qb[qq];
        }


    }
    return 0;
}

