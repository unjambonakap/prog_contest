// BEGIN CUT HERE

// END CUT HERE
#line 5 "HandlesSpelling.cpp"

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

const int maxn=1007;
const int maxm=57;
int n, m;
string s;
vs tb;

int dp[maxn];
int subs[maxn][maxm];
int dfs(int p){
	int &mx=dp[p];
	if (mx!=-1)return mx;
	mx=0;
	REP(i, m) if (subs[p][i]) checkmax(mx, (int)tb[i].size()+dfs(p+tb[i].size()));
	return mx;
}

int solve(int a, int b){
	if (a==b) return 0;
	int &r=dp[a];
	if (r!=-1) return r;
	r=1+solve(a+1, b);
	REP(i, m) if (a+tb[i].size()<=b && subs[a][i]) checkmin(r, solve(a+tb[i].size(), b));
	return r;

}

class HandlesSpelling {
	public:
	int spellIt(vector <string> parts, vector <string> _tb) {
		s="";
		FE(it, parts) s+=*it;
		n=s.length();
		tb=_tb; 
		m=tb.size();
		memset(subs, 0, sizeof(subs));
		REP(j, m) REP(i, n-tb[j].length()+1) if (s.substr(i, tb[j].length())==tb[j]) subs[i][j]=1;

		vi pos; int best=-1;
		REP(i, n){
			memset(dp, -1, sizeof(dp));
			int tmp=dfs(i);
			if (best<tmp) pos=vi(), best=tmp;
			if (best==tmp) pos.pb(i);
		}
		if (best==-1) return -n;
		int res=INT_MIN;
		int a, b;


		FE(it, pos){
			memset(dp, -1, sizeof(dp));
			a=solve(0, *it);

			memset(dp, -1, sizeof(dp));
			b=solve(*it+best, n);
			checkmax(res, best*best-a-b);
		}

		return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"MLXYDTBAAONTWTFNLMHZHJSSHTQCZUBTWOADBIGWFHQNCOXJUX", "PLFAPCPQENPSDWGBVNUAGICTGMWMXEYCBZOPWNPOVOSHAOCAEQ", "ODESSVYSFCVEOWXACVFCANVLWPZOOSKOXIFQVOQCJIVKFSTWSK", "SZGAIBZBQQAAQDERSCOISGDKJGXOYEMSUHBDKEAWSUSRKSWKOY", "QLHJSLTKHFCQTACQYDSIWVTRKIIZQGCKVWHKGVIEIEZFWMILQN", "FNWZPSGVBQAOKBIJPJIZXOSQSJDJGKHALXEGZSCNVZLOYPOXDG", "KMKMTEJCBIKUSXWKWJRAVKUQRYHNHJXHVDLMODUUFCTNSAOMFB", "EUYHSDOTFQCWQSRZLCSEGKDASNLACRODWGIQWSQVSGCBYUJIQX", "SCFOMRTYBNLZEEJXVQXYQPBLDLIHYFOPNQSLJMMSDBTHDJODJM", "ZFUIWEJVQAWTGRFCDJECXGMXMVJJZTNNYBOPEABNODGLWOOFQV", "TVMHRKQTSNAMWCUEPTNRSATBNLXPZCMHNYIRFYUFAYAJYHMQQD", "TQFSDUMDTDNYBFPFMBIPGZVSHRCVHLZWPDDRGLFBSEIQTKMUQD", "GGSVLIRUXHRRVCLIAGDMQPJRFWVDGVYFYBZDQJPPHUUEKIEZUA", "OSUWQVPDEGEEPPPRJQCCNIHTGQZMCGCVBHQZVYGHQIREBFVQTO", "IOAEMRJYDFXNDNXWWOBVBBPBPCYPPUIGJSCJETYGMFSFNFFVVI", "XIVZTZNJNQEKHISTVSUYWUHGDGHDTEGBAFIMIKXBKUELWRBDSI", "XNDINIEZIUVNTBJGVPVUSRGWYPTDQBBFXYLQVCEBIXBMFKNOCX", "BJTKPJLOWHEBWMUEHULSTAGBPHNMBLUVSPQDZFZFIDOOYDRMHW", "TDDULLGMFO"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AONTWTFNLMHZHJSSHTQCZUBT", "BAAONTWTFNLMHZHJSSHTQCZUBTWOADBIGWFHQN", "DJMZFUIWEJVQAWTGRFCDJECXGMXMVJJZTNNYBOPEABNODGLW", "BTWOADBIGWFHQN", "TBAAONTWTFNLMHZHJSSHTQCZUBTWOADBIGWFHQN", "HZHJSSHTQCZU", "TFNLMHZHJSSHTQCZUBTWOADBIGWFHQN", "TFNLMHZHJSSHTQCZUBTWOADBIGWFHQNCOXJUXPLFAPCP", "YDTBAAONTW", "XYDTBAAONTWTFNLMHZHJSSHT", "DTBAAONTWTFNLMHZHJSSHT", "HTQCZUBTWOADBIGWFHQNCOXJUXPLFAPCP", "O", "IKUSXWKWJRAVKUQ", "NOEUYMEONBGBJKGZUVIKYEUIKHXFYQHMRMQSUQREQVATW", "HJSSHTQCZUBTWOADBIGWFHQNCOXJUXPLFAPCPQ", "LXYDTBAAONTWTFNLMHZHJSSHTQCZ", "ZPSGVBQAOKBIJ", "AAONTWTFNLMH", "TFNLM", "TFNLMHZHJSSHTQCZUBTWOADBIGWFHQNCO", "MLXYDTBAAONTWTFNLMHZHJSSHTQCZ", "HJSSHTQCZUBTWOADBIGWFHQNCOXJUXPLFAPCPQENPSDWGBVN", "PJIZXOSQSJDJGKHALXEGZSCNVZLOYPOXDGKMKMTEJC", "B", "WTFNLMHZHJSSHTQCZUBTWOADBIGWFHQNC", "YDTBAAONTWTFNLMHZHJSSHTQCZUBTWOADBIGWFHQN", "QTS", "NLMHZ", "NAMWCUEP", "UBTWOADBIGWFHQNCOXJUXP", "BZ", "HZHJSSHTQCZUBTWOADBIGWFHQNCOXJUXPLFAPCPQENPSDWGB", "OFQVTVMHRK", "MLXYDTBAAONTWTFNLMHZHJSSHTQCZUBT", "WGIQWSQVSGCBYUJIQXSCFOMRTYBNLZEEJXVQXYQP", "SDOTFQCWQSRZLCSEGKDASNLACROD", "RYHNHJXHVDLMODUUFCTNSAOMFBEUYH", "ZHJSSHTQCZUBTWOADBIGWFHQNCOXJUXPLFAPCPQENPSDWGBV", "S", "DTBAAONTWTFNLMHZHJSSHTQCZUB", "CZUBTWOADBIGWFHQNCOXJUXPLFAPCPQENPSDWGBVNUAGI", "XYDTBAAONTWTFNLMHZHJSSHTQCZUBTWOADBIGWFHQNCOXJ", "BLDLIHYFOPNQSLJMMSDBTHDJO", "TNR", "AAONTWTF", "HZHJSSHTQCZUBTWOADBIGWFHQNCOXJUXPLF"}; vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 15; verify_case(0, Arg2, spellIt(Arg0, Arg1)); }
	//void test_case_0() { string Arr0[] = {"HELLO"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"E","HE","L"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 15; verify_case(0, Arg2, spellIt(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"ALGORITHM","QUALIFICATION","ROUND","TWO"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AL", "CAT", "GOR", "IFI", "ION", "ROUND", "T"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 282; verify_case(1, Arg2, spellIt(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"GOOD","LUCK"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"GOODLUCKBJ","G","L"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -5; verify_case(2, Arg2, spellIt(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"ANDDOHAVEFUN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"HAV"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(3, Arg2, spellIt(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  HandlesSpelling ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
