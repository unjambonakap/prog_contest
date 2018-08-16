// BEGIN CUT HERE

// END CUT HERE
#line 5 "SistersErasingLetters.cpp"

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
typedef vector<string> vs;

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

const int maxn=55;
int mem[maxn][maxn][2];
int n;
string s;

int proc(int a, int b, int f){
    if (b==n) return 1;
    int &r=mem[a][b][f];
    if (r!=-1) return r;

    r=1;
    REP(i, n-b){
        if (proc(a+i, b+i+1, f^1)==f){r=f; break;} 
        if (i<n-b-1 && s[a+i]!=s[b+i]){ r=s[a+i]>s[b+i]; break;}
    }
    return r;

}
class SistersErasingLetters {
	public:
	string whoWins(string word) {
        memset(mem, -1, sizeof(mem));
        n=word.length();
        s=word;
        int ans=proc(0, 0, 0);
        if (ans) return "Romashka";
        else return "Camomile";
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "topcoder"; string Arg1 = "Camomile"; verify_case(0, Arg1, whoWins(Arg0)); }
	void test_case_1() { string Arg0 = "program"; string Arg1 = "Romashka"; verify_case(1, Arg1, whoWins(Arg0)); }
	void test_case_2() { string Arg0 = "abcd"; string Arg1 = "Camomile"; verify_case(2, Arg1, whoWins(Arg0)); }
	void test_case_3() { string Arg0 = "abc"; string Arg1 = "Romashka"; verify_case(3, Arg1, whoWins(Arg0)); }
	void test_case_4() { string Arg0 = "easyproblemroundfivetopcoderopentwothousandeleven"; string Arg1 = "Camomile"; verify_case(4, Arg1, whoWins(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SistersErasingLetters ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
