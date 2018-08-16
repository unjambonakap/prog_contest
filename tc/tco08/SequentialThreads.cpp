// BEGIN CUT HERE

// END CUT HERE
#line 5 "SequentialThreads.cpp"

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



const int maxn=1000;
int n;
double pa[maxn], temp[maxn], cp[maxn][maxn];//c[j][k] => prob to pick j lower threads and k ith thread

class SequentialThreads {
	public:
	double expectedExecutionTime(vector <string> threads) {
		int cnt;
		n=threads.size();
		memset(pa, 0, sizeof(pa));
		pa[0]=1.;
		cnt=0;
		REP(i, n){
			int p=threads[i].length();
			int s=threads[i].find('S');
			if (s==-1){cnt+=p; continue;}
			
			double a, b;
			a=1./(i+1), b=1-a;
			memset(cp, 0, sizeof(cp));
			cp[0][0]=1.;
			FOR(j, 1, maxn-1) cp[j][0]=cp[j-1][0]*b, cp[0][j]=cp[0][j-1]*a;
			FOR(j, 1, maxn-1) FOR(k, 1, maxn-1) cp[j][k]+=a*cp[j][k-1]+b*cp[j-1][k];

			

			memset(temp, 0, sizeof(temp));
			FOR(k, 0, maxn-1) FOR (j, 0, maxn-k-1-cnt)
			   	temp[max(k-s, 0)+j]+=pa[j]*cp[j+cnt-1][k]*b;//if k-s<0 => we still have to pick threads to complete the ith thread's tasks. But each pick, not matter what it is, it will be used for the ith thread
			
			
			memcpy(pa, temp, sizeof(pa));
			cnt+=p;
		}
		double res=cnt;

		REP(i, maxn) res+=i*pa[i];
		return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"....."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 5.0; verify_case(0, Arg1, expectedExecutionTime(Arg0)); }
	void test_case_1() { string Arr0[] = {".","S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.9999999999999996; verify_case(1, Arg1, expectedExecutionTime(Arg0)); }
	void test_case_2() { string Arr0[] = {"..","S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 4.999999999999999; verify_case(2, Arg1, expectedExecutionTime(Arg0)); }
	void test_case_3() { string Arr0[] = {".","...S.",".........S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 16.144458312987712; verify_case(3, Arg1, expectedExecutionTime(Arg0)); }
	void test_case_4() { string Arr0[] = {".....","...S...","S......","......S..","...S.","..S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 65.45700302526924; verify_case(4, Arg1, expectedExecutionTime(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SequentialThreads ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
