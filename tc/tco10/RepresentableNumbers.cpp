// BEGIN CUT HERE

// END CUT HERE
#line 5 "RepresentableNumbers.cpp"

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


const int maxd=17;
int d[maxd];

int checkit(int n){
	FOR(a, n-1, n) FOR(b, 1, a){
		int ten=1;
		int c=0;
		//printf("trying %d %d %d over %d\n", d[3], a, b, n);
		REP(i, n){
			//printf("on step %d %d => %d\n", i, c, d[i]);
			if (i<a && i<b){
				if (c%2!=d[i]%2) goto fail;
				c=0;
				if (d[i]==0 || d[i]==1) c=1;
				else if (i<n-1 && d[i+1]&1) c=1;
			}else if (i<a){
				//printf("hre %d %d => %d\n", i+1, a, d[i+1]);
				if (c%2==d[i]%2) goto fail;
				if (i<n-1){
					if (d[i]==0) c=1;
					else if (i+1<a && d[i+1]%2==0 && c==1) c=1;
					else if (i+1==a) c=d[i+1]%2;
					else c=0;

					if (d[i]!=0) c=0;

				}
			}else{
				if (c!=d[i]) goto fail;
			}

		}
		return 1;
fail:;

	}
	return 0;

}
class RepresentableNumbers {
	public:
	int getNext(int X) {
		int tmp, n;
		if (X&1) ++X;
		while(1){
			tmp=X; n=0;
			while(tmp!=0) d[n++]=tmp%10, tmp/=10;
			if (checkit(n))return X;
			X+=2;

		}

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; verify_case(0, Arg1, getNext(Arg0)); }
	void test_case_1() { int Arg0 = 999; int Arg1 = 1000; verify_case(1, Arg1, getNext(Arg0)); }
	void test_case_2() { int Arg0 = 2000; int Arg1 = 2000; verify_case(2, Arg1, getNext(Arg0)); }
	void test_case_3() { int Arg0 = 4201234; int Arg1 = 4222222; verify_case(3, Arg1, getNext(Arg0)); }
	void test_case_4() { int Arg0 = 10101010; int Arg1 = 10102222; verify_case(4, Arg1, getNext(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  RepresentableNumbers ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
