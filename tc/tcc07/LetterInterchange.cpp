// BEGIN CUT HERE

// END CUT HERE
#line 5 "LetterInterchange.cpp"

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

const int m=26;
int mp[m][m][2];
int last[m];


class LetterInterchange {
	public:
	vector <int> interchangeWhich(vector <string> s1, vector <string> s2) {
		string s;
		FE(it, s1)s+=*it;
		FE(it, s2)s+=*it;
		int n=s.length();
		vi t(2);

		memset(mp, -1, sizeof(mp));
		memset(last, -1, sizeof(last));
		
		REP(i, n){
			int a=s[i]-'a';
			if (mp[a][a][0]==-1 && last[a]!=-1)mp[a][a][0]=last[a], mp[a][a][1]=i;


			if (last[a]==-1) REP(j, a) mp[a][j][0]=i;
			FOR(j, a+1, m-1) mp[j][a][1]=i;
			REP(j, a) mp[j][a][0]=last[j], mp[j][a][1]=i;
			last[a]=i;
		}

		map<int, pii> pos;
		pii a;


		REP(i, m) REP(j, i) if (mp[i][j][0]!=-1 && mp[i][j][1]!=-1 && mp[i][j][0]<mp[i][j][1]) pos.insert(MP(mp[i][j][0], MP(j, i)));
		if (pos.size()>0){
			a=pos.begin()->ND;
			t[0]=pos.begin()->ST;
			t[1]=mp[a.ND][a.ST][1];
			if (t[0]>t[1])swap(t[0], t[1]);
			return t;
		}
		set<pii> posa;
		REP(i, m) if (mp[i][i][0]!=-1 && mp[i][i][1]!=-1) posa.insert(MP(mp[i][i][0], mp[i][i][1]));
		if (posa.size()>0){
			t[0]=posa.begin()->ST;
			t[1]=posa.begin()->ND;
			if (t[0]>t[1])swap(t[0], t[1]);
			return t;
		}

		CLR(pos);
		REP(j, m) REP(i, j) if (mp[i][j][0]!=-1 && mp[i][j][1]!=-1) pos.insert(MP(-mp[i][j][0], MP(j, i)));
		assert(pos.size()>0);
		a=pos.begin()->ND;
		t[0]=-pos.begin()->ST;
		t[1]=mp[a.ND][a.ST][1];
		if (t[0]>t[1])swap(t[0], t[1]);
		return t;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"a", "b", "a"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"c", "a", "b", "a"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 6 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, interchangeWhich(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"aa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"bb"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, interchangeWhich(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"a"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"b", "c"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, interchangeWhich(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"a", "b"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"cb"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, interchangeWhich(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccc",
 "cccccccccccccccccccccccccccccccccccccccccccccccccc",
 "cccccccccccccccccccccccccccccccccccccccccccccccccc",
 "cccccccccccccccccccccccccccccccccccccccccccccccccc",
 "cccccccccccccccccccccccccccccccccccccccccccccccccc",
 "cccccccccccccccccccccccccccccccccccccccccccccccccc",
 "cccccccccccccccccccccccccccccccccccccccccccccccccc",
 "cccccccccccddddddddddddddddddddddddddddddddddddddd",
 "dddddddddddddddddddddddddddddddddddddddddddddddddd",
 "dddddddddddddddddddddddddddddddddddddddddddddddddd",
 "dddddddddddddddddddddddddddddddddddddddddddddddddd",
 "dddddddddddddddddddddddddddddddddddddddddddddddddd",
 "dddddddddddddddddddddddddddddddddddddddddddddddddd",
 "dddddddddddddddddddddddddddddddddddddddddddddddddd",
 "ddddddddddddddddddeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
 "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
 "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
 "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
 "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
 "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
 "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
 "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeffffff",
 "ffffffffffffffffffffffffffffffffffffffffffffffffff",
 "ffffffffffffffffffffffffffffffffffffffffffffffffff",
 "ffffffffffffffffffffffffffffffffffffffffffffffffff",
 "ffffffffffffffffffffffffffffffffffffffffffffffffff",
 "ffffffffffffffffffffffffffffffffffffffffffffffffff",
 "ffffffffffffffffffffffffffffffffffffffffffffffffff",
 "ffffffffffffffffffffffffffffffffffffffffffffffffff",
 "fffffffffffffffggggggggggggggggggggggggggggggggggg",
 "gggggggggggggggggggggggggggggggggggggggggggggggggg",
 "gggggggggggggggggggggggggggggggggggggggggggggggggg",
 "gggggggggggggggggggggggggggggggggggggggggggggggggg",
 "gggggggggggggggggggggggggggggggggggggggggggggggggg",
 "gggggggggggggggggggggggggggggggggggggggggggggggggg",
 "gggggggggggggggggggggggggggggggggggggggggggggggggg"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"gggggggggggggggggggggggggggggggggggggggggggggggggg",
 "ghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
 "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
 "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
 "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
 "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
 "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
 "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhiiiiiiiiiiii",
 "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
 "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
 "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
 "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
 "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
 "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
 "iiiiiiiiiiiiiiiiiiiiiijjjjjjjjjjjjjjjjjjjjjjjjjjjj",
 "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj",
 "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj",
 "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj",
 "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj",
 "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj",
 "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj",
 "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjkkkkk",
 "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk",
 "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk",
 "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk",
 "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk",
 "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk",
 "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk",
 "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkllll",
 "llllllllllllllllllllllllllllllllllllllllllllllllll",
 "llllllllllllllllllllllllllllllllllllllllllllllllll",
 "llllllllllllllllllllllllllllllllllllllllllllllllll",
 "llllllllllllllllllllllllllllllllllllllllllllllllll",
 "llllllllllllllllllllllllllllllllllllllllllllllllll",
 "llllllllllllllllllllllllllllllllllllllllllllllllll",
 "llllllllllllllllllllllllllllllllllllllllllllllllll",
 "lllllllllllllmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
 "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
 "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
 "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
 "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
 "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
 "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
 "mmmmmmmmmmmmmmmmmmmmmmnnnnnnnnnnnnnnnnnnnnnnnnnnnn",
 "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn",
 "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn",
 "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn",
 "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn",
 "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn",
 "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, interchangeWhich(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"aa"}	; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"b", "bcc"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, interchangeWhich(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  LetterInterchange ___test; 
        ___test.run_test(3); 
        } 
// END CUT HERE
