// BEGIN CUT HERE

// END CUT HERE
#line 5 "AlmostConvexPolygons.cpp"

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
inline int ctz(int n){return (n&1)?0:1+ctz(n>>1);}

const int maxn=16;
vector<pii> cx[two(maxn)];
int seen[maxn];
set<vector<pii> > used;

int crossProd(const pii &a, const pii &b, const pii &c){ return (b.ST-a.ST)*(c.ND-a.ND)-(b.ND-a.ND)*(c.ST-a.ST); }


vector<pii> convex(vector<pii> s){
	if (s.size()<3)return vector<pii>();
	vector<pii> hull, thull;
	int n=s.size();
	REP(i, n){
		while(hull.size()>=2 && crossProd(hull[hull.size()-2], hull.back(), s[i])>0)hull.pop_back();
		hull.pb(s[i]);
	}REPV(i, n){
		while(thull.size()>=2 && crossProd(thull[thull.size()-2], thull.back(), s[i])>0)thull.pop_back();
		thull.pb(s[i]);
	}
	thull.erase(thull.begin());
	thull.pop_back();

	hull.insert(hull.end(), ALL(thull));

	return hull;
}


class AlmostConvexPolygons {
	public:
	int count(vector <int> x, vector <int> y) {
		int n=x.size();
		vector<pii> pset;
		int res=0;
		REP(i, n) pset.pb(MP(x[i], y[i]));
		sort(ALL(pset));

		
		used.clear();
		REP(i, two(n)) if (count_bit(i)>=3){
			cx[i].clear();
			vector<pii> nset;
			REP(j, n) if (bit_set(i, j)) nset.pb(pset[j]);
			vector<pii> hull=convex(nset);
			if (hull.size()==nset.size()) cx[i]=hull, ++res;
			
		}

		REP(sa, n) REP(sb, sa){
			//if (sa!=4 || sb!=0)continue;
			vector<pii> poola, poolb;
			int ma, mb, mc;
			ma=mb=mc=(two(sa)|two(sb));

			REP(i, n) if (i!=sa && i!=sb){

				if (crossProd(pset[sa], pset[sb], pset[i])>0)poola.pb(pset[i]), ma|=two(i);
				else poolb.pb(pset[i]), mb|=two(i);
			}
			vector<int> ca, cb;
			REP(i, two(n)){
				if ((ma&i)==mc)cb.pb(i);
				else if ((mb&i)==mc)ca.pb(i);
			}
			REP(ea, ca.size()) REP(eb, cb.size()){
				int i, j;
				i=ca[ea], j=cb[eb];

				if (cx[i|j].size() || !cx[i].size() || !cx[j].size())continue;
				vector<pii> ha, hb, h;
				ha=cx[i], hb=cx[j];
				int ra, rb;
				int na, nb;
				na=ha.size(), nb=hb.size();
				ra=rb=-1;
				REP(k, na) if ((ha[k]==pset[sa] && ha[(k+1)%na]==pset[sb]) || (ha[k]==pset[sb] && ha[(k+1)%na]==pset[sa])) {ra=k;break;}
				REP(k, nb) if ((hb[k]==pset[sa] && hb[(k+1)%nb]==pset[sb]) || (hb[k]==pset[sb] && hb[(k+1)%nb]==pset[sa])) {rb=k;break;}
				if (ra==-1 || rb==-1)continue;
				for(int k=(ra+1)%na; k!=ra; k=(k+1)%na) h.pb(ha[k]);
				h.pb(ha[ra]);
				if (ha[ra]==hb[rb])
					for(int k=(nb+rb-1)%nb; k!=(rb+1)%nb; k=(nb+k-1)%nb) h.pb(hb[k]);
				else
					for(int k=(rb+2)%nb; k!=rb; k=(k+1)%nb) h.pb(hb[k]);
				assert(h.size()==count_bit(i|j));

				while(h[0]!=pset[ctz(i|j)])rotate(h.begin(), h.begin()+1, h.end());

				if (used.insert(h).ND)++res;
			}
		}

		return res;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-2,2,-2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,-2,2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {-2,2,-2,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,-2,2,2,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 16; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-2,2,-2,2,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,-2,2,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 22; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0,5,0,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,5,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 26; verify_case(3, Arg2, count(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	AlmostConvexPolygons ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
