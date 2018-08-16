// BEGIN CUT HERE

// END CUT HERE
#line 5 "CrimeLab.cpp"

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

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}

const int maxn=7;

int ta[maxn][maxn], tb[maxn][maxn];
class CrimeLab {
	public:
		int matchFragment(string tf, vector <string> cf) {
			REP(i, 7) REP(j, 7) ta[i][j]=(tf[i*7+j]=='X');
			int c=-1;
			int n=cf.size();
			REP(i, n){
				REP(j, 7) REP(k, 7) tb[j][k]=(cf[i][j*7+k]=='X')?1:0;

				for (int i=-1; i<=1; i+=2){
					bool ok=true;
					REP(j, 7){
						if (!ok)break;
						REP(k, 7) if (ta[j][k]+tb[j][(maxn+i*k-(i==-1))%maxn]!=1){ok=false; break;}
					}					if (ok) goto found;
					ok=true;
					REP(j, 7){
						if (!ok)break;
						REP(k, 7) if (ta[maxn-1-j][k]+tb[j][(maxn+i*k-(i==-1))%maxn]!=1){ok=false; break;}
					}
					if (ok) goto found;
					ok=true;
					REP(j, 7){
						if (!ok)break;
						REP(k, 7) if (ta[k][j]+tb[j][(maxn+i*k-(i==-1))%maxn]!=1){ok=false; break;}
					}
					if (ok) goto found;
					ok=true;
					REP(j, 7){
						if (!ok)break;
						REP(k, 7) if (ta[k][maxn-1-j]+tb[j][(maxn+i*k-(i==-1))%maxn]!=1){ok=false; break;}
					}
					if (ok) goto found;
				}
				continue;
found:
				if (c>-1)return -2;
				c=i;

			}
			return c;





		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { string Arg0 = "XXXXXXX.XXXXXX.XX.XXX.XX.X.X.X..X......X........."; string Arr1[] = {"XXX....XX.....XXX....XXX....XXXXXX.X......XXXX...", ".XXXXXX.....XX....XXX..XXXXX......X...XXXX....XXX", ".......X...X..X..XX..X..XX.XX..XX.XXX.XX.XXXXXXXX", "XXX....XXXX...X......XXXXX..XXX....XX.....XXXXXX."}
			; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, matchFragment(Arg0, Arg1)); }
		void test_case_1() { string Arg0 = "XXXXXXX.XXXXXX.XX.XXX.XX.X.X.X..X......X........."; string Arr1[] = {"XXX....XX.....XXX....XXX....XXXXXX.X......XXXX...",
			".XXXXXX.....XX....XXX..XXXXX.....XX...XXXX....XXX",
			"XXXXXXX.XXXXXX.XX.XXX.XX.X.X.X..X................",
			".......X...X..X..XX..X..XX.XX..XX.XXX.XX.XXXXXXXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(1, Arg2, matchFragment(Arg0, Arg1)); }
		void test_case_2() { string Arg0 = "XXXXXXX.XXXXXX.XX.XXX.XX.X.X.X..X......X........."; string Arr1[] = {"XXX....XX.....XXX....XXX....XXXXXX.X......XXXX...",
			".XXXXXX.....XX....XXX..XXXXX......X...XXXX....XXX",
			".......X...X..X..XX..X..XX.XX..XX.XXX.XX.XXXXXXXX",
			"XXX....XXXX...X......XXXXX..XXX....XX.....XXXXXX."}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -2; verify_case(2, Arg2, matchFragment(Arg0, Arg1)); }
		void test_case_3() { string Arg0 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.XXXXXX......."; string Arr1[] = {".........................................XXXXXXXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(3, Arg2, matchFragment(Arg0, Arg1)); }
		void test_case_4() { string Arg0 = "XXXX...X......XXX....XXXX...X......XX.....XXX...."; string Arr1[] = {"XXXXXXXXXXXXXXXXXXXXX.XXXX.X.X..X.X.X..X.........",
			"...XXXX...XXXX.XXXXXX....XXX..XXXXX....XXX.XXXXXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(4, Arg2, matchFragment(Arg0, Arg1)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	CrimeLab ___test; 
	___test.run_test(0); 
} 
// END CUT HERE
