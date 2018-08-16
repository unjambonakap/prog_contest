// BEGIN CUT HERE

// END CUT HERE
#line 5 "MedievalCity.cpp"

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

int v[]={-1, 0, 1, 0, -1};

int dir(char c){
	if (c=='L')return 0;
	if (c=='U')return 1;
	if (c=='R')return 2;
	if (c=='D')return 3;
	assert(0);
}

class MedievalCity {
	public:
		int getDangerousBlocks(vector <string> boundary, int db) {
			string s;
			FE(it, boundary) s+=*it;
			int mx, my;
			mx=my=0;


			int d, od; od=-1;
			int miny=INT_MAX, in=-1;
			REP(i, s.length()){
				int k=1;
				d=dir(s[i]);
				if (d%2==0 && my<miny) miny=my, in=3;
				else if (in!=-1) in=(4+in+d-od)%4;

				if (i+1<s.length() && s[i+1]<='9') k=s[++i]-'0';
				if (i+1<s.length() && s[i+1]<='9') k=k*10+s[++i]-'0';
				mx+=k*v[d], my+=k*v[d+1];
				od=d;
			}
			in=(4+in+dir(s[0])-od)%4;

			set<pii> tb[3];
			mx=my=0;
			REP(i, s.length()){
				int k=1;
				d=dir(s[i]);
				if (i!=0) in=(4+in+d-od)%4;

				if (i+1<s.length() && s[i+1]<='9') k=s[++i]-'0';
				if (i+1<s.length() && s[i+1]<='9') k=k*10+s[++i]-'0';
				FOR(j, 1, k) tb[1].insert(MP(mx+j*v[d]-(in==2||d==2), my+j*v[d+1]-(in==1||d==1))), tb[0].insert(MP(mx+j*v[d]-(in==2||d==2)+v[in], my+j*v[d+1]-(in==1||d==1)+v[in+1]));
				mx+=k*v[d], my+=k*v[d+1];
				od=d;
			}
			int cnt=0;
			REP(l, db){
				int p=(l+1)%3, np=(l+2)%3, op=l%3;
				tb[np].clear();
				FE(it, tb[p]) REP(k, 4) if (!tb[op].count(MP(it->ST+v[k], it->ND+v[k+1])) && !tb[p].count(MP(it->ST+v[k], it->ND+v[k+1]))) tb[np].insert(MP(it->ST+v[k], it->ND+v[k+1]));
				cnt+=tb[p].size();
			}
			return cnt+tb[(db+1)%3].size();
			return 0;

		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		//void test_case_0() { string Arr0[] = {"LURD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; verify_case(0, Arg2, getDangerousBlocks(Arg0, Arg1)); }
		void test_case_0() { string Arr0[] = {"RRRRRRRRRRRRRRDRRDDDLLLLDDDRRRRRRRRDDLL", "LLLLLLLLLLLUUUUUUULLDDDDDDDLLLLLLLLLUUUUUURRRRUUU"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 124; verify_case(0, Arg2, getDangerousBlocks(Arg0, Arg1)); }
		void test_case_1() { string Arr0[] = {"LUUR7D4RDLDDDL7UURU2UU"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 44; verify_case(1, Arg2, getDangerousBlocks(Arg0, Arg1)); }
		void test_case_2() { string Arr0[] = {"L50U50R50D50"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 1716; verify_case(2, Arg2, getDangerousBlocks(Arg0, Arg1)); }
		void test_case_3() { string Arr0[] = {"L50U50U50U50U50R50D50D50D50D50"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 3744; verify_case(3, Arg2, getDangerousBlocks(Arg0, Arg1)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	MedievalCity ___test; 
	___test.run_test(-1); 
}
