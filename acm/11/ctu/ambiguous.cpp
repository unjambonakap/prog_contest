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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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

const int maxn=111;
int op[maxn];
int num[maxn];
int n;

ll A[maxn][maxn];

ll opx(ll a, ll b, int x){return x?a+b:a*b;}

ll doita(int a, int b){
    ll &r=A[a][b];
    if (r!=-1) return r;
    r=0;
    if (a==b) return r=num[a];
    else if (a+1==b) return r=opx(num[a], num[a+1], op[a]);
    FOR(i, a, b-1) checkmax(r, opx(doita(a, i), doita(i+1, b), op[i]));
    return r;
}
ll doitb(int a, int b){
    ll &r=A[a][b];
    if (r!=-1) return r;
    r=1LL<<63-1;
    if (a==b) return r=num[a];
    else if (a+1==b) return r=opx(num[a], num[a+1], op[a]);
    FOR(i, a, b-1) checkmin(r, opx(doitb(a, i), doitb(i+1, b), op[i]));
    return r;
}

int main(){
    string s;
    while(cin>>s,s!="END"){
        int x=0;
        REP(i, s.length()) if (s[i]=='+' || s[i]=='*') op[x++]=s[i]=='+', s[i]=' ';
        istringstream ss(s);
        string a;
        n=0;
        while(ss>>a) num[n++]=toInt(a);
        memset(A, -1, sizeof(A));
        printf("%Ld ", doitb(0, n-1));
        memset(A, -1, sizeof(A));
        printf("%Ld\n", doita(0, n-1));

    }
    return 0;
}


