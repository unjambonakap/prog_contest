// BEGIN CUT HERE

// END CUT HERE
#line 5 "PhoneNetwork.cpp"

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
int graph[maxn][maxn];
double ng[maxn][maxn];
int visited[maxn];
int used[maxn][maxn];
const double eps=1e-10;

vector<pii> dat[maxn][maxn];
int n;
void dfs(int a){
    if (visited[a]) return;
    visited[a]=1;
    REP(i, n) if (graph[a][i]) dfs(i);

}

int checkit(double v){
    REP(i, n) REP(j, n) ng[i][j]=-1e9;

    REP(i, n) REP(j, n) if (graph[i][j]){
        int fd=0;
        double sum=0.;
        REP(k, dat[i][j].size()){
            double tmp=dat[i][j][k].ST-v*dat[i][j][k].ND;
            checkmax(ng[i][j], tmp);
            if (tmp>=0.) fd=1, sum+=tmp;
        }
        if (fd) ng[i][j]=sum;
    }
    memset(used, 0, sizeof(used));

    memset(visited, 0, sizeof(visited));
    priority_queue<pair<double, int> > q;
    int pos=0;
    visited[pos]=1;
    REP(i, n) if (graph[pos][i]) q.push(MP(ng[pos][i], i)), used[pos][i]=used[i][pos]=1;
    double c=0.;
    while(!q.empty()){
        pair<double, int> a=q.top(); q.pop();
        if (a.ST>=0.) c+=a.ST;
        if (visited[a.ND]) continue;

        if (a.ST<0.) c+=a.ST;
        int pos=a.ND;
        visited[a.ND]=1;
        REP(i, n) if (graph[a.ND][i] && !used[a.ND][i]) q.push(MP(ng[a.ND][i], i)), used[a.ND][i]=used[i][a.ND]=1;
    }
    return c>=0.;

}

class PhoneNetwork {
	public:
	double bestQuality(int _n, vector <string> cables) {
        n=_n;
        REP(i, n) REP(j, n) dat[i][j].clear();
        memset(graph, 0, sizeof(graph));



        double H, T, M;
        H=0.;
        T=1e9;
        FE(it, cables){
            int a, b, c, d;
            istringstream(*it)>>a>>b>>c>>d;
            --a; --b;
            graph[a][b]=1; graph[b][a]=1;

            dat[a][b].pb(MP(c, d));
            dat[b][a].pb(MP(c, d));

            checkmin(T, double(c)/d); checkmax(H, double(c)/d);
        }
        memset(visited, 0, sizeof(visited));
        dfs(0);
        REP(i, n) if (!visited[i]) return -1.;
        


        while((H-T)>eps){
            M=(H+T)/2.;
            if (checkit(M)) T=M;
            else H=M;
        }


        return T;
       
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 4; string Arr1[] = {"1 2 6 5","2 3 3 4","3 4 5 2","4 1 3 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.4; verify_case(0, Arg2, bestQuality(Arg0, Arg1)); }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"1 2 1 4", "1 2 5 2", "1 2 7 3", "1 2 3 3", "1 2 8 3", "1 2 2 1", "1 2 3 4", "1 3 1 1000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.4; verify_case(0, Arg2, bestQuality(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 5; string Arr1[] = {"1 2 6 5","2 3 3 4","3 4 5 2","4 1 3 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = -1.0; verify_case(1, Arg2, bestQuality(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; string Arr1[] = {"1 2 1 10","2 3 3 3","2 4 3 2","3 4 3 1","3 4 2 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.7058823529411765; verify_case(2, Arg2, bestQuality(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  PhoneNetwork ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
