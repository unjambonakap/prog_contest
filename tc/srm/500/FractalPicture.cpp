// BEGIN CUT HERE

// END CUT HERE
#line 5 "FractalPicture.cpp"

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
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


const double eps=1e-12;
const int maxn=500;

class FractalPicture {
    public:
        double x1,x2,y1,y2;

        double doity(double x, double ya, double yb, int d){
            double u=fabs(ya-yb);
            if (u<eps) return 0.;
            if (y1-eps>=max(ya,yb) || y2+eps<=min(ya,yb) || x1-eps>=x+u/3 || x2+eps<=x-u/3) return 0;
            if (y1<=min(ya,yb) && y2>=max(ya,yb) && x-u/3>=x1 && x+u/3<=x2) return fabs(yb-ya)*(maxn-d+0.5)*2./3;
            
            
            double yc=(ya+2*yb)/3.;
            double res=0.;
            if (x>=x1-eps && x<=x2+eps) res+=max(0.,min(y2,max(ya,yc))-max(y1,min(ya,yc)));
            
            res+=doity(x,yc,yb,d+1)+doitx(yc,x,x-u/3,d+1)+doitx(yc,x,x+u/3,d+1);
            return res;
        }


        double doitx(double y, double xa, double xb, int d){
            double u=fabs(xa-xb);
            if (u<eps) return 0.;
            if (x1-eps>=max(xa,xb) || x2+eps<=min(xa,xb) || y1-eps>=y+u/2 || y2+eps<=y-u/2) return 0;
            if (x1<=min(xa,xb) && x2>=max(xa,xb) && y-u/3>=y1 && y+u/3<=y2) return fabs(xb-xa)*(maxn-d+0.5)*2./3;
            double xc=(xa+2*xb)/3.;
            double res=0.;
            if (y>=y1-eps && y<=y2+eps) res+=max(0.,min(x2,max(xa,xc))-max(x1,min(xa,xc)));
            res+=doitx(y,xc,xb,d+1)+doity(xc,y,y-u/3,d+1)+doity(xc,y,y+u/3,d+1);
            return res;

        }
        double getLength(int _x1, int _y1, int _x2, int _y2) {
            x1=_x1; y1=_y1; x2=_x2; y2=_y2;

            return doity(0, 0, 81, 0);
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { int Arg0 = -1; int Arg1 = 0; int Arg2 = 1; int Arg3 = 53; double Arg4 = 53.0; verify_case(0, Arg4, getLength(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_0() { int Arg0 = 0; int Arg1 = 80; int Arg2 = 1; int Arg3 = 81; double Arg4 = 53.0; verify_case(0, Arg4, getLength(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 10; int Arg3 = 10; double Arg4 = 0.0; verify_case(1, Arg4, getLength(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_2() { int Arg0 = -10; int Arg1 = 54; int Arg2 = 10; int Arg3 = 55; double Arg4 = 21.0; verify_case(2, Arg4, getLength(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_3() { int Arg0 = 14; int Arg1 = 45; int Arg2 = 22; int Arg3 = 54; double Arg4 = 2999.0; verify_case(3, Arg4, getLength(Arg0, Arg1, Arg2, Arg3)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    FractalPicture ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
