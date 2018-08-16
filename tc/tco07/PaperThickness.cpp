// BEGIN CUT HERE

// END CUT HERE
#line 5 "PaperThickness.cpp"

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

const int maxn=2500;

int op_id[maxn];
int op_pos[maxn];
int n;

ll solve(int w, int id){
	map<int, ll> line, la, lb;
	map<int, ll>::iterator ita, itb, itc;
	line.insert(MP(0, 1));
	line.insert(MP(w, 0));
	REP(i, n){
		if ((op_id[i]&2)!=id)continue;
		if (op_pos[i]<=line.begin()->ST || op_pos[i]>=(--line.end())->ST)continue;
		ita=line.lower_bound(op_pos[i]);
		if (ita->ST>op_pos[i]){
		   	--ita;
			ita=line.insert(MP(op_pos[i], ita->ND)).ST;
		}
		ll thick=ita->ND;
		la.clear(); lb.clear();

		if ((op_id[i]&1)==1){
			itb=line.begin();
			while(itb!=ita) la.insert(*itb), ++itb;
			la[op_pos[i]]=0;


			itb=ita; 
			while(itb!=line.end()) lb.insert(MP(2*op_pos[i]-itb->ST, thick)), thick=itb->ND, ++itb;
			lb[op_pos[i]]=0;
		}else{
			itb=ita;
			while(itb!=line.end()) lb.insert(*itb), ++itb;

			itb=ita; --itb;
			thick=itb->ND;

			itb=line.begin();
			la[op_pos[i]]=thick;
			ll thick=0;
			while(itb!=ita){
				la.insert(MP(2*op_pos[i]-itb->ST, thick)), thick=itb->ND, ++itb;
			}
			itc=la.begin();
		}



		line=la; line.insert(ALL(lb));
		ll ta, tb;
		if (la.begin()->ST>line.begin()->ST) la.insert(MP(line.begin()->ST, 0LL));
		if (lb.begin()->ST>line.begin()->ST) lb.insert(MP(line.begin()->ST, 0LL));
		if ((--la.end())->ST<(--line.end())->ST) la.insert(MP((--line.end())->ST, 0LL));
		if ((--lb.end())->ST<(--line.end())->ST) lb.insert(MP((--line.end())->ST, 0LL));
		ita=la.begin(), itb=lb.begin();
		ta=ita->ND, tb=itb->ND;
		++ita; ++itb;

		itc=line.begin();
		while(itc!=line.end()){
			itc->ND=ta+tb; ++itc;
			if (ita!=la.end() && itc->ST==ita->ST) ta=ita->ND, ++ita;
			if (itb!=lb.end() && itc->ST==itb->ST) tb=itb->ND, ++itb;
		}
//		printf("======== with %d\n", op_pos[i]);
//		FE(it, line) printf("<<%d %Ld\n", it->ST, it->ND);
	}
	//printf("\n\n\n");

	ll mx=0;
	FE(it, line) checkmax(mx, it->ND);
	//printf("max %Ld\n", mx);
	return mx;
}

