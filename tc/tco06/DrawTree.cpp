// BEGIN CUT HERE

// END CUT HERE
#line 5 "DrawTree.cpp"

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


const int maxn=55;
vi children[maxn];
int lnk[maxn];
vs names;
int n;
vs res;

string drawLine(int d){
    string tmp;
    REP(i, d){
        if (lnk[i]) tmp+="| ";
        else tmp+="  ";
    }
    return tmp;


}
void rec(int p, int d){
    vi &t=children[p];
    res.pb(drawLine(d)+"+-"+names[p]);
    sort(ALL(t));
    REP(i, t.size()){
        lnk[d+1]=i<t.size()-1;
        rec(t[i], d+1);
    }
    

}

class DrawTree {
	public:
	vector <string> draw(vector <int> parents, vector <string> _names) {
        names=_names;
        int root;
        REP(i, n) children[i].clear();
        n=parents.size();

        REP(i, n){
            if (parents[i]==-1) root=i;
            else children[parents[i]].pb(i);
        }


        res.clear();
        memset(lnk, 0, sizeof(lnk));

        rec(root, 0);
        return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {-1,0,1,1,0,0,5,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"Root","SubB","LEAF1","LEAF2","LEAF3","SubA","LEAF4","LEAF5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-Root", "  +-SubB", "  | +-LEAF1", "  | +-LEAF2", "  +-LEAF3", "  +-SubA", "    +-LEAF4", "    +-LEAF5" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, draw(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,2,3,4,5,6,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A","B","C","D","E","F","G"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-G", "  +-F", "    +-E", "      +-D", "        +-C", "          +-B", "            +-A" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, draw(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,4,6,6,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A","B","C","D","E","F","G"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-G", "  +-E", "  | +-D", "  |   +-C", "  |     +-B", "  |       +-A", "  +-F" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, draw(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {6,2,3,4,5,6,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A","B","C","D","E","F","G"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-G", "  +-A", "  +-F", "    +-E", "      +-D", "        +-C", "          +-B" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, draw(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {-1,0,1,1,2,2,3,3,0,8,8,9,9,10,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-A", "  +-B", "  | +-C", "  | | +-E", "  | | +-F", "  | +-D", "  |   +-G", "  |   +-H", "  +-I", "    +-J", "    | +-L", "    | +-M", "    +-K", "      +-N", "      +-O" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, draw(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  DrawTree ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
