// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxCardGame.cpp"

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

const int maxm=55;
const int maxn=2*maxm+2;
const int maxe=2*(maxm*maxm+2*maxm);
const double maxc=5000;
const double eps=1e-10;


class FoxCardGame {
    public:
        double theMaxProportion(vector <double> pa, vector <double> pb, int k) {
            int na=pa.size();
            n=2*na+2;

            double T=1, H=110;
            REP(step,40){
                double M=(T+H)/2;
                memset(last,-1,sizeof(last));
                ne=0;
                REP(i,na) adde(0,2+i,1,0.), adde(2+na+i,1,1,0.);
                REP(i,na) REP(j,na){
                    double x=maxc-(max(pa[i]*pb[j],pa[i]+pb[j])-M*min(pa[i]*pb[j],pa[i]+pb[j]));
                    adde(2+i,2+j+na,1,x);
                }


                double fc=0.;
                memset(P,0,sizeof(P));
                REP(i,k) fc+=augment();
                
                if (fc<=k*maxc) T=M;
                else H=M;
            }
            return T;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { double Arr0[] = {1, 2, 3}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {4, 5, 6}; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; double Arg3 = 1.7692307692307692; verify_case(0, Arg3, theMaxProportion(Arg0, Arg1, Arg2)); }
        void test_case_0() { double Arr0[] = {1.50410885458, 1.49519090735, 1.50106967594, 1.50370894488, 1.50080318316, 1.49839086469, 1.50160363731, 1.50453353919, 1.49530758592, 1.50002773849, 1.49930720083, 1.49671180095, 1.50376113462, 1.49745694165, 1.49540898632, 1.50176353155, 1.49642825279, 1.49997869675, 1.50263731689, 1.50265881965, 1.50184401, 1.49888736709, 1.50412743563, 1.49939355916, 1.50394294484, 1.50242827796, 1.50284011447, 1.50024784063, 1.49911813853, 1.49532895292, 1.50340389927, 1.49576741664, 1.4951046404, 1.50294121667, 1.50454639365, 1.49842824562, 1.49792383257, 1.49703472396, 1.49998130892, 1.5038793842, 1.49943551773, 1.49822243397, 1.5043661987, 1.50105931156, 1.49807267295, 1.50170592881, 1.50244009553, 1.49924212846, 1.49887323791, 1.50386876455}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {1.50330583528, 1.50068839626, 1.49600905325, 1.50430503803, 1.50149131856, 1.49990973087, 1.50048262237, 1.4965726853, 1.50232543412, 1.50047952324, 1.5019184116, 1.49874795141, 1.50169787967, 1.50233446054, 1.49546897409, 1.50027370035, 1.49729737355, 1.50111162764, 1.50022706042, 1.49682122352, 1.50352435035, 1.5000401779, 1.50256777655, 1.49584401804, 1.50477285333, 1.50398966373, 1.49722248314, 1.49948288559, 1.49820506759, 1.49677025766, 1.50264007495, 1.5040274911, 1.50398252091, 1.49800542301, 1.49929528863, 1.49562594522, 1.4983092459, 1.49818219846, 1.50009780464, 1.49620014765, 1.49731982727, 1.4958678811, 1.49861266839, 1.50056924447, 1.49729205129, 1.50371990579, 1.49829096376, 1.49743903689, 1.49639768397, 1.49836868967}; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 50; double Arg3 = 1.7692307692307692; verify_case(0, Arg3, theMaxProportion(Arg0, Arg1, Arg2)); }
        void test_case_1() { double Arr0[] = {1.234, 5.678, 9.012, 3.456, 7.89}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {2.345, 6.789, 9.876, 5.432, 1.012}; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; double Arg3 = 4.159424420079523; verify_case(1, Arg3, theMaxProportion(Arg0, Arg1, Arg2)); }
        void test_case_2() { double Arr0[] = {1, 1.1, 1.2, 1.3, 1.4, 1.5}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {5, 10, 15, 20, 25, 30}; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; double Arg3 = 1.3972602739726028; verify_case(2, Arg3, theMaxProportion(Arg0, Arg1, Arg2)); }
        void test_case_3() { double Arr0[] = {85.302, 92.798, 76.813, 37.994, 36.737, 98.659}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {13.352, 7.3094, 54.761, 8.2706, 63.223, 37.486}; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; double Arg3 = 33.58603889836175; verify_case(3, Arg3, theMaxProportion(Arg0, Arg1, Arg2)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    FoxCardGame ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
