// BEGIN CUT HERE

// END CUT HERE
#line 5 "RemoveGame.cpp"

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
typedef vector<string> vs;

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

const int maxn=25;
int R;
ll A[2][maxn][maxn][maxn][2][2][2];//left,right,num of o, num of x, player, leftmost, rightmost
int n;


//ll solve(int a, int b, int o, int p){
//    ll &r=A[a][b][o][p];
//    if (r!=-1) return r;
//    if (s[a+1]=='o') return r=solve(a+1, b, o+1, p);
//    if (s[b-1]=='x') return r=solve(a, b-1, o, p);
//    if (a==b+1) return r=(o>=n-o&&o>=R);
//
//    r=0;
//    if (!p){
//        r+=solve(a+1, b, o, p^1);
//        if (s[a+1]=='?') r+=solve(a+1, b, o+1, p^1);
//    }else{
//        r+=solve(a, b-1, o, p^1);
//        if (s[b-1]=='?') r+=solve(a, b-1, o, p^1);
//    }
//    return r;
//}
const char *S="ox";

int simul(string s){
    int a=1, b=n-2;
    int x=1, y=1;
    int p=0;
    while(a!=b){
        if (s[a]=='o') ++x, ++a;
        else if (s[b]=='x') --b, ++y;
        else{
            if (!p){
                assert(s[a]=='x');
                ++a;
            }
            else{
                assert(s[b]=='o');
                --b;
            }
            p^=1;
        }
    }
    if (s[a]=='o') ++x;
    else ++y;
    return (x>y && x>=R);


}
ll solve(string s){

    int k, nk; k=0, nk=1;
    memset(A, 0, sizeof(A));
    //int a=1, b=n-2;
    A[0][n-1][0][0][0][0][1]=1;
    //REP(i, 2) if (s[a]!=S[1^i]) REP(j, 2) if (s[b]!=S[1^j]) A[0][b][1][1][0][i][j]=1;
    ll res=0;
    for (int a=0; a<n-1; ++a){
        memset(A[nk], 0, sizeof(A[nk]));
        REPV(p, 2) for (int b=n-1; b>=a; --b) for (int o=0; o<=a; ++o) for (int x=0; x<=n-b; ++x)  REP(i, 2) REP(j, 2) if (A[k][b][o][x][p][i][j]){
            ll v=A[k][b][o][x][p][i][j];
            if (a==b){
                if (i==j && !i) res+=(o+1>=R && o+1>x?v:0);
                if (i==j && i) res+=(o>=R && o>x+1?v:0);
            }else{
                if (!i){
                    REP(ni, 2) if (s[a+1]!=S[1^ni]) A[nk][b][o+1][x][p][ni][j]+=v;
                }else if (j){
                    REP(nj, 2) if (s[b-1]!=S[1^nj]) A[k][b-1][o][x+1][p][i][nj]+=v;
                }else if (!p){
                    assert(i);
                    assert(!j);
                    REP(ni, 2) if (s[a+1]!=S[1^ni]) A[nk][b][o][x][p^1][ni][j]+=v;
                }else{
                    assert(!j);
                    assert(i);
                    REP(nj, 2) if (s[b-1]!=S[1^nj]) A[k][b-1][o][x][p^1][i][nj]+=v;
                }


            }
        }
        k=nk; nk^=1;
    }

    return res;

}

class RemoveGame {
    public:
        long long countWinning(string field, int _R) {
            string X=field;
            R=_R;
            n=X.length();
            vi x;
            REP(i, n) if (X[i]=='?') x.pb(i);
            ll res=0;
            //return solve(X);
            REP(i, two(x.size())){
                string s=X;
                REP(j, x.size()) s[x[j]]=(i&two(j)?'x':'o');
                //cout<<s<<endl;
                res+=simul(s);
            }

            return res;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arg0 = "o??x"; int Arg1 = 2; long long Arg2 = 2LL; verify_case(0, Arg2, countWinning(Arg0, Arg1)); }
        void test_case_1() { string Arg0 = "o??x"; int Arg1 = 3; long long Arg2 = 1LL; verify_case(1, Arg2, countWinning(Arg0, Arg1)); }
        void test_case_2() { string Arg0 = "oxxxxoooox"; int Arg1 = 2; long long Arg2 = 1LL; verify_case(2, Arg2, countWinning(Arg0, Arg1)); }
        void test_case_3() { string Arg0 = "ooooxxoxxx"; int Arg1 = 1; long long Arg2 = 0LL; verify_case(3, Arg2, countWinning(Arg0, Arg1)); }
        void test_case_4() { string Arg0 = "ox?o?ox"; int Arg1 = 3; long long Arg2 = 3LL; verify_case(4, Arg2, countWinning(Arg0, Arg1)); }
        void test_case_5() { string Arg0 = "o????xooxooxxxxxxx"; int Arg1 = 5; long long Arg2 = 1LL; verify_case(5, Arg2, countWinning(Arg0, Arg1)); }
        void test_case_6() { string Arg0 = "oxxxxxxxxxoooxooxoooooooooooo??????x"; int Arg1 = 5; long long Arg2 = 64LL; verify_case(6, Arg2, countWinning(Arg0, Arg1)); }
        void test_case_7() { string Arg0 = "oo???xx???xx???oxox???xx"; int Arg1 = 7; long long Arg2 = 126LL; verify_case(7, Arg2, countWinning(Arg0, Arg1)); }
        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    RemoveGame ___test; 
    ___test.run_test(7);
} 
// END CUT HERE
