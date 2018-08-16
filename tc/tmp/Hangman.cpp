// BEGIN CUT HERE

// END CUT HERE
#line 5 "Hangman.cpp"

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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


class Hangman {
	public:

	string guessWord(string feedback, vector <string> words) {
        int n=words.size();
        int res=-1;
        set<char> has;
        REP(i, feedback.length()) if (feedback[i]!='-') has.insert(feedback[i]);
        REP(i, n) if (feedback.length()==words[i].length()){
            string &s=words[i];
            int fd=1;
            REP(j, feedback.length()) if (feedback[j]!='-'){ if (feedback[j]!=s[j]){fd=0; break;}} else if (has.count(s[j])) {fd=0; break;}
            if (fd){
                if (res!=-1) return "";
                res=i;
            }
            

        }
		
        return res==-1?"":words[res];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "N-N-A"; string Arr1[] = {"NINJA", "NINJAS", "FLIPS", "OUT", "FRISBEE"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "NINJA"; verify_case(0, Arg2, guessWord(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "B--B--"; string Arr1[] = {"BRINGS", "BARBED", "BUBBLE"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "BARBED"; verify_case(1, Arg2, guessWord(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "---------"; string Arr1[] = {"MONKEY", "FORCE", "IS", "GAINING", "STRENGTH"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = ""; verify_case(2, Arg2, guessWord(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "-AAA--"; string Arr1[] = {"CAAABB", "BAAACC"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = ""; verify_case(3, Arg2, guessWord(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "---H-O-H-B-OPHOB--"; string Arr1[] = {"ROSACEA", "GYROVAGUE", "SHACONIAN", "ALTITONANT",
 "BRACHIATION", "CERCOPITHECAN", "SCOLECOPHAGOUS",
 "RESISTENTIALISM", "SLUBBERDEGULLION", 
 "AICHMORHABDOPHOBIA", "SPECTOCLOACAPHOBIA",
 "ULTRACREPIDARIANISM", "HIPPOPOTOMONSTROSESQUIPEDALIAN",
 "CHARGOGGAGOGGMANCHAUGGAGOGGCHAUBUNAGUNGAMAUGG"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "AICHMORHABDOPHOBIA"; verify_case(4, Arg2, guessWord(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  Hangman ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
