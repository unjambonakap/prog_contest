#include <vector>
#include <unistd.h>
#include<sys/time.h>
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

const int maxn=1e5;
const int maxm=2e5;
const int maxc=2e3;

int n,m;
int par[maxn];
vector<pii> el;
vector<pair<pii,int> > ml;

int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
int join(int a, int b){
    a=root(a); b=root(b);
    if (a==b) return 0;
    par[a]=b;
    return 1;
}


void initrand(){ usleep(7); struct timeval time; gettimeofday(&time,NULL); srand(time.tv_sec * (1000000007) + time.tv_usec *(1234567891)); }

void gen_sample(){ printf("5\n1 3\n4 1\n3 5\n2 3\n3\n2 5 7\n2 4 5\n4 2 5\n"); exit(0); }

void gen_small_rand(){
    n=rand()%(int)sqrt(maxn)+2;
    for (int i=0; i<n-1;){
        int a=rand()%n, b=rand()%n;
        if (join(a,b)) el.pb(MP(a,b)), ++i;
    }
    m=rand()%(int)3*sqrt(maxn);
    REP(i,m){
        int a=rand()%n, b=rand()%(n-1);
        if (b>=a) ++b;
        int c=rand()%maxc+1;
        ml.pb(MP(MP(a,b),c));
    }

}
void gen_large_rand(){
    n=rand()%(maxn-1)+2;
    for (int i=0; i<n-1;){
        int a=rand()%n, b=rand()%n;
        if (join(a,b)) el.pb(MP(a,b)), ++i;
    }
    m=rand()%maxm;
    REP(i,m){
        int a=rand()%n, b=rand()%(n-1);
        if (b>=a) ++b;
        assert(root(a)==root(b));
        int c=rand()%maxc+1;
        ml.pb(MP(MP(a,b),c));
    }
}

void gen_big(){
    n=maxn;
    REP(i,n-1) el.pb(MP(i,i+1));
    m=maxm;
    int u=0;
    REP(i,m/3){
        ++u; ml.pb(MP(MP(0,rand()%(n/2)),rand()%maxc+1));
        ++u; ml.pb(MP(MP(n-1,n/2+rand()%(n/2)),rand()%maxc+1));
    }
    REP(i,m-u) ml.pb(MP(MP(rand()%n,rand()%n),rand()%maxc+1));
}





int main(int argc, char **argv){
    initrand();
    memset(par,-1,sizeof(par));
    if (argc<=1){cerr<<"FAIL, neer arg"<<endl; return 0;}
    int x=argv[1][0]-'0';

    if (x==1) gen_sample();
    else if (x==2) gen_small_rand();
    else if (x==3) gen_large_rand();
    else if (x==4) gen_big();

    int perm[maxn];
    REP(i,n) perm[i]=i;
    random_shuffle(perm,perm+n);

    random_shuffle(ALL(el));
    random_shuffle(ALL(ml));

    cout<<n<<endl;
    REP(i,n-1) printf("%d %d\n", perm[el[i].ST]+1,perm[el[i].ND]+1);
    cout<<m<<endl;
    REP(i,m) printf("%d %d %d\n", perm[ml[i].ST.ST]+1,perm[ml[i].ST.ND]+1,ml[i].ND);
    return 0;
}


