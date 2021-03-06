// BEGIN CUT HERE

// END CUT HERE
#line 5 "VectorCostSequence.cpp"

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


const int maxp=18;


class VectorCostSequence {
	public:
	int getSmallest(int d) {
        int res=INT_MAX;
        int hb=0;
        if (d<=2) return d;

        while(two(hb)<d) ++hb;
        checkmin(hb, maxp);


//        printf("<< %d\n", hb);
        REP(i, two(hb)+1) if (i){

            int k=hb;
            while(!(two(k)&i)) --k;
            int ans, nd;
            nd=d;
            ans=two(k)+1;
            nd-=two(k+1)-1+two(k)+1;

            REP(j, k) if (i&two(j)){
                ans+=2;
                nd-=two(j)+2;

            }

            int na;
            if (nd<0) goto out;
            na=nd/(two(k)+2);
            nd-=(two(k)+2)*na;
            ans+=na*2;
            ans+=nd;



            checkmin(res, ans);
out:;
        }
        return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; verify_case(0, Arg1, getSmallest(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; verify_case(1, Arg1, getSmallest(Arg0)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 3; verify_case(2, Arg1, getSmallest(Arg0)); }
	void test_case_3() { int Arg0 = 9; int Arg1 = 5; verify_case(3, Arg1, getSmallest(Arg0)); }
	void test_case_4() { int Arg0 = 24; int Arg1 = 9; verify_case(4, Arg1, getSmallest(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  VectorCostSequence ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
