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

const int inf=1e9;

int mp[27][33];
int m, n, k, sa, sb;
int wb[33];

int lc[27];
int nb;
int pattern[2222];
int dp[2222][33];
int F[2222];

int go(int a, int b){
    if (b==nb) return F[n]-F[a];
    if (a+k>n) return inf;
    int &r=dp[a][b];
    if (r!=-1) return r;
    r=inf;
    int bc=0;
    REP(i,k) bc+=count_bit(pattern[a+i]^mp[wb[b]][i]);

    int xo=0;
    a+=k;
    REP(i,sb+1){
        if (i>=sa) checkmin(r,go(a+i,b+1)+xo);
        xo+=F[a+i+1]-F[a+i];
    }
    return r=bc+r;
}

void build(int a, int b){
    if (b==nb) return;
    int r=dp[a][b];
    int bc=0;
    REP(i,k) bc+=count_bit(pattern[a+i]^mp[wb[b]][i]);
    int xo=0;
    a+=k;
    REP(i,sb+1){
        if (i>=sa && r==bc+xo+go(a+i,b+1)){if (b!=nb-1) printf(" %d", i); return build(a+i,b+1);}
        xo+=F[a+i+1]-F[a+i];
    }
    assert(0);
}
int main(){
    //freopen("caption.in", "r", stdin);
    //freopen("caption.ouf", "w", stdout);
    cin>>m>>n>>k>>sa>>sb;

    getchar();
    REP(i,m){
        string s; getline(cin,s);
        for (int j=0, x=0; j<s.length(); j+=k+3, ++x){
            int c;
            if (!i) lc[x]=s[j]-'A';
            c=lc[x];
            for (int u=0; u<k; ++u) if (s[j+2+u]=='*') mp[c][u]|=two(i);
        }
    }

    string a, b;
    getline(cin,a);
    vi spa(a.length());
    REP(i,a.length()) cin>>spa[i];
    int pos=0;
    REP(i,a.length()){
        pos+=spa[i];
        int c=a[i]==' '?26:a[i]-'A';
        //cout<<c<<endl;
        REP(j,k) pattern[pos+j]=mp[c][j];
        pos+=k;
    }


    F[0]=0; REP(i,n) F[i+1]=F[i]+count_bit(pattern[i]);

    getchar();
    getline(cin,b);
    nb=b.length();
    REP(i,nb) wb[i]=b[i]==' '?26:b[i]-'A';
    memset(dp,-1,sizeof(dp));
    int res=INT_MAX;
    int best=0;
    REP(i,n){
        int nv=go(i,0)+F[i];
        if (nv<res) res=nv, best=i;
    }
    cout<<res<<endl;
    cout<<best;
    build(best,0);
    puts("");
    return 0;
}


