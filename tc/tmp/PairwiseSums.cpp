// BEGIN CUT HERE

// END CUT HERE
#line 5 "PairwiseSums.cpp"

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

const int maxn=111;
int u[maxn];

class PairwiseSums {
	public:
	vector <int> reverse(vector <string> sums) {
        vi pl;
        string s; FE(it, sums) s+=" "+*it;
        istringstream ss(s);
        int a; 
        while(ss>>a) pl.pb(a);
        int n=-1;
        FOR(i, 2, 111) if (i*(i-1)/2==pl.size()){n=i; break;}
        if (n==-1) return vi();

        sort(ALL(pl));
        int fd=0;
        vi res;
        REP(i, pl[0]/2+1){

            vi build;
            build.pb(i);
            memset(u, 0, sizeof(u));
            multiset<int> q;
            REP(i, pl.size()){
                if (!q.size() || *q.begin()!=pl[i]){
                    int x=pl[i]-build[0];
                    if (build.size()==n || x<build.back()) goto fail;
                    FOR(j, 1, build.size()) q.insert(build[j]+x);
                    build.pb(x);
                }else q.erase(q.find(pl[i]));
            }
            if (q.size()) goto fail;
            if (fd++) return vi();
            res=build;
fail:;
        }
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"3 5 4 7 6 5"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 1,  2,  3,  4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, reverse(Arg0)); }
	void test_case_1() { string Arr0[] = {"0", "1000", "1000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0,  0,  1000 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, reverse(Arg0)); }
	void test_case_2() { string Arr0[] = {"15 30 45 60"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, reverse(Arg0)); }
	void test_case_3() { string Arr0[] = {"5 6 7 9 10 11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, reverse(Arg0)); }
	void test_case_4() { string Arr0[] = {"910 689 882 565 922 815 457 674 495 653 755 948",
 "631 988 881 523 740 561 719 727 410 767 660 302",
 "519 340 498 603 960 853 495 712 533 691 643 536",
 "178 395 216 374 893 535 752 573 731 428 645 466",
 "624 287 108 266 325 483 304"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 35,  73,  143,  231,  252,  267,  393,  422,  460,  488,  500 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, reverse(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  PairwiseSums ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
