// BEGIN CUT HERE

// END CUT HERE
#line 5 "OlympicGames.cpp"

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



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

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


struct team{
	int a, b, c, id;
	bool operator<(const team &t)const{return a!=t.a?a<t.a:(b!=t.b?b<t.b:(c!=t.c?c<t.c:id>t.id));}
};
team to;
deque<team> tb;
set<team> st;


class OlympicGames {
	public:
	int worstPlace(vector <string> medals, int left) {
		int n=medals.size();
		int i, j, k;
		tb=deque<team>(n);


		REP(i, n){
			istringstream ss(medals[i]);
			ss>>tb[i].a>>tb[i].b>>tb[i].c;
			tb[i].id=i;
		}
		to=tb[0]; tb.pop_front(); --n;
		to.a+=left;
		
		
		st.clear();
		st.insert(ALL(tb));

		int H, L, M;
		H=n+1;
		L=0;
		while(H>L+1){
			M=(L+H)/2;
			int c=0;
			vector<team> lst;
			FEV(it, st){
				lst.pb(*it);
				if (++c==M)break;
			}
			bool ok=false;
			vi nb(M, 0), nc(M, 0);
			int sb=left, sc=left;
			vector<pii> rem;
			REP(i, M){
				if (lst[i].a<to.a)goto fail;
				if (lst[i].a>to.a)continue;
				sb-=nb[i]=max(0, to.b-lst[i].b);
				if (nb[i]>left)goto fail;
			}
			if (sb<0)goto fail;
			REP(i, M) if (to.a==lst[i].a && to.b>=lst[i].b && to.c>=lst[i].c)rem.pb(MP(to.c-lst[i].c+1, i));

			sort(ALL(rem));
			FE(it, rem){
				assert(it->ST>=0);
				if (nb[it->ND]+it->ST<=left && sc>=it->ST) sc-=it->ST;
				else if (sb>0 && nb[it->ND]+1<=left)--sb;
				else goto fail;
			}
			
			ok=true;
fail:

			if (ok==true) L=M;
			else H=M;


		}
		return L+1;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0 0 0",
		"1 0 0",
		"1 0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; verify_case(0, Arg2, worstPlace(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0 0 0",
		"1 0 0",
		"1 0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 1; verify_case(1, Arg2, worstPlace(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"1 2 3",
		"100 0 0",
		"7 0 0",
		"7 0 0",
		"7 0 0",
		"7 0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 4; verify_case(2, Arg2, worstPlace(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"0 7 6",
		"6 0 0",
		"6 1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 1; verify_case(3, Arg2, worstPlace(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"0 5 5",
		"5 0 0",
		"5 0 10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 2; verify_case(4, Arg2, worstPlace(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"0 1 1",
		"3 0 0",
		"3 0 0",
		"3 0 1",
		"3 1 0",
		"3 1 1",
		"3 1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 5; verify_case(5, Arg2, worstPlace(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	OlympicGames ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
