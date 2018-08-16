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
#include<sys/time.h>
#include<unistd.h>
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

const int tn=10;
const int maxk=1e9;
const int maxt=1e3;

void initrand(){ usleep(7); struct timeval time; gettimeofday(&time,NULL); srand(time.tv_sec * (1000000007) + time.tv_usec *(1234567891)); }
int gcd(int a, int b){if (a<b) swap(a,b); return b?gcd(b,a%b):a;}

int checkit(int k, int x1,int x2, int y1, int y2, int t1, int t2){
    --x1; --x2; --y1; --y2;
    REP(i,t1*t2+10) if (++x1,++x2,x1%t1==y1 && x2%t2==y2) return 1;
    return 0;
}

void gen_rand(){
    int k=rand()%maxk+1;
    int t1,t2;
    t1=rand()%maxt+1;
    t2=rand()%maxt+1;

    int x1=rand()%t1+1, x2=rand()%t2+1;
    int y1=rand()%t1+1, y2=rand()%t2+1;

    printf("%d ",k);
    printf("%d %d ", x1,x2);
    printf("%d %d ", y1,y2);
    printf("%d %d\n",t1,t2);
}

void gen_coprime(){
    int k=rand()%maxk+1;
    int t1,t2;
    t1=rand()%maxt+1;
    while(t2=rand()%maxt+1, gcd(t1,t2)>1);

    int x1=rand()%t1+1, x2=rand()%t2+1;
    int y1=rand()%t1+1, y2=rand()%t2+1;

    printf("%d ",k);
    printf("%d %d ", x1,x2);
    printf("%d %d ", y1,y2);
    printf("%d %d\n",t1,t2);
}

void gen_ncoprime(int step){
redo:
    int k=rand()%maxk+1;
    int f=step<tn/3;
    int t1,t2;
    int base=rand()%(int)(sqrt(maxt)+10)+2;
    t1=rand()%(maxt/base)+1;
    t2=rand()%(maxt/base)+1;

    t1*=base; t2*=base;

    int x1=rand()%t1+1, x2=rand()%t2+1;
    int y1=rand()%t1+1, y2=rand()%t2+1;
    if (f^checkit(k,x1,x2,y1,y2,t1,t2)) goto redo;

    printf("%d ",k);
    printf("%d %d ", x1,x2);
    printf("%d %d ", y1,y2);
    printf("%d %d\n",t1,t2);
}

void gen_duplicate(){
    int k=rand()%maxk+1;
    int t1,t2;
    t1=rand()%maxt+1;
    t2=rand()%maxt+1;

    int x1=rand()%t1+1, x2=rand()%t2+1;
    int y1=rand()%t1+1, y2=rand()%t2+1;
    x1=x2;
    y1=y2;
    t1=t2;

    printf("%d ",k);
    printf("%d %d ", x1,x2);
    printf("%d %d ", y1,y2);
    printf("%d %d\n",t1,t2);
}

void gen_large(){ printf("%d %d %d %d %d %d %d\n",maxk,2,2,1,1,998,999); }

void gen_smallrand(){
    int k=rand()%(int)10+1;
    int t1,t2;
    t1=rand()%20+1;
    t2=rand()%20+1;

    int x1=rand()%t1+1, x2=rand()%t2+1;
    int y1=rand()%t1+1, y2=rand()%t2+1;

    printf("%d ",k);
    printf("%d %d ", x1,x2);
    printf("%d %d ", y1,y2);
    printf("%d %d\n",t1,t2);

}

void gen_sample(){ printf("1 1 3 2 2 2 3\n2 1 1 2 2 3 3\n1 1 1 1 1 1 1\n"); }



int main(int argc, char **argv){
    initrand();
    if (argc<=1) return 0;
    int x=argv[1][0]-'0';
    if (x==1)gen_sample();
    if (x==2)REP(i,tn) gen_smallrand();
    if (x==3)REP(i,tn) gen_duplicate();
    if (x==4)REP(i,tn) gen_ncoprime(i);
    if (x==5)REP(i,tn) gen_coprime();
    if (x==6)REP(i,tn-1) gen_rand(), gen_large();


    puts("0 0 0 0 0 0 0");
    return 0;
}
