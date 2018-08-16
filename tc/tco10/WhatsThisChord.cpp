// BEGIN CUT HERE

// END CUT HERE
#line 5 "WhatsThisChord.cpp"

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



class WhatsThisChord {
	public:
	string classify(vector <int> chord) {
		string s="C C# D D# E F F# G G# A A# B";
		string t;
		istringstream ss(s);
		map<string, int> mp;

		int n=0;
		while(ss>>t)mp.insert(MP(t, n++));
		s="E A D G B E";
		vi lst;
		istringstream nss(s);
		while(nss>>t) lst.pb(mp[t]);

		int major[3]={mp["C"], mp["E"], mp["G"]};
		int minor[3]={mp["C"], mp["D#"], mp["G"]};
		set<int> ch;
		REP(j, 6) if (chord[j]!=-1) ch.insert((12+lst[j]+chord[j])%12);
		if (ch.size()!=3)return "";
		REP(i, 12){
			bool fd;
			fd=true;
			REP(j, 3) if (!ch.count((major[j]+i)%12)){fd=false; break;}

			if (fd){
			   	FE(it, mp) if (it->ND==(major[0]+i)%12) return it->ST+" Major";
				assert(0);
			}

			fd=true;
			REP(j, 3) if (!ch.count((minor[j]+i)%12)){fd=false; break;}

			if (fd){
				FE(ita, ch) FE(it, mp) if (it->ND==(minor[*ita]+i)%12) cout<<it->ST<<endl;
			   	FE(it, mp) if (it->ND==(minor[0]+i)%12) return it->ST+" Minor";
				assert(0);
			}
			
			
		}
		return "";

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-1, 3, 2, 0, 1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "C Major"; verify_case(0, Arg1, classify(Arg0)); }
	void test_case_1() { int Arr0[] = {3,2,0,0,0,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "G Major"; verify_case(1, Arg1, classify(Arg0)); }
	void test_case_2() { int Arr0[] = {-1,0,2,2,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "A Minor"; verify_case(2, Arg1, classify(Arg0)); }
	void test_case_3() { int Arr0[] = {-1,4,3,1,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "C# Major"; verify_case(3, Arg1, classify(Arg0)); }
	void test_case_4() { int Arr0[] = {8,10,10,9,8,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "C Major"; verify_case(4, Arg1, classify(Arg0)); }
	void test_case_5() { int Arr0[] = {0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(5, Arg1, classify(Arg0)); }
	void test_case_6() { int Arr0[] = {-1,-1,4,-1,-1,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(6, Arg1, classify(Arg0)); }
	void test_case_7() { int Arr0[] = {-1, -1, 2, 0, 1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "C Major"; verify_case(7, Arg1, classify(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	WhatsThisChord ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
