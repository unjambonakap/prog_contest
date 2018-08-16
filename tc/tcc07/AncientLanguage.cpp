// BEGIN CUT HERE

// END CUT HERE
#line 5 "AncientLanguage.cpp"

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

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}

const int maxn=2500;
const int maxz=26*26;

int graph[maxz+2][maxz+2];
int visited[maxz+2];
int match[maxz+2];
int n, m;


int dfs(int p){

	if (visited[p])return 0;
	visited[p]=1;
	REP(i, maxz+2) if (graph[p][i] && (match[i]==-1 || dfs(match[i]))){ match[i]=p; return 1;}
	return 0;
}
class AncientLanguage {
	public:
	int minWords(vector <string> t) {
		
		string s;
		FE(it, t)s+=*it;
		n=s.length();

		memset(graph, 0, sizeof(graph));
		REP(i, n){
			char a, b, c;
			int ia, ib;
			if (i==0) a=s[i], b=s[i+1];
			else if (i==n-1)a=s[i-1], b=s[i];
			else a=s[i-1], b=s[i], c=s[i+1];

			char oa=a;
			a-=(a>='a'?'a':'A');
			b-=(b>='a'?'a':'A');
			c-=(c>='a'?'a':'A');
			ia=a*26+b;
			ib=b*26+c;
			if (i==0){
				if (oa>='a') graph[ia][maxz]=1;
				else graph[maxz][ia]=1;
			}else if (i==n-1){
				if (oa>='a') graph[ia][maxz+1]=1;
				else graph[maxz+1][ia]=1;
			}else{
				if (oa<='Z')swap(ia, ib);
				graph[ia][ib]=1;
			}
		}


		int cnt=0;
		memset(match, -1, sizeof(match));
		REP(i, maxz+2){
			memset(visited, 0, sizeof(visited));
			if (dfs(i))++cnt;
		}
		

		return cnt;

	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"AaAbBaAcCaAa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, minWords(Arg0)); }
	void test_case_1() { string Arr0[] = {"aA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minWords(Arg0)); }
	void test_case_2() { string Arr0[] = {"aBaB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, minWords(Arg0)); }
	void test_case_3() { string Arr0[] = {"AaB", "b"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, minWords(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  AncientLanguage ___test; 
        ___test.run_test(1); 
        } 
// END CUT HERE
