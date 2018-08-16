// BEGIN CUT HERE

// END CUT HERE
#line 5 "StudentsOrdering.cpp"

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



struct d{
    string n;
    int h;
    bool operator<(const d &a)const{
        if (h!=a.h) return h<a.h;
        return n<a.n;
    }
};



string solve(const vector<d> &a, const vector<d> &b){
    if (a.size()>b.size()+1) return "";
    string res;
    res="";
    int h=-1;
    REP(i, a.size()+b.size()){
        const d &x=i&1?b[i/2]:a[i/2];
        if (h>x.h) return "";
        h=x.h;
        res+=x.n+"-";

    }

    res.erase(res.length()-1);
    return res;

}


class StudentsOrdering {
	public:
	string findOrder(vector <string> students) {
        vector<d> a, b;
        FE(it, students){
            istringstream ss(*it);
            string x, y, z;
            ss>>x>>y>>z;
            if (z=="boy") a.pb((d){x, toInt(y)});
            else b.pb((d){x, toInt(y)});

        }
        sort(ALL(a));
        sort(ALL(b));
        string res;
        if (a.size()>b.size()) res=solve(a, b);
        else if (a.size()<b.size()) res=solve(b, a);
        else{
            string tmpa, tmpb;
            tmpa=solve(a, b);
            tmpb=solve(b, a);
            if (tmpa!="" && tmpb!="") return res=min(tmpa, tmpb);
            else if (tmpa=="") res=tmpb;
            else res=tmpa;
        }
        return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"Alex 180 boy", 
 "Josh 181 boy", 
 "Mary 158 girl", 
 "An 158 girl", 
 "Tanya 180 girl", 
 "Ted 158 boy"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "An-Ted-Mary-Alex-Tanya-Josh"; verify_case(0, Arg1, findOrder(Arg0)); }
	void test_case_1() { string Arr0[] = {"Alex 180 boy", 
 "Josh 158 boy", 
 "Mary 180 girl", 
 "An 158 girl", 
 "Mary 180 girl", 
 "Ted 158 boy"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Josh-An-Ted-Mary-Alex-Mary"; verify_case(1, Arg1, findOrder(Arg0)); }
	void test_case_2() { string Arr0[] = {"Alex 180 boy", 
 "Josh 170 boy", 
 "An 158 girl", 
 "Mary 180 girl", 
 "Ted 175 boy"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(2, Arg1, findOrder(Arg0)); }
	void test_case_3() { string Arr0[] = {"Mary 175 girl"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Mary"; verify_case(3, Arg1, findOrder(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  StudentsOrdering ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
