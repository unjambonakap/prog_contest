// BEGIN CUT HERE

// END CUT HERE
#line 5 "TableLabel.cpp"

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


const int maxn=54;
int n, m;
string tb[maxn][maxn];
int sola[maxn][maxn], solb[maxn][maxn];

class TableLabel {
	public:
	vector <string> labels(vector <string> table) {
		n=table.size();
		REP(i, n){
			string ns;
			REP(j, table[i].length()) if (table[i][j]!=' ' || (j!=table[i].length()-1 && table[i][j+1]!=' ')) ns+=table[i][j];
			istringstream ss(table[i]);
			m=0;
			while(ss>>tb[i][m])++m;
			while(tb[i][m-1].length()==0) --m;
		}
		int fd=-1;
		FOR(i, 1, tb[0][0].length()-1){
			int ni=tb[0][0].length()-i;
			string sa=tb[0][0].substr(0, i), sb=tb[0][0].substr(i);
			
			REP(j, n){
				if (tb[j][0].length()<ni || tb[j][0].substr(tb[j][0].length()-ni)!=sb)goto fail;
				string s=tb[j][0].substr(0, tb[j][0].length()-ni);
				if (!s.length())goto fail;
				REP(k, m) if (tb[j][k].length()<s.length() || tb[j][k].substr(0, s.length())!=s) goto fail; else sola[j][k]=s.length();
			}
			REP(k, m){
				if (tb[0][k].length()<i || tb[0][k].substr(0, i)!=sa)goto fail;
				string s=tb[0][k].substr(i);
				if (!s.length())goto fail;
				REP(j, n) if (tb[j][k].length()<s.length() || tb[j][k].substr(tb[j][k].length()-s.length())!=s) goto fail; else solb[j][k]=s.length();
			}
			REP(j, n) REP(k, m) if (sola[j][k]+solb[j][k]!=tb[j][k].length()) goto fail;
			

			printf("works for %d\n", i);
			if (fd!=-1)return vs(1, "multiple");
			fd=i;
fail:;
		}
		if (fd==-1)return vs(1, "none");
		vs res;
		REP(i, m) res.pb(tb[0][i].substr(fd));
		REP(i, n) res.pb(tb[i][0].substr(0, tb[i][0].length()-(tb[0][0].length()-fd)));
		return res;


	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	//void test_case_0() { string Arr0[] = {"  ABCX ABCXX   ABCXXX  ","DX DXX DXXX    "}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"X", "XX", "XXX", "ABC", "D" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, labels(Arg0)); }
	void test_case_0() { string Arr0[] = {"ABCDEFGHIJABCDEFGHIJ    ABCDEFGHIJJ           ", "                  JABCDEFGHIJ JJ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"X", "XX", "XXX", "ABC", "D" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, labels(Arg0)); }
	void test_case_1() { string Arr0[] = {"AAA AAA"," AAA   AAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"multiple" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, labels(Arg0)); }
	void test_case_2() { string Arr0[] = {"AB CD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"none" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, labels(Arg0)); }

	// END CUT HERE

	};

// BEGIN CUT HERE
int main(){
	TableLabel ___test; 
	___test.run_test(0);
} 
// END CUT HERE
