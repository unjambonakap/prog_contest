// BEGIN CUT HERE

// END CUT HERE
#line 5 "InverseSoundex.cpp"

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

const int maxn=18, maxv=8;
const int maxc=26;
ll dp[maxn][4][maxv];//char left, symbol pos, cur symbol
ll pwa[maxn], pwk[maxv][maxn];

int ca[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int cb[]={0, 1, 2, 3, 0, 1, 2, 7, 0, 2, 2, 4, 5, 5, 0, 1, 2, 6, 2, 3, 0, 1, 7, 2, 0, 2};
int cnta[maxv];
int sd[4];
int nsd;

int getc(int a){ REP(i, maxc) if (ca[i]==a) return i; }


ll solve(int cl, int sp, int s){
    ll &r=dp[cl][sp][s];
    if (r!=-1) return r;

    if (sp==nsd) return r=(!cl?1:0);
    if (!cl) return r=0;

    r=0;
    r+=cnta[s]*solve(cl-1, sp, s);//same symbol as right now
    if (s!=sd[sp]) r+=cnta[sd[sp]]*solve(cl-1, sp+1, sd[sp]);// nxt symbol
    if (s) r+=cnta[0]*solve(cl-1, sp, 0);// 0 symbol
    r+=2*solve(cl-1, sp, s);//w, h

    return r;

}

class InverseSoundex {
    public:
        long long howMany(string soundex, int length) {
            int n=length;

            memset(cnta, 0, sizeof(cnta)); REP(i, maxc) ++cnta[cb[i]];




            REPV(i, 4) if (soundex[i]!='0'){ nsd=i+1; break;}
            REP(i, nsd) sd[i]=(!i?cb[getc(soundex[i])]:soundex[i]-'0');
            int ss=sd[0];
            REP(i, nsd) if (i && sd[i]==0) return 0;


            pwa[0]=1; REP(i, n) pwa[i+1]=pwa[i]*maxc;
            REP(k, maxv){
                pwk[k][0]=1;
                REP(i, n) pwk[k][i+1]=pwk[k][i]*(2+cnta[k]);
            }

            memset(dp, -1, sizeof(dp));
            ll res=0;

            
            if (!ss || ss==7){
                //starting with 0 symbol, more tricky: fix the first non zero symbol, which will be deleted
                if (nsd==1){
                    res=res+pwk[0][n-1];
                    FOR(k, 1, 6) REP(j, n-1){//start letter, j junk characters (0 or w, h), then start with symbol k (which will be then be replaced by the starting letter)
                        res=res+pwk[0][j]*cnta[k]*pwk[0][n-j-2];
                        REP(p, n-j-2) res=res+pwk[0][j]*cnta[k]*pwk[k][p]*cnta[k]*pwk[0][n-j-2-p-1];
                    }

                }else{
                    FOR(i, nsd, n){
                        if (nsd==4){
                            FOR(k, 1, 6) REP(j, i-1) res=res+cnta[k]*pwk[0][j]*solve(i-j-2, 1, k)*pwa[n-i];
                        } else{
                            FOR(k, 1, 6) REP(j, i-1){//start letter, j junk characters (0 or w, h), then start with symbol k (which will be then be replaced by the starting letter)
                                res=res+pwk[0][j]*cnta[k]*solve(i-j-2, 1, k)*pwk[0][n-i];
                                REP(p, n-i) res=res+pwk[0][j]*cnta[k]*solve(i-j-2, 1, k)*pwk[sd[nsd-1]][p]*cnta[sd[nsd-1]]*pwk[0][n-i-p-1];
                            }
                        }
                    }
                }


            }else{
                FOR(i, nsd, n){
                    if (nsd==4) res=res+solve(i-1, 1, ss)*pwa[n-i];
                    else{
                        res=res+solve(i-1, 1, ss)*pwk[0][n-i];
                        REP(p, n-i) res=res+solve(i-1, 1, ss)*pwk[sd[nsd-1]][p]*cnta[sd[nsd-1]]*pwk[0][n-i-p-1];
                    }
                }
            }




            return res;



        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arg0 = "M146"; int Arg1 = 4; long long Arg2 = 4LL; verify_case(0, Arg2, howMany(Arg0, Arg1)); }
        void test_case_1() { string Arg0 = "B253"; int Arg1 = 5; long long Arg2 = 2048LL; verify_case(1, Arg2, howMany(Arg0, Arg1)); }
        //void test_case_2() { string Arg0 = "B255"; int Arg1 = 5; long long Arg2 = 192LL; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
        void test_case_2() { string Arg0 = "Z600"; int Arg1 = 5; long long Arg2 = 6145; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
        void test_case_3() { string Arg0 = "H440"; int Arg1 = 9; long long Arg2 = 33239490; verify_case(3, Arg2, howMany(Arg0, Arg1)); }
        //void test_case_3() { string Arg0 = "E000"; int Arg1 = 2; long long Arg2 = 26LL; verify_case(3, Arg2, howMany(Arg0, Arg1)); }
        void test_case_4() { string Arg0 = "K405"; int Arg1 = 7; long long Arg2 = 0LL; verify_case(4, Arg2, howMany(Arg0, Arg1)); }
        void test_case_5() { string Arg0 = "R464"; int Arg1 = 5; long long Arg2 = 53LL; verify_case(5, Arg2, howMany(Arg0, Arg1)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    InverseSoundex ___test; 
    ___test.run_test(3);
} 
// END CUT HERE
