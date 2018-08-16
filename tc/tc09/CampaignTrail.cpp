// BEGIN CUT HERE

// END CUT HERE
//#line 5 "CampaignTrail.cpp"

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
const int MAX_N=52;


double dp[2][MAX_N][MAX_N*100];
int sum[MAX_N];



class CampaignTrail {
	public:
		double probWin(vector <int> el, vector <int> wa, vector <int> wb, int visits) {
			int n, ne;
			int i, j, k;
			int lim;

			n=el.size(), ne=0;
			memset(sum, 0, sizeof(sum));
			for (i=1; i<=n; ++i)sum[i]=sum[i-1]+el[i-1];
			ne=sum[n];
			lim=floor(double(ne)/2)+1;


			for (i=0; i<=ne; ++i)
				for (j=0; j<=visits; ++j)
					dp[n%2][j][i]=double(i>=lim), dp[(n+1)%2][j][i]=0.;
				

			for (i=n-1; i>=0; --i){
				int p, np;
				double pa, pb;
				pa=wa[i]/100., pb=wb[i]/100.;

				p=i%2, np=(i+1)%2;
//				printf("on %d\n", i);
				for (j=0; j<=visits; ++j){
					for (k=max(0, lim-(ne-sum[i])); k<=sum[i]; ++k){
						double sa, sb;
						sa=sb=0.;
						if (j<visits)
							sb=pb*dp[np][j+1][k+el[i]]+(1-pb)*dp[np][j+1][k];

						sa=pa*dp[np][j][k+el[i]]+(1-pa)*dp[np][j][k];
						dp[p][j][k]=max(sa, sb);
//						printf("%d(%d) %d %d => %lf %lf xx %lf %lf\n", i, p, j, k, sa, sb, pa, pb);
					}
				}


			}
			return dp[0][0][0];



		}


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 5, 1, 5 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 50, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 50, 100, 50 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; double Arg4 = 0.625; verify_case(0, Arg4, probWin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = { 4, 9, 5 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 50, 50 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 100, 100, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; double Arg4 = 0.5; verify_case(1, Arg4, probWin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = { 5, 9, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 50, 50, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 0, 100, 100 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; double Arg4 = 0.75; verify_case(2, Arg4, probWin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = { 1, 1, 1, 1, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0, 0, 0, 49 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 100, 100, 100, 100, 51 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; double Arg4 = 0.49; verify_case(3, Arg4, probWin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = { 1, 1, 1, 1, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0, 0, 0, 49 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 100, 100, 100, 100, 51 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; double Arg4 = 0.51; verify_case(4, Arg4, probWin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = { 1, 1, 1, 1, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0, 0, 0, 49 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 100, 100, 100, 100, 51 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; double Arg4 = 1.0; verify_case(5, Arg4, probWin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arr0[] = { 1, 1, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 25, 50, 25 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 50, 25, 50 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; double Arg4 = 0.5; verify_case(6, Arg4, probWin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_7() { int Arr0[] = { 1, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 0, 100 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; double Arg4 = 0.0; verify_case(7, Arg4, probWin(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CampaignTrail ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
