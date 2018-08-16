// BEGIN CUT HERE

// END CUT HERE
#line 5 "FlattenOut.cpp"

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


const int maxn=55;
int dh[maxn];

class FlattenOut {
	public:
	vector<long long> simulateIt(vector<long long> h, long long T) {
        int n=h.size();
        n=50;
        h.resize(50);
        REP(i,n) h[i]=rand()%2?1ll*rand()*rand()%(ll)1e16:-1ll*rand()*rand()%ll(1e16);
        T=1ll*rand()*rand()%ll(1e16);


        out(h);

        while(T){
            int fd=0, fd2=0;
            memset(dh,0,sizeof(dh));
            REP(i,n){
                if (!h[i] && h[(i+n-1)%n]>0) fd=1;
                else if (h[i]>0) --dh[i], ++dh[(i+1)%n], fd2=1;
            }
            if (!fd2) break;
            if (fd){ REP(i,n) h[i]+=dh[i]; --T; continue;}
            ll nstep=T;
            REP(i,n) if (dh[i]) nstep=min(nstep,abs(h[i]));
            REP(i,n) h[i]+=dh[i]*nstep;
            T-=nstep;
        }
        puts("");
        out(h);
        puts("");
        return h;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector<long long> &Expected, const vector<long long> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long Arr0[] = {1, 3, -4, -4, 2, 0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; long Arr2[] = {0, 3, -3, -4, 1, 1 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, simulateIt(Arg0, Arg1)); }
	void test_case_1() { long Arr0[] = {1, 3, -4, -4, 2, 0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; long Arr2[] = {1, 2, -2, -4, 0, 1 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, simulateIt(Arg0, Arg1)); }
	void test_case_2() { long long Arr0[] = {9999999999999999ll, -9999999999999999ll, 9999999999999999ll, -9999999999999999ll}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 9999999999999999LL; long long Arr2[] = {0, 0, 0, 0 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, simulateIt(Arg0, Arg1)); }
	void test_case_3() { long Arr0[] = {0, 0, 0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; long Arr2[] = {0, 0, 0 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, simulateIt(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  FlattenOut ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
