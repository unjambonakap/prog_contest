// BEGIN CUT HERE

// END CUT HERE
#line 5 "SplitSubgraphs.cpp"

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

const int maxn=20;
int graph[maxn][maxn];
int e[two(maxn)], f[two(maxn)];
int n;
int pos[maxn];

int solve(int m, int p, const vi &a, int b){
    if (p==n) return 1;
    int res=solve(m, p+1, a, b);

    vi na;
    if ((e[m]&m)==m) na.pb(m);
    if ((f[m]&m)==0) na.pb(two(p));
    m|=two(p);
    pos[p]=b;
    REP(k, 2){
        int x=k?two(p):0;
        FE(it, a){
            int v=*it|x;
            if ((e[v]&v)==v && (f[m^v]&(m^v))==0) na.pb(v);
        }
    }
    if (na.size()) res+=solve(m, p+1, na, b+1);
    return res;

}

class SplitSubgraphs {
    public:
        int howMany(vector <string> tmp) {
            n=tmp.size();
            REP(i, n) REP(j, n) graph[i][j]=tmp[i][j]=='1';
            e[0]=0;
            REP(i, n){
                e[two(i)]=two(i);
                REP(j, n) if (graph[i][j])  e[two(i)]|=two(j);
                f[two(i)]=e[two(i)]^two(i);
            }
            REP(i, two(n)) if (count_bit(i)>=2) e[i]=e[low_bit(i)]&e[i^low_bit(i)], f[i]=f[low_bit(i)]|f[i^low_bit(i)];

            int ans=0;
            REP(i, n) REP(j, i){
                vi s;

                s.pb(two(i));
                s.pb(two(j));
                pos[0]=j; pos[1]=i;
                ans+=solve(two(i)|two(j), i+1, s, 2); 
            }

            return ans;

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {"011",
            "101",
            "110"
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, howMany(Arg0)); }
        //void test_case_1() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, howMany(Arg0)); }
        void test_case_1() { string Arr0[] = {
            "01111111111111111111", "10111111111111111111", "11011111111111111111", "11101111111111111111", "11110111111111111111", "11111011111111111111", "11111101111111111111", "11111110111111111111", "11111111011111111111", "11111111101111111111", "11111111110000000000", "11111111110000000000", "11111111110000000000", "11111111110000000000", "11111111110000000000", "11111111110000000000", "11111111110000000000", "11111111110000000000", "11111111110000000000", "11111111110000000000"
             }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, howMany(Arg0)); }
        void test_case_2() { string Arr0[] = {"0000",
            "0000",
            "0001",
            "0010"
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 11; verify_case(2, Arg1, howMany(Arg0)); }
        void test_case_3() { string Arr0[] = {"0100",
            "1000",
            "0001",
            "0010"
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, howMany(Arg0)); }
        void test_case_4() { string Arr0[] = {"01100",
            "10110",
            "11001",
            "01001",
            "00110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(4, Arg1, howMany(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    SplitSubgraphs ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
//01111111111111111111, 10111111111111111111, 11011111111111111111, 11101111111111111111, 11110111111111111111, 11111011111111111111, 11111101111111111111, 11111110111111111111, 11111111011111111111, 11111111101111111111, 11111111110111111111, 11111111111011111111, 11111111111101111111, 11111111111110111111, 11111111111111011111, 11111111111111101111, 11111111111111110111, 11111111111111111011, 11111111111111111101, 11111111111111111110
