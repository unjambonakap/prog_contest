// BEGIN CUT HERE

// END CUT HERE
#line 5 "CampLunches.cpp"

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

int gcd(int a, int b){if (a<b)return gcd(b, a); return gcd(a, b);}
int _gcd(int a, int b){ return b==0?a:_gcd(b, a-(a/b)); }
void _eucl(int a, int b, int &r, int &u, int &v, int ua, int va, int ub, int vb){
	if (b==0){r=a; u=ua; v=va; return;}
	int c=a/b;
	assert(c>=1);
	_eucl(b, a-c*b, r, u, v, ub, vb, ua-c*ub, va-c*vb);
}
void eucl(int a, int b, int &r, int &u, int &v){if (a<b)swap(a, b); _eucl(a, b, r, u, v, 1, 0, 0, 1);}




class CampLunches {
	public:
	int firstMatching(vector <string> menu1, vector <string> menu2) {
		map<string, vi> la, lb;

		FE(it, menu1)
			la[*it].pb(it-menu1.begin());
		
		FE(it, menu2)
			lb[*it].pb(it-menu2.begin());
		int na, nb; na=menu1.size(); nb=menu2.size();
		if (na<nb)swap(la, lb), swap(na, nb);

		int s=INT_MAX;
		int d, u, v;
		eucl(na, nb, d, u ,v);

		FE(it, la){
			typeof(lb.begin()) ita;
			if ((ita=lb.find(it->ST))==lb.end())continue;
			FE(itb, it->ND) FE(itc, ita->ND){
				int a, b;a=*itb; b=*itc;

				if ((b-a)%d)continue;
				s=min(s, (na*nb/d+(a+(b-a)/d*u*na)%(na*nb/d))%(na*nb/d));

			}

		}
		
		return s==INT_MAX?-1:s;

	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"pbj", "pizza"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"pbj", "pizza"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, firstMatching(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"pbj", "pizza"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"pizza", "pbj"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(1, Arg2, firstMatching(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"pbj", "pizza"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"pizza", "pbj", "pizza"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(2, Arg2, firstMatching(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"pbj"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"pizza", "tuna", "pbj"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, firstMatching(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"pizza", "pbj", "meatballs", "peanut butter and jelly", "pizza hero"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"pbj", "meatballs", "peanut butter and jelly", "pizza hero"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 16; verify_case(4, Arg2, firstMatching(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"pizza"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"pizza ", "pizza"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(5, Arg2, firstMatching(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CampLunches ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
