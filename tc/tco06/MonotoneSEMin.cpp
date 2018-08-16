// BEGIN CUT HERE

// END CUT HERE
#line 5 "MonotoneSEMin.cpp"

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


const int maxn=2504;
const double inf=1e5;

double dp[maxn][maxn];
pair<double, double> ta[maxn];//average, cost
pair<double, int> tb[maxn];//next average, end
int b[maxn];

class MonotoneSEMin {
	public:
        double proc(int x, int y){ return double(b[y+1]-b[x])/(y-x+1); }
        double cost(int x, int y){
            int l=b[y+1]-b[x];
            return l*(1-double(l)/(y-x+1));
        }

        double min(vector <string> bits) {
            string s;
            FE(it, bits) s+=*it;

            int n=s.size();
            b[0]=0;
            REP(i, n) b[i+1]=b[i]+(s[i]=='1');
        
            REP(i, n+1) REP(j, n+1) dp[i][j]=inf;
            REP(i, n) dp[0][i]=cost(0, i);

            REP(i, n){
                int na=0, nb=0;
                REP(j, i+1) ta[na++]=MP(proc(j, i), dp[j][i]);
                FOR(j, i+1, n-1) tb[nb++]=MP(proc(i+1, j), j);
                sort(ta, ta+na); sort(tb, tb+nb);
                int pos=0;
                double best=inf;
                REP(j, nb){
                    while(pos<na && ta[pos].ST<tb[j].ST){
                        checkmin(best, ta[pos].ND);
                        ++pos;
                    }
                    checkmin(dp[i+1][tb[j].ND], best+cost(i+1, tb[j].ND));
                }
            }
            double res=inf;
            REP(i, n) checkmin(res, dp[i][n-1]);
            return res;


        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {"10001110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.5; verify_case(0, Arg1, min(Arg0)); }
        void test_case_1() { string Arr0[] = {"00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(1, Arg1, min(Arg0)); }
        void test_case_2() { string Arr0[] = {"11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(2, Arg1, min(Arg0)); }
        void test_case_3() { string Arr0[] = {"1010100101010101001010101001",
            "0101010100100010010001010101",
            "1110110101001011010111011011",
            "1010111101110110111000111100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 26.244842801985662; verify_case(3, Arg1, min(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    MonotoneSEMin ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE


