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

const int maxn=4e5+10;
int n;
int par[maxn];
char *s[maxn];
int nx[maxn];
char buf[maxn];
vi e[maxn];
int M;


char A[maxn];
int px[maxn];
int res=0;


void add(char c, int p){
    int x=px[p-1];
    while(x>=0 && A[x+1]!=c) x=px[x];
    px[p]=x+(A[x+1]==c);
}

void go(int a, int m){
    int om=m;
    REP(i,e[a].size()){
        m=om;
        int b=e[a][i];
        int nn=nx[b];
        REP(j,nn){
            add(s[b][j],m);
            if (px[m]==M-1) ++res;
            ++m;
        }
        go(b,m);
    }
}

int main(){
    while(cin>>n,!cin.eof()){
        res=0;
        int pos=0;
        FOR(i,1,n){
            s[i]=buf+pos;
            int a; scanf("%d %s",&a,s[i]);
            --a;
            par[i]=a;
            nx[i]=strlen(s[i]);
            pos+=nx[i];
            e[a].pb(i);
        }
        scanf(" %s",A);
        int m=strlen(A);
        M=m;
        A[m]='#';
        px[0]=-1;
        FOR(i,1,m+1) add(A[i],i);
        go(0,m+1);
        cout<<res<<endl;

        REP(i,n) e[i].clear();
    }
    return 0;
}

