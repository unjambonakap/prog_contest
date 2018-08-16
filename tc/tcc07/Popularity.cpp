// BEGIN CUT HERE

// END CUT HERE
#line 5 "Popularity.cpp"

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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}




class Popularity {
	public:
	vector <string> sort(vector <string> reply) {
		map<string, int> cnt;
		int n=reply.size();
		REP(i, n){
			istringstream ss(reply[i]);
			string a;
			ss>>a;
			if (cnt.count(a)==0)cnt.insert(MP(a, 0));
			++cnt[a];
		}
		set<int> num;
		FE(it, cnt) num.insert(it->ND);

		vs ret;
		FEV(it, num){
			REP(i, n){
				istringstream ss(reply[i]);
				string a;
				ss>>a;
				if (*it==cnt[a])ret.pb(reply[i]);
			}

		}
		return ret;



	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"DON XI","EAGER TOPLEASE","BJ SMITH","BJ JONES","BJ BJ","DON SMITH","EAGER SMITH"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"BJ SMITH", "BJ JONES", "BJ BJ", "DON XI", "EAGER TOPLEASE", "DON SMITH", "EAGER SMITH" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, sort(Arg0)); }
	void test_case_1() { string Arr0[] = {"BOB JONES", "BOB ADAMS", "BOBBY ADAMS", "BOB ADAMS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"BOB JONES", "BOB ADAMS", "BOB ADAMS", "BOBBY ADAMS" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, sort(Arg0)); }
	void test_case_2() { string Arr0[] = {"FRED EVANS","AL BAKER","CAL ADAMS","ED FARMER","AL ADAMS","CAL DETROIT"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AL BAKER", "CAL ADAMS", "AL ADAMS", "CAL DETROIT", "FRED EVANS", "ED FARMER" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, sort(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	Popularity ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
