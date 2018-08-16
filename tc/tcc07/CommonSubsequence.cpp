// BEGIN CUT HERE

// END CUT HERE
#line 5 "CommonSubsequence.cpp"

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

inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}


const int maxc=127;
const int maxn=2500;


int cnt[maxc];
int na, nb;
int skip[maxc][2];

int chooseC(int p, string &s, int z){

	int c=0;
	int n=s.length();
	REP(it, n) if (s[(n+it-1)%n]==p){
		int l=skip[it][z];
		if (l==-1)continue;

		int nc=0;
		for(; l<n; ++l) if (s[(n+it+l)%n]==p)++nc;
		c=max(c, nc);
	}
	return c;
}
int procSkip(int z, string &s, int n, int c){
	REP(i, s.length()){
		int j=skip[i][z];
		if (n==0)continue;
		int nk=0;
		for (; nk!=n && j<s.length(); ++j) if (s[(i+j)%s.length()]==c)++nk;
		skip[i][z]=(nk!=n?-1:j);
	}
}

class CommonSubsequence {
	public:
	string maxLex(vector <string> a, vector <string> b, int suffixLength) {
		string sa, sb;
		FE(it, a)sa+=*it;
		FE(it, b)sb+=*it;
		na=sa.length(), nb=sb.length();
		memset(cnt, 0, sizeof(cnt));
		memset(skip, 0, sizeof(skip));


		int ma, mb;
		string res;
		REPV(i, maxc){
			int m=min(chooseC(i, sa, 0), chooseC(i, sb, 1));
			cnt[i]=m;
			res+=string(m, (char)i);
			procSkip(0, sa, m, i);
			procSkip(1, sb, m, i);
		}
		if (res.length()<suffixLength)return res;
		return res.substr(res.length()-suffixLength);
		
		
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = {"baab"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"aaabb"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; string Arg3 = "bbaa"; verify_case(0, Arg3, maxLex(Arg0, Arg1, Arg2)); }
	void test_case_0() { string Arr0[] = {"baab"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"aaabb"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; string Arg3 = "bbaa"; verify_case(0, Arg3, maxLex(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"a", "cb"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"bc", "a"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 100; string Arg3 = "cb"; verify_case(1, Arg3, maxLex(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"xzzzzzzzzzzzzzzzzzzx"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"xxxxzzzzzzzzzzz"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; string Arg3 = "zzzzzzzzxx"; verify_case(2, Arg3, maxLex(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"ichhbca", "aghafbbgbaehi"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"jdhccgeiaaijbddh"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; string Arg3 = "iihhge"; verify_case(3, Arg3, maxLex(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CommonSubsequence ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