class PaperThickness {
	public:
		long long maxThickness(vector <string> folds, int w, int h) {
			string s, t;
			FE(it, folds) s+=*it;
			istringstream ss(s);

			n=0;
			while(ss>>t){
				char temp=t[0];
				op_pos[n]=toInt(t.substr(1));
				op_id[n]=0;
				if (temp>='a') op_id[n]|=1;
				if ((temp|two(5))=='y') op_id[n]|=2;
				++n;
			}
			return solve(w, 0)*solve(h, 2);
			return 0;

		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		//void test_case_0() { string Arr0[] = {"X1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; long long Arg3 = 2LL; verify_case(0, Arg3, maxThickness(Arg0, Arg1, Arg2)); }
		void test_case_0() { string Arr0[] = {"X42168 y25754 Y22059 x82222 Y23787 Y24614 x59349 y", "25733 Y25338 x58639 y25689 x54095 Y25531 y25629 Y2", "5574 X51188 y25625 y25579 x51668 Y25578 x51286 Y25", "579 y25579 X51253 X51269 y25579 x51276 Y25579 Y255", "79 X51270 x51270 y25579 y25579 y25579 x51270 y2557", "9 y25579 x51270 x51270 Y25579 X51270 y25579 x51270", " y25579 y25579 X51270 Y25579 Y25579 Y25579 X51270 ", "Y25579 x51270 x51270 x51270 x51270 x51270 Y25579 X", "51270 x51270 X51270 y25579 Y25579 y25579 x51270 x5", "1270 X51270 x51270 x51270 X51270 x51270 Y25579 Y25", "579 X51270 Y25579 y25579 x51270 x51270 y25579 y255", "79 X51270 y25579 X51270 x51270 Y25579 y25579 Y2557", "9 y25579 Y25579 y25579 X51270 Y25579 y25579 X51270", " x51270 X51270 X51270 Y25579 x51270 Y25579 y25579 ", "y25579 y25579 Y25579 X51270 y25579 Y25579 X51270 x", "51270 X51270 y25579 Y25579 y25579 y25579 x51270 x5", "1270 X51270 y25579 Y25579 y25579 y25579 X51270 Y25", "579 x51270 x51270 y25579 x51270 y25579 y25579 y255", "79 y25579 y25579 y25579 Y25579 Y25579 X51270 x5127", "0 Y25579 X51270 x51270 Y25579 y25579 y25579 X51270", " x51270 y25579 x51270 x51270 X51270 x51270 Y25579 ", "X51270 X51270 X51270 Y25579 X51270 X51270 y25579 Y", "25579 X51270 x51270 Y25579 Y25579 x51270 y25579 y2", "5579 Y25579 y25579 y25579 X51270 X51270 y25579 y25", "579 X51270 Y25579 y25579 X51270 X51270 X51270 X512", "70 Y25579 Y25579 y25579 X51270 y25579 Y25579 Y2557", "9 y25579 x51270 y25579 y25579 x51270 x51270 X51270", " X51270 y25579 X51270 X51270 Y25579 X51270 Y25579 ", "X51270 X51270 y25579 y25579 X51270 Y25579 Y25579 Y", "25579 X51270 y25579 X51270 X51270 Y25579 x51270 y2", "5579 Y25579 Y25579 X51270 X51270 X51270 y25579 Y25", "579 Y25579 y25579 x51270 Y25579 Y25579 X51270 x512", "70 x51270 Y25579 Y25579 x51270 X51270 Y25579 Y2557", "9 X51270 x51270 y25579 Y25579 X51270 Y25579 x51270", " x51270 x51270 y25579 Y25579 y25579 X51270 x51270 ", "x51270 X51270 Y25579 X51270 x51270 x51270 X51270 y", "25579 x51270 X51270 x51270 Y25579 x51270 x51270 y2", "5579 X51270 x51270 Y25579 x51270 x51270 x51270 x51", "270 X51270 y25579 y25579 Y25579 X51270 x51270 y255", "79 Y25579 y25579 y25579 Y25579 Y25579 Y25579 x5127", "0 Y25579 Y25579 X51270 x51270 y25579 x51270 x51270", " X51270 Y25579 Y25579 x51270 x51270 x51270 Y25579 ", "X51270 Y25579 y25579 x51270 X51270 X51270 y25579 X", "51270 x51270 Y25579 X51270 X51270 y25579 x51270 x5", "1270 X51270 y25579 x51270 Y25579 Y25579 Y25579 X51", "270 X51270 Y25579 x51270 X51270 X51270 Y25579 X512", "70 y25579 X51270 Y25579 y25579 x51270 X51270 Y2557", "9 y25579 X51270 x51270 X51270 x51270 Y25579 x51270", " y25579 X51270 X51270 Y25579 X51270 x51270 y25579 ", "X51270 Y25579 x51270 y25579 Y25579 x51270 X51270"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100000; int Arg2 = 100000; long long Arg3 = 2LL; verify_case(0, Arg3, maxThickness(Arg0, Arg1, Arg2)); }
		void test_case_1() { string Arr0[] = {"X0 x-1 Y-10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; long long Arg3 = 1LL; verify_case(1, Arg3, maxThickness(Arg0, Arg1, Arg2)); }
		void test_case_2() { string Arr0[] = {"X2", " y3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 4; long long Arg3 = 4LL; verify_case(2, Arg3, maxThickness(Arg0, Arg1, Arg2)); }
	//	void test_case_3() { string Arr0[] = {"Y1 ", "y3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 4; long long Arg3 = 3LL; verify_case(3, Arg3, maxThickness(Arg0, Arg1, Arg2)); }
		void test_case_3() { string Arr0[] = {"X1 ", "x3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 4; long long Arg3 = 3LL; verify_case(3, Arg3, maxThickness(Arg0, Arg1, Arg2)); }
		void test_case_4() { string Arr0[] = {"x1 y1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; long long Arg3 = 4LL; verify_case(4, Arg3, maxThickness(Arg0, Arg1, Arg2)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	PaperThickness ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
