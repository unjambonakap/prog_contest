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

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=6010;
int cross[maxn][maxn];
int ymax[maxn], ymin[maxn];

int cdir(int d, char m){
    if (m=='L') return (d+1)%4;
    return (d+3)%4;
}
void cpos(int d, int &x, int &y){
    if (d==0) ++y;
    else if (d==1) cross[--x][y]=1;
    else if (d==2) --y;
    else cross[x++][y]=1;
}

int end(int x){ return ymax[x]==INT_MIN;}

int solve(){
    int l=INT_MIN;
    int xo;
    xo=max_element(ymax, ymax+maxn)-ymax;
    REP(i, xo) if (!end(i)) l=ymax[i]=max(l, ymax[i]);
    l=INT_MIN;
    FORV(i, maxn-1, xo) if (!end(i)) l=ymax[i]=max(l, ymax[i]);


    xo=min_element(ymin, ymin+maxn)-ymin;
    l=INT_MAX;
    REP(i, xo) if (!end(i)) l=ymin[i]=min(l, ymin[i]);
    l=INT_MAX;
    FORV(i, maxn-1, xo) if (!end(i)) l=ymin[i]=min(l, ymin[i]);
    int res=0;
    REP(i, maxn) if (!end(i)){
        res+=ymax[i]-ymin[i]+1;
    }
    return res;

}

int main(){
    int tn;
    cin>>tn;


    FOR(ti, 1, tn){
        memset(cross, 0, sizeof(cross));
        int n;
        cin>>n;
        int x=maxn/2;
        int d=0;
        int y=maxn/2;
        REP(i, n){
            string s;
            int a;
            cin>>s>>a;
            REP(j, a) REP(k, s.length()){
                if (s[k]=='F') cpos(d, x, y);
                else d=cdir(d, s[k]);
            }
        }

        int cnt=0;
        REP(i, maxn){
            ymax[i]=INT_MIN;
            ymin[i]=INT_MAX;
            int s=0;
            REP(j, maxn-1){
                if (cross[i][j]) s^=1;
                if (s) ++cnt, checkmax(ymax[i], j), checkmin(ymin[i], j);
                
            }
        }
        printf("Case #%d: %d\n", ti, solve()-cnt);
    }


}
