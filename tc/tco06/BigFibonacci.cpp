// BEGIN CUT HERE

// END CUT HERE
#line 5 "BigFibonacci.cpp"

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

int mod;

struct matrix{
    int m[2][2];
    matrix(int id=0){
        if (id){
            REP(i, 2) REP(j, 2) m[i][j]=(i==j);
        }else{
            m[0][0]=m[0][1]=m[1][0]=1;
            m[1][1]=0;
        }
    }
    matrix &operator=(const matrix &a){
        memcpy(m, a.m, sizeof(m));
        return *this;

    }
    matrix operator*(const matrix &a)const{
        matrix b;
        REP(i, 2) REP(j, 2) b.m[i][j]=(ll(m[i][0])*a.m[0][j]+ll(m[i][1])*a.m[1][j])%mod;
        return b;
    }

    


};
matrix fast_exp(matrix a, ll p){
    matrix e(1);
    while(p){
        if (p&1) e=e*a;
        a=a*a;
        p>>=1;
    }
    return e;

}
class BigFibonacci {
    public:
        int fibNumber(string index, int M) {
            ll p;
            mod=M;
            istringstream ss(index);
            ss>>p;
            matrix m;

            m=fast_exp(m, p);

            return m.m[1][0];

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arg0 = "7"; int Arg1 = 10; int Arg2 = 3; verify_case(0, Arg2, fibNumber(Arg0, Arg1)); }
        void test_case_1() { string Arg0 = "5"; int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, fibNumber(Arg0, Arg1)); }
        void test_case_2() { string Arg0 = "0"; int Arg1 = 23; int Arg2 = 0; verify_case(2, Arg2, fibNumber(Arg0, Arg1)); }
        void test_case_3() { string Arg0 = "17"; int Arg1 = 2; int Arg2 = 1; verify_case(3, Arg2, fibNumber(Arg0, Arg1)); }
        void test_case_4() { string Arg0 = "54"; int Arg1 = 341890; int Arg2 = 177022; verify_case(4, Arg2, fibNumber(Arg0, Arg1)); }
        void test_case_5() { string Arg0 = "300"; int Arg1 = 77531; int Arg2 = 0; verify_case(5, Arg2, fibNumber(Arg0, Arg1)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    BigFibonacci ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
