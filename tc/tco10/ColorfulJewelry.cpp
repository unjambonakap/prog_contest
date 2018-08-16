// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulJewelry.cpp"

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


const int maxn=45;
const int maxr=maxn*maxn;
const int mod=1e9+9;
const char *rmp="RGB";


int A[3][maxn][maxn];
int n, m;
int cnt[maxr][maxr];
ll scnk[maxr][maxr];
ll fact[3*maxr], ifact[3*maxr];

int cnk(int n, int k){return fact[n]*ifact[k]%mod*ifact[n-k]%mod;}

ll fast_exp(ll a, int p){
    ll r=1;
    while(p){
        if (p&1) r=r*a%mod;
        p>>=1;
        a=a*a%mod;
    }
    return r;
}

int rect(int c, int i, int j, int a, int b){
    int r=A[c][i][j];
    r-=i-a<0?0:A[c][i-a][j];
    r-=j-b<0?0:A[c][i][j-b];
    r+=i-a<0||j-b<0?0:A[c][i-a][j-b];
    return r;
}

class ColorfulJewelry {
	public:
	int getChains(vector <string> mp, int K) {

        fact[0]=ifact[0]=1;
        for (int i=1; i<3*maxr; ++i) fact[i]=fact[i-1]*i%mod, ifact[i]=fast_exp(fact[i], mod-2);


        n=mp.size(); m=mp[0].length();

        memset(A, 0, sizeof(A));
        REP(k, 3) REP(i, n) REP(j, m) A[k][i][j]=(mp[i][j]==rmp[k])+(i>0?A[k][i-1][j]:0)+(j>0?A[k][i][j-1]:0)-(j>0&&i>0?A[k][i-1][j-1]:0);



        memset(cnt, -1, sizeof(cnt));

        REP(i, n) REP(j, m) REP(a, i+1) REP(b, m){
            int tb[3];
            REP(k, 3){
                tb[k]=rect(k, i, j, K, K)+rect(k, a, b, K, K);
                if (i-K>=a);
                else if (b<=j && j-K<b) tb[k]-=rect(k, a, b, K+a-i, K+b-j);
                else if (b>j && b-K<j) tb[k]-=rect(k, a, j, K+a-i, K+j-b);
            }
            checkmax(cnt[tb[0]][tb[1]], tb[2]);
        }
        REPV(i, maxr-1) REPV(j, maxr-1) checkmax(cnt[i][j], max(cnt[i+1][j], cnt[i][j+1]));

        REP(i, maxr){
            scnk[i][0]=1;
            for (int k=1; k<maxr; ++k) scnk[i][k]=(scnk[i][k-1]+cnk(i+k, k))%mod;
        }


        ll res=0;
        REP(i, maxr) REP(j, maxr) if (cnt[i][j]!=-1){
            ll s=cnk(i+j, j)*scnk[i+j][cnt[i][j]]%mod;
            ll b=0;
            if (i%2==0 && j%2==0){
                b=cnk((i+j)/2, j/2)*scnk[(i+j)/2][cnt[i][j]/2]%mod;
                if (cnt[i][j]&1) b=b*2%mod;
                else if (cnt[i][j]) b=(b+cnk((i+j)/2, j/2)*scnk[(i+j)/2][cnt[i][j]/2-1])%mod;

            }else if (i%2==0 || j%2==0) b=cnk((i+j)/2, j/2)*scnk[(i+j)/2][cnt[i][j]/2]%mod;

            if (i+j==0) s=(s+mod-2)%mod;
            s=(s+b)*ifact[2]%mod;
            //printf("%Ld %Ld => %Ld\n", res, s, (res+s)%mod);
            res=(res+s)%mod;
        }
        return res;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { string Arr0[] = { "RGB" }
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 6; verify_case(0, Arg2, getChains(Arg0, Arg1)); }
        void test_case_1() { string Arr0[] = { "RGB" }
            ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 9; verify_case(1, Arg2, getChains(Arg0, Arg1)); }
            void test_case_2() { string Arr0[] = { "RGB" }
                ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 9; verify_case(2, Arg2, getChains(Arg0, Arg1)); }
                void test_case_3() { string Arr0[] = { "RRRRR", 
                    "RGGRR", 
                    "RGGGG", 
                    "RRRGG" }
                    ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 280; verify_case(3, Arg2, getChains(Arg0, Arg1)); }
                    void test_case_4() { string Arr0[] = { "RRRRRRRRRR", 
                        "RRRRRRRRRR", 
                        "RRRRRRRRRR", 
                        "RRRRRRRRRR", 
                        "RRRRRRRRRR", 
                        "RRRRRRRRRR", 
                        "RRRRRRRRRR", 
                        "RRRRRRRRRR", 
                        "RRRRRRRRRR", 
                        "RRRRRRRRRR" }
                        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 68; verify_case(4, Arg2, getChains(Arg0, Arg1)); }
                        void test_case_5() { string Arr0[] = { "RRRGGGGG", 
                            "RRRGGGGG", 
                            "RRRGGBBB", 
                            "GGGGGBBB", 
                            "GGGGGBBB" }
                            ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 613435159; verify_case(5, Arg2, getChains(Arg0, Arg1)); }

                            // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    ColorfulJewelry ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE

