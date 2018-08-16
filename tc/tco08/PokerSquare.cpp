// BEGIN CUT HERE

// END CUT HERE
#line 5 "PokerSquare.cpp"

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


int col[]={'S', 'H', 'D', 'C'};
int val[]={'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
int mp[6][5][2];



void setCard(char a, char b, int i, int j){
	int k;
	for (k=0; k<sizeof(val)/sizeof(int); ++k)
		if (val[k]==a)
			mp[i][j][0]=k;
	for (k=0; k<4; ++k)
		if (col[k]==b)
			mp[i][j][1]=k;
}

int getVal(){
	int s=0;
	int i, j, k;
	for (i=0; i<5; ++i){
		map<int, int> csa, vsa;
		int ns=0;
		for (j=0; j<5; ++j){
			int c, v;
			c=mp[i][j][1], v=mp[i][j][0];
			if (csa.find(c)==csa.end())csa.insert(MP(c, 0));
			if (vsa.find(c)==vsa.end())vsa.insert(MP(v, 0));
			++csa[c];
			++vsa[v];
		}
		int pair=0, th=0, fo=0;
		int prev=-1;

		int st=1;
		FE(it, vsa){
			if (prev!=-1 && st)
				st=(it->ST==prev+1);

			if (it->ND==2)
				++pair;
			else if (it->ND==3)
				th=1;
			else if (it->ND==4)
				fo=1;
			prev=it->ST;
		}
		st&=(vsa.size()==5);
		int flush;
		flush=(csa.size()==1);

		if (pair==1)ns=2;
		if (pair==2)ns=5;
		if (th)ns=10;
		if (st)ns=15;
		if (flush)ns=20;
		if (th&&pair)ns=25;
		if (fo)ns=50;
		if (st&&flush)ns=75;
		if (st&&flush&&vsa.begin()->ST==8)ns=100;
		s+=ns;
	}
	for (i=0; i<5; ++i){
		map<int, int> csa, vsa;
		int ns=0;
		for (j=0; j<5; ++j){
			int c, v;
			c=mp[j][i][1], v=mp[j][i][0];
			if (csa.find(c)==csa.end())csa.insert(MP(c, 0));
			if (vsa.find(c)==vsa.end())vsa.insert(MP(v, 0));
			++csa[c];
			++vsa[v];
		}
		int pair=0, th=0, fo=0;
		int prev=-1;

		int st=1;
		FE(it, vsa){
			if (prev!=-1 && st)
				st=(it->ST==prev+1);

			if (it->ND==2)
				++pair;
			else if (it->ND==3)
				th=1;
			else if (it->ND==4)
				fo=1;
			prev=it->ST;
		}
		st&=(vsa.size()==5);
		int flush;
		flush=(csa.size()==1);

		if (pair==1)ns=2;
		if (pair==2)ns=5;
		if (th)ns=10;
		if (st)ns=15;
		if (flush)ns=20;
		if (th&&pair)ns=25;
		if (fo)ns=50;
		if (st&&flush)ns=75;
		if (st&&flush&&vsa.begin()->ST==8)ns=100;
		s+=ns;
	}

	return s;

}


class PokerSquare {
	public:
		int bestScore(vector <string> board, vector <string> remaining) {
			vector<int> emptyPlace;
			vector<pii> rem;
			int i, j, k;

			REP(i, SZ(remaining)){
				setCard(remaining[i][0], remaining[i][1], 5, 0);
				rem.pb(MP(mp[5][0][0], mp[5][0][1]));
			}


			REP(i, 5)
				REP(j, 5){
					if (board[i][3*j]=='-')
						emptyPlace.pb(i+5*j), mp[i][j][0]=mp[i][j][1]=-1;
					else
						setCard(board[i][3*j], board[i][3*j+1], i, j);
				}

			int s=0;
			sort(ALL(rem));
			for (i=0; i<SZ(rem); ++i)
				mp[emptyPlace[i]%5][emptyPlace[i]/5][0]=rem[i].ST, mp[emptyPlace[i]%5][emptyPlace[i]/5][1]=rem[i].ND;
			s=max(s, getVal());
			while(next_permutation(ALL(rem))){
				for (i=0; i<SZ(rem); ++i)
					mp[emptyPlace[i]%5][emptyPlace[i]/5][0]=rem[i].ST, mp[emptyPlace[i]%5][emptyPlace[i]/5][1]=rem[i].ND;
				s=max(s, getVal());

			}


			return s;

		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		//{{"2D KS 4C -- 8S", "-- -- AD 9H JD", "7S AC JC 6H 6C", "8D JH 3H TH 4S", "7D QH 2C TC --"}, }

		void test_case_0() { string Arr0[] = {"TD -- 4S -- 6S", "TC KH 9S 3S 2C", "AS 5H 6D 8H KD", "4C 5C 8D 3H 6C", "7S TH -- JH 5D"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"8C", "9D", "4H"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, bestScore(Arg0, Arg1)); }
		//void test_case_0() { string Arr0[] = {"-- 2H 4D 6H 8C", 
		//	"2S 4H 6D 8D TS", 
		//	"4S 6C 8S TC 3H", 
		//	"6S 8H TD 3S 5C", 
		//	"-- TH 5D 4C 2D"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"QS", "KD"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, bestScore(Arg0, Arg1)); }
		void test_case_1() { string Arr0[] = {"-- 2H 4D 6H 8C", 
			"2S 4H 6D 8D TS", 
			"4S 6C 8S TC 3H", 
			"6S 8H TD 3S 5C", 
			"-- TH 5D 4C 2D"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"QS", "QD"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(1, Arg2, bestScore(Arg0, Arg1)); }
		void test_case_2() { string Arr0[] = {"-- 2H 4D 6H 8C", 
			"2S 4H 6D 8D TS", 
			"4S 6C 8S TC 3H", 
			"6S 8H TD 3S 5C", 
			"-- TH 5D 4C --"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"QS", "KS", "QD"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 22; verify_case(2, Arg2, bestScore(Arg0, Arg1)); }
		void test_case_3() { string Arr0[] = {"-- AH AD -- 2C", 
			"KS KH KD -- 3C", 
			"QS -- -- QC 4C", 
			"JS JH JD -- 5C", 
			"-- TH TD TC --"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AC", "QD", "KC", "QH", "TS", "AS", "6C", "JC"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 725; verify_case(3, Arg2, bestScore(Arg0, Arg1)); }
		void test_case_4() { string Arr0[] = {"6C 9S 4H QC --",
			"2S 3C AS AH JH",
			"-- 5C 2C KC --",
			"QH QD TC 8S KS",
			"JD 8D 7S 9H --"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"TH","TS","5H","5D"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 31; verify_case(4, Arg2, bestScore(Arg0, Arg1)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	PokerSquare ___test; 
	___test.run_test(0); 
} 
// END CUT HERE
