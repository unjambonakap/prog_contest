// BEGIN CUT HERE

// END CUT HERE
#line 5 "ArtShift.cpp"

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

const int maxn=30;
int prime[maxn];
vi tb;
int mem[two(11)][maxn][maxn];

int proc(int m, int na, int nb){
    int &r=mem[m][na][nb];
    if (r!=-1) return r;
    r=1;


    FOR(i, 2, na+nb){
        int nm=0;
        REP(j, tb.size()) if (tb[j]<=i && i%tb[j]==0) nm|=two(j);
        if (m&nm) continue;
        FOR(k, 1, i-1) if (na-k>=0 && nb-i+k>=0) checkmax(r, proc(m|nm, na-k, nb-i+k)*i);
    }
    
    return r;
    
    

}

class ArtShift {
	public:
	int maxShifts(string s) {
        int na=0, nb=0;
        REP(i, s.length()) if (s[i]=='W') ++na; else ++nb;

        tb.clear();

        memset(prime, 1, sizeof(prime));
        FOR(i, 2, maxn-1) if (prime[i]){
            int j=2*i;
            tb.pb(i);
            while(j<maxn) prime[j]=0, j+=i;
        }
        memset(mem, -1, sizeof(mem));
        return proc(0, na, nb);

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arg0 = "BW"; int Arg1 = 2; verify_case(0, Arg1, maxShifts(Arg0)); }
	void test_case_0() { string Arg0 = "BBBBBWBBBBBBWBBBBBBBWBBBBBBBBB"; int Arg1 = 2; verify_case(0, Arg1, maxShifts(Arg0)); }
	void test_case_1() { string Arg0 = "BBBWBBB"; int Arg1 = 7; verify_case(1, Arg1, maxShifts(Arg0)); }
	void test_case_2() { string Arg0 = "BWBWB"; int Arg1 = 6; verify_case(2, Arg1, maxShifts(Arg0)); }
	void test_case_3() { string Arg0 = "WWWWWWWWW"; int Arg1 = 1; verify_case(3, Arg1, maxShifts(Arg0)); }
	void test_case_4() { string Arg0 = "WWWWWWWWWBBWB"; int Arg1 = 60; verify_case(4, Arg1, maxShifts(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ArtShift ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
