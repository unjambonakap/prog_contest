// BEGIN CUT HERE

// END CUT HERE
#line 5 "FlashFlood.cpp"

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

int h, r;
vi ht;
int n, m;
const int sep=50;


double flood(int a, int b){
	if (a==b-1)return 0.;
	double v=0;
	int h=min(ht[a], ht[b]);
	FOR(i, a, b-1){
		int va, vb;
		
		va=max(ht[i], ht[i+1]);
		vb=min(ht[i], ht[i+1]);
		v+=double(min(h, va)-vb)/(va-vb)*double(min(h, va)-vb)/2.+max(0, h-va);
	}
	return v*12;

}

struct cmpA{ bool operator()(const pair<double, pii> &a, const pair<double, pii> &b)const{ return a.ST/a.ND.ST/r<b.ST/b.ND.ST/r; } };

class FlashFlood {
	public:
	double hours(int _r, vector <int> _ht) {
		r=_r, ht=_ht;
		n=ht.size();
		reverse(ALL(ht));
		int mid=-1;
		REP(i, n) if (mid==-1 || ht[mid]<ht[i]) mid=i;

		vi step; step.pb(0);
		FOR(i, 1, mid) if (ht[i]>ht[step.back()]) step.pb(i);
		m=step.size();
		deque<pair<double, pii> > fld;
		REP(i, m-1) fld.pb(MP(flood(step[i], step[i+1]), MP(step[i+1]-step[i], i)));
		double t=0.;
		while(1){
			sort(ALL(fld), cmpA());

			double dt=fld[0].ST/fld[0].ND.ST/r;
			t+=dt;
			if (fld[0].ND.ND==0)return t;
			int nid=-1, add=fld[0].ND.ST;
			FOR(i, 1, fld.size()-1) if (fld[i].ND.ND<fld[0].ND.ND) nid=max(nid, fld[i].ND.ND);

			assert(nid!=-1);
			fld.pop_front();
			FE(it, fld){
			   	it->ST-=dt*it->ND.ST*r;
				if (it->ND.ND==nid) it->ND.ST+=add;
			}
		}
		return -1;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 7; int Arr1[] = {150,140}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(0, Arg2, hours(Arg0, Arg1)); }
	//{12, }
	void test_case_0() { int Arg0 = 12; int Arr1[] = {110, 170, 175, 155, 160, 161, 140, 150}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.4561904761904767; verify_case(0, Arg2, hours(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 7; int Arr1[] = {160,140,150}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 6.428571428571427; verify_case(1, Arg2, hours(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 12; int Arr1[] = {110,170,175,155,160,140,150}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.6562500000000018; verify_case(2, Arg2, hours(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	FlashFlood ___test; 
	___test.run_test(0);
} 
// END CUT HERE
