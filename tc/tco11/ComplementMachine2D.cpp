// BEGIN CUT HERE

// END CUT HERE
#line 5 "ComplementMachine2D.cpp"

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
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=40;
int ra[maxn], ca[maxn];
int m[maxn][maxn];

class ComplementMachine2D {
	public:
	int largestSubmatrix(vector <string> _m) {

        int r, c;
        r=_m.size(); c=_m[0].length();
        REP(i, r) REP(j, c) m[i][j]=_m[i][j]-'0';
        int ans=0;
        REP(i, r) REP(j, c) REP(f, 2){
            memset(ra, -1, sizeof(ra));
            memset(ca, -1, sizeof(ca));
            ra[i]=f;
            int mc=c-1;
            FOR(v, j, mc) ca[v]=ra[i]^m[i][v];
            checkmax(ans, c-j);
            FOR(u, i+1, r-1){
                ra[u]=m[u][j]^ca[j];
                FOR(v, j, mc) if (m[u][v]!=ra[u]^ca[v]){mc=v-1; break;}
                checkmax(ans, (u-i+1)*(mc-j+1));
            }

        }
        return ans;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0011",
 "0011",
 "1100",
 "0111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(0, Arg1, largestSubmatrix(Arg0)); }
	void test_case_1() { string Arr0[] = {"0011",
 "1011",
 "0101",
 "1010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(1, Arg1, largestSubmatrix(Arg0)); }
	void test_case_2() { string Arr0[] = {"1011",
 "0011",
 "0101",
 "1010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(2, Arg1, largestSubmatrix(Arg0)); }
	void test_case_3() { string Arr0[] = {"0000110101010",
 "0111101010111",
 "1110110111011"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(3, Arg1, largestSubmatrix(Arg0)); }
	void test_case_4() { string Arr0[] = {"11000000000110101101",
 "00111111011101101101",
 "00110011110111100010",
 "10011110111110000111",
 "00111010000000110111",
 "00001101011011010110",
 "11010010100100101100",
 "11101101011011000001",
 "11000010100100111001",
 "11011010100100101010",
 "10110010100100110110",
 "01100010100100111001",
 "10110010100100110011",
 "01110101011011001010",
 "01111101011011001011",
 "00001000010010101011",
 "11100101100100110001",
 "10100100111001010101",
 "11111000001010011110",
 "01110100001110011111"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; verify_case(4, Arg1, largestSubmatrix(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ComplementMachine2D ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
