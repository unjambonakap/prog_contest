// BEGIN CUT HERE

// END CUT HERE
#line 5 "SequenceMerger.cpp"

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


const int maxn=57;
const int thres=1e9;
int ne, na, ng;
vi elist[maxn];
int alist[maxn][3];
int glist[maxn][3];

int getNum(string s){
	if (s.size()>10) return 1e9+1;
	ll t;
	istringstream(s)>>t;
	if (t>1e9)return 1e9+1;
	return t;
}

int cnt_infa(int p, int n){
	if (n<alist[p][0]) return 0;
	if (alist[p][1]==0) return (n>=alist[p][0]?alist[p][2]:0);

	return min(alist[p][2], (n-alist[p][0])/alist[p][1]+1);
}
int cnt_infe(int p, int n){
	REP(i, elist[p].size()) if (elist[p][i]>n) return i;
	return elist[p].size();
}
	

int cnt_infg(int p, int n){
	if (glist[p][1]==0) return glist[p][2]-(n<glist[p][1]);
	if (glist[p][1]==1) return (n>=glist[p][0]?glist[p][2]:0);
	ll a=glist[p][0];
	int cnt=0;
	while(a<=n && cnt<glist[p][2]) ++cnt, a*=glist[p][1];
	//printf("%d %d => %d\n", p, n, cnt);
	return cnt;
}

class SequenceMerger {
	public:
	vector <int> getVal(vector <string> seqs, vector <int> positions) {
		ne=na=ng=0;
		REP(i, seqs.size()){
			istringstream ss(seqs[i]);
			string tmp;
			ss>>tmp;
			if (tmp[0]=='E'){
				elist[ne]=vi();
				while(ss>>tmp) elist[ne].pb(getNum(tmp));
				sort(ALL(elist[ne]));
				ne++;
			}else if (tmp[0]=='G'){
				REP(i, 3) ss>>tmp, glist[ng][i]=getNum(tmp);
				++ng;

			}else if (tmp[0]=='A'){
				REP(i, 3) ss>>tmp, alist[na][i]=getNum(tmp);
				++na;

			}else assert(0);

		}
//		printf("%d %d %d\n", na, ne, ng);
		vi res;
		FE(it, positions){

			int H, T, M;
			T=-1; H=1e9+1;
			bool fd=true;
			while(H>T+1){
				M=(T+H)/2;
				ll p=0;
				REP(i, na) p+=cnt_infa(i, M);
				REP(i, ne) p+=cnt_infe(i, M);
				REP(i, ng) p+=cnt_infg(i, M);
	//			printf("%d => %Ld\n", M, p);
				
				if (p>=*it) H=M;
				else T=M;
			}
			res.pb(H==1e9+1?-1:H);
		}
		return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"E 1 1000000000 1000000001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1000000000, -1, -1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getVal(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"A 1 1 10", "G 1 2 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 2, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, -1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getVal(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"A 1000000000 1000000000 1000000000","G 100000000000000000 1000000000000 100000000000000", "E 1000000000000000 10000000 10 1111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 1111, 10000000, 1000000000, -1, -1, -1, -1, -1, -1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getVal(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"G 1 1 999999999", "E 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,999999999,1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getVal(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"A 100 341 1524", "G 1 3 45235", "E 653 87 12341 8785 123 543"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100000,1,10,10000,100,1000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-1, 1, 441, -1, 28403, 334621 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, getVal(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SequenceMerger ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
