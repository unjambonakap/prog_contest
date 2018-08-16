// BEGIN CUT HERE

// END CUT HERE
#line 5 "AkariDaisukiDiv1.cpp"

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

const int mod=1e9+7;
const int maxn=103;
int N;


int doit(string a, string b){

    int res=0;
    REP(i,a.length()-b.length()+1){
        int fd=1;
        REP(j,b.length()) if (b[j]!=a[i+j]){fd=0; break;}
        res+=fd;
    }
    return res;
}


int faste(int a, int p){ int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*a*x%mod; return x; }

class AkariDaisukiDiv1 {
    public:
        int countF(string A, string B, string C, string S, string F, int k) {
            while(k&&S.length()<F.length()) S=A+S+B+S+C, --k;
            if (S.length()<F.length()) return 0;
            string st=S, nd=S;
            st.erase(F.length()-1);
            nd.erase(0,nd.length()-F.length()+1);

            int bc=doit(S,F);
            int add=0;
            while(k){
                string nst, nnd;
                nst=A+st;
                nnd=nd+C;
                add=doit(nst,F)+doit(nnd,F)+doit(nd+B+st,F);
                bc=(2ll*bc+add)%mod;

                nst.erase(F.length()-1);
                nnd.erase(0,nnd.length()-F.length()+1);
                --k;

                if (nst==st && nnd==nd) break;
                st=nst; nd=nnd;
            }
            
            int res=(1ll*faste(2,k)*(add+bc)-add)%mod;
            return res;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arg0 = "a"; string Arg1 = "b"; string Arg2 = "c"; string Arg3 = "x"; string Arg4 = "axb"; int Arg5 = 2; int Arg6 = 2; verify_case(0, Arg6, countF(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
        void test_case_1() { string Arg0 = "a"; string Arg1 = "b"; string Arg2 = "c"; string Arg3 = "x"; string Arg4 = "abcdefghij"; int Arg5 = 1; int Arg6 = 0; verify_case(1, Arg6, countF(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
        void test_case_2() { string Arg0 = "a"; string Arg1 = "a"; string Arg2 = "a"; string Arg3 = "b"; string Arg4 = "aba"; int Arg5 = 2; int Arg6 = 4; verify_case(2, Arg6, countF(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
        void test_case_3() { string Arg0 = "a"; string Arg1 = "b"; string Arg2 = "c"; string Arg3 = "d"; string Arg4 = "baadbdcbadbdccccbaaaadbdcbadbdccbaadbdcba"; int Arg5 = 58; int Arg6 = 191690599; verify_case(3, Arg6, countF(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
        void test_case_4() { string Arg0 = "a"; string Arg1 = "x"; string Arg2 = "y"; string Arg3 = "b"; string Arg4 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"; int Arg5 = 49; int Arg6 = 1; verify_case(4, Arg6, countF(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
        void test_case_5() { string Arg0 = "waai"; string Arg1 = "akari"; string Arg2 = "daisuki"; string Arg3 = "usushio"; string Arg4 = "id"; int Arg5 = 10000000; int Arg6 = 127859200; verify_case(5, Arg6, countF(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
        void test_case_6() { string Arg0 = "vfsebgjfyfgerkqlr"; string Arg1 = "ezbiwls"; string Arg2 = "kjerx"; string Arg3 = "jbmjvaawoxycfndukrjfg"; string Arg4 = "bgjfyfgerkqlrvfsebgjfyfgerkqlrvfsebgjfyfgerkqlrvfs"; int Arg5 = 1575724; int Arg6 = 483599313; verify_case(6, Arg6, countF(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    AkariDaisukiDiv1 ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
