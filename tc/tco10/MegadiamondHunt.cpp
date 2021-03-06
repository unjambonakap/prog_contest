// BEGIN CUT HERE

// END CUT HERE
#line 5 "MegadiamondHunt.cpp"

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


const int maxn=57;
int mp[maxn];
int n;

int end_d(int p){
	int a, b;
	if (p==n-1)return -1;
	a=b=0;
	while(p<n && mp[p]==1) ++a, ++p;
	while(p<n && mp[p]==0 && b!=a) ++b, ++p;
	

	if (a==0 || a!=b)return -1;
	return p;


}
class MegadiamondHunt {
	public:
	int getValue(string mine) {
		n=mine.size();
		REP(i, n) mp[i]=(mine[i]=='<'?1:0);

		int res=0;
		while(1){
			int i=0;
			int a, b;
			a=-1;
			while(i<n){
				int nd=end_d(i);

				if (nd!=-1){
				   	if (a==-1 || b>nd-i) b=nd-i, a=i;
				   	i=nd;
				}else ++i;
			}
			if (a==-1)break;
			res+=b*b/4;
			FOR(i, a, n-b-1) mp[i]=mp[i+b];
			n-=b;

		}
		return res;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "><<><>>><"; int Arg1 = 5; verify_case(0, Arg1, getValue(Arg0)); }
	void test_case_1() { string Arg0 = "<<><<>><<>>>"; int Arg1 = 14; verify_case(1, Arg1, getValue(Arg0)); }
	void test_case_2() { string Arg0 = ">>>>>><<<<<<<"; int Arg1 = 0; verify_case(2, Arg1, getValue(Arg0)); }
	void test_case_3() { string Arg0 = "<<<<<<><><><<<<>>><><><<>><<<><<>><<<>>><<<<<>>>>>"; int Arg1 = 57; verify_case(3, Arg1, getValue(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MegadiamondHunt ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
