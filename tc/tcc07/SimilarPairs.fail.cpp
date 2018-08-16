// BEGIN CUT HERE

// END CUT HERE
#line 5 "SimilarPairs.cpp"

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


struct state{
	vi pi;
	vector<pair<string, int> > to;
};

map<string, state> mp, nmp;
int n;

class SimilarPairs {
	public:
	int howManyElements(vector <string> text, int k) {
		string s;
		FE(it, text) s+=*it;
		n=s.length();
		CLR(mp);
		REP(i, n) mp.insert(MP(string(1, s[i]), state())), mp[string(1, s[i])].pi.pb(i);

		FE(it, mp) FE(ita, mp) if (k>0 || it==ita) it->ND.to.pb(MP(ita->ST, it!=ita));
		

		int c=0;
		FE(it, mp) FE(ita, it->ND.to){
			if (fabs(it->ND.pi.front()-mp[ita->ST].pi.back())>=1){++c; break;}
			else if (fabs(mp[ita->ST].pi.front()-it->ND.pi.back())>=1){++c; break;}
		}
		map<string, state>::iterator itz;
		FOR(i, 1, s.length()/2-1){
			nmp=mp; mp.clear();

			FE(it, nmp){
				set<pair<string, int> > npf, tnpf[26];
				FE(ita, it->ND.to) FE(itb, nmp[ita->ST].pi) if (*itb+i<n){
					if (ita->ND<=k-1) npf.insert(MP(ita->ST+s[*itb+i], ita->ND));
					else tnpf[s[*itb+i]-'a'].insert(MP(ita->ST+s[*itb+i], k));
				}
				FE(ita, it->ND.pi) if (*ita+i<n){
					string ns=it->ST+s[*ita+i];
					if ((itz=mp.find(ns))==mp.end()){
					   	itz=mp.insert(MP(ns, state())).ST;
						FE(itb, tnpf[ns[i]-'a']) itz->ND.to.pb(*itb);
						FE(itb, npf) itz->ND.to.pb(MP(itb->ST, itb->ND+(ns[i]!=itb->ST[i])));
					}
					itz->ND.pi.pb(*ita);
				}
			}
			FE(it, mp) FE(ita, it->ND.to){

				map<string, state>::iterator itz=mp.find(ita->ST);
				if (fabs(it->ND.pi.front()-itz->ND.pi.back())>=i+1){++c; break;}
				else if (fabs(itz->ND.pi.front()-it->ND.pi.back())>=i+1){++c; break;}
			}



		}


		return c;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = {"abacd"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 6; verify_case(0, Arg2, howManyElements(Arg0, Arg1)); }
	void test_case_0() { string Arr0[] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaa", "a", "aaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaa", "aaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaa", "aabaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aa", "aaaa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 6; verify_case(0, Arg2, howManyElements(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"aaaa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; verify_case(1, Arg2, howManyElements(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"abcdefgh"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 15; verify_case(2, Arg2, howManyElements(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"a", "ab", "abc"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 3; verify_case(3, Arg2, howManyElements(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"abacd"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; verify_case(4, Arg2, howManyElements(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	SimilarPairs ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
