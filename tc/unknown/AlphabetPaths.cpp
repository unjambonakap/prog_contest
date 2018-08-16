// BEGIN CUT HERE

// END CUT HERE
#line 5 "AlphabetPaths.cpp"

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
typedef vector<string> vs;

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

const int maxp=555;
const int maxn=22;


int n;
map<int,int> A[maxp];
int next[maxp][4];
int type[maxp];
int vx[]={-1,1,0,0};
int vy[]={0,0,1,-1};

int tb[two(18)];
int pos;

void go(int a, int m, int d){
    if (!d) {tb[pos++]=m; return;}
    REP(k, 4){
        int b=next[a][k];
        int x;
        if (b==-1 || (x=type[b])==-1) continue;
        if (!(m&two(x))) go(b, m|two(x), d-1);
    }
}


class AlphabetPaths {
	public:
	long long count(vector <string> lm) {
        int r, c;
        r=lm.size(); c=lm[0].length();
        map<char, int> seen;
        memset(type, -1, sizeof (type)); 
        REP(i, r) REP(j, c) if (lm[i][j]!='.'){
            if (!seen.count(lm[i][j])) seen[lm[i][j]]=pos++;
            type[i*c+j]=seen[lm[i][j]];
        }

        memset(next, -1, sizeof(next));
        REP(i, r) REP(j, c) REP(k, 4) if (type[i*c+j]!=-1){
            int x=i+vx[k], y=j+vy[k];
            if (x>=0 && y>=0 && x<r && y<c && type[x*c+y]!=-1) next[i*c+j][k]=x*c+y;
        }
        int ans=0;
        int MASK=two(21)-1;
        REP(i, r*c) if (type[i]!=-1){
            pos=0;
            go(i, two(type[i]), 10);
            sort(tb, tb+pos);
            REP(j, pos){
                int x=MASK^tb[j]|two(type[i]);
                ans+=upper_bound(tb, tb+pos, x)-lower_bound(tb, tb+pos, x);
            }
        }
        return ans;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"ABCDEABCDEABCDEABCDE", "FZHIXFZHIXFZHIXFZHIX", "KLMNOKLMNOKLMNOKLMNO", "PQRSTPQRSTPQRSTPQRST", "VABCDVABCDVABCDVABCD", "ABCDEABCDEABCDEABCDE", "FZHIXFZHIXFZHIXFZHIX", "KLMNOKLMNOKLMNOKLMNO", "PQRSTPQRSTPQRSTPQRST", "VABCDVABCDVABCDVABCD", "ABCDEABCDEABCDEABCDE", "FZHIXFZHIXFZHIXFZHIX", "KLMNOKLMNOKLMNOKLMNO", "PQRSTPQRSTPQRSTPQRST", "VABCDVABCDVABCDVABCD", "ABCDEABCDEABCDEABCDE", "FZHIXFZHIXFZHIXFZHIX", "KLMNOKLMNOKLMNOKLMNO", "PQRSTPQRSTPQRSTPQRST", "VABCDVABCDVABCDVABCD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, count(Arg0)); }
//	void test_case_0() { string Arr0[] = {"ABCDEFZHIXKLMNOPQRST", "...................V"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {".................VT.",
 "....................",
 "ABCDEFZHIXKLMNOPQRS.",
 "..................S.",
 ".................VT."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"TBCDE.PQRSA", 
 "FZHIXKLMNOV"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 50LL; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"ABCDEF.",
 "V....Z.",
 "T....H.",
 "S....I.",
 "R....X.",
 "KLMNOPQ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  AlphabetPaths ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
