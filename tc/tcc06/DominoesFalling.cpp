// BEGIN CUT HERE

// END CUT HERE
#line 5 "DominoesFalling.cpp"

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


const int maxn=2600;
const int inf=maxn;


int n;
int mp[maxn];
int mem[maxn][maxn];

int proc(int p, int a){
    if (a==0) return 0;
    if (p>=n) return a;
    int &res=mem[p][a];
    if (res!=-1) return res;
    res=INT_MAX;
    FOR(i, 2, 5) checkmin(res, proc(p+i, a-1));
    return res=res+mp[p];
}


class DominoesFalling {
	public:
	int rearrangeTiles(vector <string> cells) {
        string s;
        FE(it, cells) s+=*it;
        int cnt=0;
        n=s.length(); REP(i, n) mp[i]=s[i]=='.', cnt+=1-mp[i];
        int ans=INT_MAX;
        memset(mem, -1, sizeof(mem));
        REP(i, n+1) checkmin(ans, proc(i, cnt));
        
        return ans;


    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { string Arr0[] = {"XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, rearrangeTiles(Arg0)); }
    void test_case_0() { string Arr0[] = {"XXXXXX.XX.XXX.XXXXX...X.XXXXXXXXX...XXX.XX.XXXXX.X", "XXXXX.XXXXXX..XXXXXXXXXX.XX.X.XXXXXXX.XXXXXXXXXXXX", "XXXXXXXXXXXXX..XXXXXXXXXXXXX.XXXX.XX.XX.XXXXX.XX.X", "XXXXX.XXXXXXXXXXXXXXXX.X.XXXX.XXXXXXXX.XX.XXX.X..X", "X.XXXXXXX.XXXXXXXXXXXXXXXX.XXX.XXXX.XXXXXXXXXXXXXX", ".XXXXX.XXX..XX..XXXXXXXXXXX.XXX.XXXXXXXXX.XXXXXXX.", "XX..X.XXXXXX.XXXXXXXXXXXX.XXXXXXXXXX.XXXXXXXXXXX.X", "XX.XXXXXXXXX.XXXXXX.XXXXXXXXXXXXX.XXX.XXXXXXXXXXX.", "XXXXXXXXXXXX.X.X..XXXXXXXXX.XXXXXXXXXX.XXXXXXXX.XX", "XXXXXXXXXXXXXX.XXXXXXXX.XXXXXXXXXXXXX..X.XXXXXXX..", ".XXXXX.X.XX.XXXX.XXXXXXX.X.XXXXXXXXXXXXX...X.XXXXX", ".XXXXXXXXXX..XXX.XX.XXXXXX.X.XXXXXXXXX.XXXX.XXXXXX", "X.XXXXXXX.XXXXXXXXX.XXXX.XXXXXX.XXXXXXX.XX..XXX.XX", "XX.XXXXXXX.XX..XXXXXXXXXX.XX.X.X.X.XXXXXXXXXX.XX.X", "XXXXXXXX.XXXXX.XXXXXXXXXXXXXXX.XXXXXXX.XX.XXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXX", "XX.XXXXXXXXXXXX.XXXXXXXXX.XXX.XXXXXX.X..XX.XXXXXXX", "XXXXXX.XXXXXXXXXXXXXXXXXXX..XXX.XXXXXXXXXXXXXX.X.X", ".XXXXXXXXXXX.XXX.XXXXXXXXXXXXXXXXXXXX.X.XXXXXXXXXX", "XXXXXXXXXXX..XXXXXX.XXXXXXXXX..XXX.X.XXX.X.XXXXXXX", ".XXXXX.XX.XXXXXXX.X.XXXXXXXXXXXXXXXXXX.XXXXX.XXXXX", "XXXXXXXXXXXXXXXXX.XXX.XXXXXXXXXXXXXXXXXXXXXXXXXXXX", "X.XXX..XXXXX.X.XXXXXXXXXX.XXXXXXXXXXXXXXXXX.XXXXXX", "XXXXXXXX.XXXXXX.XXXXXXXXXX...X.X.X.XX.XXXXX.XXXXXX", "XXXXXXX.XXXX.XX.XXXXXX.XXXXX.XXX.XXXXXX.XXXXXXXXX.", "XXXXXXXXXXX.XXXXXXX.XX.X..XXXXXX.XXXXXXXXX.XXXXXXX", "XXXXXXXXX..XXXXXXXXXXXX.XXXXXX.X.X..XXXX.XXX.XX.XX", "XX.X.XXXXXXXXX..XX.XXXXXXXXXXXX.XX.XX.XX.X.XXXXXXX", "XXX.XXXXXXXXXX.XX.XX.XX.XX.XXXX.XXXXX.XXXXXXXXXX.X", ".X.XX.X..XXXX.XXXX....X..XXXXXXXXX.X.XXXXXXXXXXXX.", "X..XXXX.XXXXXXXXXX.XX.XXX.X.XXX.XXXXXXXXXXXXXXXX.X", "XXXX.XXXXX.XXXXXXXXXX.XXXXXXXX..XXXXXXX.XXXX.XXXXX", "XXXXXXXXXXXXX.XX.X..XXX.X.XX.XXXXXXXXX.XXX.XXXX..X", "XXXXXXXXXXX.XXXXXXX.XXX.XXXXXXXX.XXXXXX.XXXXXXX.XX", "X..XX..XXXXXXXXXXXXX..X.XXXXX.XXXXXXXXXXXXXXX.XXXX", "XXXXXXX.X....XX..XXXXXXXXXXXXXXXXX.X.XXXXXXXXXXXXX", "X.XXX.X.XXXXXXXXX.XXXXXXX.XXXXXXX.XXXXXXXXX.X.XXXX", "X.XXXXXX.XXXXXXXXXXX.XXXXXXXX.X.XXXX.XXXXXX.XX.XXX", "XXXX.XXXXX.X.XXXXXX.XXXX.XXXXXXXXXXXX.XXXXXXX.XX.X", "XXXXXXX.XXX.XXXX.XX.XXX.XXXXXXX.XXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXX.XXXX.XXX.X.XX.XXXXX.XXXXXXX.XXX.X.XXX", "X.XXXXXXXXXXXXXXXX.XXX.XXXXXXXXX.XX.XXXXXXXXXXXXXX", "XXXXXX.XX.XXX.XXX.XXX.XX.XXX.XXXXXXXXXXX..XXX..XXX", "XX.XXXXXXXXX.XXXX.XXXXXX..XXXX.X..XXXXXXXXXXXXXXX.", "XXXXXXXX.XXXXXXX.XXXXXXXXX...XXXXXXXXXXXXXXX.XX.X.", ".XXXXXX..XX.XX.XXXXXX.XXX.XXXXXXXXXX.XXXXXXXXXXXXX", ".XXXXXXXXXXXXXXXXXXX.XXXXXXXXXX.XXXXXXX..XXXXXXXXX", "XXXXX.XXXXXXX.XXXXXXXXXX.XX.XX..XXXXX..XX..XXXXXXX", "XXX.X.XX.X.X.XXXXXXXXXXXXXXXXXXXXXXXXXXXX..XXXXX.X", "XX.X..XXXX.XXXXXXXXXXXXX.X.XXXXX.XXXXXXX.XXXX.XXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, rearrangeTiles(Arg0)); }
    void test_case_1() { string Arr0[] = {"X.....X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, rearrangeTiles(Arg0)); }
    void test_case_2() { string Arr0[] = {"X.X............",
        "...............",
        ".....X.X.X.....",
        "...............",
        "............X.X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, rearrangeTiles(Arg0)); }
    void test_case_3() { string Arr0[] = {"X.X....X..X...", ".X......"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, rearrangeTiles(Arg0)); }
        void test_case_4() { string Arr0[] = {".XX.X.XXXXXX", "X.X.XXXXXXXXXXXX", ".X.X.X.XXXXXXX.XXX", ".XXXXXX.XX", 
            "XX.XXXXX.XXXXX", "XXXXX...X...X", "XXXX.XXXXXXXXX.XXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 34; verify_case(4, Arg1, rearrangeTiles(Arg0)); }
        void test_case_5() { string Arr0[] = {".......X.X.", ".....X.....", ".............X", "....X...X..", ".X...X.X..", 
            ".XXX........X......X", "......X..X....", "....X..........."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(5, Arg1, rearrangeTiles(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    DominoesFalling ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
