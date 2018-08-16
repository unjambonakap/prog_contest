// BEGIN CUT HERE

// END CUT HERE
#line 5 "DiscountCombination.cpp"

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


const double EPS=10e-9;

double pr;
double getNc(const pii &a){ return pr*((100-a.ND)/100.)+a.ST; } 

struct cmpA{
	bool operator()(const pii &a, const pii &b)const{
		return getNc(a)>getNc(b)+EPS;
	}
};

class DiscountCombination {
	public:
	double minimumPrice(vector <string> discounts, int price) {
		int n=discounts.size();
		int i, j, k, u, v;
		vector<int> p[3];
		REP(i, n){
			istringstream ss(discounts[i]);
			int a, b;
			ss>>a>>b;
			p[b-1].pb(a);
		}
		REP(i, 3)sort(ALL(p[i]));


		int d[3];
		double sol=10e10;
		REP(d[0], p[0].size()+1)
			REP(d[1], p[1].size()+1)
				REP(d[2], p[2].size()+1){
					double pr=double(price);
					int c=0;
					REP(u, 3)
						REP(v, d[u])
							pr*=(99-u)/100., c+=p[u][v];
					sol=min(sol, pr+c);


				}



		return sol;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1 1", "1 2", "1 3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; double Arg2 = 97.06; verify_case(0, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"1000 1", "100 2", "10 3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 33; double Arg2 = 33.0; verify_case(1, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"10 2", "2 3", "6 2", "3 2", "3 1",
 "2 3", "9 3", "4 3", "2 3", "10 1"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; double Arg2 = 7.921497975738132E8; verify_case(2, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"8667276 2",
 "3833771 1",
 "9208836 1",
 "5081823 3",
 "3367749 1",
 "4393655 2",
 "552508 1",
 "8648685 2",
 "3798496 2",
 "8104796 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 246918635; double Arg2 = 2.415526549689562E8; verify_case(3, Arg2, minimumPrice(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  DiscountCombination ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
