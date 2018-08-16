// BEGIN CUT HERE

// END CUT HERE
#line 5 "SongsList.cpp"

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

int iperm[]={0, 1, 2};

struct song{
	string s[3];
	vi perm;
	song(){ perm=vi(iperm, iperm+3); }
	bool operator<(const song &e)const{
		REP(i, 3) if (s[perm[i]]!=e.s[e.perm[i]])return (s[perm[i]]<e.s[e.perm[i]]);
		assert(0);
		return 0;
	}

};

class SongsList {
	public:
	vector <int> getPositions(vector <string> songs) {
		int n=songs.size();
		vector<song> tb(n);
		REP(i, n){
			string a, b, c;
			istringstream ss (songs[i]);
		   	ss>>tb[i].s[0]; ss>>tb[i].s[1]; ss>>tb[i].s[2];
		}

		set<int> pos;
		do{
			set<int> npos;
			npos.insert(0);
			FOR(i, 1, n-1){
				tb[i].perm=vi(iperm, iperm+3);
				int ns=0;
				do{
					if (tb[0]<tb[i])ns|=1;
					else ns|=2;
				}while(next_permutation(ALL(tb[i].perm)));
				set<int> tpos;
				FE(it, npos){
					if (ns&1)tpos.insert(*it);
					if (ns&2)tpos.insert(*it+1);
				}
				npos=tpos;
			}
			pos.insert(ALL(npos));
		}while(next_permutation(ALL(tb[0].perm)));
		return vi(ALL(pos));
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = { "beatles help yesterday",
  "queen innuendo showmustgoon",
  "eagles hotelcalifornia hotelcalifornia" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getPositions(Arg0)); }
	void test_case_1() { string Arr0[] = { "a a a",
  "b b b",
  "c c c" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getPositions(Arg0)); }
	void test_case_2() { string Arr0[] = { "b e h",
  "i i i",
  "g g g",
  "f f f",
  "d d d",
  "c c c",
  "a a a" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getPositions(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SongsList ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
