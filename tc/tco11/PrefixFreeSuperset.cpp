// BEGIN CUT HERE

// END CUT HERE
#line 5 "PrefixFreeSuperset.cpp"

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


struct node{
    node *l, *r;
    int d, lock;
    node():l(0), r(0), lock(0), d(0){}
};

const int maxn=62;
node tb[maxn*maxn*2];
int pos;
string s;

ll dx[2*maxn];

void dfs(node *e){
    if (e->l) dfs(e->l), dfs(e->r);
    else if (!e->lock) ++dx[e->d];
}

void add(node *e, int p){
    if (p==s.length()){e->lock=1; return;}
    if (e->l==0){
        e->l=tb+pos++, e->r=tb+pos++;
        e->r->l=e->l->l=0;
        e->r->d=e->l->d=e->d+1;
        e->r->lock=e->l->lock=0;
    }
    add(s[p]=='0'?e->l:e->r, p+1);
}

class PrefixFreeSuperset {
	public:
	long long minSumLength(vector <string> cur, long long k) {
        pos=0;
        node *r=tb+pos++;
        r->l=r->r=0;
        r->d=0;

        ll ans=0;
        FE(it, cur){
            s=*it;
            add(r, 0);
            ans+=s.length();
        }

        k-=cur.size();
        memset(dx, 0, sizeof(dx));

        dfs(r);
        REP(i, 95){
            if (dx[i]>=k) return ans+i*k; 
            if (dx[i]+dx[i+1]>=k) return ans+i*dx[i]+(k-dx[i])*(i+1);
            else if (2*dx[i]+dx[i+1]>=k){
                ll a=k-dx[i+1]-dx[i];
                return ans+(dx[i]-a)*i+(2*a+dx[i+1])*(i+1);
            } else dx[i+1]+=2*dx[i];
        }
        return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; long long Arg2 = 9LL; verify_case(0, Arg2, minSumLength(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"01","000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; long long Arg2 = 9LL; verify_case(1, Arg2, minSumLength(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"0011","011110101","11101010111","11101010100000000","11101010100000001111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1000000000000LL; long long Arg2 = 39971901640560LL; verify_case(2, Arg2, minSumLength(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"010","00","011","1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; long long Arg2 = 9LL; verify_case(3, Arg2, minSumLength(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"010","00","011","1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; long long Arg2 = -1LL; verify_case(4, Arg2, minSumLength(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  PrefixFreeSuperset ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
