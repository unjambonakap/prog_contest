// BEGIN CUT HERE

// END CUT HERE
#line 5 "RandomWalks.cpp"

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


const int maxp=two(16);
const int maxd=200000;
int store[maxp];

int vx[]={0, 0, -1, 1};
int vy[]={1, -1, 0, 0};
int ch[]={'U', 'D', 'L', 'R'};

class RandomWalks {
	public:
	string generateWalk(int seed) {
		memset(store, -1, sizeof(store));
		REP(i, maxp) store[i]=((i==0?seed:store[i-1])*25173+13849)%maxp;
		REP(i, maxp)store[i]>>=14;
		vi tb[4];
		REP(i, maxp) tb[store[i]].pb(i);
		set<pair<pii, pii> > seen;

		string s;
		int p=0;
		pii a, b, nb;
		a=MP(0, 0);
		while(s.length()<maxd){
			int d, pd, npd;
			pd=-1;

			REP(i, 4){
				vector<int>::iterator ita=lower_bound(ALL(tb[i]), p);
				if (ita==tb[i].end())ita=tb[i].begin();
				npd=*ita-p; if (npd<0)npd+=maxp;
				if (pd==-1 || pd>npd){
					b=MP(a.ST+vx[i], a.ND+vy[i]);
					pair<pii, pii> pp=MP(min(a, b), max(a, b));
					if (!seen.count(pp)) nb=b, pd=npd;
				}
			}
			assert(pd!=-1);
			seen.insert(MP(min(a, nb), max(a, nb)));
			p=(p+pd)%maxp;
			s+=ch[store[p]];
			p=(p+1)%maxp;
			a=nb;
			if (nb==MP(0, 0)){
				if (s.length()<=40)return s;
				return s.substr(0, 20)+"..."+s.substr(s.length()-20);
			}
			

		}
		return "";
		
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 14760; string Arg1 = "LDRU"; verify_case(0, Arg1, generateWalk(Arg0)); }
	void test_case_1() { int Arg0 = 21; string Arg1 = "DLUR"; verify_case(1, Arg1, generateWalk(Arg0)); }
	void test_case_2() { int Arg0 = 124; string Arg1 = "RULUURDLLURULDLDLLLD...RURRUUURULDLDDDDRRRR"; verify_case(2, Arg1, generateWalk(Arg0)); }
	void test_case_3() { int Arg0 = 3; string Arg1 = "DDRRURDDLURRDRRRRDDL...RDRULUURDLLLDDRDLLDD"; verify_case(3, Arg1, generateWalk(Arg0)); }
	void test_case_4() { int Arg0 = 2; string Arg1 = ""; verify_case(4, Arg1, generateWalk(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  RandomWalks ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
