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

const int maxn=1111111;
char buf[maxn];
int n;

int tb[4][4][4]={
        {{0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}},


        {{0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}},

        {{0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}},

        {{0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}}
};

int go(){
    vi x;
    x.pb(0);
    REP(i,n){
        int r=-1, r2=-1;
        if (buf[i]=='(') x.pb(0);
        else if (buf[i]==')'){
            int u=x.back(); x.pop_back();
            int f1=u&15, f2=u>>6, op=(u>>4)&15;
            r=0;
            if (op){ REP(j,4) REP(k,4) if ((f1&(1<<j))  && (f2&(1<<k))) r|=tb[op][j][k];
            }else r=f1;
            printf("RES %d\n", r);

        }else if (buf[i]=='?') r=3;
        else if (buf[i]=='0') r=1;
        else if (buf[i]=='1') r=2;
        else r2=buf[i]=='&'?1:buf[i]=='|'?2:3;


        if (r!=-1){
            if (x.back()&15) x.back()|=r<<6;
            else x.back()|=r;
        }
        if (r2!=-1) x.back()|=r2<<4;
        printf("%d >> %d\n", i,x.back());

    }
    assert(x.size()==1);
    return x[0];
}

int main(){

    cin>>n;
    scanf(" %s", buf); n=strlen(buf);
    puts(go()==3?"YES":"NO");
    return 0;
}


