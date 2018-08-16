// BEGIN CUT HERE

// END CUT HERE
#line 5 "MarbleTop.cpp"

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


int k;
struct cmpA{
	bool operator()(int a, int b){
		if (a%k!=b%k){
			if (a%k==0)return 1;
			else if (b%k==0)return 0;
			return a<b;

		}
		return a<b;
	}

};


class MarbleTop {
	public:
	int minCuts(int _k, vector <int> stock, vector <int> orders) {
		k=_k;
		int nk;
		int ns, no;
		ns=stock.size(), no=orders.size();
		map<int, int> stk;
		REP(i, ns) ++stk[stock[i]];

		vi nodr;
		nk=0;
		REP(i, no) if (orders[i]!=k) nodr.pb(orders[i]); else ++nk;

		orders=nodr;
		no=orders.size();
		sort(ALL(orders), greater<int>());

		nk-=stk[k];
		stk[k]=0;
		int c=0;
		map<int, int>::iterator ita;
		REP(i, no){
			ita=stk.lower_bound(orders[i]);
			while(ita!=stk.end() && (ita->ND==0 || ita->ST%k!=orders[i]%k)) ++ita;
			if (ita==stk.end()) return -1;
			int a=(ita->ST-orders[i])/k;
			
			c+=a;
			--ita->ND;
			stk[k]+=a;
		}
		map<int, int, cmpA> nstk;
		nstk.insert(ALL(stk));
		while(nk>0){
			ita=nstk.begin();
			while(ita!=nstk.end()){
				if (ita->ST>=k && ita->ND){
					if (ita->ST==k)nk-=ita->ND, ita->ND=0;
					else --nk, ++c, --ita->ND, ++nstk[ita->ST-k];
					break;
				}
				++ita;
			}
			if (ita==nstk.end())return -1;
		}
		return c;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	//{40, , }
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 40; int Arr1[] = {37, 12, 18}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {12, 18, 40}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(0, Arg3, minCuts(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 5; int Arr1[] = {5,3,11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {6,6,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(1, Arg3, minCuts(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arr1[] = {7,6,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3,1,1,1,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; verify_case(2, Arg3, minCuts(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MarbleTop ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
