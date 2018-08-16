// BEGIN CUT HERE

// END CUT HERE
#line 5 "FrogAndFly.cpp"

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
vector<pii> ha, hb;
double xa[maxn], xb[maxn];
vector<double> yx;
int na;
double area[maxn];
int hwall, dfrog, dfly;

double f(double yo){
    double y=yo+(hwall-yo)*(dfrog+dfly)/dfrog;
    int a=upper_bound(ALL(yx), y)-yx.begin();
    if (a==na) return 0.;
    if (a==0) return area[0];
    double xu=xa[a]+(y-yx[a])*(xa[a-1]-xa[a])/(yx[a-1]-yx[a]);
    double xv=xb[a]+(y-yx[a])*(xb[a-1]-xb[a])/(yx[a-1]-yx[a]);
    return area[a]+(yx[a]-y)*(xv+xb[a]-xu-xa[a])/2.;

}


class FrogAndFly {
	public:
	double visibility(int _hwall, int _dfrog, int _dfly, int ylow, int yhigh, vector <int> xw, vector <int> yw) {
        hwall=_hwall; dfrog=_dfrog; dfly=_dfly;

        ha.clear(); hb.clear();
        int yh=max_element(ALL(yw))-yw.begin();
        int yl=min_element(ALL(yw))-yw.begin();
        int nx=yw.size();
        for (int i=yl; i%nx!=yh; ++i) ha.pb(MP(xw[i%nx], yw[i%nx])); ha.pb(MP(xw[yh], yw[yh]));
        if (ha[1].ND==ha[0].ND) ha.erase(ha.begin());
        if (ha.back().ND==ha[ha.size()-2].ND) ha.pop_back();
        for (int i=yl+nx; i%nx!=yh; --i) hb.pb(MP(xw[i%nx], yw[i%nx])); hb.pb(MP(xw[yh], yw[yh]));
        if (hb[1].ND==hb[0].ND) hb.erase(hb.begin());
        if (hb.back().ND==hb[hb.size()-2].ND) hb.pop_back();
        yx.clear();
        FE(it, ha) yx.pb(it->ND);
        FE(it, hb) yx.pb(it->ND);
        sort(ALL(yx));

        yx.resize(unique(ALL(yx))-yx.begin());
        na=yx.size();

        int p=0;
        REP(i, na){
            if (p+1<ha.size() && yx[i]==ha[p+1].ND) ++p;
            if (yx[i]==ha[p].ND) xa[i]=ha[p].ST;
            else xa[i]=ha[p].ST+(ha[p+1].ST-ha[p].ST)*(yx[i]-ha[p].ND)/double(ha[p+1].ND-ha[p].ND);
            
        }
        p=0;
        REP(i, na){
            if (p+1<hb.size() && yx[i]==hb[p+1].ND) ++p;
            if (yx[i]==hb[p].ND) xb[i]=hb[p].ST;
            else xb[i]=hb[p].ST+(hb[p+1].ST-hb[p].ST)*(yx[i]-hb[p].ND)/double(hb[p+1].ND-hb[p].ND);
            
        }
        if (xa[1]>xb[1] || xa[0]>xb[0]) REP(i, na) swap(xa[i], xb[i]);

        double ans=0.;
        area[na-1]=0.;
        for (int i=na-2; i>=0; --i) area[i]=area[i+1]+(yx[i+1]-yx[i])*(xb[i]+xb[i+1]-xa[i]-xa[i+1])/2.;

        int nstep=1e6;
        double step=1.*(yhigh-ylow)/nstep;
        for (int i=0; i<nstep; ++i){
            double y=ylow+step*i;
            ans+=step*(f(y)+4*f(y+step/2)+f(y+step))/6;
        }
		

        return ans/area[0]/(yhigh-ylow);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 10; int Arg3 = 5; int Arg4 = 15; int Arr5[] = {5, 5, 15, 15}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {5, 15, 15, 5}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); double Arg7 = 0.5; verify_case(0, Arg7, visibility(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { int Arg0 = 14; int Arg1 = 10; int Arg2 = 10; int Arg3 = 5; int Arg4 = 15; int Arr5[] = {5, 5, 15, 15}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {5, 15, 15, 5}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); double Arg7 = 0.02; verify_case(1, Arg7, visibility(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 5; int Arg2 = 10; int Arg3 = 5; int Arg4 = 15; int Arr5[] = {10, 20, 15}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {5, 5, 15}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); double Arg7 = 0.4166666666666665; verify_case(2, Arg7, visibility(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { int Arg0 = 0; int Arg1 = 1; int Arg2 = 20; int Arg3 = 10; int Arg4 = 100; int Arr5[] = {0, 10, 20, 30, 15}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {20, 10, 10, 20, 40}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); double Arg7 = 1.0; verify_case(3, Arg7, visibility(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { int Arg0 = 100; int Arg1 = 30; int Arg2 = 10; int Arg3 = 20; int Arg4 = 40; int Arr5[] = {10, 20, 30, 20}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {20, 10, 20, 30}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); double Arg7 = 0.0; verify_case(4, Arg7, visibility(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  FrogAndFly ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
