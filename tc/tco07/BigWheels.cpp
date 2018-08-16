// BEGIN CUT HERE

// END CUT HERE
#line 5 "BigWheels.cpp"

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

const double eps=1e-11;
const int maxn=55, maxv=105;
int wh[maxn][maxv];
int nv[maxn];
int n;
double dp[maxn][maxv];
int seen[maxn][maxv];
int mx[maxn];

set<int> res;
double solve(int p, int m){
	if (p==n) return 0.;
	double &r=dp[p][m];
	if (seen[p][m]) return r;
	seen[p][m]=1;

	r=0.;
	REP(i, nv[p]){
		int g=wh[p][i];
		int best=-1;
		double pbest=0.;
		if (g>m) pbest=1.-solve(p+1, g), best=0;
		double temp=0.;
		REP(j, nv[p]){
			int ng=wh[p][j];
			if (ng+g<=mx[p] && ng+g>m) temp+=(1.-solve(p+1, ng+g))/nv[p];
		}
		//if (p==0) printf("xxxxxxxxxx%d => %lf %lf\n", i, pbest, temp);
		if (best==-1 || temp+eps>=pbest) pbest=temp, best=1;

		if (best==1){
			REP(j, nv[p]){
				int ng=wh[p][j];
				if (ng+g>mx[p] || ng+g<=m) r+=solve(p+1, m)/nv[p]/nv[p];
				else r+=1./nv[p]/nv[p];
			}
		}else r+=1./nv[p];
		if (p==0 && best==0) res.insert(g);
	}
	//printf("%d %d => %lf\n", p, m, r);
	return r;

}

class BigWheels {
	public:
	vector <int> enough(vector <string> wheels) {
		res.clear();
		n=wheels.size();
		memset(nv, 0, sizeof(nv));
		REP(i, n){
			istringstream ss(wheels[i]);
			while (ss>>wh[i][nv[i]++]); --nv[i];
		}
		REP(i, n) mx[i]=*max_element(wh[i], wh[i]+nv[i]);
		memset(seen, 0, sizeof(seen));
		solve(0, 0);
		return vi(ALL(res));
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = { "1 100 100",
  "2 100",
  "3 100" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, enough(Arg0)); }
	void test_case_1() { string Arr0[] = { "1 2", "2 1" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, enough(Arg0)); }
	void test_case_2() { string Arr0[] = { "8 2 4",
  "0 7 7 7 7" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, enough(Arg0)); }
	void test_case_3() { string Arr0[] = { "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20",
  "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20",
  "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {14, 15, 16, 17, 18, 19, 20 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, enough(Arg0)); }
	void test_case_4() { string Arr0[] = { "5" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, enough(Arg0)); }
	void test_case_5() { string Arr0[] = { "4 4 4", "7 6" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, enough(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  BigWheels ___test; 
        ___test.run_test(3);
        } 
// END CUT HERE
