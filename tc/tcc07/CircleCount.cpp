// BEGIN CUT HERE

// END CUT HERE
#line 5 "CircleCount.cpp"

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


const int maxn=27;
const int MAX=2000000000;
int n;
int remap[maxn];
int st[maxn], dst[maxn];
long double fact[maxn];

class CircleCount {
	public:
	int countOrder(string circle) {
		fact[0]=1;
		REP(i, maxn-1) fact[i+1]=fact[i]*(i+1);

		n=circle.length();
		ll res=0;
		REP(i, n) if (circle[i]>='a'){
			int j=(i+1)%n;
			while(circle[j]-'A'!=circle[i]-'a' && circle[j]<='Z')j=(j+1)%n;
			if (circle[j]-'A'!=circle[i]-'a'){
				j=(n+i-1)%n;
				while(circle[j]-'A'!=circle[i]-'a' && circle[j]<='Z')j=(n+j-1)%n;
				if (circle[j]-'A'!=circle[i]-'a')continue;
			}
			int k=j;
			string ns;
			while((k=(k+1)%n)!=j) if (k!=i) ns+=circle[k];
			int id=0;
			memset(remap, -1, sizeof(remap));
			REP(i, ns.length()) if (ns[i]>='a') remap[ns[i]-'a']=id++;
			REP(i, ns.length()) if (ns[i]>='a') st[remap[ns[i]-'a']]=i; else dst[remap[ns[i]-'A']]=i;

			bool ok=true;
			REP(i, id) REP(j, id) if (i!=j){
			   	if (min(st[i], dst[i])<min(st[j], dst[j]) && max(st[i], dst[i])>max(st[j], dst[j])){ok=false; goto out;}
				if (st[i]>dst[i] && st[j]<st[i] && dst[j]>st[i]){ok=false; goto out;}
				if (st[i]<dst[i] && st[j]>st[i] && dst[j]<st[i]){ok=false; goto out;}
				if (st[i]>dst[i] && dst[j]>dst[i] && st[j]<dst[i]){ok=false; goto out;}
				if (st[i]<dst[i] && dst[j]<dst[i] && st[j]>dst[i]){ok=false; goto out;}
			}
out:
			if (!ok)continue;

			int nd=-1, cnt=0;
			vi tb;

			REP(i, ns.length()){
				int a=remap[ns[i]-(ns[i]>='a'?'a':'A')];
				++cnt;
				if (i==nd){
					assert(cnt%2==0);
					tb.pb(cnt/2);
					nd=-1, cnt=0;
				}
				else if (nd==-1) nd=max(dst[a], st[a]);
				else nd=max(nd, max(dst[a], st[a]));
			}

			int s=0;
			FE(it, tb) s+=*it;
			long double temp=fact[s];
			FE(it, tb)temp/=fact[*it];
			res+=(ll)temp;

			if (temp>MAX)return -1;
			if (res>MAX)return -1;
		}
		return (int)res;


	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "aBAbcCdefDEFghijGHIJklKLPQpq"; int Arg1 = 3; verify_case(0, Arg1, countOrder(Arg0)); }
	//void test_case_0() { string Arg0 = "BACacb"; int Arg1 = 3; verify_case(0, Arg1, countOrder(Arg0)); }
	void test_case_1() { string Arg0 = "ABCacb"; int Arg1 = 0; verify_case(1, Arg1, countOrder(Arg0)); }
	void test_case_2() { string Arg0 = "xX"; int Arg1 = 1; verify_case(2, Arg1, countOrder(Arg0)); }
	void test_case_3() { string Arg0 = "ABCabc"; int Arg1 = 2; verify_case(3, Arg1, countOrder(Arg0)); }
	void test_case_4() { string Arg0 = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPp"; int Arg1 = -1; verify_case(4, Arg1, countOrder(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	CircleCount ___test; 
	___test.run_test(0);
} 
// END CUT HERE
