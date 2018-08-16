#include <vector>
#include <list>
#include <map>
#include <set>
#include<unistd.h>
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
#include<sys/time.h>


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

const int maxn=10000;
const int maxk=10000;

int par[maxn], f[maxn];;
int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
void join(int a, int b){
    a=root(a); b=root(b);
    if (a==b) f[a]=1;
    else par[a]=b, f[b]|=f[a];
}

int perm[maxn];

void initrand(){ usleep(7); struct timeval time; gettimeofday(&time,NULL); srand(time.tv_sec * (1000000007) + time.tv_usec *(1234567891)); }
void init(int n){ memset(par,-1,sizeof(par)); memset(f,0,sizeof(f)); REP(i,n) perm[i]=i; random_shuffle(perm,perm+n);}
vector<string> res;

void disp1(int a, int b, int fx=0){if (fx) swap(a,b); res.pb(toStr(0)+" "+toStr(perm[a]+1)+" "+toStr(perm[b]+1));}
void disp2(int a){res.pb(string("1 ")+toStr(perm[a]+1));}
void disp(int n){printf("%d %d\n", n,res.size()); REP(i,res.size()) cout<<res[i]<<endl;}

int gen_sample(){ printf("2 4\n0 1 2\n1 1\n0 1 2\n1 2\n"); exit(0);}

int gen_log(int fx){

    int n=4096;
    init(n);
    int used=0;
    int sz=1;
    while(sz<n){
        for (int j=0; j<n; j+=2*sz){
            int a=j+rand()%sz, b=j+sz+rand()%sz;
            join(a,b);
            disp1(a,b,fx);
            ++used;
        }

        sz<<=1;
        for (int j=0; j<n; j+=sz){
            if (f[root(j)] && rand()%4==0){
                int a=rand()%sz, b=rand()%(sz-1);
                if (b>=a) ++b;
                join(a+j,b+j);
                disp1(a+j,b+j,fx);
                ++used;
            }else if (!f[root(j)] && rand()%3==0){
                int a=rand()%sz, b=rand()%(sz-1);
                if (b>=a) ++b;
                join(a+j,b+j);
                disp1(a+j,b+j,fx);
                ++used;
            }
        }

        for (int j=0; j<n; j+=sz) REP(k,2){
            int a=j+rand()%sz;
            disp2(a);
        }
    }
    return n;
}

int gen_ll(int fx){
    int n=maxn/2;
    init(n);
    int u=sqrt(n);
    REP(i,u){
        REP(j,u-1) disp1(i*u+j,i*u+j+1,fx);
        if (rand()%2) disp1(i*u,i*u+u-1,fx);
        REP(k,u/5) disp2(i*u+rand()%u);
    }
    FOR(i,1,u) disp1(i*u-1,i*u,fx);
    REP(i,n) disp2(i);
    return n;
}


int gen_rand(){
    int n=rand()%maxn+2;
    init(n);
    int k=maxk;
    REP(i,k){
        int u=rand()%2;
        if (u==0 && n>1){
            int a=rand()%n, b=rand()%(n-1);
            if (b>=a) ++b;
            disp1(a,b);
        }else{
            int x=rand()%n;
            disp2(x);
        }
    }
    return n;
}

int main(int argc, char **argv){
    initrand();

    if (argc<=1){printf("need arg\n"); return 0;}
    int x=argv[1][0]-'0';
    int nx;
    if (x==1) nx=gen_sample();
    else if (x==2) nx=gen_log(0);
    else if (x==3) nx=gen_log(1);
    else if (x==4) nx=gen_ll(0);
    else if (x==5) nx=gen_ll(1);
    else if (x==6) nx=gen_rand();
    if (res.size()>maxk) res.resize(maxk);
    disp(nx);
    return 0;
}


