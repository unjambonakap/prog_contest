// BEGIN CUT HERE

// END CUT HERE
#line 5 "FunnyGames.cpp"

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

const int maxn=34;
const int maxm=two(maxn/2+2)+10;

int tree[maxm];
int U[maxn], V[maxn];
int n, K;
int sleaf;


int proc(int p, int m, ll u, ll v){
    if (m==K-1 || p==n) return u>0 && v>0;
    return proc(p+1, m, u ,v)+proc(p+1, m+1, u+U[p], v+V[p]);
}


void update(int a, int c){ tree[a]+=c; if (a!=1) update(a/2, c); }
int query(int a, int l, int u, int v){
    if (v==u) return 0;
    if (v==l) return tree[a];
    int m=(l+u)/2;
    if (v<m) return query(2*a, l, m, v)+tree[2*a+1];
    return query(2*a+1, m, u, v);
}

class FunnyGames {
	public:
	long long countWays(vector <int> A, vector <int> B, vector <int> C, int k) {
        n=A.size();
        REP(i, n) U[i]=A[i]-B[i], V[i]=A[i]-C[i];
        K=k;
        ll res=-proc(0, 0, 0, 0);
		
        out(U, n);
        out(V, n);
        vector<pair<ll, ll> > a, b;
        REP(i, two(n/2)){
            ll u, v; u=v=0;
            REP(j, n/2) if (i&two(j)) u+=U[j], v+=V[j];
            a.pb(MP(u, v));
        }

        vector<ll> c;
        REP(i, two(n-n/2)){
            ll u, v; u=v=0;
            REP(j, n-n/2) if (i&two(j)) u+=U[n/2+j], v+=V[n/2+j];
            b.pb(MP(u, v));
            c.pb(v);
        }
        sort(ALL(a)); sort(ALL(b)); sort(ALL(c));
        memset(tree, 0, sizeof(tree));
        int leaf=two(n-n/2);
        REP(i, c.size()) update(leaf+(lower_bound(ALL(c), c[i])-c.begin()), 1);
        int p=0;
        FEV(it, a){
            while(p<b.size() && b[p].ST+it->ST<=0) update(leaf+(lower_bound(ALL(c), b[p++].ND)-c.begin()), -1);
            res+=query(1, 0, leaf, lower_bound(ALL(c), -it->ND+1)-c.begin());
        }

        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {42144752, 45375244, 522231, 11834530, 2015217, 20200657, 48365057, 131929, 61767164, 21663723, 56207051, 6242051, 65944159}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {66118592, 10579598, 7741102, 4792435, 61526793, 11884179, 23057193, 64813710, 21059240, 59365365, 62370687, 45061908, 29834467}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10299483, 25813974, 28949504, 51393422, 45825519, 54026343, 62605471, 6188449, 58985512, 5700560, 12881688, 27585694, 43069385}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; long long Arg4 = 3LL; verify_case(0, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
//void test_case_0() { int Arr0[] = {1,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; long long Arg4 = 3LL; verify_case(0, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
void test_case_1() { int Arr0[] = {1,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,2,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; long long Arg4 = 1LL; verify_case(1, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }

void test_case_2() { int Arr0[] = {1000000000,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; long long Arg4 = 4LL; verify_case(2, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
void test_case_3() { int Arr0[] = {2,3,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,3,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; long long Arg4 = 0LL; verify_case(3, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
void test_case_4() { int Arr0[] = {1000,2000,3000,1000,2000,3000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2000,3000,1000,3000,1000,2000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3000,1000,2000,2000,3000,1000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; long long Arg4 = 14LL; verify_case(4, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
FunnyGames ___test; 
    ___test.run_test(0);
    } 
// END CUT HERE
