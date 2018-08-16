// BEGIN CUT HERE

// END CUT HERE
#line 5 "YetAnotherStonesGame.cpp"

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


int parent[6];
void init_merge(int nm){ memset(parent, -1, sizeof(int)*nm); }
int getParent(int a){return (parent[a]==-1)?a:(parent[a]=getParent(parent[a]));}
int merge(int a, int b){parent[getParent(a)]=getParent(b);}


class YetAnotherStonesGame {
	public:
	int fewestStones(vector <int> moves, string mark) {
		int n=mark.length();
		int nm=*max_element(ALL(moves));
		int i, j, k;
		for (i=0; i<nm; ++i)
			mark+=mark[i];

		int cost=100;

		for (i=1; i<two(nm); ++i){
			bool ok=true;
			int id=0;
			vi istate;
		   	set<vi> sl[60];
			for (j=0; j<nm && ok; ++j){
				if (mark[j]=='X' && bit_set(i, j))ok=false;
				istate.pb(bit_set(i, j)?id++:-1);
			}
			if (!ok)continue;

			sl[0].insert(istate);
			for (j=0; j<n; ++j){
				FE(it, sl[j]){
					vi q=*it;

					q.pb(-1);
					int cur=q[0];
					assert(cur<6);
					q.erase(q.begin());
					if (cur==-1){
						if (mark[j]=='X')
							sl[j+1].insert(q);
						continue;
					}
					FE(ita, moves){
						if (mark[j+*ita]=='X' || q[*ita-1]!=-1)continue;
						q[*ita-1]=cur;
						sl[j+1].insert(q);
						q[*ita-1]=-1;
					}
				}
			}
			FE(it, sl[n]){
				bool ok=true;
				vi q=*it;
				init_merge(nm);
				int r=count_bit(i);
				for (j=0; j<nm && ok; ++j){
					if ((istate[j]==-1)!=(q[j]==-1))ok=false;
					else if (istate[j]!=-1){
						assert(q[j]!=-1 && q[j]<6);
						if (getParent(istate[j])!=getParent(q[j]))
							--r, merge(istate[j], q[j]);
						assert(r>0);

					}
				}
				if (ok)
					cost=min(cost, r);
			}

		}
		return cost==100?-1:cost;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "............"; int Arg2 = 4; verify_case(0, Arg2, fewestStones(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "............."; int Arg2 = 1; verify_case(1, Arg2, fewestStones(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "..X..XX.X...XX"; int Arg2 = -1; verify_case(2, Arg2, fewestStones(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {5,3,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "....X...X.X.X..........X..X.....XXX....X....XXX"; int Arg2 = 3; verify_case(3, Arg2, fewestStones(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  YetAnotherStonesGame ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
