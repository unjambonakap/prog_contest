// BEGIN CUT HERE

// END CUT HERE
#line 5 "PrimeSums.cpp"

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

const int MAX_N=51;

char primeL[510001]; 
ll flist[510000];

class PrimeSums {
	public:
	long long getCount(vector<int> bag) {
		map<int, int> bc;
		int i, j, k;


		memset(primeL, 1, sizeof(primeL));
		primeL[0]=primeL[1]=0;
		for (i=2; i<510001; ++i){
			if (primeL[i]==0)continue;
			for (j=i+i; j<510001; j+=i)
				primeL[j]=0;
		}

		FE(it, bag){
			if (bc.find(*it)==bc.end())
				bc[*it]=0;
			++bc[*it];
		}

		memset(flist, 0, sizeof(flist));
		flist[0]=1;
		FE(it, bc){
			int a, b;
			a=it->ST, b=it->ND;
			int ov=flist[0];
			REPV(i, 500000)
				if (flist[i]) FOR(j, 1, b)
					flist[i+a*j]+=(i+a*j==0?ov:flist[i]);
		}
		//FE(it, bc){
		//	map<int, ll> ncnt=cnt;
		//	FEV(ita, cnt){
		//		for (i=1; i<=it->ND; ++i){
		//			int nv=ita->ST+ll(it->ST)*i;
		//			assert(nv<=500000);
		//			if (ncnt.find(nv)==ncnt.end())ncnt.insert(MP(nv, 0LL));
		//			ncnt[nv]+=ita->ND;
		//		}
		//	}
		//	cnt=ncnt;
		//}


		ll res=0;
		REP(i, 500000){
			if (flist[i] && primeL[i])
				res+=flist[i];
		}
		return res;




	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arr0[] = {1,1,2,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; verify_case(0, Arg1, getCount(Arg0)); }
	void test_case_0() { int Arr0[] = {9997, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; verify_case(0, Arg1, getCount(Arg0)); }
	void test_case_1() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(1, Arg1, getCount(Arg0)); }
	void test_case_2() { int Arr0[] = {4,6,8,10,12,14}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(2, Arg1, getCount(Arg0)); }
	void test_case_3() { int Arr0[] = {1,2,4,8,16,32,64,128}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 54LL; verify_case(3, Arg1, getCount(Arg0)); }
	void test_case_4() { int Arr0[] = {1234,5678,9012,3456,7890,2345,6789,123,4567,8901}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 97LL; verify_case(4, Arg1, getCount(Arg0)); }
	void test_case_5() { int Arr0[] = {0,0,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 3LL; verify_case(5, Arg1, getCount(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	PrimeSums ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
