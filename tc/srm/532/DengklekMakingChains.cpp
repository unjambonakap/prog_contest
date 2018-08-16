// BEGIN CUT HERE

// END CUT HERE
#line 5 "DengklekMakingChains.cpp"

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

int val(char c){return c=='.'?-1:c-'0';}

class DengklekMakingChains {
	public:
	int maxBeauty(vector <string> chains) {
        int a; a=0;
        int res=0;
        vector<pii> b, c;
        REP(i,chains.size()){
            string &s=chains[i];
            int x=val(s[0]), y=val(s[1]), z=val(s[2]);
            if (x!=-1&&y!=-1&&z!=-1) a+=x+y+z;
            else{
                checkmax(y,0);
                if (x!=-1) b.pb(MP(x+y,i));
                if (z!=-1) c.pb(MP(z+y,i));

                checkmax(res,x);
                checkmax(res,y);
                checkmax(res,z);
            }
        }
        int tmp=0;
        FE(it,b) FE(ita,c) if (it->ND!=ita->ND) checkmax(tmp,it->ST+ita->ST);
        FE(it,b) checkmax(tmp,it->ST);
        FE(it,c) checkmax(tmp,it->ST);
        return max(res,a+tmp);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".15", "7..", "402", "..3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 19; verify_case(0, Arg1, maxBeauty(Arg0)); }
	void test_case_1() { string Arr0[] = {"..1", "7..", "567", "24.", "8..", "234"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 36; verify_case(1, Arg1, maxBeauty(Arg0)); }
	void test_case_2() { string Arr0[] = {"...", "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, maxBeauty(Arg0)); }
	void test_case_3() { string Arr0[] = {"16.", "9.8", ".24", "52.", "3.1", "532", "4.4", "111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 28; verify_case(3, Arg1, maxBeauty(Arg0)); }
	void test_case_4() { string Arr0[] = {"..1", "3..", "2..", ".7."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(4, Arg1, maxBeauty(Arg0)); }
	void test_case_5() { string Arr0[] = {"412", "..7", ".58", "7.8", "32.", "6..", "351", "3.9", "985", "...", ".46"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; verify_case(5, Arg1, maxBeauty(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  DengklekMakingChains ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
