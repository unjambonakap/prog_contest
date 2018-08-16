// BEGIN CUT HERE

// END CUT HERE
#line 5 "CheapestTabComplete.cpp"

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

const int maxn=55;
set<string> ok;

class CheapestTabComplete {
	public:
	int getFewest(vector <string> names, string w) {
        int n=names.size();
        int m=w.length();
        int dp[m+1];
        memset(dp, 0x7, sizeof(dp));
        dp[0]=0;
        sort(ALL(names));
        ok.clear();
        REP(i, n) if (names[i].length()<=w.length()){
            int fd=1;
            REP(j, names[i].length()) if (names[i][j]!=w[j]){fd=0; break;}
            if (fd) ok.insert(names[i]);


        }

        REP(i, m){
            checkmin(dp[i+1], dp[i]+1);
            REP(j, n) if (ok.count(names[j])) checkmin(dp[names[j].length()], dp[i]+j+1);
            vs b;
            REP(j, n) if (names[j].length()>i && names[j][i]==w[i]) b.pb(names[j]);
            names=b;
            sort(ALL(names));
            n=names.size();

        }


        return dp[m]+1;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "myname"; int Arg2 = 7; verify_case(0, Arg2, getFewest(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"myn","myname"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "myname"; int Arg2 = 3; verify_case(1, Arg2, getFewest(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"abc","ab","abcd","frankies","frank","a","a"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "frankie"; int Arg2 = 5; verify_case(2, Arg2, getFewest(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"a","a","f","f","fr","fr","fra","fra","fran","fran","frank","frank"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "frankie"; int Arg2 = 8; verify_case(3, Arg2, getFewest(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"a","a","bcde","bcde","bcde","bcdefghij"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "bcdefghijk"; int Arg2 = 6; verify_case(4, Arg2, getFewest(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"aaaa","aaaa","aaaa","aaaa","aaaa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "aaaaaaaaaaaaaaaaaaaaaaa"; int Arg2 = 21; verify_case(5, Arg2, getFewest(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CheapestTabComplete ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
