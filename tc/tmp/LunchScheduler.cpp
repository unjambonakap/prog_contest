// BEGIN CUT HERE

// END CUT HERE
#line 5 "LunchScheduler.cpp"

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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)

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

const int maxn=9;
int mp[maxn][maxn];
int A[maxn], B[maxn];

class LunchScheduler {
	public:
	int getOverlap(vector <string> M) {
        int n=M.size();
        REP(i, n) REP(j, n) mp[i][j]=M[i][j]=='1';
        int perm[n];
        REP(i, n) perm[i]=i;
        memset(A, 0, sizeof(A));
        REP(i, n) REP(j, n) A[i]+=mp[i][j];

        int ans=n;
        do{
            int res=0;
            int cnt=0;
            memcpy(B, A, sizeof(A));
            REP(i, n){
                int a=perm[i];
                ++cnt;
                checkmax(res, cnt);
                if (B[a]) REP(j, i){
                    int b=perm[j];
                    if (mp[a][b]){
                        if (!--B[a]) --cnt;
                        if (!--B[b]) --cnt;
                    }
                }else --cnt;

            }
            checkmin(ans, res);
        }while(next_permutation(perm, perm+n));

        return ans;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0110", 
 "1010", 
 "1100", 
 "0000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, getOverlap(Arg0)); }
	void test_case_1() { string Arr0[] = {"011111",
 "101111",
 "110111",
 "111011",
 "111101",
 "111110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(1, Arg1, getOverlap(Arg0)); }
	void test_case_2() { string Arr0[] = {"01000000",
 "10000000",
 "00000000",
 "00000000",
 "00000000",
 "00000000",
 "00000001",
 "00000010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, getOverlap(Arg0)); }
	void test_case_3() { string Arr0[] = {"011011010",
 "101000111",
 "110010110",
 "000001101",
 "101001000",
 "100110101",
 "011101010",
 "111000100",
 "010101000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, getOverlap(Arg0)); }
	void test_case_4() { string Arr0[] = {"000",
 "000",
 "000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, getOverlap(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  LunchScheduler ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
