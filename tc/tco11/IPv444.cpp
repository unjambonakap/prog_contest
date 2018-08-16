// BEGIN CUT HERE

// END CUT HERE
#line 5 "IPv444.cpp"

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

struct data{
    vi tb;
    int v;

    data(string s, int v):v(v){
        REP(i, s.length()) if (s[i]=='.') s[i]=' ';
        istringstream ss(s);
        string t;
        while(ss>>t){
            if (t=="*") tb.pb(-1);
            else tb.pb(toInt(t));
        }
    }
    data(){}
};

vector<data> A;
int n;

class IPv444 {
	public:
	long long getMaximumMoney(vector <string> request, vector <int> price) {
        A.clear();
        n=request.size();
        REP(i, n) A.pb(data(request[i], price[i]));

        ll ans=0;
        vi tb[4];
        REP(j, 4){
            REP(i, n) tb[j].pb(A[i].tb[j]);
            sort(ALL(tb[j]));
            tb[j].resize(unique(ALL(tb[j]))-tb[j].begin());
        }
        int na=1000-tb[0].size()+1;
        int nb=1000-tb[1].size()+1;
        int nc=1000-tb[2].size()+1;
        int nd=1000-tb[3].size()+1;
        REP(a, tb[0].size()) REP(b, tb[1].size()) REP(c, tb[2].size()) REP(d, tb[3].size()){
            ll mul=1;
            if (tb[0][a]==-1) mul*=na;
            if (tb[1][b]==-1) mul*=nb;
            if (tb[2][c]==-1) mul*=nc;
            if (tb[3][d]==-1) mul*=nd;
            int vx=0;
            REP(k, n){
                if (A[k].tb[0]!=-1 && A[k].tb[0]!=tb[0][a]) continue;
                if (A[k].tb[1]!=-1 && A[k].tb[1]!=tb[1][b]) continue;
                if (A[k].tb[2]!=-1 && A[k].tb[2]!=tb[2][c]) continue;
                if (A[k].tb[3]!=-1 && A[k].tb[3]!=tb[3][d]) continue;
                checkmax(vx, A[k].v);
            }
            ans+=mul*vx;

        }

		

        return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"66.37.210.86"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {47}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 47LL; verify_case(0, Arg2, getMaximumMoney(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0.0.0.*", "0.0.0.3", "0.0.0.5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1010LL; verify_case(1, Arg2, getMaximumMoney(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"*.*.*.*", "123.456.789.0", "434.434.434.434", "999.*.999.*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 5, 3, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1000005000006LL; verify_case(2, Arg2, getMaximumMoney(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"*.*.999.999", "888.888.999.*", "888.888.*.999", "777.777.777.777", "777.*.*.777"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {19, 33, 42, 777, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 26075718LL; verify_case(3, Arg2, getMaximumMoney(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"127.0.0.1", "*.0.0.*", "*.*.255.255", "192.68.*.*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {999999, 629851, 294016, 438090}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1361957076132LL; verify_case(4, Arg2, getMaximumMoney(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  IPv444 ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
