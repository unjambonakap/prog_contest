// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulBalls.cpp"

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

const double eps=10e-9;
map<vi, int> dp;
const int maxn=1600;
double trans[maxn][maxn];
int n;
int nb;
vi st[maxn];

int proc(vi &state){
	sort(ALL(state), greater<int>());
	if (state.back()==0) state.pop_back();

	if (dp.find(state)!=dp.end())return dp.find(state)->ND;
	int id;
	dp.insert(MP(state, id=n));
	st[n++]=state;

	
	trans[id][id]=1.;
	if (state.size()==1)return id;
	REP(i, state.size()) REP(j, state.size()){
		if (i==j && state[i]==1)continue;
		vi ns=state;
		++ns[i]; --ns[j];
		trans[id][proc(ns)]-=(i==j?state[i]*(state[i]-1):state[i]*state[j])/double(nb*(nb-1));
	}
	return id;
}



class ColorfulBalls {
	public:
	double expectedStepCount(string colors) {
		int col[27];
		vi state;

		CLR(dp);

		n=0;
		nb=colors.length();
		memset(col, 0, sizeof(col));
		memset(trans, 0, sizeof(trans));

		FE(it, colors) ++col[*it-'A'];
		REP(i, 27) if (col[i]>0) state.pb(col[i]);
		proc(state);

		assert(n<maxn);
		int q[maxn];
		double x[maxn], y[maxn];
		memset(x, 0, sizeof(x));
		FOR (i, 2, 24){
			int qe=0;
		   	REP(j, n) if (st[j].size()==i) q[qe++]=j;
			memset(y, 0, sizeof(y));

			REP(j, qe) {
				y[q[j]]=1.;
				REP(k, n) if (st[k].size()<i) y[q[j]]-=trans[q[j]][k]*x[k];
			}
			
								
			REP(j, qe){
				int p=j;
				FOR(k, j+1, qe-1) if (fabs(trans[q[p]][q[j]])<fabs(trans[q[k]][q[j]]))p=k;
				REP(k, qe) swap(trans[q[p]][q[k]], trans[q[j]][q[k]]);
				swap(y[q[p]], y[q[j]]);
				assert(fabs(trans[q[j]][q[j]])>eps);
				FOR(k, j+1, qe-1){
					double temp=trans[q[k]][q[j]]/trans[q[j]][q[j]];
					y[q[k]]-=temp*y[q[j]];
				   	REP(u, qe) trans[q[k]][q[u]]-=trans[q[j]][q[u]]*temp;
				}
			}
			REPV(j, qe){
				double temp=0.;
				FOR(k, j+1, qe-1) temp+=trans[q[j]][q[k]]*x[q[k]];
				assert(fabs(trans[q[j]][q[j]])>eps);
				x[q[j]]=(y[q[j]]-temp)/trans[q[j]][q[j]];
			}
		}


		return x[0];

	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABCDEFGHIABCDEFGHIABCDEFG"; double Arg1 = 1.0; verify_case(0, Arg1, expectedStepCount(Arg0)); }
	void test_case_1() { string Arg0 = "Q"; double Arg1 = 0.0; verify_case(1, Arg1, expectedStepCount(Arg0)); }
	void test_case_2() { string Arg0 = "AAAAAAA"; double Arg1 = 0.0; verify_case(2, Arg1, expectedStepCount(Arg0)); }
	void test_case_3() { string Arg0 = "ZCZ"; double Arg1 = 3.0; verify_case(3, Arg1, expectedStepCount(Arg0)); }
	void test_case_4() { string Arg0 = "KLM"; double Arg1 = 4.0; verify_case(4, Arg1, expectedStepCount(Arg0)); }
	void test_case_5() { string Arg0 = "AAABB"; double Arg1 = 11.666666666666668; verify_case(5, Arg1, expectedStepCount(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ColorfulBalls ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
