// BEGIN CUT HERE

// END CUT HERE
#line 5 "BasketballStandings.cpp"

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
string toStr(double a){ostringstream os; os<<a; return os.str();}

struct state;

double gap(state a, state b);

struct state{
	int a, b;
	string s;
	state(){}
	state(string tmp){ istringstream ss(tmp);
		ss>>s;ss>>a>>b; b+=a;}
	bool operator<(const state &s)const{ double tmp=gap(*this, s); return (tmp>0?1:(tmp==0?this->s<s.s:0));}
};
double gap(state a, state b){
	int sgn=1;
	if (a.b<b.b)swap(a, b), sgn*=-1;
	return (a.a-b.a-(a.b-b.b)*0.5)*sgn;
}


const int maxn=55;
int n;
state tb[maxn];

class BasketballStandings {
	public:
	vector <string> constructTable(vector <string> teams) {
		n=teams.size();
		int m=-1;
		REP(i, n) tb[i]=state(teams[i]);
		sort(tb, tb+n);
		vs res;
		REP(i, n){
			char buf[100];
			sprintf(buf, "%1.1lf", fabs(gap(tb[0], tb[i])));
			res.pb(tb[i].s+" "+string(buf));
		}
		return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"A 1 1", "A 8 8","D 0 0", "B 7 7", "C 99 99", "BAA 13 13"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A 0.0", "A 0.0", "B 0.0", "BAA 0.0", "C 0.0", "D 0.0" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, constructTable(Arg0)); }
	void test_case_1() { string Arr0[] = {"B 11 10", "A 10 10", "C 10 11", "D 20 5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"D 0.0", "B 7.0", "A 7.5", "C 8.0" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, constructTable(Arg0)); }
	void test_case_2() { string Arr0[] = {"MAVS 54 11", "SUNS 50 16", "SPURS 46 20", "JAZZ 43 23"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"MAVS 0.0", "SUNS 4.5", "SPURS 8.5", "JAZZ 11.5" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, constructTable(Arg0)); }
	void test_case_3() { string Arr0[] = {"TEAMA 17 15", "TEAMB 14 11", "TEAMC 3 0",
 "TEAMD 99 94", "LOSER 10 85", "WINNER 76 34"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"WINNER 0.0", "TEAMD 18.5", "TEAMB 19.5", "TEAMC 19.5", "TEAMA 20.0", "LOSER 58.5" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, constructTable(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  BasketballStandings ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
