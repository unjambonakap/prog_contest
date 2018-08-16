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

const int maxn=5;
const int maxc=55;
int xa[maxn], ya[maxn], xb[maxn], yb[maxn];

int n;
int mp[maxc][maxc];
int m;

int go(){
    REP(i,m) REP(j,i) FOR(k,1,m+1){
        int fd=1;
        map<int,int> cnt;
        REP(x,k) REP(y,k) if (!mp[x+i][y+j]){fd=0; break;} else ++cnt[mp[x+i][y+j]];
        if (!fd) continue;
        FE(it,cnt){
            int u=it->ST;
            if (it->ND!=(yb[u]-ya[u])*(xb[u]-xa[u])){fd=0; break;}
        }
        if (fd) return 1;
    }
    return 0;
}


int go2(){
    REP(a,n) REP(b,n) REP(c,n) REP(d,n){
        int xl=xa[a], xh=xb[b], yl=ya[c], yh=yb[d];
        if (xl>=xh || yl>=yh) continue;
        if (xh-xl!=yh-yl) continue;
        int area=(xh-xl)*(yh-yl);
        REP(k,n) if (xl<=xa[k] && xb[k]<=xh
                && yl<=ya[k] && yb[k]<=yh) area-=(xb[k]-xa[k])*(yb[k]-ya[k]);
        else area=-1;
        if (area==0) return 1;
    }
    return 0;


}


int main(){
    cin>>n;
    REP(i,n) scanf(" %d%d%d%d",xa+i,ya+i,xb+i,yb+i);
    puts(go2()?"YES":"NO");
    //vi lst;
    //REP(i,n) lst.pb(xa[i]), lst.pb(xb[i]), lst.pb(yb[i]), lst.pb(ya[i]);

    //sort(ALL(lst));
    //lst.resize(unique(ALL(lst))-lst.begin());
    //REP(i,n) xa[i]=lower_bound(ALL(lst),xa[i])-lst.begin();
    //REP(i,n) xb[i]=lower_bound(ALL(lst),xb[i])-lst.begin();
    //REP(i,n) ya[i]=lower_bound(ALL(lst),ya[i])-lst.begin();
    //REP(i,n) yb[i]=lower_bound(ALL(lst),yb[i])-lst.begin();

    //REP(i,n) FOR(x,xa[i],xb[i])  FOR(y,ya[i],yb[i]) mp[x][y]=i+1;

    //m=lst.size();
    //puts(go()?"YES":"NO");



    return 0;
}

