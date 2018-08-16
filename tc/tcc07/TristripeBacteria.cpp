// BEGIN CUT HERE

// END CUT HERE
#line 5 "TristripeBacteria.cpp"

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



const int maxn=52;
int mp[maxn][maxn];
int nmp[maxn][maxn];
int parent[maxn*maxn];
int n, m;
int la[maxn], ca[maxn];

int root(int a){return parent[a]=(parent[a]==a?a:root(parent[a]));}

int checkit(int rem, int pm[][maxn]){
	int work[maxn][maxn];
	bool fd=0;
	pii s;
	REP(i, n) REP(j, m) if (pm[i][j]==1){fd=true; s=MP(i, j); break;}
	if (!fd)return 1;
	if (rem==0)return 0;
	memcpy(work, pm, sizeof(work));
	int k=s.ST;
	while(k>=0 && work[k][s.ND]) work[k--][s.ND]=2;
	k=s.ST+1;
	while(k>=0 && work[k][s.ND]) work[k++][s.ND]=2;

	if (checkit(rem-1, work))return 1;
	memcpy(work, pm, sizeof(work));
	k=s.ND;
	while(k>=0 && work[s.ST][k]) work[s.ST][k--]=2;
	k=s.ND+1;
	while(k>=0 && work[s.ST][k]) work[s.ST][k++]=2;
	return checkit(rem-1, work);



}

class TristripeBacteria {
	public:
		int howMany(vector <string> photo) {
			n=photo.size(); m=photo[0].length();

			REP(i, n) REP(j, m) mp[i][j]=(photo[i][j]=='*');

			REP(i, n) REP(j, m) parent[i+j*n]=i+j*n;
			REP(i, n) REP(j, m) if (mp[i][j]) REP(k, 2) if (mp[i+k][j+(k^1)]) parent[root(i+k+(j+(k^1))*n)]=root(i+j*n);

			map<int, vector<pii> > co;

			REP(i, n) REP(j, m) if (mp[i][j]) co[root(i+j*n)].pb(MP(i, j));

			int c=0;
			FE(it, co){
				memset(nmp, 0, sizeof(nmp));
				FE(itp, it->ND) nmp[itp->ST][itp->ND]=1;
				if (checkit(3, nmp))++c;
			}
			return c;

		}


// BEGIN CUT HERE
public:
void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
void test_case_0() { string Arr0[] = {"........................***...",
	"......*........*.........***..",
	"...******..................***",
	"......*.............*.........",
	".....**.........******........",
	".............................."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, howMany(Arg0)); }
	void test_case_1() { string Arr0[] = {".....................*********",
		"......*..............*********",
		"...******............*********",
		"......*.........*...*.........",
		".....**.........******........",
		"....**........................"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, howMany(Arg0)); }
		void test_case_2() { string Arr0[] = {"."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, howMany(Arg0)); }
		void test_case_3() { string Arr0[] = {"*****************"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, howMany(Arg0)); }
		void test_case_4() { string Arr0[] = {"*","*","*","*","*","*","*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, howMany(Arg0)); }

		// END CUT HERE

		};

// BEGIN CUT HERE
int main(){
	TristripeBacteria ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
