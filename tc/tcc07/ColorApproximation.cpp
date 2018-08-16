// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorApproximation.cpp"

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


const int maxn=51;

string hex(int a){
	if (a<=9)return string(1, a+'0');
	return string(1, a-10+'A');
}

class ColorApproximation {
	public:
	string bestApproximation(vector <string> _colors) {
		int tb[3][maxn];
		string s;
		REP(i, _colors.size()) s+=_colors[i]+" ";
		vector<string> colors;
		istringstream ss(s);
		string a;
		while(ss>>a){colors.pb(a);}

		int n=colors.size();
		int m[3][2];

		REP(j, 3)m[j][0]=INT_MAX, m[j][1]=INT_MIN;
		REP(i, n){
			int d;
			sscanf(colors[i].c_str(), "%x", &d);
			REP(j, 3){
				m[j][0]=min(m[j][0], d&0xff);
				m[j][1]=max(m[j][1], d&0xff);
				d>>=8;
			}
		}
		string res;
		int md=-1;
		REP(j, 3){
			int t=(m[j][1]+m[j][0])/2;
		   	md=max(md, max(m[j][1]-t, t-m[j][0]));
		}
		REP(j, 3){
			int a=max(0, m[j][1]-md);
			res=hex(a/16)+hex(a%16)+res;
		}
		return res;
		

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"F36F4E"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "F36F4E"; verify_case(0, Arg1, bestApproximation(Arg0)); }
	void test_case_1() { string Arr0[] = {"7A946B","3B6473"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "5A7453"; verify_case(1, Arg1, bestApproximation(Arg0)); }
	void test_case_2() { string Arr0[] = {"40FE20", "800040"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "017F00"; verify_case(2, Arg1, bestApproximation(Arg0)); }
	void test_case_3() { string Arr0[] = {"626848 321D3A 60EACA 521A88 9C188F",
 "94F0B3 B55795 B34004 20983C 7A644B"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "49845E"; verify_case(3, Arg1, bestApproximation(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ColorApproximation ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
