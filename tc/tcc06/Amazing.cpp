// BEGIN CUT HERE

// END CUT HERE
#line 5 "Amazing.cpp"

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

const int maxn=10;
const int maxc=1e5;

int n, m, na, nb;
double f;

int cost[maxn][maxn];
double ca[maxc], cb[maxc];
double fv[maxn+1];

void reca(int p, int r, double v){
    if (r==0){ca[na++]=v; return;}
    REP(i, n) reca(i, r-1, v+cost[i][p]*fv[r-1]);
}
void recb(int p, int r, double v){
    if (r==m){cb[nb++]=v; return;}
    REP(i, n) recb(i, r+1, v+cost[p][i]*fv[r]);
}

class Amazing {
	public:
	double totalE(double factor, int numTrips, vector <string> effort) {
        n=effort.size();
        m=numTrips;


        fv[0]=1.;
        REP(i, m) fv[i+1]=fv[i]*factor;
        double ans=1e10;
        double dest=1000.;

        REP(i, n){
            istringstream ss(effort[i]);
            REP(j, n) ss>>cost[i][j];
        }
        //REP(i, n) out(cost[i], n);
        //printf("\n");

        REP(i, n){
            na=nb=0;
            reca(i, m/2, 0);
            recb(i, m/2, 0);

            sort(ca, ca+na);
            sort(cb, cb+nb);
            //out(ca, na);
            //out(cb, nb);
            //printf("\n");
            REP(i, na){
                int p=lower_bound(cb, cb+nb, dest-ca[i])-cb;
                if (p<nb) checkmin(ans, cb[p]+ca[i]-dest);
                if (p) checkmin(ans, dest-cb[p-1]-ca[i]);
            }
        }
        return ans;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { double Arg0 = 1.0; int Arg1 = 2; string Arr2[] = {"1000 300 700","200 0 901","35 100 0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 1.0; verify_case(0, Arg3, totalE(Arg0, Arg1, Arg2)); }
	void test_case_1() { double Arg0 = 2.0; int Arg1 = 2; string Arr2[] = {"1000 300 700","200 0 901","35 100 0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 29.0; verify_case(1, Arg3, totalE(Arg0, Arg1, Arg2)); }
	void test_case_2() { double Arg0 = 1.3; int Arg1 = 10; string Arr2[] = {"1000 300 700","200 0 901","35 100 0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 2.8999999999998636; verify_case(2, Arg3, totalE(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Amazing ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
