// BEGIN CUT HERE

// END CUT HERE
#line 5 "CircuitDesign.cpp"

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

const int maxn=55;
const int mod=1000000007;

ll cnk[maxn][maxn];
ll fact[maxn];

vi e[2][maxn];
int visited[maxn];
int n;
vi sa, sb;

void dfs(int a){
    if (visited[a]) return;
    visited[a]=1;
    sa.pb(a);
    FE(it, e[0][a]) FE(itb, e[1][*it]) dfs(*itb);
}

ll proc(){
    int na=sa.size();

    ll ans=0;
    REP(i, na) FE(it, e[0][sa[i]]){
        int pos[2];
        pos[0]=sa[i], pos[1]=*it;
        int p=-1;
        ll tmp=1;
        REP(i, 2) if (e[i][pos[i]].size()>=2){
            if (p!=-1) goto out;
            p=i;
        }
        if (p==-1) return 1;

        while(1){
            int nx=-1;
            int np=p^1;
            FE(it, e[p][pos[p]]){
                if (e[np][*it].size()>=2 && *it!=pos[np]){
                    if (nx!=-1) goto out;
                    nx=*it;
                }
            }
            tmp=tmp*fact[e[p][pos[p]].size()-(nx!=-1?2:1)]%mod;
            if (nx==-1) break;
            pos[p=np]=nx;
        }
        ans=(ans+tmp)%mod;
out:;
    }
    return ans;
}

class CircuitDesign {
    public:
        int countPerms(int _n, vector <int> top, vector <int> bottom) {
            n=_n;

            fact[0]=1;
            REP(i, n+1) if (i) fact[i]=fact[i-1]*i%mod;
            memset(cnk, 0, sizeof(cnk));
            REP(i, n+1) cnk[i][0]=1;
            REP(i, n+1) REP(j, i+1) if (i&&j) cnk[i][j]=(cnk[i-1][j-1]+cnk[i-1][j])%mod;


            REP(i, 2) REP(j, n) e[i][j].clear();
            REP(i, top.size()) e[0][top[i]-1].pb(bottom[i]-1);
            REP(i, top.size()) e[1][bottom[i]-1].pb(top[i]-1);
            memset(visited, 0, sizeof(visited));

            ll ans=1;
            int cnt=0;
            REP(i, n) if (!visited[i] && e[0][i].size()){
                sa.clear(); 
                dfs(i);
                ans=ans*proc()%mod;
                ++cnt;
            }
            ans=ans*fact[cnt]%mod;


            int na, nb; na=nb=0;
            REP(i, n) if (!e[0][i].size()) ++na;
            REP(i, n) if (!e[1][i].size()) ++nb;

            ans=ans*fact[na]%mod*fact[nb]%mod;
            ans=ans*cnk[n][na]%mod*cnk[n][nb]%mod;
            return ans;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arg0 = 4; int Arr1[] = {1,1,2,4,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,2,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 32; verify_case(0, Arg3, countPerms(Arg0, Arg1, Arg2)); }
        void test_case_1() { int Arg0 = 2; int Arr1[] = {1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(1, Arg3, countPerms(Arg0, Arg1, Arg2)); }
        void test_case_2() { int Arg0 = 3; int Arr1[] = {1,1,1,2,2,2,3,3,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,3,1,2,3,1,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(2, Arg3, countPerms(Arg0, Arg1, Arg2)); }
        void test_case_3() { int Arg0 = 30; int Arr1[] = {5,5,5,5,5,5,5,5,5, 5,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,3,4,5,6,7,8,9,10,15,15,15,15,15,15,15,15,15,15,25,25,25,25,25,25,25,25,25,25}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 628573100; verify_case(3, Arg3, countPerms(Arg0, Arg1, Arg2)); }
        void test_case_4() { int Arg0 = 5; int Arr1[] = {1,2,3,4,5,1,2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,3,4,5,5,1,4,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(4, Arg3, countPerms(Arg0, Arg1, Arg2)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    CircuitDesign ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
