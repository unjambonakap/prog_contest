// BEGIN CUT HERE

// END CUT HERE
#line 5 "MatrixPainting.cpp"

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

const int n=9;
int mp[n][n], ma[n][n];
int ra[2*n], rb[2*n];


class MatrixPainting {
	public:
	int countRepaints(vector <string> matrix) {
        REP(i, n) REP(j, n) mp[i][j]=matrix[i][j]=='0';

        REP(i, n){ra[i]=0; REP(j, n) ra[i]+=mp[i][j];}
        REP(i, n){ra[n+i]=0; REP(j, n) ra[n+i]+=mp[j][i];}
        int ans=INT_MAX;
        REP(m, two(2*n)) if (count_bit(m)<ans){
            int nm=m, fd=1;
            memcpy(rb, ra, sizeof(ra)); memcpy(ma, mp, sizeof(mp));
            while(fd && nm){
                fd=0;
                REP(i, 2*n) if ((nm&two(i)) && rb[i]<=4){
                    fd=1;
                    nm^=two(i);
                    if (i>=n){
                        int k=i-n;
                        REP(j, n) if (ma[j][k]) ma[j][k]=0, --rb[j];
                    }else{
                        REP(j, n) if (ma[i][j]) ma[i][j]=0, --rb[j+n];
                    }
                    rb[i]=0;

                }


            }
            if (nm) continue;

            fd=0;
            REP(i, 2*n) if (rb[i]){fd=1; break;}
            if (!fd) ans=count_bit(m);
        }
        return ans==INT_MAX?-1:ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"001111111",
 "011111111",
 "011111111",
 "011111111",
 "011111111",
 "101111111",
 "101111111",
 "101111111",
 "101111111"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, countRepaints(Arg0)); }
	void test_case_1() { string Arr0[] = {"011111111",
 "101111111",
 "110111111",
 "111011111",
 "111101111",
 "111110111",
 "111111011",
 "111111101",
 "111111110"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(1, Arg1, countRepaints(Arg0)); }
	void test_case_2() { string Arr0[] = {"000000001",
 "000000011",
 "000000111",
 "000001111",
 "000011111",
 "000011110",
 "000011100",
 "000011000",
 "000010000"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 14; verify_case(2, Arg1, countRepaints(Arg0)); }
	void test_case_3() { string Arr0[] = {"000000001",
 "000000011",
 "000000111",
 "000001111",
 "000011111",
 "000011110",
 "000011100",
 "000011000",
 "000000000"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, countRepaints(Arg0)); }
	void test_case_4() { string Arr0[] = {"011111111",
 "010001001",
 "111111101",
 "011111111",
 "101010100",
 "011111111",
 "111111101",
 "111011101",
 "011111111"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, countRepaints(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MatrixPainting ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
