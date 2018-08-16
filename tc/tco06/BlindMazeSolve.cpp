// BEGIN CUT HERE

// END CUT HERE
#line 5 "BlindMazeSolve.cpp"

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

const int maxn=5;
const int maxv=20;
int n, m, nm;
int mp[maxn][maxn];
char seen[two(maxv)];
string best[two(maxv)];

int nxt[maxv][4];
int mask;
int vx[]={-1, 0, 1, 0};
int vy[]={0, 1, 0, -1};
char move[]={'U', 'R', 'D', 'L'};
int end;
struct state{
    int m;
    string s;
};

string solve(){
    memset(seen, 0, sizeof(seen));

    queue<int> q;
    q.push(mask);
    while(!q.empty()){
        int p=q.front(); q.pop();
        if (!p) return best[p];
        seen[p]=1;

        REP(k, 4){
            int np=0;
            REP(i, nm) if (p&two(i)) np|=nxt[i][k];
            if (seen[np]==1)continue;


            string ns=best[p]+move[k];

            if (!seen[np] || (ns.length()==best[np].length() &&  ns<best[np])) best[np]=ns, seen[np]=2, q.push(np);
            seen[np]=2;
        }
    }
    return "";

}

class BlindMazeSolve {
    public:
        string getSolution(vector <string> maze) {
            n=maze.size();
            m=maze[0].length();

            mask=0;
            nm=n*m;
            end=0;
            memset(nxt, -1, sizeof(nxt));
            REP(i, n) REP(j, m) if (maze[i][j]=='.'){
                int v=i+j*n;
                mask|=two(v);
                REP(k, 4){
                    int ni=i+vx[k], nj=j+vy[k];
                    if (ni<0 || ni>=n) ni=i;
                    else if (nj>=m) nj=j;
                    if (nj>=0 && maze[ni][nj]=='X') ni=i, nj=j;


                    int nv;
                    if (nj<0) nv=end;
                    else nv=two(ni+nj*n);
                    nxt[v][k]=nv;
                }

            }
            return solve();

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {".X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "L"; verify_case(0, Arg1, getSolution(Arg0)); }
        //void test_case_0() { string Arr0[] = {"..X.", "X.X.", "X...", "X.X.", "..XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "DDDULLDDLL"; verify_case(0, Arg1, getSolution(Arg0)); }
        void test_case_1() { string Arr0[] = {
            "..",
            ".."
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LL"; verify_case(1, Arg1, getSolution(Arg0)); }
        void test_case_2() { string Arr0[] = {
            "X..",
            "X..",
            "XXX"
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(2, Arg1, getSolution(Arg0)); }
        void test_case_3() { string Arr0[] = {
            "X...",
            "XXX.",
            "X...",
            "X.XX",
            "..XX"
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "RRDDLLDDLL"; verify_case(3, Arg1, getSolution(Arg0)); }
        void test_case_4() { string Arr0[] = {".XX."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(4, Arg1, getSolution(Arg0)); }
        void test_case_5() { string Arr0[] = {
            "XXX.",
            "..X.",
            "X...",
            "XX..",
            "X..."
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "DDDRULULULL"; verify_case(5, Arg1, getSolution(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    BlindMazeSolve ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
