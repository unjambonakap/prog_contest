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

const int maxn=1e6+10;
const int np=3;
int pl[]={97,101,103};
string a, b;
ll px[np][maxn];
ll ha[np][maxn], hb[np][maxn], hra[np][maxn], hrb[np][maxn];
int pi[2*maxn];
int pi2[2*maxn];
string sx;
int n;

pii go(){
    if (a.length()!=b.length()) return MP(-1,-1);
    n=a.length();
    REP(i,np){
        int p=pl[i];
        px[i][0]=1;
        REP(j,n) px[i][j+1]=px[i][j]*p;
        ha[i][0]=hb[i][0]=hra[i][n]=hrb[i][n]=0;
        REP(j,n) ha[i][j+1]=p*ha[i][j]+a[j]-31;
        REP(j,n) hb[i][j+1]=p*hb[i][j]+b[j]-31;
        for (int j=n-1; j>=0; --j) hra[i][j]=p*hra[i][j+1]+a[j]-31;
        for (int j=n-1; j>=0; --j) hrb[i][j]=p*hrb[i][j+1]+b[j]-31;
    }
    sx=a;
    reverse(ALL(sx));
    sx+=char(127)+b;
    pi[0]=-1;
    FOR(i,1,sx.length()){
        int p=pi[i-1];
        while(p>=0 && sx[i]!=sx[p+1]) p=pi[p];
        if (sx[i]==sx[p+1]) ++p;
        pi[i]=p;
    }
    REPV(i,n-1){
        int fd=1;
        REP(j,np) if (hrb[j][n-i-1]!=ha[j][i+1]){fd=0; break;}
        if (!fd) continue;
        
        int val=INT_MAX;
        REP(j,np){
            int T=0, H=n-i;
            while(T+1<H){
                int M=(T+H)/2;
                if (ha[j][i+1+M]-ha[j][i+1]*px[j][M]==hb[j][M]) T=M;
                else H=M;
            }
            if (T==0){val=INT_MAX; break;}
            checkmin(val,T);
        }
        if (val==INT_MAX)continue;


        int val2=pi[2*n-i-1]+1;
        if (!val2) continue;
        if (val+val2<n-i-1){
            continue;
        }
        val=n-i-1-val2;
        return MP(i,i+val+1);

    }


    return MP(-1,-1);
}
int main(){
    getline(cin,a);
    getline(cin,b);
    pii res=go();
    printf("%d %d\n", res.ST, res.ND);
    return 0;
}
