// BEGIN CUT HERE

// END CUT HERE
#line 5 "RLESum.cpp"

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

struct event{
	ll x;
	int e, id;
	char v;
	bool operator<(const event &ev)const{
		if (x!=ev.x) return x<ev.x;
		if (e!=ev.e) return e==1;
		
		return id<ev.id;
	}

};


vector<pair<ll, int> > tsf(string a){
	vector<pair<ll, int> > p;
	int i=0;

	while(i<a.length()){
		if (a[i]=='['){
			ll rep=0;
			++i;

			while(a[i]!=']')rep=rep*10+(a[i++]-'0');
			p.pb(MP(rep, (int)a[++i]-'0'));
			++i;
			continue;
		}
		p.pb(MP(1LL, (int)a[i++]-'0'));
	}
	return p;
}

class RLESum {
	public:
	vector <int> getDigits(string a, string b, vector <string> k) {
		vector<pair<ll, int> > ta, tb;
		ta=tsf(a); tb=tsf(b);

		vector<event> el;
		reverse(ALL(ta));
		reverse(ALL(tb));
		ll s;
		s=0; FE(it, ta) el.pb((event){s, 1, 0, it->ND}), s+=it->ST;
		el.pb((event){s, 1, 0, 0});
		s=0; FE(it, tb) el.pb((event){s, 1, 1, it->ND}), s+=it->ST;
		el.pb((event){s, 1, 1, 0});

		REP(i, k.size()){
			ll x;
			istringstream(k[i])>>x;
			el.pb((event){x, 0, i, 0});
		}

		sort(ALL(el));
		event ea, eb;
		ll lp=-1;
		int c, fc;
		c=fc=0;

		vi res(k.size(), -1);
		FE(it, el){
			int ca;
			if (lp==it->x)ca=fc;
			else ca=c;

			if (it->e!=0){
				if (it->id==0) ea=*it;
				else eb=*it;
				fc=ca;
				c=ea.v+eb.v+fc>=10;
				lp=it->x;
			}else
				res[it->id]=(ea.v+eb.v+ca)%10;
			

		}

		return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "[12]3"; string Arg1 = "[3]1[3]2[3]3"; string Arr2[] = {"12", "11", "10", "9", "8","7","6","5","4","3","2","1","0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, getDigits(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "[5]9"; string Arg1 = "[5]9"; string Arr2[] = {"5", "0", "1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 8, 9 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, getDigits(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "123456789"; string Arg1 = "987656789"; string Arr2[] = {"10", "9", "1", "3", "1", "2"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 1, 7, 3, 7, 5 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, getDigits(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  RLESum ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
