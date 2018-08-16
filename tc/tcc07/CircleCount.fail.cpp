// BEGIN CUT HERE

// END CUT HERE
#line 5 "CircleCount.cpp"

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


const int maxn=27;
const int MAX=2000000000;
map<int, int> dp;
int n;
string circle;
int st[maxn];
int dst[maxn];

int hinder[2][2][maxn];

int solve(int s){
	if (s==0)return 1;
	if (dp.count(s))return dp[s];

	int &r=dp[s];
	r=0;

	ll res=0;
	REP(i, n) if (bit_set(s, i) &&
		   	(((hinder[0][0][i]&s)==0 && (hinder[1][0][i]&(~s))==0) ||
			 ((hinder[0][1][i]&s)==0 && (hinder[1][1][i]&(~s))==0))
			)
		res+=solve(s^two(i));
	if (res>=MAX)throw string("a");
	return r=res;

}

int cor[maxn];
class CircleCount {
	public:
	int countOrder(string _circle) {
		dp.clear();
		circle=_circle;
		set<int> pos;

		n=circle.length();
		REP(i, n) if (circle[i]>='a') pos.insert(circle[i]-'a');
		memset(cor, -1, sizeof(cor));
		int id=0;
		FE(it, pos)
		   	cor[*it]=id++;
		assert(id==n/2);


		REP(i, n){
			
			if (circle[i]<='Z'){
			   	dst[cor[circle[i]-'A']]=i;
			}
			else st[cor[circle[i]-'a']]=i;
		}
		memset(hinder, 0, sizeof(hinder));

		REP(i, n/2){
			int j=(st[i]+1)%n;

			while(j!=dst[i]){
				if (circle[j]>='a') hinder[0][0][i]|=two(cor[circle[j]-'a']);
				j=(j+1)%n;
			}j=(n+st[i]-1)%n;
			while(j!=dst[i]){
				if (circle[j]>='a') hinder[0][1][i]|=two(cor[circle[j]-'a']);
				j=(n+j-1)%n;
			}
			j=(st[i]+1)%n;
			while(j!=dst[i]){
				if (circle[j]<='Z') hinder[1][0][i]|=two(cor[circle[j]-'A']);
				j=(j+1)%n;
			}j=(n+st[i]-1)%n;
			while(j!=dst[i]){
				if (circle[j]<='Z') hinder[1][1][i]|=two(cor[circle[j]-'A']);
				j=(n+j-1)%n;
			}
		}
		int r;
		n/=2;
		try {
			r=solve(two(n)-1);
		}catch(string a){
			return -1;

		}
		return r;


	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "BACacb"; int Arg1 = 3; verify_case(0, Arg1, countOrder(Arg0)); }
	void test_case_1() { string Arg0 = "ABCacb"; int Arg1 = 0; verify_case(1, Arg1, countOrder(Arg0)); }
	void test_case_2() { string Arg0 = "xX"; int Arg1 = 1; verify_case(2, Arg1, countOrder(Arg0)); }
	void test_case_3() { string Arg0 = "ABCabc"; int Arg1 = 2; verify_case(3, Arg1, countOrder(Arg0)); }
	void test_case_4() { string Arg0 = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPp"; int Arg1 = -1; verify_case(4, Arg1, countOrder(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	CircleCount ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
