// BEGIN CUT HERE

// END CUT HERE
#line 5 "DistantPoints.cpp"

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


pii solve(int n, int k){
    int nx=two(n), ny=two(n);
    if (k==0) return MP(0, 0);
    if (k==1) return MP(nx, ny);
    if (k==2) return MP(0, ny);
    if (k==3) return MP(nx, 0);

    k-=4;
    int step=0;
    int nsqr=1;
    for (;; step^=1){
        int cnt;
        if (step==0){
            cnt=nsqr*nsqr;
            if (k<cnt){
                int x=k/nsqr, y=k%nsqr;
                return MP(nx/nsqr*x+nx/nsqr/2, ny/nsqr*y+ny/nsqr/2);
            }
            k-=cnt;
        }else{
            cnt=nsqr*(nsqr+1)*2;
            if (k<cnt){
                int x=0, y=0;
                int bit=0;
                while(1){
                    if (k<nsqr+bit) return MP(x, (bit?0:nx/nsqr/2)+nx/nsqr*k);



                    x+=nx/nsqr/2;
                    k-=nsqr+bit;
                    bit^=1;
                }
            }
            nsqr<<=1;
            k-=cnt;
        }
    }

}

class DistantPoints {
    public:
        vector <int> getKth(int N, int K) {
            pii p=solve(N, K-1);
            vi v;
            v.pb(p.ST+1);
            v.pb(p.ND+1);
            return v;

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
        //void test_case_0() { int Arg0 = 4; int Arg1 = 2; int Arr2[] = {17, 17 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getKth(Arg0, Arg1)); }
        void test_case_0() { int Arg0 = 2; int Arg1 = 11; int Arr2[] = {2, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getKth(Arg0, Arg1)); }
        void test_case_1() { int Arg0 = 4; int Arg1 = 3; int Arr2[] = {1, 17 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getKth(Arg0, Arg1)); }
        void test_case_2() { int Arg0 = 4; int Arg1 = 5; int Arr2[] = {9, 9 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getKth(Arg0, Arg1)); }
        void test_case_3() { int Arg0 = 3; int Arg1 = 14; int Arr2[] = {1, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getKth(Arg0, Arg1)); }
        void test_case_4() { int Arg0 = 5; int Arg1 = 1089; int Arr2[] = {33, 32 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, getKth(Arg0, Arg1)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    DistantPoints ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
