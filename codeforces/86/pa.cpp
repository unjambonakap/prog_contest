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

char buf[111111];

int main(){
    int a,b,c; a=b=c=0;
    int type=-1;

    int fd=1;
    int tmp;
    while(scanf("%s", buf)>0){
        int x=-1, f=-1;
        int n=strlen(buf);
        char *s=buf+n;

        if (n>=4 && !strcmp(s-4,"lios")) x=0, f=0;
        else if (n>=5 && !strcmp(s-5, "liala")) x=0, f=1;
        else if (n>=3 && !strcmp(s-3, "etr")) x=1, f=0;
        else if (n>=4 && !strcmp(s-4, "etra")) x=1, f=1;
        else if (n>=6 && !strcmp(s-6, "initis")) x=2, f=0;
        else if (n>=6 && !strcmp(s-6, "inites")) x=2, f=1;
        else fd=0;

        if (type!=-1 && type!=f) fd=0;
        type=f;
        if (x==0 && (b||c)) fd=0;
        if (x==1 && c) fd=0;





        if (x==0) ++a;
        if (x==1) ++b;
        if (x==2) ++c;

        if (!fd) break;

    }
    if ((a+b+c)>1 && b!=1) fd=0;
    if (fd) puts("YES");
    else puts("NO");
    return 0;
}

