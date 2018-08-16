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

const int maxn=111;
int vis[maxn][maxn];
int w,h;
int vx[]={1,2}, vy[]={2,1};
int ans=0;

int in(int a, int b){return a>=0 && a<w && b>=0 && b<h;}
void dfs(int a, int b){
    if (!in(a,b)) return;
    if (vis[a][b]) return;
    vis[a][b]=1;
    ++ans;
    for (int sgn1=-1; sgn1<=1; sgn1+=2) for (int sgn2=-1; sgn2<=1; sgn2+=2) REP(k,2) dfs(a+vx[k]*sgn1,b+vy[k]*sgn2);
}
int checkit(int _w, int _h){
    w=_w; h=_h;
    memset(vis,0,sizeof(vis));
    ans=0;
    dfs(0,0);
    return ans;
}
int go(int w, int h){
    if (w>h) swap(w,h);
    if (w==1) return 1;
    if (w==2) return (h+1)/2;
    if (w==3 && h==3) return 8;
    return w*h;
}
class KnightCircuit2{ 
    public: 
        int maxSize(int w, int h){ 
            return go(w,h);
        } 

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, maxSize(Arg0, Arg1)); }
        void test_case_1() { int Arg0 = 15; int Arg1 = 2; int Arg2 = 8; verify_case(1, Arg2, maxSize(Arg0, Arg1)); }
        void test_case_2() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 10000; verify_case(2, Arg2, maxSize(Arg0, Arg1)); }

        // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    KnightCircuit2 ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
