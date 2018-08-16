// BEGIN CUT HERE

// END CUT HERE
#line 5 "MemorizingPi.cpp"

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

const int maxn=2510;
pair<int, string> dp[maxn];
int seen[maxn];
string s;

int cost(string a){
	bool fd;

	fd=true; REP(i, a.length())if (i>0 && a[i]!=a[i-1]){fd=false; break;}
	if (fd)return 1;
	int b=toInt(a);
	if (a[0]!='0' && count_bit(b)==1)return 2;
	fd=true; REP(i, a.length())if (i>0 && a[i]!=a[i-1]+1){fd=false; break;}
	if (fd) return 4;
	fd=true; REP(i, a.length())if (i>0 && a[i]!=a[i-1]-1){fd=false; break;}
	if (fd) return 5;
	if (a[0]==a[a.length()-1])return 7;
	REP(i, a.length()) REP(j, i) if (a[i]==a[j])return 8;
	return 10;

}


pair<int, string> proc(int a){
	if (a>=s.length())return MP(a==s.length()?0:-1, "");
	if (seen[a])return dp[a];
	seen[a]=1;
	pair<int, string> res, np;
	res.ST=-1;
	FOR(i, 3, 4){
		np=proc(a+i);
		if (np.ST==-1)continue;
		np.ST+=cost(s.substr(a, i));
		if (res.ST==-1 || np.ST<res.ST) res=MP(np.ST, s.substr(a, i)+" "+np.ND);
	}
	return dp[a]=res;
}

class MemorizingPi {
	public:
	vector <string> segmentation(vector <string> digits) {
		s="";
		FE(it, digits) s+=*it;
		memset(seen, 0, sizeof(seen));
		
		string res=proc(0).ND;
		res.erase(res.length()-1);

		int p=0, np;
		vs tb;
		while((np=p+100)<res.length()){
			while(res[np]!=' ')--np;
			tb.pb(res.substr(p, np-p));
			p=np+1;
		}
		tb.pb(res.substr(p));
		return tb;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	//void test_case_0() { string Arr0[] = { "2562222567" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"256 2222 567" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, segmentation(Arg0)); }
	void test_case_0() { string Arr0[] = {"012345678901234567890123456789", "987654321098765432109876543210", "012345678901234567890123456789", "555", "012345678901234567890123456789", "555", "987654321098765432109876543210"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"256 2222 567" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, segmentation(Arg0)); }
	void test_case_1() { string Arr0[] = { "2222",
  "2",
  "25",
  "555",
  "555" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"222 222 555 5555" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, segmentation(Arg0)); }
	void test_case_2() { string Arr0[] = { "31415926535897932384626433832795028841971693993751",
  "05820974944592307816406286208998628034825342117067",
  "98214808651328230664709384460955058223172535940812",
  "84811174502841027019385211055596446229489549303819",
  "64428810975665933446128475648233786783165271201909",
  "14564856692346034861045432664821339360726024914127",
  "37245870066063155881748815209209628292540917153643",
  "67892590360011330530548820466521384146951941511609" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"3141 5926 535 8979 3238 4626 433 832 7950 2884 1971 6939 9375 1058 2097 4944 5923 0781 6406 2862", "0899 8628 0348 2534 2117 0679 8214 8086 5132 8230 6647 0938 4460 9550 5822 3172 5359 4081 2848 111", "7450 2841 0270 1938 5211 0555 9644 6229 4895 4930 3819 6442 8810 9756 6593 3446 128 475 6482 3378", "678 3165 2712 0190 914 5648 5669 234 6034 8610 454 3266 4821 3393 6072 6024 9141 2737 2458 7006 6063", "1558 8174 8815 2092 0962 8292 5409 1715 3643 678 9259 0360 0113 3053 054 8820 4665 2138 4146 9519", "4151 1609" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, segmentation(Arg0)); }
	void test_case_3() { string Arr0[] = { "111222333444555",
  "111222333444555",
  "111222333444555",
  "111222333444555",
  "1112223334445555",
  "111222333444555",
  "111222333444555",
  "111222333444555",
  "111222333444555",
  "11122233344445555" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"111 222 333 444 555 111 222 333 444 555 111 222 333 444 555 111 222 333 444 555 111 222 333 444 5555", "111 222 333 444 555 111 222 333 444 555 111 222 333 444 555 111 222 333 444 555 111 222 333 4444", "5555" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, segmentation(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MemorizingPi ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
