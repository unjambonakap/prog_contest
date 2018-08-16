// BEGIN CUT HERE

// END CUT HERE
#line 5 "MoreNim.cpp"

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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)

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

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
ll toll(string s){ll a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=55;
ll A[maxn];
ll B[maxn];
int n;

int rank(int n){
    int p=0;
    memcpy(A, B, sizeof(A));
    REP(i, 64){
        int x=-1;
        FOR(j, p, n) if (A[j]&two(i)){x=j; break;}
        if (x==-1) continue;
        swap(A[p], A[x]);
        FOR(j, p+1, n) if (A[j]&two(i)) A[j]^=A[p];
        ++p;
    }
    return p;
}

class MoreNim {
	public:
	long long bestSet(vector <string> heaps) {
        n=heaps.size();
        REP(i, n) B[i]=toll(heaps[i]);
        sort(B, B+n, greater<ll>());
        ll ans=0;

        int p=0;
        REP(i, n){
            B[p]=B[i];
            if (rank(p+1)==p+1) ++p;
            else ans+=B[i];
        }
        return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = {"5","5","6","6","5","5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 21LL; verify_case(0, Arg1, bestSet(Arg0)); }
	void test_case_0() { string Arr0[] = {"2128485358", "1992373084", "174529906", "262870535", "360254783", "1682124923", "945624172", "1897230586", "26609193", "1412319055", "2057060638", "275847260", "180619818", "2102268008", "924468313", "628911214", "1494816820", "2006217182", "2139902124", "26102161", "334986831", "211230172", "1683448218", "1622934781", "605963119", "1347434603", "683036448", "2033069731", "1693598611", "2115055746", "1143765350", "1690387551", "1359829534", "1439111246", "1563166915", "1088438881", "1980249721", "1970276542", "688356855", "547241181", "998586089", "1792957522", "1561661091", "756575984", "1233151405", "2041400613", "489097739", "269052629", "433484891", "1367491127"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 21LL; verify_case(0, Arg1, bestSet(Arg0)); }
	void test_case_1() { string Arr0[] = {"1","2","3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(1, Arg1, bestSet(Arg0)); }
	void test_case_2() { string Arr0[] = {"1","2","3","4","5","6","7","8","9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 16LL; verify_case(2, Arg1, bestSet(Arg0)); }
	void test_case_3() { string Arr0[] = {"1","2","4","8","16","32","64","128","256"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(3, Arg1, bestSet(Arg0)); }
	void test_case_4() { string Arr0[] = {"12","13","16","121","13","14","52","23","1","29"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 27LL; verify_case(4, Arg1, bestSet(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  MoreNim ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
