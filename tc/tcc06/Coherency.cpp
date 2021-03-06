// BEGIN CUT HERE

// END CUT HERE
#line 5 "Coherency.cpp"

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

int m;
int checkit(multiset<int> &s){
    if (s.empty()) return 1;
    int p=*s.begin();
    FE(it, s){
        if (*it-p>m) return 0;
        p=*it;
    }
    return 1;
}
int checkitb(multiset<int> &s){
    if (s.empty()) return 1;
    int p=*--s.end();
    FEV(it, s){
        if (p-*it>m) return 0;
        p=*it;
    }
    return 1;
}

class Coherency {
	public:
	int starters(vector <int> t, int _m) {
        m=_m;
        multiset<int> tb(ALL(t));
        set<int> can;
        int n=tb.size();
        if (!checkit(tb)) return 0;

        int lb=*tb.begin(), ub=*(--tb.end());
        tb.insert(ub);
        tb.insert(lb);


        FE(it, tb){
            int p=*it;
            multiset<int> ta=tb;
            ta.erase(ta.find(p));
            int fd=1;
            while(p!=lb){
                multiset<int>::iterator ita=ta.lower_bound(p-m);
                assert(ita!=ta.end());
                p=*ita;
                ta.erase(ita);
            }
            if (fd && checkit(ta)){can.insert(*it); continue;}

            p=*it;
            ta=tb;
            ta.erase(ta.find(p));
            fd=1;
            while(p!=ub){
                multiset<int>::iterator ita=--ta.upper_bound(p+m);
                assert(ita!=ta.end());
                p=*ita;
                ta.erase(ita);
            }
            if (fd && checkitb(ta)){ can.insert(*it); continue;}
        }


        return can.size();
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] =  {8,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 0; verify_case(0, Arg2, starters(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {8,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 2; verify_case(1, Arg2, starters(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {6,1,11,5,7,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 2; verify_case(2, Arg2, starters(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Coherency ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
