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

const int maxn=222222;
char s[maxn], t[maxn];
int a[maxn], b[maxn];
int n, m;
int prev[maxn];


int go(){
    memset(prev,-1,sizeof(prev));
    int j=0;
    REP(i,n){
        for (; j<a[i]; ++j) prev[t[j]]=j;
        int p=prev[s[i]];
        if (p==-1) return 0;
        if (b[i+1]>p) return 0;
    }
    return 1;
}

int main(){
    scanf(" %s", s);
    scanf(" %s", t);
    n=strlen(s); m=strlen(t);
    REP(i,n) s[i]-='a';
    REP(i,m) t[i]-='a';

    int j=0;
    REP(i,n){ if (j<m && s[i]==t[j]) ++j; a[i]=j; }
    j=m-1;
    b[n]=m-1;
    for (int i=n-1; i>=0; --i){ if (j>=0 && s[i]==t[j]) --j; b[i]=j;}

    puts(go()?"Yes":"No");

    return 0;
}



