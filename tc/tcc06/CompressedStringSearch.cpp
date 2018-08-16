// BEGIN CUT HERE

// END CUT HERE
#line 5 "CompressedStringSearch.cpp"

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



class CompressedStringSearch {
	public:
	long long indexOf(vector <string> dictionary, string haystack, string needle) {
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"A=bCc","c=123","b=c119"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "abCca"; string Arg2 = "9C1"; long long Arg3 = 6LL; verify_case(0, Arg3, indexOf(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "nowisthetimeforallgoodmen"; string Arg2 = "time"; long long Arg3 = 8LL; verify_case(1, Arg3, indexOf(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "time"; string Arg2 = "nowisthetimeforallgoodmen"; long long Arg3 = -1LL; verify_case(2, Arg3, indexOf(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"A=BBB","B=CCC","C=DDD","D=EEE","E=FFF","F=GGG","G=HHH","H=III","I=JJJ",
 "J=KKK","K=LLL","L=MMM","M=NNN","N=OOO","O=PPP","P=QQQ","Q=RRR","R=SSS",
 "S=TTT","T=UUU","U=VVV","V=WWW","W=XXX","X=YYY","Y=ZZZ","Z=000","0=111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Atime"; string Arg2 = "1time"; long long Arg3 = 7625597484986LL; verify_case(3, Arg3, indexOf(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"A=three_blind_mice","B=_the","C=By_","D=_see_","E=_a_","F=ife_","G=_you","H=DhowCrun","I=all_ran_after",
 "J=_farmers_w","K=who_cut_offBir_tails_withEcarvingknF","L=didG_everDsuchEthing_in"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "A_AHHCIBJFKLGr_lFas_A"; string Arg2 = "your_life_as_three"; long long Arg3 = 181LL; verify_case(4, Arg3, indexOf(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CompressedStringSearch ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
