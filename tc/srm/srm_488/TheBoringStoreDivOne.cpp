// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBoringStoreDivOne.cpp"

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

const int maxn=47;
int n, m;
string a, b;


class TheBoringStoreDivOne {
	public:
	string find(string _a, string _b) {
		a=_a, b=_b;
		int n=a.length(), m=b.length();
		map<string, string> ta, tb;
		map<string, string>::iterator itm;

		REP(i, n) REP(j, i+1){
			string s=a.substr(j, i-j+1);
			REP(k, j-s.length()+1) if (a.substr(k, s.length())==s) REP(t, j-k-s.length()+1){
			   	string tmp=a.substr(k+s.length(), t);
				itm=ta.find(tmp);
				if (itm==ta.end())ta.insert(MP(tmp, s));
				else if (itm->ND.length()<s.length() || (itm->ND.length()==s.length() && s<itm->ND)) itm->ND=s;
			}
			FOR(k, i+1, n-s.length()) if (a.substr(k, s.length())==s) REP(t, n-s.length()-k+1){
			   	string tmp=a.substr(k+s.length(), t);
				itm=ta.find(tmp);
				if (itm==ta.end())ta.insert(MP(tmp, s));
				else if (itm->ND.length()<s.length() || (itm->ND.length()==s.length() && s<itm->ND)) itm->ND=s;
			}
		}

		reverse(ALL(b));
		REP(i, m) REP(j, i+1){
			string s=b.substr(j, i-j+1);
			string ts=s;
			reverse(ALL(ts));
			REP(k, j-s.length()+1) if (b.substr(k, s.length())==s) REP(t, j-k-s.length()+1){
				string tmp=b.substr(k+s.length(), t);
				reverse(ALL(tmp));
				itm=tb.find(tmp);
				if (itm==tb.end())tb.insert(MP(tmp, ts));
				else if (itm->ND.length()<s.length() || (itm->ND.length()==s.length() && ts<itm->ND)) itm->ND=ts;
			}
			FOR(k, i+1, m-s.length()) if (b.substr(k, s.length())==s) REP(t, m-s.length()-k+1){
				string tmp=b.substr(k+s.length(), t);
				reverse(ALL(tmp));
				itm=tb.find(tmp);
				if (itm==tb.end())tb.insert(MP(tmp, ts));
				else if (itm->ND.length()<s.length() || (itm->ND.length()==s.length() && ts<itm->ND)) itm->ND=ts;
			}
		}

		string best="";
		FE(it, ta) if (tb.count(it->ST)){
			string s=it->ND+it->ST+tb[it->ST];
			if (best.length()<s.length() || (s.length()==best.length() && s<best)) best=s;
		}

		return best;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arg0 = "StoreOfJohn"; string Arg1 = "StoreOfBrus"; string Arg2 = "or"; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_0() { string Arg0 = "aaaaabaaaaaa"; string Arg1 = "aaaaabaaaabaa"; string Arg2 = "aaaaaaaaaab"; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "JohnAndJohn"; string Arg1 = "John"; string Arg2 = ""; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "JohnLikesToPlayGames"; string Arg1 = "BrusAlsoLikesToPlayGames"; string Arg2 = "esToPlayGames"; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "abacaba"; string Arg1 = "abacabadabacaba"; string Arg2 = "abaabacaba"; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  TheBoringStoreDivOne ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
