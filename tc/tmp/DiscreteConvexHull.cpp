// BEGIN CUT HERE

// END CUT HERE
#line 5 "DiscreteConvexHull.cpp"

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
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=333;

int ya[maxn], yb[maxn];
map<int,int> yl, yh;

class DiscreteConvexHull {
	public:
	long long minArea(vector <string> cells) {
        string s; FE(it, cells) s+=*it+" ";
        REP(i, s.length()) if (s[i]==',') s[i]=' ';

        istringstream ss(s);
        int a, b;
        vector<pii> pl;
        while(ss>>b){ ss>>a; pl.pb(MP(a,b)); }
        int n=pl.size();
        sort(ALL(pl));

        ya[0]=pl[0].ND;
        FOR(i, 1, n) ya[i]=min(ya[i-1], pl[i].ND);
        yb[n-1]=pl[n-1].ND;
        for (int i=n-2; i>=0; --i) yb[i]=min(yb[i+1], pl[i].ND);


        yl.clear(); yh.clear();
        REP(i, n){
            int xo=pl[i].ST;
            if (!yl.count(xo)) yl[xo]=max(ya[i], yb[i]);
            else checkmin(yl[xo], max(ya[i], yb[i]));
        }

        ya[0]=pl[0].ND;
        FOR(i, 1, n) ya[i]=max(ya[i-1], pl[i].ND);
        yb[n-1]=pl[n-1].ND;
        for (int i=n-2; i>=0; --i) yb[i]=max(yb[i+1], pl[i].ND);
        REP(i, n){
            int xo=pl[i].ST;
            if (!yh.count(xo)) yh[xo]=min(ya[i], yb[i]);
            else checkmax(yh[xo], min(ya[i], yb[i]));
        }

        int last=pl[0].ST;
        int pa=yl[last], pb=yh[last];
        ll res=pb-pa+1;
        FE(it, yl) if (it!=yl.begin()){
            int x=it->ST;
            int a=it->ND, b=yh[x];

            //res-=pb-pa+1;
            int lb=min(b,pb), la=max(a,pa);
            if (la<lb) res+=1LL*(x-last-1)*(lb-la+1)+b-a+1;
            else res+=x-last+1+max(b,pb)-min(a,pa), res-=pb-pa+1;
            last=x;
            pa=a; pb=b;

        }


        return res;

    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { string Arr0[] = {"1,7 4,11 6,5 7,1 11,8"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 26LL; verify_case(0, Arg1, minArea(Arg0)); }
    void test_case_1() { string Arr0[] = {"1000000000,1 1,1000000000",
        "1,1 1000000000,1000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1000000000000000000LL; verify_case(1, Arg1, minArea(Arg0)); }
    void test_case_2() { string Arr0[] = {"1563,17653 793487,12"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 809566LL; verify_case(2, Arg1, minArea(Arg0)); }
    void test_case_3() { string Arr0[] = {"1643,152 2342,32 53425,2",
        "52,235 234,6346 265,65 234,23",
        "352,45 128,63",
        "100,200"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 266982LL; verify_case(3, Arg1, minArea(Arg0)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    DiscreteConvexHull ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
