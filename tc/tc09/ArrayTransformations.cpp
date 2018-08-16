// BEGIN CUT HERE

// END CUT HERE
#line 5 "ArrayTransformations.cpp"

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




class ArrayTransformations {
	public:

	int minimalValue(vector <string> initialArray, int K, int C) {
		int a[300], na[300], nb[300];

		string s;
		FE(it, initialArray)
			s+=*it;
		cout<<s<<endl;
		istringstream ss(s);
		int n=0;

		while(ss>>a[n])++n;
		int H, L, M;
		H=2000000;
		L=-1;
		int nk, nc;
		int i, j, k;

		while(L+1<H){
			M=(H+L)/2;

			nk=0;
			for (i=0; i<n; ++i)
				nk+=nb[i]=na[i]=max(0, a[i]-M);
			nc=nk;
			if (nk>K){
				for (i=1; i<n; ++i){
					for (j=0; j+i<n; ++j){
						int r=min(nk-K, min(na[j], nb[j+i]));
						if (r==0)continue;
						nk-=r;
						nc+=(i-1)*r;
						na[j]-=r; nb[j+i]-=r;
					}
				}


			}
			if (nk<=K && nc<=C)
				H=M;
			else
				L=M;
		}
		return H;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"6 2 9 4 5 1 7 8 3 10"};  vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 11; int Arg3 = 7; verify_case(0, Arg3, minimalValue(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"1 5 9", " 2 9 0 ", "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 10; int Arg3 = 6; verify_case(1, Arg3, minimalValue(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"1 0 3 0 0 0 0 3 0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 7; int Arg3 = 2; verify_case(2, Arg3, minimalValue(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"765 358 938 10 ", "83", "9", " 172"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 200; int Arg3 = 838; verify_case(3, Arg3, minimalValue(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ArrayTransformations ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
