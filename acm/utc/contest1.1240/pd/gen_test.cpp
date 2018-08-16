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

const int maxn=1000;
const int maxk=5e4;
const ll maxa=1e18;

int r, c, k;
ll a[maxn][maxn];

void initrand(){ usleep(7); struct timeval time; gettimeofday(&time,NULL); srand(time.tv_sec * (1000000007) + time.tv_usec *(1234567891)); }

void gen_sample(){ printf("2 2 2\n2 6\n4 5\n"); exit(0); }

void gen_small_rand(){
    r=rand()%(int)sqrt(maxn)+1;
    c=rand()%(int)sqrt(maxn)+1;
    k=rand()%25+1;
    REP(i,r) REP(j,c) a[i][j]=rand()%1000000000+1;
}
void gen_large_rand(){
    r=rand()%maxn+1;
    c=rand()%maxn+1;
    k=rand()%50+1;
    REP(i,r) REP(j,c) a[i][j]=1ll*rand()*rand()%maxa+1;
}
void gen_large_rand_with0(){
    r=rand()%maxn+1;
    c=rand()%maxn+1;
    k=rand()%50+1;
    REP(i,r) REP(j,c) a[i][j]=rand()%7?1ll*rand()*rand()%maxa+1:0;
}

void gen_zeropath(){
    r=rand()%maxn+1;
    c=rand()%maxn+1;
    k=2;
    REP(i,r) REP(j,c) a[i][j]=rand()%1000000000+1;
    int x=r-1, y=0;
    while(x>0 && y<c-1){
        a[x][y]=0;
        if (rand()%2) --x;
        else ++y;
    }
}

int isp(int a){FOR(i,2,a) if (a%i==0) return 0; return 1;}
void gen_big(){
    k=1;
    r=c=maxn;
    vi s;
    for (int x=2; k*x<=maxk; ++x) if (isp(x)) k*=x, s.pb(x);
    REP(i,r) REP(j,c){
        ll rem=1;
        REP(k,s.size()){
            int u=s[rand()%(int)s.size()];
            int v=rand()%10;
            REP(f,v) if (1.*u*rem<=maxa+10 && u*rem<=maxa) rem*=u;
        }
        a[i][j]=rem;
    }
}

void gen_1(){ r=c=k=1; a[0][0]=2; }




int main(int argc, char **argv){
    initrand();
    if (argc<=1){cerr<<"FAIL, neer arg"<<endl; return 0;}
    int x=argv[1][0]-'0';

    if (x==1) gen_sample();
    else if (x==2) gen_small_rand();
    else if (x==3) gen_large_rand();
    else if (x==4) gen_large_rand_with0();
    else if (x==5) gen_zeropath();
    else if (x==6) gen_big();
    else if (x==7) gen_1();

    printf("%d %d %d\n",r,c,k);
    REP(i,r){ REP(j,c-1) printf("%Ld ", a[i][j]); printf("%Ld\n", a[i][c-1]); }
    return 0;
}


