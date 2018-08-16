// BEGIN CUT HERE

// END CUT HERE
#line 5 "BuffetLine.cpp"

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


map<string, int> mp;
int n, m;
const int maxn=12, maxm=8;

int dp[two(maxn)][two(maxm)];
int item[maxn];
vi ans;


int proc(int a, int b){
    int &r=dp[a][b];
    if (r!=-1) return r;
    if (a==0) return r=count_bit(b);
    r=INT_MAX;


    if (!(b&1)) REP(i, n) if (a&two(i)){
        int A=b>>1;
        int B=item[i];
        int nb=0;

        while(B){
            if (A && low_bit(A)<low_bit(B)) nb|=low_bit(A), A&=A-1;
            else nb|=low_bit(B), B&=B-1, A&=A-1;
        }
        
        nb|=A;
        checkmin(r, proc(a^two(i), nb));
    }
    if (b) checkmin(r, proc(a, b&b-1)+1);

    return r;
}

int build(int a, int b, int f){
    int r=dp[a][b];
    if (a==0) return 0;

    int pick=-1, nbi;

    if (!(b&1)) REP(i, n) if (a&two(i)){

        int A=b>>1;
        int B=item[i];
        int nb=0;
        while(B){
            if (A && low_bit(A)<low_bit(B)) nb|=low_bit(A), A&=A-1;
            else nb|=low_bit(B), B&=B-1, A&=A-1;
        }
        nb|=A;
        if (r==proc(a^two(i), nb)){ pick=i; nbi=nb; break; }
    }
    if (f!=-1) return pick!=-1 && pick<f;

    if (b && r==proc(a, b&b-1)+1 && (pick==-1 || build(a, b&b-1, pick))) build(a, b&b-1, -1);
    else{
        ans.pb(pick);
        build(a^two(pick), nbi, -1);
    }
    return 0;
}

class BuffetLine {
    public:
        vector <int> order(string food, vector <string> cravings) {
            istringstream ss(food);
            m=0;
            string s;

            mp.clear();
            while(ss>>s) mp[s]=m++;
            n=cravings.size();
            REP(i, n){
                istringstream ss(cravings[i]);
                string s;
                item[i]=0;
                while(ss>>s) item[i]|=two(mp[s]);
            }

            memset(dp, -1, sizeof(dp));
            int res=proc(two(n)-1, 0);

            ans.clear();
            build(two(n)-1, 0, -1);
            return ans;

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
        void test_case_0() { string Arg0 = "applesauce beans carrots dates eggplant"; string Arr1[] = { "beans",
            "applesauce",
            "dates" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 0, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, order(Arg0, Arg1)); }
        void test_case_1() { string Arg0 = "applesauce beans carrots dates eggplant"; string Arr1[] = { "beans",
            "applesauce",
            "beans",
            "dates" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1, 3, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, order(Arg0, Arg1)); }
        void test_case_2() { string Arg0 = "bread water"; string Arr1[] = { "" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, order(Arg0, Arg1)); }
        void test_case_3() { string Arg0 = "A B C D E F"; string Arr1[] = { "A C E D",
            "A B D E F",
            "B C A D",
            "B C F D E",
            "B D C F" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3, 1, 0, 4, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, order(Arg0, Arg1)); }
        void test_case_4() { string Arg0 = "A B C"; string Arr1[] = { "A", "A", "A", "A",
            "B", "B", "B", "B",
            "C", "C", "C", "C" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {8, 4, 0, 9, 5, 1, 10, 6, 2, 11, 7, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, order(Arg0, Arg1)); }
        void test_case_5() { string Arg0 = "A G E F D B H C"; string Arr1[] = { "D C A H",
            "H B F G A",
            "B F G D",
            "F C E B A G",
            "D H B C",
            "B A D F G",
            "E B C F D",
            "A D H E B G",
            "A H B G E C",
            "F D A B C",
            "B D A G C",
            "A G E C F" }
            ; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 4, 1, 10, 9, 6, 2, 3, 11, 8, 7, 5 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, order(Arg0, Arg1)); }

            // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    BuffetLine ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
