// BEGIN CUT HERE

// END CUT HERE
#line 5 "QuickTableau.cpp"

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

const int maxn=4;
const int n=4;
int mp[maxn][maxn];
int used[maxn*maxn];
int minv[maxn][maxn], maxv[maxn][maxn];
int pos[maxn*maxn];
int tb[maxn][maxn];
int ntb[maxn*maxn];
int npos[maxn*maxn];
int ans;

void rec(int a, int b){
    if (b==n){++a; b=0;}
    if (a==n){
        memcpy(npos, pos, sizeof(pos));
        memcpy(ntb, tb[0], sizeof(ntb));
        int res=0;
        REP(i, n*n) if (npos[i]!=used[i]){
            ++res;
            swap(ntb[npos[i]], ntb[used[i]]);
            swap(npos[i], npos[ntb[npos[i]]]);

        }
        checkmin(ans, res);

        return;
    }

    int ma=minv[a][b];
    int mb=maxv[a][b];
    if (a>0) checkmax(ma, mp[a-1][b]);
    if (b>0) checkmax(ma, mp[a][b-1]);
    FOR(i, ma, mb) if (used[i]==-1){
        used[i]=a*n+b;
        mp[a][b]=i;
        rec(a, b+1);
        used[i]=-1;
    }

}

class QuickTableau {
	public:
	int numSwaps(vector <int> table) {
        REP(i, n) REP(j, n) tb[i][j]=table[i*n+j]-1;
        REP(i, n) REP(j, n) pos[tb[i][j]]=i*n+j;
        REP(i, n) REP(j, n) maxv[i][j]=n*n-((n-i)*(n-j)), minv[i][j]=(i+1)*(j+1)-1;
        memset(used, -1, sizeof(used));
        ans=INT_MAX;
        rec(0, 0);
        return ans;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {
 1,  2,  3,  4,
 5,  6,  7,  8,
 9, 10, 11, 12,
13, 16, 14, 15
}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, numSwaps(Arg0)); }
	void test_case_1() { int Arr0[] = {
16, 15, 14, 13,
12, 11, 10,  9,
 8,  7,  6,  5,
 4,  3,  2,  1
}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(1, Arg1, numSwaps(Arg0)); }
	void test_case_2() { int Arr0[] = {
 2,  1,  3,  4,
 5,  6,  7,  8,
 9, 10, 11, 12,
13, 14, 15, 16
}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, numSwaps(Arg0)); }
	void test_case_3() { int Arr0[] = {
 4,  3,  2,  1,
 5,  6,  7,  8,
 9, 10, 11, 12,
13, 14, 15, 16
}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, numSwaps(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  QuickTableau ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
