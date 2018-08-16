// BEGIN CUT HERE

// END CUT HERE
#line 5 "RandomNetwork.cpp"

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



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

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

const double EPS=10e-10;



class RandomNetwork {
	public:
	vector <double> probableLocation(vector <string> network, int steps) {
		int i, j, k;
		int n=network.size();
		int deg[n];
		vector<double> sa(n, 0.);

		sa[0]=1.;
		memset(deg, 0, sizeof(deg));
		REP(i, n)
			REP(j, n)
				if (network[i][j]=='Y')++deg[i];
		REP(k, steps){
			vector<double> sb(n, 0.);
			REP(i, n)
				if (sa[i]>=EPS){
					REP(j, n)
						if (network[i][j]=='Y')
							sb[j]+=sa[i]/deg[i];
				}
			sa=sb;
		}
		return sa;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <double> &Expected, const vector <double> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"NYYY", "YNYY", "YYNY", "YYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; double Arr2[] = {1.0, 0.0, 0.0, 0.0 }; vector <double> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, probableLocation(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"NYYY", "YNYY", "YYNY", "YYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arr2[] = {0.3333333333333333, 0.2222222222222222, 0.2222222222222222, 0.2222222222222222 }; vector <double> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, probableLocation(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NYY", "NNY", "NYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; double Arr2[] = {0.0, 0.5, 0.5 }; vector <double> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, probableLocation(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"NYYNN", "NNYYN", "NNNYY", "YNNNY", "YYNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; double Arr2[] = {0.375, 0.125, 0.0, 0.125, 0.375 }; vector <double> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, probableLocation(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"NYYY", "NNYY", "NNNY", "YNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; double Arr2[] = {0.5, 0.1111111111111111, 0.1111111111111111, 0.2777777777777778 }; vector <double> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, probableLocation(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  RandomNetwork ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
