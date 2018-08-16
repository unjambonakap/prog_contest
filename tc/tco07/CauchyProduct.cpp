// BEGIN CUT HERE

// END CUT HERE
#line 5 "CauchyProduct.cpp"

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

int _gcd(int a, int b){ return (b==0?a:_gcd(b, a-(a/b)*b));}
int gcd(int a, int b){ return _gcd(max(a, b), min(a, b)); }
int lcm(int a, int b){assert(a || b);return a*b/gcd(a, b);}

string build(pii a){
	string s;
	if (a.ST<0 || a.ND<0) s="-";
	int d=gcd(fabs(a.ST), fabs(a.ND));
	s+=toStr(fabs(a.ST)/d)+"/"+toStr(fabs(a.ND)/d);
	return s;
}

pii sub(pii a, pii b){
	pii r;
	r.ND=lcm(a.ND, b.ND);
	assert(a.ND && b.ND);
	r.ST=a.ST*(r.ND/a.ND)-b.ST*(r.ND/b.ND);
	int d=gcd(fabs(r.ST), fabs(r.ND));
	assert(d!=0);
	r.ST/=d;
	r.ND/=d;
	return r;
}
pii mul(pii a, pii b){
	pii r(a.ST*b.ST, a.ND*b.ND);
	int d=gcd(fabs(r.ST), fabs(r.ND));
	assert(d!=0);
	r.ST/=d;
	r.ND/=d;
	if (r.ND<0) r.ST=-r.ST, r.ND=-r.ND;
	return r;

}


class CauchyProduct {
	public:
	vector <string> findInverse(vector <int> start, vector <int> repeat, int n) {
		vi lst=start;
		REP(i, n-start.size()+1) lst.pb(repeat[i%repeat.size()]);

		pii plist[n];
		plist[0]=MP(1, start[0]);
		FOR(i, 1, n-1){
			plist[i]=MP(0, 1);
			REP(j, i) if (lst[i-j]!=0 && plist[j].ND) plist[i]=sub(plist[i], mul(plist[j], MP(lst[i-j], 1)));
			plist[i]=mul(plist[i], MP(1, lst[0]));
		}
		vs res;
		REP(i, n) res.pb(build(plist[i]));
		
		return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	//void test_case_0() { int Arr0[] = {1}	; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; string Arr3[] = {"1/1", "-1/1", "0/1", "0/1", "0/1" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, findInverse(Arg0, Arg1, Arg2)); }
	void test_case_0() { int Arr0[] = {-9, -1, -8, -12}	; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13, 12, -14}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; string Arr3[] = {"1/1", "-1/1", "0/1", "0/1", "0/1" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, findInverse(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; string Arr3[] = {"1/1", "-2/1", "2/1", "-2/1", "2/1" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, findInverse(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 20; string Arr3[] = {"1/1", "-2/1", "1/1", "0/1", "0/1", "3/1", "-9/1", "9/1", "0/1", "-9/1", "18/1", "-36/1", "45/1", "-9/1", "-63/1", "126/1", "-171/1", "180/1", "-36/1", "-333/1" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, findInverse(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1,2}	; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 35; string Arr3[] = {"1/1", "-2/1", "1/1", "0/1", "0/1", "3/1", "-9/1", "9/1", "0/1", "-9/1", "18/1", "-36/1", "45/1", "-9/1", "-63/1", "126/1", "-171/1", "180/1", "-36/1", "-333/1", "747/1", "-927/1", "720/1", "99/1", "-1818/1", "3960/1", "-4923/1", "3123/1", "2097/1", "-10674/1", "20457/1", "-24552/1", "13464/1", "17379/1", "-62865/1" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, findInverse(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {2,3,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,6,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; string Arr3[] = {"1/2", "-3/4", "1/8", "1/16", "1/32" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(4, Arg3, findInverse(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {-19,14,-8,-2,-19,12,-4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-6,-6,2,14,-5,-18,17,-8,8,
 -16,-2,-12,11,16,-12,-17,5,
  1,11,11,0,10,-14,8,1,4,
 -8,1,-16,16,19,-4,18,4,
 -11,-15,9,4,-8,10,-5,-9,9,-9,16,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arr3[] = {"-1/19", "-14/361", "-44/6859" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(5, Arg3, findInverse(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CauchyProduct ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
