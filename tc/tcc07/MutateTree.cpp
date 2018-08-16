// BEGIN CUT HERE

// END CUT HERE
#line 5 "MutateTree.cpp"

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

struct node{
	char v;
	node *p, *r, *l;
};
const int maxn=50;
node tb[maxn];

int parse(string s, int p, int &k){
	if (p<0)return -2;
	node *n=tb+p;
	n->v=s[p];
	if (n->v<='Z'){ k=p; return p-1; }

	int ret=parse(s, p-1, k);
	if (ret<0)return -2;
	tb[k].p=n;
	n->r=tb+k;


	ret=parse(s, ret, k);
	tb[k].p=n;
	n->l=tb+k;

	k=p;
	return ret;
}


int haveChild(node *b, node *a){
	if (b->v==a->v)return 1;
	if (b->v<='Z')return 0;
	return haveChild(b->l, a)||haveChild(b->r, a);
}

string postdisp(node *a){
	if (a->v<='Z')return string(1, a->v);
	return postdisp(a->l)+postdisp(a->r)+string(1, a->v);

}


class MutateTree {
	public:
	string newTree(string tree, int ra, int rb) {
		if (ra>rb)swap(ra, rb);
		int sa, sb;

		int k;
		if (parse(tree, tree.length()-1, k)!=-1)return "BADTREE";
		node *a, *b;
		a=tb+ra, b=tb+rb;
		if (haveChild(b, a))return "OVERLAP";

		node temp=*a;
		a->l=b->l, a->r=b->r, a->v=b->v;
		b->l=temp.l, b->r=temp.r, b->v=temp.v;
		return postdisp(&tb[tree.length()-1]);
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABxCRQgzq"; int Arg1 = 3; int Arg2 = 2; string Arg3 = "CABxRQgzq"; verify_case(0, Arg3, newTree(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "rAB"; int Arg1 = 1; int Arg2 = 2; string Arg3 = "BADTREE"; verify_case(1, Arg3, newTree(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "ABxCRQgzq"; int Arg1 = 3; int Arg2 = 7; string Arg3 = "OVERLAP"; verify_case(2, Arg3, newTree(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "CEGHfdbIa"; int Arg1 = 3; int Arg2 = 2; string Arg3 = "CEHGfdbIa"; verify_case(3, Arg3, newTree(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "X"; int Arg1 = 0; int Arg2 = 0; string Arg3 = "OVERLAP"; verify_case(4, Arg3, newTree(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "IPDqWmSbEa"; int Arg1 = 9; int Arg2 = 1; string Arg3 = "BADTREE"; verify_case(5, Arg3, newTree(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MutateTree ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
