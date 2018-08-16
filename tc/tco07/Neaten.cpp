// BEGIN CUT HERE

// END CUT HERE
#line 5 "Neaten.cpp"

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
void outc(char *t, int n){REP(i, n)printf("%d", t[i]); cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxp=160, zero=55;
char lb[maxp], ub[maxp], num[maxp], temp[maxp], tmpb[maxp];

void add(char *a, char *b, char *c){
	char t[maxp];
	memset(t, 0, sizeof(t));
	int ct=0;
	REPV(i, maxp){
		t[i]=a[i]+b[i]+ct;
		ct=0;
		if (t[i]>9)ct=1, t[i]-=10;
	}
	memcpy(c, t, sizeof(t));
}
int sub(char *a, char *b, char *c){
	char t[maxp];
	memset(t, 0, sizeof(t));
	int ct=0;
	REPV(i, maxp){
		t[i]=a[i]-b[i]-ct;
		ct=0;
		if (t[i]<0)ct=1, t[i]+=10;
	}
	memcpy(c, t, sizeof(t));
	return ct!=0;
}
void shift(char *a, int k, char *c){
	char t[maxp];
	memset(t, 0, sizeof(t));
	REP(i, maxp-k) t[i+k]=a[i];
	memcpy(c, t, sizeof(t));
}

int lt(char *a, char *b){ REP(i, maxp) if (a[i]!=b[i])return a[i]<b[i]; return 0;}

int proc(){
	int res=INT_MAX;

	FORV(i, maxp-1, zero){
		memcpy(temp, lb, sizeof(temp)); FOR(j, i+1, maxp-1) temp[j]=0;
		memset(tmpb, 0, sizeof(tmpb)); tmpb[i]=1;
		add(temp, tmpb, temp);

		if (lt(temp, ub)){
			int cnta=0;
			REP(j, zero+1) if (temp[j]!=0){cnta=zero-j+1;break;}
			if (i!=zero) ++cnta;
		   	checkmin(res, cnta+i-zero);
		}



	}

	return res;

}


class Neaten {
	public:
	int shortest(int k, string nm) {
		char tpk[maxp];
		memset(tpk, 0, sizeof(tpk));
		tpk[zero+k]=1;


		int dot=nm.length();
		memset(num, 0, sizeof(num));
		REP(i, dot) if (nm[i]=='.'){dot=i;break;}


		REP(i, dot) num[zero-(dot-1-i)]=nm[i]-'0';
		FOR(i, dot+1, nm.length()-1) num[zero+i-dot]=nm[i]-'0';



		int res=INT_MAX;
		memcpy(lb, num, sizeof(num)); memcpy(ub, num, sizeof(num));
		if (sub(lb, tpk, lb))return 1;
		add(ub, tpk, ub);


		checkmin(res, proc());

		memcpy(lb, num, sizeof(num)); memcpy(ub, num, sizeof(num));
		memcpy(temp, num, sizeof(num)); shift(temp, k, temp);
		sub(lb, temp, lb); add(ub, temp, ub);

		checkmin(res, proc());

		return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 2; string Arg1 =  "00."; int Arg2 = 1; verify_case(0, Arg2, shortest(Arg0, Arg1)); }
	void test_case_0() { int Arg0 = 1; string Arg1 =  "1001.2"; int Arg2 = 1; verify_case(0, Arg2, shortest(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arg1 = ".20050"; int Arg2 = 2; verify_case(1, Arg2, shortest(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; string Arg1 = "10000"; int Arg2 = 4; verify_case(2, Arg2, shortest(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1; string Arg1 = "0.901"; int Arg2 = 1; verify_case(3, Arg2, shortest(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 3; string Arg1 = "91.909"; int Arg2 = 2; verify_case(4, Arg2, shortest(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Neaten ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
