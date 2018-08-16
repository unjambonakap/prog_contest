// BEGIN CUT HERE

// END CUT HERE
#line 5 "TransposeMyMusic.cpp"

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


const char *fl[]={"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
const char *sl[]={"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
const char *sk[]={"Bb", "Bbm", "Db", "Dbm", "Eb", "Ebm", "F", "Fm", "Gb", "Gbm", "Ab", "Abm"};


pii getCode(string s){
	int minor=0;
	if (s[s.length()-1]=='m')s.erase(s.length()-1), minor=1;
	REP(i, 12) if (sl[i]==s)return MP(i, minor);
	REP(i, 12) if (fl[i]==s)return MP(i, minor);
	assert(0);
	return pii();
}

class TransposeMyMusic {
	public:
	string transposeMusic(vector <string> sm, string newKey) {
		string s;
		FE(it, sm) s+=*it;
		istringstream ss(s);
		string sa, res;

		int pad;
		int sharp=1;
		ss>>sa;
		REP(i, 12) if (sk[i]==newKey){sharp=0; break;}
		int ida, idb;
		ida=getCode(sa).ST, idb=getCode(newKey).ST;
		pad=idb-ida;
		res+=newKey;

		while(ss>>sa){
			if (sa=="")continue;
			if (sa=="|"){res+=" |"; continue;}
			res+=" ";
			pii p=getCode(sa);
			if (sharp)res+=sl[(12+p.ST+pad)%12];
			else res+=fl[(12+p.ST+pad)%12];
			if (p.ND)res+="m";



		}
		return res;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"G D Am | G D C | G D Am | G D C"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "F"; string Arg2 = "F C Gm | F C Bb | F C Gm | F C Bb"; verify_case(0, Arg2, transposeMusic(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"A Bb B C Db D Eb E F Gb G Ab"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "A"; string Arg2 = "A A# B C C# D D# E F F# G G#"; verify_case(1, Arg2, transposeMusic(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"C G Am F | C G F C Dm C | C G A",
		"m F | G F C Dm C | Am F G ",
		"F C Dm C"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "F#"; string Arg2 = "F# C# D#m B | F# C# B F# G#m F# | F# C# D#m B | C# B F# G#m F# | D#m B C# B F# G#m F#"; verify_case(2, Arg2, transposeMusic(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"A# | | | Bb"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "G#"; string Arg2 = "G# | | | G#"; verify_case(3, Arg2, transposeMusic(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"Gm C Gm | Eb D C Gm | Gm C Gm"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Dbm"; string Arg2 = "Dbm Gb Dbm | A Ab Gb Dbm | Dbm Gb Dbm"; verify_case(4, Arg2, transposeMusic(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	TransposeMyMusic ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
