// BEGIN CUT HERE

// END CUT HERE
#line 5 "Rafting.cpp"

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
inline double sqr(double a){return a*a;}

typedef pair<double, double> pdd;

const double eps=1e-10;
const double inf=1e10;
const int maxn=10;
vi x, y;
int n, K, rs, hs;
double timea[maxn][maxn];
struct data{double t, sx, ex;};
data best[two(maxn)][maxn][maxn];


double rec(int p, int d, int s){
	if (!s) return 0;
	double res=inf;
	REP(j, n) if (s&two(j) && (j!=d || s==two(j))) checkmin(res, rec(j, d, s^two(j))+timea[p][j]);
	return res;

}

pdd tsp(int s, double sx, int ka, int kb){

	double t=sqrt(sqr(sx-x[ka])+sqr(y[ka]))/hs+rec(ka, kb, s-two(ka));
	
	sx+=t*rs;
	double a, b, c, d;
	a=sqr(rs)-sqr(hs);
	b=2.*(sx-x[kb])*rs;
	c=sqr(y[kb])+sqr(sx-x[kb]);
	d=sqr(b)-4*a*c;
	assert(d>=0.);

	assert(-b+sqrt(d)>=0);
	double nt=(-b-sqrt(d))/(2*a);
	assert(nt>=0);
	return MP(t+nt, sx+nt*rs);

}
double solve(int state, double sx){
	if (count_bit(state)==K)return 0.;
	int na=0;
	int remap[n];
	
	REP(i, n) if (!(state&two(i))) remap[na++]=i;
	int ok=n-na;
	double res=inf;
	REP(i, two(na)) if (i && count_bit(i)+ok<=K){
		int rm=0;
		REP(j, na) if (i&two(j)) rm|=two(remap[j]);
		data d; d.ex=inf;
		REP(a, n) REP(b, n) if (rm&two(a) && rm&two(b) && (a!=b||rm==two(a)) && best[rm][a][b].sx+eps>=sx) checkmin(res, best[rm][a][b].t+solve(state|rm, best[rm][a][b].ex));
	}
	return res;
}


class Rafting {
	public:
		double minRunningTime(int _rs, int _hs, vector <int> _x, vector <int> _y, int _K) {
			x=_x, y=_y, K=_K; n=x.size();
			rs=_rs, hs=_hs;

			REP(i, n) REP(j, i+1) timea[i][j]=timea[j][i]=sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]))/hs;

			REP(i, two(n)) REP(a, n) REP(b, n) if (i&two(a) && i&two(b) && (a!=b || i==two(a))){
				long double H, T;
				pdd L, R;
				H=inf; T=-inf;
				while(H-T>eps){
					L=tsp(i, (2*T+H)/3, a, b);
					R=tsp(i, (T+2*H)/3, a, b);
					
					if (L.ST<R.ST) H=(T+2*H)/3;
					else T=(2*T+H)/3;
				}
				best[i][a][b]=(data){L.ST, T, T+rs*L.ST};

				//printf("%d => %.15lf %lf %lf\n", i,  best[i][a][b].t, best[i][a][b].sx, best[i][a][b].ex);
			}
			printf("start solve\n");
			return solve(0, -inf);

		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { int Arg0 = 48; int Arg1 = 49; int Arr2[] = {-10, -36, -24, -44, -19, -27}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {47, 48, 38, 27, 1, 43}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 6; double Arg5 = 0.04000800240080029; verify_case(0, Arg5, minRunningTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		//void test_case_0() { int Arg0 = 1; int Arg1 = 50; int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; double Arg5 = 0.04000800240080029; verify_case(0, Arg5, minRunningTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_1() { int Arg0 = 1; int Arg1 = 50; int Arr2[] = {0, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; double Arg5 = 0.04000800240080029; verify_case(1, Arg5, minRunningTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_2() { int Arg0 = 1; int Arg1 = 2; int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; double Arg5 = 1.1547005383792515; verify_case(2, Arg5, minRunningTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_3() { int Arg0 = 1; int Arg1 = 50; int Arr2[] = {10, -10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; double Arg5 = 0.08001600480160058; verify_case(3, Arg5, minRunningTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_4() { int Arg0 = 4; int Arg1 = 21; int Arr2[] = {6, -1, 4, 6, 7, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 5, 3, 2, 5, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 6; double Arg5 = 0.9517633779247896; verify_case(4, Arg5, minRunningTime(Arg0, Arg1, Arg2, Arg3, Arg4)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	Rafting ___test; 
	___test.run_test(0);
} 
// END CUT HERE
