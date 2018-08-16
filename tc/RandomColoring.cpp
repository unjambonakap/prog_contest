// BEGIN CUT HERE

// END CUT HERE
#line 5 "RandomColoring.cpp"

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


const int maxv=55;
double P[2][maxv][maxv][maxv], P2[2][maxv][maxv][maxv];
int mr, mg, mb;

void add(double px, int p, int r, int g, int b, int d, int sgn){
    int rl=r-d, gl=g-d, bl=b-d;
    int rh=r+d, gh=g+d, bh=b+d;
    checkmax(rl,0); checkmax(gl,0); checkmax(bl,0);
    checkmin(rh,mr); checkmin(gh,mg); checkmin(bh,mb);
    double x=(rh-rl+1)*(gh-gl+1)*(bh-bl+1);
    px/=x;
    P[p][rl][gl][bl]+=sgn*px;
    P2[p][rh][gh][bh]-=sgn*px;
}

class RandomColoring {
	public:
	double getProbability(int N, int _mr, int _mg, int _mb, int sr, int sg, int sb, int d1, int d2) {
        mr=_mr; mg=_mg; mb=_mb;
        memset(P,0,sizeof(P));
        memset(P2,0,sizeof(P2));
        P[0][sr][sg][sb]=1.;
        int p=0, np=1;
        double res=0.;
        REP(i,N){
            memset(P[np],0,sizeof(P[np]));
            memset(P2[np],0,sizeof(P2[np]));
            REP(r,mr) REP(g,mg) REP(b,mb){
                double px=P[p][r][g][b];
                //if (px<=0) continue;
                printf("%d >> %d %lf\n", i, r, px);
                assert(px>=0);
                if (i==N-1){
                    int dr=abs(sr-r), dg=abs(sg-g), db=abs(sb-b);
                    int fa=dr<=d2&&dg<=d2&&db<=d2;
                    int fb=dr<=d1&&dg<=d1&&db<=d1;
                    if (fa&&!fb) res+=px;
                    
                }else add(px,np,r,g,b,d2,1), add(px,np,r,g,b,d1,-1);

                px-=P2[p][r][g][b];
                assert(px>=0);

                P[p][r+1][g][b]+=px;
                P[p][r][g+1][b]+=px;
                P[p][r][g][b+1]+=px;

                P[p][r+1][g+1][b]-=px;
                P[p][r+1][g][b+1]-=px;
                P[p][r][g+1][b+1]-=px;

                P[p][r+1][g+1][b+1]-=2*px;
            }
            p=np; np^=1;
        }
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 5; int Arg2 = 1; int Arg3 = 1; int Arg4 = 2; int Arg5 = 0; int Arg6 = 0; int Arg7 = 0; int Arg8 = 1; double Arg9 = 0.0; verify_case(0, Arg9, getProbability(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 5; int Arg2 = 1; int Arg3 = 1; int Arg4 = 2; int Arg5 = 0; int Arg6 = 0; int Arg7 = 0; int Arg8 = 1; double Arg9 = 0.22222222222222227; verify_case(1, Arg9, getProbability(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_2() { int Arg0 = 7; int Arg1 = 4; int Arg2 = 2; int Arg3 = 2; int Arg4 = 0; int Arg5 = 0; int Arg6 = 0; int Arg7 = 3; int Arg8 = 3; double Arg9 = 1.0; verify_case(2, Arg9, getProbability(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 7; int Arg2 = 8; int Arg3 = 9; int Arg4 = 1; int Arg5 = 2; int Arg6 = 3; int Arg7 = 0; int Arg8 = 10; double Arg9 = 0.0; verify_case(3, Arg9, getProbability(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_4() { int Arg0 = 10; int Arg1 = 7; int Arg2 = 8; int Arg3 = 9; int Arg4 = 1; int Arg5 = 2; int Arg6 = 3; int Arg7 = 4; int Arg8 = 10; double Arg9 = 0.37826245943967396; verify_case(4, Arg9, getProbability(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_5() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 2; int Arg3 = 2; int Arg4 = 1; int Arg5 = 0; int Arg6 = 0; int Arg7 = 1; int Arg8 = 2; double Arg9 = 0.09090909090909148; verify_case(5, Arg9, getProbability(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  RandomColoring ___test; 
        ___test.run_test(1); 
        } 
// END CUT HERE
