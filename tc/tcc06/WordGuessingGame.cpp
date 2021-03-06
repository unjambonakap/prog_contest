// BEGIN CUT HERE

// END CUT HERE
#line 5 "WordGuessingGame.cpp"

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

const int maxn=9, maxm=18;
const int maxc=26;
const int maxs=110;


int n, m;
int mem[maxn][two(maxm)];
string wl[maxm];
int nmk[maxn][maxc];


int pos;
vs resl[maxs*maxn];

int solve(int p, int mk){
    if (p==n) return mk?-2:0;
    int &r=mem[p][mk];
    if (r!=-1) return r;
    r=-2;
    int a;
    vs tmp;

    REP(i, maxc) if ((a=solve(p+1, mk^nmk[p][i]))!=-2){
        if (r==-2) r=pos++;
        FE(it, resl[a]) tmp.pb(string(1, i+'A')+*it);
        resl[r]=tmp;
    }
    return r;
}

class WordGuessingGame {
	public:
	vector <string> possibleWords(vector <string> even, vector <string> odd) {
        m=even.size();
        REP(i, m) wl[i]=even[i];
        REP(i, odd.size()) wl[m+i]=odd[i];
        m+=odd.size();
        n=wl[0].length();


        memset(nmk, 0, sizeof(nmk));
        REP(i, n) REP(j, maxc) REP(k, m) nmk[i][j]|=two(k)*(wl[k][i]==j+'A');




        pos=0;
        resl[pos++].pb("");

        memset(mem, -1, sizeof(mem));
        int res=solve(0, (two(odd.size())-1)<<even.size());


        if (res==-2) return vs();
        vs a=resl[res];
        sort(ALL(a));

        a.resize(unique(ALL(a))-a.begin());
        return a;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"DAY","MAY","BUY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"SAY","DUE","TEN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"SEE" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, possibleWords(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"QMNA","UQJE"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"HUIF","QMZB","QEHJ","LBJL"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"HBHB", "HBZJ", "HEZL", "LEIB", "LEZF", "LUHB", "LUZJ", "QBIA", "QBNF", "QUNL" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, possibleWords(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NODSN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"MOOTN","CRXXU","SREQR","DEREX","HOYGF","CDLCP","ZTDOC","STEEB"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"CODER" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, possibleWords(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AB","BC","CA"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, possibleWords(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  WordGuessingGame ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
