// BEGIN CUT HERE

// END CUT HERE
#line 5 "FourSubstrings.cpp"

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

const int maxn=2510, maxl=52, ns=4;
vs ts;
string s;
int n;

int subs[maxn][ns];
int dpa[maxn][maxl][two(ns)], dpb[maxn][maxl][two(ns)];

int proca(int p, int c, int m){
	if (p==n) return (m==two(ns)-1?0:-2);
	int &r=dpa[p][c][m];
	if (r!=-1) return r;

	r=INT_MAX;
	REP(i, two(ns)) if (!(i&m)){
		int nc=c, nr;
		REP(j, ns) if (i&two(j)){
			checkmax(nc, (int)ts[j].length());
		   	if (!subs[p][j]){nc=-1; break;}
		}
		if (nc==-1)continue;
		nr=proca(p+1, max(nc-1, 0), m|i);
		if (nr==-2)continue;
		checkmin(r, nr+nc-c);
	}
	return r=(r==INT_MAX?-2:r);
}
int procb(int p, int c, int m){
	if (p==n) return (m==two(ns)-1?0:-2);
	int &r=dpb[p][c][m];
	if (r!=-1) return r;

	r=INT_MIN;
	REP(i, two(ns)) if (!(i&m)){
		int nc=c, nr;
		REP(j, ns) if (i&two(j)){
			checkmax(nc, (int)ts[j].length());
		   	if (!subs[p][j]){nc=-1; break;}
		}
		if (nc==-1)continue;
		nr=procb(p+1, max(nc-1, 0), m|i);
		if (nr==-2)continue;
		checkmax(r, nr+nc-c);
	}
	return r=(r==INT_MIN?-2:r);
}


class FourSubstrings {
	public:
	vector <int> getCoverageCount(vector <string> text, string a, string b, string c, string d) {
		s="";
		FE(it, text) s+=*it;
		n=s.length();
		ts.clear(); ts.pb(a); ts.pb(b); ts.pb(c); ts.pb(d);


		memset(subs, 0, sizeof(subs));
		REP(i, 4) REP(j, n-ts[i].length()+1){
			subs[j][i]=1;
			REP(k, ts[i].length()) if (ts[i][k]!=s[j+k]){subs[j][i]=0; break;}
		}
		memset(dpa, -1, sizeof(dpa)); memset(dpb, -1, sizeof(dpb));
		vi res;
		res.pb(proca(0, 0, 0));
		res.pb(procb(0, 0, 0));
		return res;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"abacaba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ab"; string Arg2 = "ba"; string Arg3 = "a"; string Arg4 = "c"; int Arr5[] = {4, 6 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(0, Arg5, getCoverageCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { string Arr0[] = {"hello"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "he"; string Arg2 = "l"; string Arg3 = "l"; string Arg4 = "o"; int Arr5[] = {4, 5 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(1, Arg5, getCoverageCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { string Arr0[] = {"ababababa", "baba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ababababa"; string Arg2 = "ababababa"; string Arg3 = "ababababa"; string Arg4 = "ababababa"; int Arr5[] = {9, 13 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(2, Arg5, getCoverageCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { string Arr0[] = {"foursubstrings"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "our"; string Arg2 = "s"; string Arg3 = "ring"; string Arg4 = "sub"; int Arr5[] = {10, 11 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(3, Arg5, getCoverageCount(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  FourSubstrings ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
