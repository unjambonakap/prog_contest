// BEGIN CUT HERE

// END CUT HERE
#line 5 "TreeReconstruct.cpp"

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


const int maxn=55;
int n;
int m[maxn][maxn];

class TreeReconstruct {
	public:
	int reconstruct(vector <string> ga, vector <string> gb) {
        n=ga.size();
        REP(i, n) REP(j, n) istringstream(string(1, ga[i][j])+gb[i][j])>>hex>>m[i][j];
        
        REP(i, n) REP(j, n) REP(k, n) if (m[i][j]>m[i][k]+m[k][j]) return -1;
        set<vi> res;
        REP(i, n){
            res.insert(vi(m[i], m[i]+n));

        }

        REP(a, n) REP(b, a) REP(c, b){
            int da, db, dc, ab, ac, bc;
            ab=m[a][b]; ac=m[a][c]; bc=m[b][c];
            int t;
            t=ab+ac-bc; if (t%2) return -1; da=t/2;
            t=ab+bc-ac; if (t%2) return -1; db=t/2;
            t=ac+bc-ab; if (t%2) return -1; dc=t/2;
            vi tmp(n, 0);
            tmp[a]=da; tmp[b]=db; tmp[c]=dc;
            REP(i, n) if (i!=a && i!=b && i!=c){
                int v[3];
                v[0]=m[i][a]-da; v[1]=m[i][b]-db; v[2]=m[i][c]-dc;
                sort(v, v+3);
                if (v[2]<0 || v[2]!=v[1]) return -1;
                tmp[i]=v[2];
            }
            res.insert(tmp);



        }
        return res.size();

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0000",
 "0000",
 "0000",
 "0000"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0444",
 "4044",
 "4404",
 "4440"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(0, Arg2, reconstruct(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0000",
 "0000",
 "0000",
 "0000"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0233",
 "2033",
 "3302",
 "3320"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(1, Arg2, reconstruct(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"00001",
 "00001",
 "00011",
 "00100",
 "11100"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"066C6",
 "60CA4",
 "6C02C",
 "CA20A",
 "64CA0"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(2, Arg2, reconstruct(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"00000",
 "00000",
 "00001",
 "00000",
 "00100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"06839",
 "60E7B",
 "8E0B1",
 "37B0A",
 "9B1A0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(3, Arg2, reconstruct(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"023825",
 "202704",
 "320633",
 "876084",
 "203805",
 "543450"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0198AA",
 "10ED9F",
 "9E0D7F",
 "8DD06E",
 "A97608",
 "AFFE80"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(4, Arg2, reconstruct(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"0000",
 "0000",
 "0000",
 "0000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0121",
 "1012",
 "2101",
 "1210"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(5, Arg2, reconstruct(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  TreeReconstruct ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
