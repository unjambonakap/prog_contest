// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheChroniclesOfAmber.cpp"

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


const double eps=10e-11;
const int maxn=55;
int graph[maxn][maxn];


bool checkit(int a, int b, int c, int d, double T){
	ll z=ll(a-c)*(a-c)+ll(b-d)*(b-d);
	return (z<=T*T+eps);

}

class TheChroniclesOfAmber {
	public:
	double minimumTime(vector <int> px, vector <int> py, vector <int> dx, vector <int> dy) {
		int n=px.size();

		double H=10000*sqrt(2)+10;
		double L=0.;
		while(L+eps<H){
			double M=(H+L)/2.;

			memset(graph, 0, sizeof(graph));
			REP(i, n) REP(j, n) if (checkit(px[i], py[i], dx[j], dy[j], M)) graph[j][i]=1;
			bool fd=false;
			REP(k, n+1){
				REP(i, n){
					bool tmp=false;
				   	REP(j, n) if (j!=k && (k!=n || j==i) && graph[i][j]) {tmp=true; break;}
					if (!tmp)goto fail;
				}

				fd=true;
				break;
fail:;
			}
			//REP(i, n) {REP(j, n) printf("%d ", graph[i][j]); printf("\n");}
			//REP(i, n) if (graph[i][3]) printf(">> %d\n", i);

			//printf("%d\n", find(n));
			//break;
			if (fd) H=M;
			else L=M;
		}

		
		return L;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arr0[] = {1,5,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4,2,3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 4.0; verify_case(0, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_0() { int Arr0[] = {0, 0, 0, 0, 10, 20, 30, 30, 30, 30, 20, 10, 1000, 1000, 1000, 1000, 1010, 1020, 1030, 1030, 1030, 1030, 1020, 1010, 10000, 10000, 10000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 10, 20, 30, 30, 30, 30, 20, 10, 0, 0, 0, 1000, 1010, 1020, 1030, 1030, 1030, 1030, 1020, 1010, 1000, 1008, 1000, 9000, 8000, 9050}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 10, 20, 30, 30, 30, 30, 20, 10, 0, 0, 0, 1000, 1010, 1020, 1030, 1030, 1030, 1030, 1020, 1010, 1000, 1000, 1000, 9999, 10000, 9995}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {30, 30, 30, 30, 20, 10, 0, 0, 0, 0, 10, 20, 1030, 1030, 1030, 1030, 1020, 1010, 1000, 1000, 1000, 1000, 1010, 1020, 9043, 8005, 9054}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 4.0; verify_case(0, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,0,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,2,4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 1.0; verify_case(1, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,0,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4,2,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 1.0; verify_case(2, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {0,3,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,4,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3,5,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4,0,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 4.47213595499958; verify_case(3, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {3629,6751,8655,5115,7809,6759,7133,1810,6102,2539,1777,242}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5294,180,988,7780,1635,7904,845,7405,4800,2567,4795,2339}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {8723,9275,6705,5875,7981,7666,1158,4135,17,2984,5086,3570}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {6166,53,5980,4499,412,9074,8190,847,650,9158,9116,4396}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 2622.582696503582; verify_case(4, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  TheChroniclesOfAmber ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
