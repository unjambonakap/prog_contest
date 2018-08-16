// BEGIN CUT HERE

// END CUT HERE
#line 5 "BlackWhiteRectangles.cpp"

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


struct Rect{
	int xa, xb, ya, yb;
	int id;
	int pattern;
	bool operator<(const Rect &r)const{return (ya!=r.ya)?ya<r.ya:(yb!=r.yb?yb<r.yb:id<r.id);}
};

struct Event{
	int px, id;
	int start;
	bool operator<(const Event &e)const{return (px!=e.px)?px<e.px:id<e.id;}
};
struct Eventy{
	int py, id;
	int start;
	bool operator<(const Eventy &e)const{return (py!=e.py)?py<e.py:id<e.id;}
};
int n;

vector<Rect> rl;
vector<Event> el;
set<Eventy> lsw;

int cntBlack(int xa, int xb, int ya, int yb, ll onr){

	if (onr==0)return 0;
	int black[2][2];
	memset(black, 0, sizeof(black));
	for (int x=0; x<2; ++x)
		for (int y=0; y<2; ++y)
			for (int i=0; i<n; ++i)
				if (twoll(i)&onr){
					int b;
					if (rl[i].pattern==1){
						b=1;
					}else if (rl[i].pattern==2){
						b=(ya+y-rl[i].ya)%2;
					}else if (rl[i].pattern==3){
						b=(xa+x-rl[i].xa)%2;
					}else{
						b=(1+xa+x-rl[i].xa+ya+y-rl[i].ya)%2;
					}

					black[x][y]|=b;
				}
	int ca, cb;
	int nx, ny;
	ny=yb-ya, nx=xb-xa;
	ca=ny/2*(black[0][0]+black[0][1]);
	cb=ny/2*(black[1][0]+black[1][1]);
	if (ny%2==1)
		ca+=black[0][0], cb+=black[1][0];
	int s;
	s=nx/2*(ca+cb);
	if (nx%2==1)s+=ca;
	return s;

}


class BlackWhiteRectangles {
	public:

	int blackCount(vector <string> rectangles) {

		n=rectangles.size();
		rl=vector<Rect>(n);
		for (int i=0; i<n; ++i){
			istringstream ss(rectangles[i]);
			ss>>rl[i].xa>>rl[i].ya>>rl[i].xb>>rl[i].yb>>rl[i].pattern;
			rl[i].id=i;
		}

		CLR(el);
		for (int i=0; i<n; ++i){
			el.pb((Event){rl[i].xa, rl[i].id, 1});
			el.pb((Event){rl[i].xb, rl[i].id, 0});
		}

		sort(ALL(el));
		CLR(lsw);

		int s=0;
		for (int i=0; i<el.size(); ++i){

			if (i>0 && el[i].px>el[i-1].px){
				ll onr=0;
				set<Eventy>::iterator prev=lsw.end();
				FE(it, lsw){
					if (prev!=lsw.end() && prev->py<it->py)
						s+=cntBlack(el[i-1].px, el[i].px, prev->py, it->py, onr);
					if (it->start==1)
						onr|=twoll(it->id);
					else
						onr^=twoll(it->id);
					prev=it;
				}

			}
			if (el[i].start){
				lsw.insert((Eventy){rl[el[i].id].ya, el[i].id, 1});
				lsw.insert((Eventy){rl[el[i].id].yb, el[i].id, 0});
			}
			else{
				lsw.erase((Eventy){rl[el[i].id].ya, el[i].id, 1});
				lsw.erase((Eventy){rl[el[i].id].yb, el[i].id, 0});
			}

		}


		return s;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1 1 6 8 1",
 "11 1 16 8 2",
 "1 11 6 18 3",
 "11 11 16 18 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 82; verify_case(0, Arg1, blackCount(Arg0)); }
	void test_case_1() { string Arr0[] = {"1 1 11 11 1",
 "1 1 11 11 2",
 "9 9 19 19 3",
 "9 9 19 19 4"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 172; verify_case(1, Arg1, blackCount(Arg0)); }
	void test_case_2() { string Arr0[] = {"1 6 9 9 1",
 "1 9 7 10 1",
 "1 5 8 7 1",
 "2 6 8 8 1",
 "2 1 3 4 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 40; verify_case(2, Arg1, blackCount(Arg0)); }
	void test_case_3() { string Arr0[] = {"7 5 9 6 4",
 "6 3 9 6 4",
 "8 3 9 8 4",
 "5 9 10 10 4",
 "5 3 8 5 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(3, Arg1, blackCount(Arg0)); }
	void test_case_4() { string Arr0[] = {"7 1 10 3 1",
 "8 2 9 7 4",
 "5 3 7 4 3",
 "4 3 9 4 2",
 "3 1 9 2 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(4, Arg1, blackCount(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  BlackWhiteRectangles ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
