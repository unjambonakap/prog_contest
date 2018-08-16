// BEGIN CUT HERE

// END CUT HERE
#line 5 "ManhattanPatrol.cpp"

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

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

int bit[1025];

void bit_add(int a){ while(a<1024) ++bit[a], a+=(a^a-1)&a; }
int bit_get(int a){int res=0; while(a) res+=bit[a], a^=(a^a-1)&a; return res;}

class ManhattanPatrol {
	public:
	long long countIntersections(int n, int AX, int BX, int MX, int AY, int BY, int MY) {
        vi xl, yl;
        xl.pb(BX); yl.pb(BY);
        REP(i, n-1){
            xl.pb((xl.back()*AX+BX)%MX);
            yl.pb((yl.back()*AY+BY)%MY);
        }
        vi A;
        REP(i, n) A.pb(yl[i]); sort(ALL(A)); 

        vector<pii> pl;
        REP(i, n) pl.pb(MP(xl[i], lower_bound(ALL(A), yl[i])-A.begin()+1));

        sort(ALL(pl));

        ll res=0;
        REP(i, n){
            int y=pl[i].ND;
            int a=0;
            memset(bit, 0, sizeof(bit));
            FOR(j, i+1, n-1){
                if (pl[j].ND<y) res+=1LL*a*bit_get(pl[j].ND), bit_add(pl[j].ND);
                else ++a;
            }
        }
        REPV(i, n){
            int y=pl[i].ND;
            int a=0;
            memset(bit, 0, sizeof(bit));
            REPV(j, i){
                if (pl[j].ND<y) res+=1LL*a*bit_get(pl[j].ND), bit_add(pl[j].ND);
                else ++a;
                
            }
        }
        return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 2; int Arg3 = 11; int Arg4 = 2; int Arg5 = 2; int Arg6 = 13; long long Arg7 = 1LL; verify_case(0, Arg7, countIntersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { int Arg0 = 7; int Arg1 = 1; int Arg2 = 2; int Arg3 = 11; int Arg4 = 2; int Arg5 = 2; int Arg6 = 13; long long Arg7 = 2LL; verify_case(1, Arg7, countIntersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 1; int Arg2 = 2; int Arg3 = 7; int Arg4 = 1; int Arg5 = 1; int Arg6 = 6; long long Arg7 = 5LL; verify_case(2, Arg7, countIntersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 1; int Arg2 = 1; int Arg3 = 11; int Arg4 = 13; int Arg5 = 1; int Arg6 = 16; long long Arg7 = 0LL; verify_case(3, Arg7, countIntersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { int Arg0 = 20; int Arg1 = 6; int Arg2 = 1; int Arg3 = 211; int Arg4 = 13; int Arg5 = 11; int Arg6 = 186; long long Arg7 = 862LL; verify_case(4, Arg7, countIntersections(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ManhattanPatrol ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
