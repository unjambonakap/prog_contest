// BEGIN CUT HERE

// END CUT HERE
#line 5 "SemifinalAssignment.cpp"

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


const int maxn=26;
const int maxv=1010;
const double eps=1e-13;

class SemifinalAssignment {
	public:
	vector <double> getProbability(vector <int> worst, vector <int> best, int K) {
        int n=worst.size();
        vector<double> res(2*n, 0.);

        REP(v, maxv-1) REP(u, n){
            double p[n], A[n+1][K+1], B[n+1][K+1];
            REP(j, n){
                int k=best[j]-worst[j]+1;
                if (j==u) p[j]=(v>=worst[j] && v<=best[j]?1./k:0.);
                else{
                    int pos=v+(j>u);
                    p[j]=pos>best[j]?0.:min(1., double(best[j]-pos+1)/k);
                }
            }

            memset(A, 0, sizeof(A)); memset(B, 0, sizeof(B));
            A[0][0]=1.;
            B[n][0]=1.;
            REP(i, n) REP(j, i+1) if (j<K){
                if (i!=u) A[i+1][j]+=A[i][j]*(1.-p[i]);
                A[i+1][j+1]+=A[i][j]*p[i];
            }
            REPV(i, n) REP(j, n-i) if (j<K){
                if (i!=u) B[i][j]+=B[i+1][j]*(1.-p[i]);
                B[i][j+1]+=B[i+1][j]*p[i];
            }
            REP(i, n) REP(j, i+1) if (j<K) res[2*i+(j+1)/2%2]+=p[i]*A[i][j]*B[i+1][K-j-1];

        }
        return res;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const vector <double> &Expected, const vector <double> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
    void test_case_0() { int Arr0[] = { 1, 0, 1, 1, 1, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 1, 3, 1, 1, 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; double Arr3[] = {1.0, 0.0, 0.0, 0.75, 0.0, 1.0, 0.75, 0.25, 0.25, 0.0, 0.0, 0.0 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, getProbability(Arg0, Arg1, Arg2)); }
    void test_case_1() { int Arr0[] = { 11, 11, 11, 10 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 12, 12, 12, 11 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; double Arr3[] = {0.875, 0.0, 0.125, 0.625, 0.0, 0.375, 0.0, 0.0 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, getProbability(Arg0, Arg1, Arg2)); }
    void test_case_2() { int Arr0[] = { 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 1000 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; double Arr3[] = {1.0, 0.0 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, getProbability(Arg0, Arg1, Arg2)); }
    void test_case_3() { int Arr0[] = { 1, 2 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 10, 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; double Arr3[] = {1.0, 0.0, 0.0, 1.0 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, getProbability(Arg0, Arg1, Arg2)); }
    void test_case_4() { int Arr0[] = { 1, 1, 1, 2, 2, 2, 3, 3, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 4, 5, 6, 4, 5, 6, 4, 5, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; double Arr3[] = {0.02041666666666667, 0.0, 0.11527777777777776, 0.0, 0.25810185185185186, 0.0, 0.011435185185185187, 0.0, 0.0875925925925926, 0.0, 0.23171296296296295, 0.0, 0.005046296296296296, 0.0, 0.0625, 0.0, 0.2079166666666667, 0.0 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(4, Arg3, getProbability(Arg0, Arg1, Arg2)); }
    void test_case_5() { int Arr0[] = { 1, 2, 5, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 9, 7, 8, 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; double Arr3[] = {0.6527777777777779, 0.0, 0.34722222222222227, 0.21296296296296297, 0.0, 0.9305555555555559, 0.0, 0.856481481481482 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(5, Arg3, getProbability(Arg0, Arg1, Arg2)); }
    void test_case_6() { int Arr0[] = { 3, 317, 25, 447, 96, 333, 361, 103 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 947, 773, 601, 544, 594, 399, 786, 954 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; double Arr3[] = {0.6649201903354007, 0.0, 0.32850646461892563, 0.6163949837246063, 0.006573345045673984, 0.4544927900216218, 0.2180181176461977, 0.7769069045939901, 0.3815407626549669, 0.15220532165978432, 0.6601865341758356, 8.501235695949892E-4, 0.7402545855229999, 0.2430210789578823, 0.0, 0.756128797472523 }; vector <double> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(6, Arg3, getProbability(Arg0, Arg1, Arg2)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    SemifinalAssignment ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
