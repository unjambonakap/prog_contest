// BEGIN CUT HERE

// END CUT HERE
#line 5 "NextBetter.cpp"

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


const int maxn=57;
vs data, cnd;
int qual[maxn][maxn];
int n;
int match[maxn], rmatch[maxn];
int graph[maxn][maxn];
int visited[maxn];
int lock[maxn];


struct cmpA{ bool operator()(int a, int b)const{return cnd[a]<cnd[b];} };

int dfs(int a){
	if (visited[a])return 0;
	visited[a]=1;
	REP(i, n) if (graph[a][i] && (match[i]==-1 || dfs(match[i]))){
		match[rmatch[a]=i]=a;
		return 1;
	}
	return 0;
}

vs solve(int a, int b){
	vs res;
	memset(graph, 0, sizeof(graph));
	FOR(i, a, b){
		FOR(j, a, n-1){
			if (i==a && cnd[j]<=cnd[i])continue;
			if (i==b && qual[i][j]<=qual[i][i])continue;
			if (i!=b && qual[i][j]!=qual[i][i])continue;
			graph[i][j]=1;
		}
	}
	int na=b-a+1;
	int cnt=0;
	memset(match, -1, sizeof(match));
	FOR(i, a, b){
		memset(visited, 0, sizeof(visited));
	   	if (dfs(i)) ++cnt;
	}
	if (cnt!=na) return res;

	vi scnd;
	FOR(i, a, n-1) scnd.pb(i);
	sort(ALL(scnd), cmpA());
	

	FOR(i, a, b){
		int cnta=0;
		FOR(k, a, n-1) if (match[k]!=-1) ++cnta;
		assert(cnta==b-a+1);

		REPV(j, scnd.size()) if (graph[i][scnd[j]]){
			graph[i][scnd[j]]=0;
			if (match[scnd[j]]!=i) continue;
			match[scnd[j]]=-1;
			memset(visited, 0, sizeof(visited));
			if (!dfs(i)){
				graph[i][scnd[j]]=1;
				match[scnd[j]]=i;
			}else{
				int cnta=0;
				FOR(k, a, n-1) if (match[k]!=-1) ++cnta;
				assert(cnta==b-a+1);
			}
		}
	}
	REP(i, a) res.pb(cnd[i]);
	FOR(i, a, b) res.pb(cnd[rmatch[i]]);
	vs temp;
	int cnta=0;
	FOR(i, a, n-1) if (match[i]!=-1) ++cnta;
	assert(cnta==b-a+1);
	FOR(i, a, n-1) if (match[i]==-1) temp.pb(cnd[i]);
	sort(ALL(temp));
	res.insert(res.end(), ALL(temp));
	return res;




}

class NextBetter {
	public:
		vector <string> nextPerm(vector <string> _data, vector <string> _cnd) {
			data=_data, cnd=_cnd;
			n=data.size();

			memset(qual, 0, sizeof(qual));
			REP(i, n) REP(j, n) REP(k, min(data[i].length(), cnd[j].length())) if (data[i][k]==cnd[j][k]) ++qual[i][j];

			vs ans;
			REPV(i, n-1){
				vs res;
				FOR(j, i, n-1){
					vs temp=solve(i, j);
					if (temp.size() && (!ans.size() || temp<ans)) ans=temp;
				}

				if (ans.size()) return ans;
			}
			return cnd;


		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
		//void test_case_0() { string Arr0[] = {"ab","cde"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"xx","ade"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"xx", "ade" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, nextPerm(Arg0, Arg1)); }
		void test_case_0() { string Arr0[] = {"k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "kza", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "k", "s", "k", "k", "k", "k", "k", "k", "k"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"a", "yz", "yy", "yx", "yk", "yj", "yi", "yh", "yg", "yf", "ye", "yd", "yc", "yb", "ya", "ty", "tty", "ttty", "yyn", "yym", "yyl", "yyk", "yyj", "yyi", "yyh", "yyg", "yyf", "yye", "yyd", "yyc", "yyb", "yya", "yvq", "yvp", "yvo", "yvn", "yvm", "yvl", "yvk", "yvj", "yvi", "yvh", "yvg", "yvf", "yve", "yvd", "yvc", "yvb", "yva", "s"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"a", "yz", "yy", "yx", "yk", "yj", "yi", "yh", "yg", "yf", "ye", "yd", "yc", "yb", "ya", "ty", "tty", "yva", "s", "ttty", "yvb", "yvc", "yvd", "yve", "yvf", "yya", "yvg", "yvh", "yvi", "yvj", "yvk", "yvl", "yvm", "yvn", "yvo", "yvp", "yvq", "yyb", "yyc", "yyd", "yye", "yyf", "yyg", "yyh", "yyi", "yyj", "yyk", "yyl", "yym", "yyn"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, nextPerm(Arg0, Arg1)); }
		
		void test_case_1() { string Arr0[] = {"ad","cde"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"xx","yde"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"yde", "xx" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, nextPerm(Arg0, Arg1)); }
		void test_case_2() { string Arr0[] = {"ade","cde","acd"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ab","ae","c"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"ab", "c", "ae" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, nextPerm(Arg0, Arg1)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	NextBetter ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
