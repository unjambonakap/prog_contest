// BEGIN CUT HERE

// END CUT HERE
#line 5 "NotchedWoodBarsPuzzle.cpp"

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

const int maxk=4, maxn=8;
int n, k;
int a[maxk], b[maxk], seen[maxn];
int na[maxk];
int inva[maxk], invb[maxk];
int sgna;

int bars[maxn];
int invbars[maxn];
int pool[maxk], poola[maxk];
int took[maxk];
int cnt;
int tba[maxk][maxk], tbb[maxk][maxk];

set<int> s;
int inv(int m, int k){
    if (k==0) return 0;
    return inv(m&(two(k-1)-1), k-1)<<1|(m&two(k-1))>>(k-1);
}

void rotate(int tb[][maxk]){
    int ntb[maxk][maxk];
    REP(i, k) REP(j, k) ntb[k-1-i][k-1-j]=tb[i][j];
    memcpy(tb, ntb, sizeof(ntb));
}
void flip(int tb[][maxk]){
    int ntb[maxk][maxk];
    REP(i, k) REP(j, k) ntb[i][j]=tb[i][k-1-j];
    memcpy(tb, ntb, sizeof(ntb));
}
int build(int tb[][maxk]){
    int m=0;
    REP(i, k) REP(j, k) if (tb[i][j]) m|=two(i*k+j);
    return m;
}

int checkit(int p){
    memset(took, 0, sizeof(took)); memset(pool, 0, sizeof(pool));

    REP(i, k){
        int m=(p&two(i)?invbars[a[i]]:bars[a[i]]);
        poola[i]=m;
        REP(j, k) if (!(m&two(j))) pool[k-1-j]|=two(i);

    }

    REP(i, k){
        int fd=0;
        REP(j, k) if (!took[j] && (pool[i]==b[j] || pool[i]==invb[j])){took[j]=1; fd=1; break;}
        if (!fd) return 0;
    }
    REP(i, k) REP(j, k) tba[i][j]=bool(poola[i]&two(j)), tbb[i][j]=bool(pool[i]&two(j));

    int tmp=build(tba)|(build(tbb)<<16);
    if (s.count(tmp)) return 0;
    s.insert(tmp);
    rotate(tba); rotate(tbb);


    tmp=build(tba)|(build(tbb)<<16);
    s.insert(tmp);

    flip(tba); flip(tbb);
    tmp=build(tbb)|(build(tba)<<16);
    s.insert(tmp);

    rotate(tba); rotate(tbb);
    tmp=build(tbb)|(build(tba)<<16);
    s.insert(tmp);

    return 1;
}

void rec(int pos, int rem){
    if (pos==n){
        if (rem!=k) return;
        int nb=0;

        REP(i, n) if (!seen[i]) b[nb]=bars[i], invb[nb++]=invbars[i];
        memcpy(a, na, sizeof(a));
        do{ 
            REP(j, two(k)) if (checkit(j)) ++cnt;
        }while(next_permutation(a, a+k));

        return;
    }
    na[rem]=pos;
    seen[pos]=1;
    rec(pos+1, rem+1);
    seen[pos]=0;
    rec(pos+1, rem);
}

class NotchedWoodBarsPuzzle {
    public:
        int countSolutions(vector <string> _bars) {
            n=_bars.size(); k=n/2;
            cnt=0;
            memset(bars, 0, sizeof(bars));
            REP(i, n) REP(j, k) bars[i]|=(_bars[i][j]=='D'?two(j):0);
            REP(i, n) invbars[i]=inv(bars[i], k);

            s.clear();
            rec(0, 0);

            return cnt;


        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { string Arr0[] = {"SD", "SD", "SD", "SD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, countSolutions(Arg0)); }
        void test_case_0() { string Arr0[] = {"DS", "SS", "SD", "DD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, countSolutions(Arg0)); }
        void test_case_1() { string Arr0[] = {"SDS", "SDS", "SDS", "DDD","SSS","DDD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, countSolutions(Arg0)); }
        void test_case_2() { string Arr0[] = {"SDD", "SSS", "SDS", "DDD", "SDD", "DSS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, countSolutions(Arg0)); }
        void test_case_3() { string Arr0[] = {"SDDS", "SDDS", "SDDS", "SDDS", "SDDS", "SDDS", "SDDS", "SDDS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, countSolutions(Arg0)); }
        void test_case_4() { string Arr0[] = {"DSDD", "DDSD", "SDDD", "SSSS", "DSSD", "DSSS", "SSDD", "SDSD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 80; verify_case(4, Arg1, countSolutions(Arg0)); }
        void test_case_5() { string Arr0[] = {"SSSS","SSSS","SSSS","SSSS","DDDD","DDDD","DDDD","DDDD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(5, Arg1, countSolutions(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    NotchedWoodBarsPuzzle ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
