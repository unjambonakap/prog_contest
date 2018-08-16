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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const ull MODULO = 1E9 + 7;


bool size_is_ok(const int rep, const int size, const string &s, string & result_s) {
	ull sum = 0;
	map<ull,int> m;
	REP(i,size) {
		sum = (sum << 5) + s[i];
	}
	ull hash = sum % MODULO;
	m[hash] = 1;
	FOR(i, size, s.size()) {
		sum -= s[i-size] << (5*(size-1));
		sum = (sum << 5) + s[i];
		hash = sum % MODULO;
		//cout << s.substr(i-size+1, size) << " " << hash << endl;
		if (m.find(hash) == m.end())
			m[hash] = 0;
		m[hash] += 1;

		if (m[hash] == rep) {
			//cout << s.substr(i-size+1, size) << endl;
			result_s = s.substr(i-size+1, size);
			return true;
		}
	}

	return false;
}

void binary_search(int m, const string & s) {
	int a=0, b=s.size(), n=0;
	n = (b-a) / 2;
	string result;

	while (1) {
		if (size_is_ok(m,n,s,result))
			a = n;
		else
			b = n;
		n = a + (b-a) / 2;
		if (b<=a or a==n)
			break;
	}

	if (n==0)
		cout << "none" << endl;
	else {
		cout << n << " " << s.rfind(result) << endl;
	}
}

int main() {
	int m=0;
	string s;
	
	while (1) {
		cin >> m;
		if (m==0) break;
		cin >> s;
		binary_search(m,s);
	}
	//binary_search(3, "baaaababababbababbab");
	//binary_search(11, "baaaababababbababbab");
	//binary_search(3, "cccccc");

	return 0;
}

