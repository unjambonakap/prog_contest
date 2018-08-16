// BEGIN CUT HERE

// END CUT HERE
#line 5 "CostMatrix.cpp"

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

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=25;
int m[maxn][maxn], nm[maxn][maxn];
int proced[maxn][maxn];
int n;

int ended(){
	REP(i, n) REP(j, n) if (!proced[i][j])return 0;
	return 1;
}



class CostMatrix {
	public:
	int leastTotalCost(vector <string> matrix) {
		n=matrix.size();
		REP(i, n){
			istringstream ss(matrix[i]);
			REP(j, n) ss>>m[i][j];
		}
		memcpy(nm, m, sizeof(nm));
		REP(k, n) REP(i, n) REP(j, n) checkmin(nm[i][j], nm[i][k]+nm[k][j]);
		REP(i, n) REP(j, n) if (nm[i][j]!=m[i][j])return -1;
		int res=0;

		REP(i, n) proced[i][i]=0;
		REP(i, n) REP(j, n) if (i!=j) proced[i][j]=100000;
		while(1){
			pii p(-1, -1);

			REP(i, n) REP(j, n) if (proced[i][j]!=m[i][j] && (p.ST==-1 || m[i][j]<m[p.ST][p.ND])) p=MP(i, j);
			if (p.ST==-1)break;

			res+=m[p.ST][p.ND];
			proced[p.ST][p.ND]=proced[p.ND][p.ST]=m[p.ST][p.ND];
			REP(k, n) REP(i, n) REP(j, n) checkmin(proced[i][j], proced[i][k]+proced[k][j]);

		}
		//while(!ended()){
		//	pii p;
		//	REP(i, n) REP(j, n) if (!proced[i][j])
		//}
		return res;
		

	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0 2 2",
 "2 0 2",
 "2 2 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(0, Arg1, leastTotalCost(Arg0)); }
	void test_case_1() { string Arr0[] = {"0 6 15 2 6",
 "6 0 9 8 12",
 "15 9 0 16 18",
 "2 8 16 0 4",
 "6 12 18 4 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 55; verify_case(1, Arg1, leastTotalCost(Arg0)); }
	void test_case_2() { string Arr0[] = {"0 1 6 17 26 13 7 16",
 "1 0 5 16 25 12 7 15",
 "6 5 0 21 21 8 12 11",
 "17 16 21 0 41 28 23 31",
 "26 25 21 41 0 13 32 10",
 "13 12 8 28 13 0 19 3",
 "7 7 12 23 32 19 0 22",
 "16 15 11 31 10 3 22 0"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 69; verify_case(2, Arg1, leastTotalCost(Arg0)); }
	void test_case_3() { string Arr0[] = {"0 1 3", 
 "1 0 1", 
 "3 1 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, leastTotalCost(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CostMatrix ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
