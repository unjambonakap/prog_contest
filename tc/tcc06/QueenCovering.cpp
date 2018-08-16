// BEGIN CUT HERE

// END CUT HERE
#line 5 "QueenCovering.cpp"

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
#define twoll(x) (1ULL << (x))
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


const int n=8, nn=n*n;
ull m[nn];
ull b[n][n];
string tmp;
string res;
int fd;

int vx[]={-1, 0, 1, 1, 1, 0, -1, -1};
int vy[]={1, 1, 1, 0, -1, -1, -1, 0};



int in(int a, int b){return a>=0&&b>=0&&a<n&&b<n;}

void rec(int p, int a, int nx, ll k){
    if (a==nx){
        if (k!=(ull)-1) return;
        fd=1;
        checkmin(res, tmp);
        return;
    }
    if (p==nn) return;
    FOR(i, p, nn-1) if (!(k&b[i/n][i%n])){
        tmp[2*a]=i/n+'1';
        tmp[2*a+1]=i%n+'A';
        rec(i+1, a+1, nx, k|m[i]);
    }
    

}

class QueenCovering {
	public:
	string getPlacement(vector <string> board) {
        ull s=0;
        REP(i, n) REP(j, n) b[i][j]=twoll(i*n+j);
        REP(i, n) REP(j, n) s|=(board[i][j]=='#'?b[i][j]:0);
        
        REP(i, n) REP(j, n){
            ll z=0;
            REP(k, 8){
                int x=i, y=j;
                while(in(x, y)){
                    z|=b[x][y];
                    x+=vx[k], y+=vy[k];
                }
            }
            m[i*n+j]=z;
        }

        res="";
        fd=0;
        REP(i, 9){ 

            res=string(2*i, 'z');
            tmp=string(2*i, 'z');
            rec(0, 0, i, s);
            if (fd) return res;
        }
        assert(0);

    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { string Arr0[] = {
        "........",
        "..######",
        ".#.#####",
        ".##.####",
        ".###.###",
        ".####.##",
        ".#####.#",
        "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "1A8B"; verify_case(0, Arg1, getPlacement(Arg0)); }
    void test_case_1() { string Arr0[] = {
        "#......#",
        ".#......",
        "..#...#.",
        "........",
        "..#.....",
        "..#..#..",
        "#.......",
        "#...###."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "1B2D3A4C5E"; verify_case(1, Arg1, getPlacement(Arg0)); }
    void test_case_2() { string Arr0[] = {
        "........",
        "........",
        "........",
        "........",
        "........",
        "........",
        "........",
        "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "1A2C3E4B5D"; verify_case(2, Arg1, getPlacement(Arg0)); }
    void test_case_3() { string Arr0[] = {
        "..##.##.",
        ".###..##",
        "##..###.",
        "#..#...#",
        ".#.##.#.",
        "#...##..",
        "#..#####",
        "..#..#.#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "1A4C5H6B"; verify_case(3, Arg1, getPlacement(Arg0)); }
    void test_case_4() { string Arr0[] = {
        "########",
        "########",
        "########",
        "########",
        "########",
        "########",
        "########",
        "########"
    }
    ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(4, Arg1, getPlacement(Arg0)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    QueenCovering ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
