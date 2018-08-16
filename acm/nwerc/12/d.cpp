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

const int maxn=55;
int lst[maxn];
int mk[10];
int n;
int W;

const char *px="012456;25;02346;02356;1235;01356;013456;025;0123456;012356;";

int mask(int a){
    a%=1440;
    int m=0;
    m|=mk[a/600];
    m|=mk[a/60%10]<<7;
    m|=mk[a/10%6]<<14;
    m|=mk[a%10]<<21;
    return m;
}

int checkit(int a){
    REP(i,n) if ((mask(a+i)&W)!=lst[i]) return 0;
    return 1;
}

int main(){
    int x=0;
    REP(i,10){
        while(px[x]!=';') mk[i]|=1<<px[x]-'0', ++x;
        ++x;
    }

    while(scanf(" %d",&n)>0){
        W=0;
        REP(i,n){
            int a,b; scanf(" %d:%d",&a,&b);
            lst[i]=mk[a/10];
            lst[i]|=mk[a%10]<<7;
            lst[i]|=mk[b/10]<<14;
            lst[i]|=mk[b%10]<<21;
            W|=lst[i];
        }

        int st=1;
        REP(i,1440){
            if (checkit(i)){
                if (st) st=0;
                else printf(" ");
                printf("%02d:%02d",i/60,i%60);
            }
        }
        puts(st?"none":"");
    }

    return 0;
}

