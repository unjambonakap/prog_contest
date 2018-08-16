// BEGIN CUT HERE

// END CUT HERE
#line 5 "RaceTrack.cpp"

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

const int maxn=55;
int mp[maxn];
int dp[maxn][maxn];
int n;
string res;

int solve(int p, int m){
	int &r=dp[p][m];
	if (r!=-1)return r;
	if (m==0)return r=INT_MAX;
	r=0;
	if (p==n)return r=0;
	FOR(i, p+1, n-1) r=max(r, min(solve(i, m-1), mp[i]-mp[p]));
	return r;
}
void build(int p, int m, int v){
	res[p]='1';
	if (m==0)return;
	FOR(i, p+1, n-1) if (mp[i]-mp[p]>=v && solve(i, m-1)>=v){
		build(i, m-1, v);
		return;
	}
	assert(0);

}


class RaceTrack {
	public:
	string judgePositions(int length, int m, vector <int> pos) {
		n=pos.size();
		REP(i, n) mp[i]=pos[i];
		memset(dp, -1, sizeof(dp));
		int k=-1, vk;
		REP(i, n-m+1){
			int a=solve(i, m-1);
			if (k==-1 || vk<a) k=i, vk=a;
		}
		res=string(n, '0');
		build(k, m-1, vk);
		return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 11; int Arg1 = 3; int Arr2[] = {0, 5, 10, 11}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "1110"; verify_case(0, Arg3, judgePositions(Arg0, Arg1, Arg2)); }
	void test_case_0() { int Arg0 = 1156; int Arg1 = 29; int Arr2[] = {10, 19, 43, 86, 102, 136, 227, 265, 307, 316, 347, 360, 362, 420, 433, 484, 501, 562, 570, 579, 721, 729, 737, 738, 746, 758, 773, 799, 885, 897, 928, 935, 948, 1126}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "1110"; verify_case(0, Arg3, judgePositions(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 11; int Arg1 = 2; int Arr2[] = {0, 5, 10, 11}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "1001"; verify_case(1, Arg3, judgePositions(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 11; int Arg1 = 4; int Arr2[] = {0, 5, 10, 11}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "1111"; verify_case(2, Arg3, judgePositions(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 5; int Arr2[] = {6, 9, 33, 59, 100, 341, 431, 444, 565, 857}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "1000010111"; verify_case(3, Arg3, judgePositions(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  RaceTrack ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
