// BEGIN CUT HERE

// END CUT HERE
#line 5 "CrossingTheRiver.cpp"

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

const int maxn=55;
vi A;
int n;
int na, nb, d;
int ND;
int sta, stb;

int dp[maxn][maxn][maxn][3][3];

int go(int p, int na, int nb, int fa, int fb){
    if (!na && fa!=2){
        if (A[p-1]!=ND) return 0;
        fa=2;
    }
    if (!nb) fb=2;
    if (!na && !nb) return 1;
    if (p==n) return 0;

    int &r=dp[p][na][nb][fa][fb];
    if (r!=-1) return r;
    r=0;
    int da=A[p]-(sta!=na?A[p-1]:d);
    int db=A[p]-(stb!=nb?A[p-1]:ND-d);
    if (sta==na) fa=0;
    int nfa=fa==2?2:da+fa;
    int nfb=fb==2?2:db+fb;

    if ((fa==2 || da+fa<2) && (fb==2 || db+fb<2));
    else return 0;

    r|=go(p+1,na,nb,nfa,nfb);
    if (na) r|=go(p+1,na-1,nb,0,nfb);
    

    if (nb && db>=0 && db<2) r|=go(p+1,na,nb-1,nfa,0);
    return r;
}

int checkit(){
    sta=na;
    stb=nb;
    int cnt=0;
    REP(i,n) if (A[i]==d) ++cnt;
    if (cnt>=na) return 1;
    REP(i,n){
        memset(dp,-1,sizeof(dp));
        ND=A[i];
        if (go(0,na,nb,0,2)) return 1;
    }
    return 0;
}

class CrossingTheRiver {
    public:
        string isItEvenPossible(int wa, int lw, vector <int> bh, int dx) {
            na=wa; nb=lw; A=bh; d=dx;
            sort(ALL(A));
            n=A.size();
            return checkit()?"POSSIBLE":"IMPOSSIBLE";
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arg0 = 3; int Arg1 = 3; int Arr2[] = {3,4,4,5,5, 6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; string Arg4 = "POSSIBLE"; verify_case(0, Arg4, isItEvenPossible(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arr2[] = {3,4,4,5,6, 6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; string Arg4 = "IMPOSSIBLE"; verify_case(1, Arg4, isItEvenPossible(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_2() { int Arg0 = 5; int Arg1 = 2; int Arr2[] = {4,4,4,4,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; string Arg4 = "POSSIBLE"; verify_case(2, Arg4, isItEvenPossible(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_3() { int Arg0 = 5; int Arg1 = 5; int Arr2[] = {5,5,5,5,5,5, 2,3,4,4,6, 7, 3, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; string Arg4 = "POSSIBLE"; verify_case(3, Arg4, isItEvenPossible(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_4() { int Arg0 = 5; int Arg1 = 7; int Arr2[] = {6,6,6,6,6,6,6, 6,6,6,6,6,7,8,9,10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; string Arg4 = "POSSIBLE"; verify_case(4, Arg4, isItEvenPossible(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_5() { int Arg0 = 1; int Arg1 = 1; int Arr2[] = {5,3,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; string Arg4 = "IMPOSSIBLE"; verify_case(5, Arg4, isItEvenPossible(Arg0, Arg1, Arg2, Arg3)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    CrossingTheRiver ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
