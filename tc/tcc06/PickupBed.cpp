// BEGIN CUT HERE

// END CUT HERE
#line 5 "PickupBed.cpp"

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


const double sqt=sqrt(2.)/2.;
const double maxv=1e3+10;
const double eps=1e-10;


inline int in(double x, double l, double xo, double yo){
    double la=l/(1+sqt*2);
    double d=fabs(x-xo);
    if (d+eps>l/2) return 0;
    if (d-eps<la/2) return yo<=l;
    d-=la/2;
    return yo-eps<l-d && yo+eps>d;

}

class PickupBed {
	public:
	double length(vector <int> _ht) {
        int n=_ht.size();
        vector<double> ht;
        REP(i, n) ht.pb(_ht[i]);

        int order[n];
        REP(i, n) order[i]=i;

        double ans=1e9;
        double pos[n];
        do{
            double res=0.;
            double lp=0.;
            if (order[0]>order[n-1]) goto out;
            REP(i, n){
                double l=ht[order[i]]/2.;
                double H=lp+maxv, T=max(l, lp);
                while(T+eps<H){
                    int ok=1;
                    double M=(H+T)/2.;
                    double xb=l*2/(1+sqt*2);
                    REP(j, i) if (pos[j]+ht[order[j]]/2>M-l){
                        double xa=ht[order[j]]/(1+sqt*2);
                        if (in(pos[j], ht[order[j]], M-l, sqt*xb) || in(pos[j], ht[order[j]], M-l, xb*(sqt+1)) 
                                || in(M, 2*l, pos[j]+ht[order[j]]/2, sqt*xa) || in(M, 2*l, pos[j]+ht[order[j]]/2, xa*(sqt+1))){ok=0; break;}

                    }

                    if (ok) H=M;
                    else T=M;

                }
                pos[i]=T;
                checkmax(res, T+l);
                if (res>=ans) goto out;

                lp=T+l/(1+2*sqt)+eps;


            }
            checkmin(ans, res);

out:;
        }while(next_permutation(order, order+n));
        return ans;

    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { int Arr0[] = {5,5,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 15.0; verify_case(0, Arg1, length(Arg0)); }
    void test_case_0() { int Arr0[] = {50, 5, 5, 1000, 200, 10, 1, 1000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 15.0; verify_case(0, Arg1, length(Arg0)); }
    void test_case_1() { int Arr0[] =  {17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 17.0; verify_case(1, Arg1, length(Arg0)); }
    void test_case_2() { int Arr0[] = {1,10,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 10.0; verify_case(2, Arg1, length(Arg0)); }
    void test_case_3() { int Arr0[] = {2,10,2}
        ; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 10.97056274847714; verify_case(3, Arg1, length(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    PickupBed ___test; 
    ___test.run_test(0); 
} 
// END CUT HERE
