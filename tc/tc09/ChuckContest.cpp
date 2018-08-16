// BEGIN CUT HERE

// END CUT HERE
#line 5 "ChuckContest.cpp"

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

int strToInt(string s){
	istringstream ss(s);
	int a;
	ss>>a;
	return a;
}
string intToStr(int a){
	ostringstream os;
	os<<a;
	return os.str();
}

int dp[52][61][20];
int dpa[52][61][20];
vector<pii> lb, ub;
vi pt;
int np, n;

struct cmpA{
	bool operator()(const pii &a, const pii &b)const{ return a.ST!=b.ST?a.ST<b.ST:a.ND>b.ND;}
};

class ChuckContest {
	public:
	string chuckRules(int numProblems, vector <string> lowerBounds, vector <string> upperBounds, vector <int> partTimes) {
		int i, j, k, a, b, c;
		np=numProblems;
		n=lowerBounds.size();

		pt=partTimes;
		lb.clear(); ub.clear();
		for (i=0; i<n; ++i){
			int pa, pb;
			pa=lowerBounds[i].find(" "), pb=upperBounds[i].find(" ");
			lb.pb(MP(strToInt(lowerBounds[i].substr(0, pa)), -strToInt(lowerBounds[i].substr(pa+1))));
			ub.pb(MP(strToInt(upperBounds[i].substr(0, pb)), -strToInt(upperBounds[i].substr(pb+1))));
		}

		for (i=1; i<n; ++i)
			if (lb[i]<lb[i-1])lb[i]=lb[i-1];
		for (i=n-2; i>=0; --i)
			if (ub[i]>ub[i+1])ub[i]=ub[i+1];

		memset(dp, -1, sizeof(dp));
		memset(dpa, -1, sizeof(dpa));
		dp[0][0][0]=0;
		dpa[0][0][0]=0;
		int v, va, nv, nva, temp, tempa, nvs, nvsa, temps;
		for (i=0; i<n; ++i){
			int st=(i==0?1:pt[i-1]+1);
			for (j=0; j<=np; ++j){
				for (k=0; k<20; ++k){
					if ((v=dp[i][j][k])==-1)continue;
					va=dpa[i][j][k];

					for (a=max(j, lb[i].ST); a<=ub[i].ST; ++a){
						tempa=(a-j)*st;
						temps=(k+tempa)%20-20;
						nvs=v+tempa;
						nvsa=va+tempa;
						for (b=0; b<20; ++b){
							nv=nvs, nva=nvsa;
							temp=(b-temps)%20;
							if (temp!=0){
								if(a-j==0)continue;
								c=ceil(double(temp)/(a-j));

								if (c>pt[i]-st)continue;
								nv+=temp;
								nva+=temp;
							}
							if (a==lb[i].ST && nv>=-lb[i].ND)
								continue;
							if (a==lb[i].ST && nva>=-lb[i].ND)
								nva-=ceil((nva+lb[i].ND+1)/20.)*20;
								
							if (a>j){
								if (a==lb[i].ST){
									nva+=floor((-lb[i].ND-1-nva)/20.)*20;
								//	assert(nva<lb[i].ND);
								}else
									nva=100000+b;

							}
							
					//		assert(nv%20==b);
					//		assert(nva%20==b);
							if (a==ub[i].ST && nv<=-ub[i].ND){
								if (a==j && nva<=-ub[i].ND)continue;
								nv+=ceil((-ub[i].ND+1-nv)/20.)*20;
					//			assert(nv-20<=ub[i].ND);
							}
							if (a==lb[i].ST && nv>=-lb[i].ND)
								continue;
					//		assert(a<ub[i].ST || nv>ub[i].ND);
							if (dp[i+1][a][b]==-1 || nv<dp[i+1][a][b])
								dp[i+1][a][b]=nv;
							dpa[i+1][a][b]=max(dpa[i+1][a][b], nva);
						}
					}
				}
			}
		}
		pii best;
		best.ST=-1;
		for (i=lb[n-1].ST; i<=ub[n-1].ST; ++i)
			for (j=0; j<20; ++j){
				if (dp[n][i][j]!=-1)
					best=max(best, MP(i, dp[n][i][j]), cmpA());
				
				
			}
		if (best.ST==-1)return "";
		return intToStr(best.ST)+" "+intToStr(best.ND);
	}

	








// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; string Arr1[] = {"1 31"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "1 21"; verify_case(0, Arg4, chuckRules(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; string Arr1[] = {"10 31"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "10 30"; verify_case(1, Arg4, chuckRules(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 10; string Arr1[] = {"10 30"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = ""; verify_case(2, Arg4, chuckRules(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 60; string Arr1[] = {"60 60"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 100000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1500}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = ""; verify_case(3, Arg4, chuckRules(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 10; string Arr1[] = {"1 21", "1 23"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 19", "1 21"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {20, 60}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = ""; verify_case(4, Arg4, chuckRules(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 10; string Arr1[] = {"1 3", "1 100000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 1", "10 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {30, 31}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "10 281"; verify_case(5, Arg4, chuckRules(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arg0 = 17; string Arr1[] = {"4 982", "5 182", "14 103"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"14 14", "9 703", "17 440"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {6, 10, 16}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "17 441"; verify_case(6, Arg4, chuckRules(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ChuckContest ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
