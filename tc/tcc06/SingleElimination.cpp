// BEGIN CUT HERE

// END CUT HERE
#line 5 "SingleElimination.cpp"

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

const int maxn=8;
double px[maxn][maxn];
int tb[maxn];
int team;
int n;

double doit(){
    double state[2][n];
    int p=0, np=1;
    REP(i, n) state[p][i]=1.;
    for (int k=1; k<=n>>1; k<<=1){
        memset(state[np], 0, sizeof(double)*n);
        for (int i=0; i<n; i+=2*k) FOR(j, i, i+k-1){
            FOR(l, i+k, i+2*k-1) state[np][j]+=state[p][j]*state[p][l]*px[tb[j]][tb[l]], state[np][l]+=state[p][j]*state[p][l]*px[tb[l]][tb[j]];
        }
        p=np; np^=1;
    }
    return state[p][0];
}


class SingleElimination {
	public:
	double bestChance(vector <string> chances, int team) {
        n=chances.size();
        REP(i, n){
            istringstream ss(chances[i]);
            REP(j, n){ int a; ss>>a; px[i][j]=a/100.;}
        }

        REP(i, n) tb[i]=i;
        swap(tb[0], tb[team-1]);
        sort(tb+1, tb+n);
        double ans=0.;
        do checkmax(ans, doit());
        while(next_permutation(tb+1, tb+n));
        return ans;
            
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0 79 45 44 7 73 25 11 35 34 29 98 81 69 61 90", "21 0 86 22 86 6 54 10 80 67 75 67 38 91 52 30", "55 14 0 77 97 93 76 85 25 74 20 20 50 80 49 70", "56 78 23 0 78 24 59 37 83 70 11 61 69 71 96 45", "93 14 3 22 0 84 48 49 61 98 48 69 56 3 4 74", "27 94 7 76 16 0 33 76 84 45 25 49 12 43 46 61", "75 46 24 41 52 67 0 44 17 38 26 94 12 95 89 98", "89 90 15 63 51 24 56 0 42 96 80 35 52 2 23 81", "65 20 75 17 39 16 83 58 0 24 69 46 68 9 100 89", "66 33 26 30 2 55 62 4 76 0 81 97 71 50 69 24", "71 25 80 89 52 75 74 20 31 19 0 80 41 64 40 52", "2 33 80 39 31 51 6 65 54 3 20 0 90 97 85 1", "19 62 50 31 44 88 88 48 32 29 59 10 0 94 98 97", "31 9 20 29 97 57 5 98 91 50 36 3 6 0 27 54", "39 48 51 4 96 54 11 77 0 31 60 15 2 73 0 90", "10 70 30 55 26 39 2 19 11 76 48 99 3 46 10 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 0.45; verify_case(0, Arg2, bestChance(Arg0, Arg1)); }
	//void test_case_0() { string Arr0[] = {"0 90 0 100", "10 0 50 100", "100 50 0 100", "0 0 0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 0.45; verify_case(0, Arg2, bestChance(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0 90 0 100", "10 0 50 100", "100 50 0 100", "0 0 0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; double Arg2 = 0.9500000000000001; verify_case(1, Arg2, bestChance(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = { "0" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 1.0; verify_case(2, Arg2, bestChance(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = { "0 50 50 50 50 50 50 50",
  "50 0 50 50 50 50 50 50",
  "50 50 0 50 50 50 50 50",
  "50 50 50 0 50 50 50 50",
  "50 50 50 50 0 50 50 50",
  "50 50 50 50 50 0 50 50",
  "50 50 50 50 50 50 0 50",
  "50 50 50 50 50 50 50 0" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; double Arg2 = 0.125; verify_case(3, Arg2, bestChance(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SingleElimination ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
