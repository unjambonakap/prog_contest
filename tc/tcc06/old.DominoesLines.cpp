// BEGIN CUT HERE

// END CUT HERE
#line 5 "DominoesLines.cpp"

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


const int n=7;

int graph[n][n];
int deg[n];
int parent[n];
vs res;

int root(int a){return parent[a]==-1?a:parent[a]=root(parent[a]);}

int proc(int p){
    memset(deg, 0, sizeof(deg));
    memset(parent, -1, sizeof(parent));
    REP(i, n) REP(j, n) if (graph[i][j]){
        deg[i]+=graph[i][j];
        if (root(i)!=root(j)) parent[root(i)]=root(j);
    }

    int ans=0;
    REP(i, n) if (root(i)==i && deg[i]){
        int cnt=0;
        REP(j, n) if (root(i)==root(j)) cnt+=deg[j]%2;
        cnt/=2;
        if (!cnt) ans+=(p!=-1 && root(p)==i?0:1);
        else{
            if (p!=-1 && root(p)==i && deg[p]%2) --cnt;
            ans+=cnt;
        }
    }

    return ans;
}

void solve(int p, int a, int b){
    int ans=proc(-1);
    REP(i, n) if (graph[p][i]){
        --graph[p][i]; --graph[i][p];

        int na=proc(-1);
        if (na==ans-1){
            res[a]+=toStr(p)+":"+toStr(i);
            if (a+1==b) return;
            REP(j, n) if (deg[j] && proc(j)==na-1){solve(j, a+1, b); return;}
            assert(0);
        }else if (na==ans && deg[i] && proc(i)==ans-1){
            res[a]+=toStr(p)+":"+toStr(i)+"-";
            solve(i, a, b);
            return;
        }
        ++graph[p][i]; ++graph[i][p];
    }
    assert(0);
    return;

}

class DominoesLines {
	public:
	vector <string> constructLines(vector <string> tiles) {
        memset(graph, 0, sizeof(graph));
        REP(i, tiles.size()){
            ++graph[tiles[i][0]-'0'][tiles[i][2]-'0'];
            ++graph[tiles[i][2]-'0'][tiles[i][0]-'0'];
        }

        int ans=proc(-1);
        res=vs(ans);
        REP(i, n) if (deg[i] && proc(i)==ans-1){solve(i, 0, ans); break;}
        return res;

	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	//void test_case_0() { string Arr0[] = {"0:6", "6:6", "0:0", "6:6", "6:0", "0:6", "6:0", "6:0", "0:0", "6:0", "6:0", "0:0", "6:6", "0:6", "6:0", "0:6", "0:3", "3:2", "2:3", "2:4", "1:4", "5:4", "5:1", "5:5", "1:4", "1:1", "4:1", "1:5", "4:4", "4:5", "5:1", "5:5", "5:4", "4:4", "4:1", "1:4", "4:1", "4:5", "5:4", "1:1", "1:1", "1:4", "4:5", "5:1", "1:5", "1:4", "5:5", "4:1", "1:1", "5:4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0:1-1:1-1:2", "3:1-1:4" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, constructLines(Arg0)); }
//void test_case_0() { string Arr0[] = {"1:0", "1:1", "1:2", "1:3", "1:4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0:1-1:1-1:2", "3:1-1:4" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, constructLines(Arg0)); }
void test_case_0() { string Arr0[] = {"3:2", "0:2", "2:3", "6:1", "4:1", "4:1", "5:6", "0:6", "0:3", "5:5", "4:6", "0:4", "3:3", "0:1", "2:6", "1:5", "3:4", "2:2", "5:3", "2:5", "2:1", "0:0", "5:4", "0:6", "5:3", "4:0", "0:1", "1:1", "3:4", "4:0", "6:3", "1:1", "0:2", "1:6", "4:4", "5:0", "0:0", "0:4", "3:0", "5:0", "3:3", "6:1", "2:2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1:0-0:0-0:0-0:1-1:1-1:1-1:2", "3:0-0:2-2:0-0:3-3:2-2:2-2:2-2:3-3:3-3:3-3:4-4:0-0:4-4:0-0:4-4:1-1:4-4:3-3:5-5:0-0:5-5:1-1:6-6:0-0:6-6:1-1:6-6:2-2:5-5:3-3:6-6:4-4:4-4:5-5:5-5:6"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, constructLines(Arg0)); }
	void test_case_1() { string Arr0[] = {"4:0", "4:1", "4:2", "4:3", "4:4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0:4-4:1", "2:4-4:4-4:3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, constructLines(Arg0)); }
	void test_case_2() { string Arr0[] = {"0:0", "1:1", "2:2", "3:3", "6:6", "6:0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0:0-0:6-6:6", "1:1", "2:2", "3:3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, constructLines(Arg0)); }
	void test_case_3() { string Arr0[] = {"0:4", "6:6", "1:2", "1:1", "3:1", "4:4", "0:1", "1:5", "5:0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0:1-1:1-1:2", "3:1-1:5-5:0-0:4-4:4", "6:6" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, constructLines(Arg0)); }
	void test_case_4() { string Arr0[] = {"3:1", "0:2", "6:1", "6:3", "4:6", "6:4", 
 "2:3", "4:0", "5:2", "2:2", "6:6"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"2:0-0:4", "3:1-1:6-6:4-4:6-6:6-6:3-3:2-2:2-2:5" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, constructLines(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  DominoesLines ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
