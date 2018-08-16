// BEGIN CUT HERE

// END CUT HERE
#line 5 "BinaryPowerBishop.cpp"

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


const int MAX_P=30;
int high_bit(int n){if (n==0)return -1; REP(i, MAX_P) if (n&two(i) && n-two(i)<two(i))return i;}
vector<vector<pii> > lst;

void rec(int x, int y, int p, vector<pii> tb){
	if (lst.size()!= 0 && tb.size()>lst[0].size())return;
	if (x==0 || y==0){
		if (x!=y)return;
		if (lst.size()==0 || tb.size()<lst[0].size())CLR(lst);
		lst.pb(tb);
		return;
	}

	REP(i, 2){
		int m=two(p-i);
		vector<pii> ntb=tb;
		ntb.pb(MP(x<0?m:-m, y<0?m:-m));
		int np=high_bit(max(abs(x+ntb.back().ST), abs(y+ntb.back().ND)));
		if (np>=p-i) continue;
		rec(x+ntb.back().ST, y+ntb.back().ND, min(np+1, p-i-1), ntb);
	}

}

class BinaryPowerBishop {
	public:
	vector <string> getPath(int fx, int fy) {
		vs res;
		if (fx+fy&1)return res;
		CLR(lst);

		res.pb("0,0");
		if (fx==0 || fy==0)return (fx==fy?res:vs());

		rec(fx, fy, high_bit(max(abs(fx), abs(fy)))+1, vector<pii>());

		if (lst.size()==0)return vs();
		FE(it, lst){
			vs nr; nr.pb("0,0");
			vector<pii> p=*it;
			int px, py;
			px=py=0;
			while(p.size()){
				string np, temp; int id=-1;
			   	REP(i, p.size()) if ((temp=toStr(px-p[i].ST)+","+toStr(py-p[i].ND))<np || id==-1)id=i, np=temp;
				
				px-=p[id].ST, py-=p[id].ND;
				nr.pb(np); p.erase(p.begin()+id);
			}



			if (res.size()==1 || nr<res)res=nr;
		}
		return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 4; string Arr2[] = {"0,0", "16,16" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getPath(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 8; int Arg1 = 24; string Arr2[] = {"0,0", "-8,8", "8,24" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getPath(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 11; int Arg1 = 22; string Arr2[] = { }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getPath(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 123; int Arg1 = 321; string Arr2[] = {"0,0", "-128,128", "-112,112", "-104,104", "-100,100", "-102,98", "-101,97", "-133,65", "123,321" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getPath(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  BinaryPowerBishop ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
