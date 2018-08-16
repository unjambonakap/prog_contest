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

const int maxn=1e6+10;
const int maxq=2*maxn;
const int maxb=3e3;


int n,nq;

int tb[maxq];

int type[maxq];
int ne[maxq];
int m;

map<ll,int> rmpe;
int pos;
int ea[maxq], eb[maxq];

int in[maxq];

int block[maxq];




int l[maxq];
int l2[maxq];

int vis[maxn];

int rmp[maxn], cntx[maxn];
int repr[maxn];

int par[maxn];

int root(int a){return par[a]<0?a:par[a]=root(par[a]);}



int join(int a, int b){
    a=root(a); b=root(b);
    if (a!=b){
        par[a]+=par[b];
        par[b]=a;
    }
}

int get(int a, int b){
    ll h=1ll*a*maxn+b;
    if (!rmpe.count(h)){
        ea[pos]=a; eb[pos]=b;
        return rmpe[h]=pos++;
    }
    return rmpe[h];
}

int main(){
    cin>>n>>nq;
    m=0;

    vi tmp;
    REP(i,nq){
        scanf(" %d",type+i);

        if (type[i]==1){
            int a,b; scanf(" %d%d",&a,&b);
            --a; --b;
            type[i]*=-1;
            ne[i]=get(a,b);
            tmp.pb(ne[i]);
        }else if (type[i]==2){
            type[i]*=-1;
            int a; scanf(" %d",&a);
            ne[i]=tmp[a-1];
        }else{
            type[i]=m;
            scanf(" %d",ne+i);
            REP(j,ne[i]) scanf(" %d",tb+m), --tb[m++];
        }
    }

    assert(m<maxq);
    memset(block,-1,sizeof(block));
    memset(repr,-1,sizeof(repr));
    memset(vis,-1,sizeof(vis));



    int step=0;
    int nx=0;
    int qq=0;

    REP(i,nq){
        int j=i;
        int cnt=0;
        ++step;


        for (; j<nq && cnt<maxb; ++j) if (type[j]==-2 && block[ne[j]]!=step) ++cnt, block[ne[j]]=step;

        fprintf(stderr, "picking %d %d\n",i,j);

        memset(par,-1,sizeof(int)*n);
        int nx2=0;
        REP(k,nx){
            if (!in[l[k]]) swap(l[k--],l[--nx]);
            else{
                if (block[l[k]]!=step) join(ea[l[k]],eb[l[k]]);
                else l2[nx2++]=l[k];
            }
        }

        for (; i<j; ++i){
            if (type[i]==-1){
                if (in[ne[i]]) continue;
                in[ne[i]]=1;

                l[nx++]=ne[i];
                if (block[ne[i]]!=step) join(ea[ne[i]],eb[ne[i]]);
                else l2[nx2++]=ne[i];

            }else if (type[i]==-2) in[ne[i]]=0;
            else{

                int *ta=tb+type[i];
                int nn=ne[i];

                int nu=0;
                REP(k,nn){
                    vis[ta[k]]=i;

                    int a=root(ta[k]);
                    if (repr[a]==-1) rmp[nu]=a, repr[a]=nu, cntx[nu++]=par[a];
                    ++cntx[repr[a]];
                }

                int can=0;

                REP(k,nu) if (cntx[k]<0) goto clean;

                REP(k,nx2){
                    int e=l2[k];
                    if (!in[e]) swap(l2[k--],l2[--nx2]);
                    else if ((vis[ea[e]]==i)!=(vis[eb[e]]==i)) goto clean;
                }

                can=1;
clean:
                puts(can?"YES":"NO");
                REP(k,nu) repr[rmp[k]]=-1;
            }
        }

        --i;
    }



    return 0;
}

