// BEGIN CUT HERE

// END CUT HERE
#line 5 "BoxFilling.cpp"

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


ll _proc2d(int sa, int sb, int ca, int cb){
	if (cb==1)return ca;
	return ll(sa)+(sb-1==1?ca:_proc2d(sb-1, sa, cb-1, ca));
}
//20542327381710
//644865205656070
ll proc2d(int sa, int sb, int ca, int cb){

	ll d=max(0, min(ca, cb)-2);
	ll temp=0;
	if (d>0)
		temp=d*sa-d*(d-1)/2+d*(sb-1)-d*(d-1)/2;
	return temp+_proc2d(sa-d, sb-d, ca-d, cb-d);
}

ll _proc3d(int sx, int sy, int sz, int cx, int cy, int cz, int perm){
	if (cz==1){
		if (perm==0 || perm==2){
			return proc2d(sx, sy, cx, cy);
		}
		return proc2d(sy, sx, cy, cx);
	}
	ll temp=ll(sx)*sy;
	if (sz-1==1){
		if (perm==0 || perm==2){
			return proc2d(sx, sy, cx, cy)+temp;
		}
		return proc2d(sy, sx, cy, cx)+temp;
	}
	return temp+_proc3d(sz-1, sx, sy, cz-1, cx, cy, (perm+1)%3);
}

class BoxFilling {
	public:
		long long getNumber(int sizeX, int sizeY, int sizeZ, int cubeX, int cubeY, int cubeZ) {
			ll temp;
			ll a, b, c, d;

			c=0;
			if (sizeX==1)++c;
			if (sizeY==1)++c;
			if (sizeZ==1)++c;
			if (c==1){
				if (sizeX==1)
					return proc2d(sizeY, sizeZ, cubeY, cubeZ);
				else if (sizeY==1)
					return proc2d(sizeX, sizeZ, cubeX, cubeZ);
				return proc2d(sizeX, sizeY, cubeX, cubeY);

			}else if (c==2){
				if (sizeX!=1)return cubeX;
				if (sizeY!=1)return cubeY;
				if (sizeZ!=1)return cubeZ;
			}else if (c==3)return 1;
			a=cubeX-1, b=cubeY-1, c=cubeZ-1;
			d=max(0LL, min(min(a, b), c)-2);

			temp=0;
			if (d>0){
				temp=d*sizeX*sizeY-(d-1)*d/2*(sizeX+sizeY)+(d-1)*d*(2*d-1)/6;
				temp+=d*sizeX*(sizeZ-1)-(d-1)*d/2*(sizeX+sizeZ-1)+(d-1)*d*(2*d-1)/6;
				temp+=d*(sizeY-1)*(sizeZ-1)-(d-1)*d/2*(sizeY-1+sizeZ-1)+(d-1)*d*(2*d-1)/6;
			}
			//		printf("proc %Ld on z\n", (d*sizeX*sizeY-(d-1)*d/2*(sizeX+sizeY))+(d-1)*d*(2*d-1)/6);
			//		printf("proc %Ld on y\n", (d*sizeX*(sizeZ-1)-(d-1)*d/2*(sizeX+sizeZ-1))+(d-1)*d*(2*d-1)/6);
			//printf("proc %Ld on x\n", (d*(sizeY)*(sizeZ-1)-(d-1)*d/2*(sizeY-1+sizeZ-1))+(d-1)*d*(2*d-1)/6);
			return temp+_proc3d(sizeX-d, sizeY-d, sizeZ-d, cubeX-d, cubeY-d, cubeZ-d, 0);


		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		//void test_case_0() { int Arg0 = 4; int Arg1 = 5; int Arg2 = 1; int Arg3 = 2; int Arg4 = 4; int Arg5 = 1; long long Arg6 = 13LL; verify_case(0, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
		void test_case_0() { int Arg0 = 1000000; int Arg1 = 1000000; int Arg2 = 1000000; int Arg3 = 999841; int Arg4 = 999232; int Arg5 = 999932; long long Arg6 = 13LL; verify_case(0, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
		void test_case_1() { int Arg0 = 4; int Arg1 = 3; int Arg2 = 3; int Arg3 = 2; int Arg4 = 2; int Arg5 = 2; long long Arg6 = 25LL; verify_case(1, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
		void test_case_2() { int Arg0 = 4; int Arg1 = 3; int Arg2 = 3; int Arg3 = 4; int Arg4 = 2; int Arg5 = 1; long long Arg6 = 9LL; verify_case(2, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
		void test_case_3() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 1; int Arg4 = 1; int Arg5 = 1; long long Arg6 = 1LL; verify_case(3, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
		void test_case_4() { int Arg0 = 43633; int Arg1 = 35453; int Arg2 = 34533; int Arg3 = 2344; int Arg4 = 32442; int Arg5 = 34221; long long Arg6 = 9416237809215LL; verify_case(4, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
		void test_case_5() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 10; int Arg3 = 3; int Arg4 = 1; int Arg5 = 2; long long Arg6 = 14LL; verify_case(5, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
		void test_case_6() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 4; int Arg3 = 3; int Arg4 = 2; int Arg5 = 3; long long Arg6 = 28LL; verify_case(6, Arg6, getNumber(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	BoxFilling ___test; 
	___test.run_test(0);
} 
// END CUT HERE
