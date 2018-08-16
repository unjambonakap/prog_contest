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

const int maxn=1e6+10;
char a[maxn], b[maxn];
int na,nb;
int rmp[255];

int nxt[maxn][3];
int cnt[3][3];

int main(){
    int ti=0;
    while(1){
        if (scanf(" %s",a)<=0) break;
        scanf(" %s",b);
        //if (++ti!=5) continue;
        rmp['R']=0; rmp['G']=1; rmp['B']=2;

        na=strlen(a); nb=strlen(b);
        REP(i,na) a[i]=rmp[a[i]];
        REP(i,nb) b[i]=rmp[b[i]];

        REP(j,3) nxt[nb][j]=nb-1;
        REPV(i,nb){
            REP(j,3) nxt[i][j]=nxt[i+1][j];
            nxt[i][b[i]]=i;
        }


        memset(cnt,0,sizeof(cnt));
        ll res=0;
        int l=0,r=0;
        int nd=0;
        REP(i,na){
            for (; r<nb && b[r]!=a[i]; ++r) if (r) ++cnt[b[r-1]][b[r]]; 
            if (r==nb) --r, nd=1;
            res+=r-l+1;
            if (i && a[i]!=a[i-1]) res-=cnt[a[i]][a[i-1]];
            
            if (!nd && r) ++cnt[b[r-1]][b[r]];
            ++r;
            if (b[l]==a[i]){
                if (++l==nb) break;
                --cnt[b[l-1]][b[l]];
            }
        }

        cout<<res<<endl;
    }
    return 0;

}

