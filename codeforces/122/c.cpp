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

int M[6];
string res[4];
double m[6][8]={
    {1, 0,0, 0,0,0,     0,  0},
    {0, 1,1, 0,0,0,     0,  1},
    {1, -1,1, 0,0,0,    0,  3},
    {-1, 0,-1, 1,1,1,   1,  2},
    {0, 0,-1, -1,-1,1,  1,  4},
    {-1, 1,0, -1,1,-1,  1,  5},
};
double val[7];

int go(){
    REP(i,6) m[i][7]=M[int(m[i][7])];
    int n=6;
    REP(i,n){
        int p=i;
        FOR(j,i+1,n) if (fabs(m[j][i])>fabs(m[p][i])) p=j;
        if (fabs(m[p][i])<1e-6) assert(0);
        REP(j,8) swap(m[p][j],m[i][j]);
        REP(j,n) if (j!=i){
            double v=m[j][i]/m[i][i];
            REP(k,8) m[j][k]-=v*m[i][k];
        }
        double v=1./m[i][i];
        REP(j,8) m[i][j]*=v;
    }

    for (int i=1; i<1e6; ++i){
        int fd=1;
        REP(j,6){
            val[j]=m[j][7]-m[j][6]*i;
            if (val[j]<0 || val[j]>i || fabs(val[j]-round(val[j]))>1e-6){fd=0; break;}
        }
        if (!fd) continue;
        if (i<val[0]+val[2]) continue;
        if (val[0]<val[1]+val[4] || val[1]<val[3] || val[0]<val[3]+val[4]) continue;
        if (val[2]<val[5]) continue;
        

        REP(k,4) REP(j,i) res[k].pb('a');
        REP(j,val[0]) res[1][j]='b';
        REP(j,val[1]) res[2][j]='b';
        REP(j,val[2]) res[2][j+val[0]]='b';

        REP(j,val[3]) res[3][j]='b';
        REP(j,val[4]) res[3][j+val[1]]='b';
        REP(j,val[5]) res[3][j+val[0]]='b';
        REP(j,i-val[0]-val[2]) res[3][i-1-j]='b';
        return 1;
    }
    return 0;
}

int main(){
    REP(i,6) scanf(" %d", M+i);
    if (!go()) puts("-1");
    else{cout<<res[0].size()<<endl;  REP(i,4) cout<<res[i]<<endl;}
    return 0;
}


