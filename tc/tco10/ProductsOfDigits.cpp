// BEGIN CUT HERE

// END CUT HERE
#line 5 "ProductsOfDigits.cpp"

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

int lst[]={9, 8, 7, 6, 5, 4, 3, 2};

ll build(int a){
	if (a==0)return 10;
	if (a==1)return 1;
	int tb[10];
	memset(tb, 0, sizeof(tb));
	REP(i, sizeof(lst)/sizeof(int)){
		while(a%lst[i]==0){
			++tb[i];
			a/=lst[i];
		}
	}
	ll res=0;
	REPV(i, sizeof(lst)/sizeof(int)){
		REP(j, tb[i]) res=lst[i]+res*10;
	}
	return res;
}

int getp(ll a){
	ll p=1;
	while(a!=0) p*=a%10, a/=10;
	return p;
}
int getpa(ll a){
	ll p=1;
	if (a<100) return 0;
	while(a!=0) p*=a%10, a/=10;
	return p;
}
class ProductsOfDigits {
	public:
	long long firstOccurrence(vector <int> prod) {
		int n=prod.size();
		ll res=LLONG_MAX;

		REP(i, 1100) if (i){
			bool fd=true;
			REP(j, n) if (prod[j]!=getp(i+j)){fd=false; break;}
			if (fd) return i;
		}

		REP(i, 1000){
			bool fd=true;
			int id=-1;
			REP(j, n) if (prod[j]!=0) {id=j; break;}
			assert(id!=-1);
			if (getp(id+i)==0)continue;
			int left=prod[id]/getp(id+i);
			REP(j, n){
				int tmp=getpa(i+j);
				if (tmp==0 && prod[j]!=0){fd=false; break;}
				if (prod[j]==0 && tmp!=0){fd=false; break;}
				if (tmp!=0 && (prod[j]%tmp||prod[j]/tmp!=left)){fd=false; break;}
			}
			if (!fd)continue;
			checkmin(res, i+build(left)*1000);
		}
		return res;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 244140625}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(0, Arg1, firstOccurrence(Arg0)); }
	//void test_case_0() { int Arr0[] = {1, 2, 3, 4, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(0, Arg1, firstOccurrence(Arg0)); }
	void test_case_1() { int Arr0[] = {9, 0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 9LL; verify_case(1, Arg1, firstOccurrence(Arg0)); }
	void test_case_2() { int Arr0[] = {0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 100LL; verify_case(2, Arg1, firstOccurrence(Arg0)); }
	void test_case_3() { int Arr0[] = {288}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 489LL; verify_case(3, Arg1, firstOccurrence(Arg0)); }
	void test_case_4() { int Arr0[] = {108864, 127008, 145152, 163296, 0, 22680, 45360, 68040, 90720}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 789946LL; verify_case(4, Arg1, firstOccurrence(Arg0)); }
	void test_case_5() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(5, Arg1, firstOccurrence(Arg0)); }
	void test_case_6() { int Arr0[] = {0, 1, 2, 3, 4, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 10LL; verify_case(6, Arg1, firstOccurrence(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	ProductsOfDigits ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
