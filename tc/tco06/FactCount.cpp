// BEGIN CUT HERE

// END CUT HERE
#line 5 "FactCount.cpp"

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

const int n=26;
int graph[n][n];
int visited[n];

int parent[n];
int ngraph[n][n];
int m;
int sz[n];
int pred[n];

void dfs(int a, int b){
    if (visited[a]) return;
    visited[a]=1;
    graph[b][a]=1;
    REP(i, n) if (graph[a][i]) dfs(i, b);
}

int dfsa(int a){
    if (visited[a]) return 0;
    visited[a]=1;
    int r=two(a);
    REP(i, m) if (ngraph[i][a]) r|=dfsa(i);
    return r;
}


class FactCount {
	public:
	int minFacts(vector <string> ta) {
        string s;
        FE(it, ta){
            FE(ita, *it) if (*ita!=' ') s+=*ita;
        }

        assert(s.length()%2==0);
        memset(graph, 0, sizeof(graph));
        REP(i, s.length()/2) graph[s[2*i]-'A'][s[2*i+1]-'A']=1;
        REP(i, n){
            memset(visited, 0, sizeof(visited));
            REP(j, n) if (graph[i][j]) dfs(j, i);
        }


        memset(parent, -1, sizeof(parent));
        memset(sz, 0, sizeof(sz));
        int cnt=0;
        REP(i, n) if (parent[i]==-1) FOR(j, i+1, n-1) if (graph[i][j] && graph[j][i]) parent[j]=i, ++sz[i];
        REP(i, n) if (parent[i]==-1){
            if (sz[i]==0) cnt+=graph[i][i];
            else cnt+=sz[i]+1;
        }

        int remap[n];
        m=0;
        REP(i, n) if (parent[i]==-1) remap[m++]=i;
        memset(ngraph, 0, sizeof(ngraph));
        REP(i, m) REP(j, m) if (i!=j && graph[remap[i]][remap[j]]) ngraph[i][j]=1;


        REP(i, m){
            memset(visited, 0, sizeof(visited));
            pred[i]=dfsa(i)|two(i);
        }

        REP(i, m){
            int mask=pred[i]^two(i);
            while(mask){
                int tmp=0;
                REP(j, m) if (ngraph[j][i] && count_bit(pred[j]&mask)>count_bit(tmp&mask)) tmp=pred[j];
                mask=(mask^tmp)&mask;
                ++cnt;
            }

        }

        return cnt;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = {"AA AA AA AB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minFacts(Arg0)); }
	void test_case_0() { string Arr0[] = {"AB BC CA AA EE FG GA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(0, Arg1, minFacts(Arg0)); }
	void test_case_1() { string Arr0[] = {"AB AC CA AA BC", "AD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, minFacts(Arg0)); }
	void test_case_2() { string Arr0[] = {"AB BA BC CB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, minFacts(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  FactCount ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
