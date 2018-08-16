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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxn=55;
vi bc;
string bs;
vi ac;
vi ta, tb;


class ICPCBalloons{ 
    public: 
    int minRepaintings(vector <int> _bc, string _bs, vector <int> _ac){ 
        bc=_bc;
        bs=_bs;
        ac=_ac;
        sort(ALL(ac));

        ta.clear(); tb.clear();
        REP(i,bc.size()){
            if (bs[i]=='M') ta.pb(bc[i]);
            else tb.pb(bc[i]);
        }
        sort(ALL(ta)); sort(ALL(tb));
        reverse(ALL(ta));
        reverse(ALL(tb));
        reverse(ALL(ac));

        int n=ac.size();

        int res=INT_MAX;
        REP(i,1<<n){
            int have1=0, have2=0, p1=0, p2=0;
            int can=1;
            int ans=0;
            int s1=0, s2=0;
            REP(j,n){
                if (i&(1<<j)){
                    s1+=ac[j];
                    if (p1==ta.size()){
                        have1-=ac[j];
                        ans+=ac[j];
                    }else{
                        int x=ta[p1++]-ac[j];
                        if (x<0) ans+=-x;
                        have1+=x;
                    }
                }else{
                    s2+=ac[j];
                    if (p2==tb.size()){
                        have2-=ac[j];
                        ans+=ac[j];
                    }else{
                        int x=tb[p2++]-ac[j];
                        if (x<0) ans+=-x;
                        have2+=x;
                    }
                }
            }
            while(p1<ta.size()) have1+=ta[p1++];
            while(p2<tb.size()) have2+=tb[p2++];
            if (have1<0 || have2<0) can=0;

            if (can) res=min(res,ans);
        }


        return res==INT_MAX?-1:res;
    } 


    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arr0[] = {100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "L"; int Arr2[] = {1,2,3,4,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; verify_case(0, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
    void test_case_1() { int Arr0[] = {100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "M"; int Arr2[] = {10,20,30,40,50}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(1, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
    void test_case_2() { int Arr0[] = {5,6,1,5,6,1,5,6,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "MLMMLMMLM"; int Arr2[] = {7,7,4,4,7,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(2, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
    void test_case_3() { int Arr0[] = {100,100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ML"; int Arr2[] = {50,51,51}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(3, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
    void test_case_4() { int Arr0[] = {8,5,1,4,1,1,3,1,3,3,5,4,5,6,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "MMMLLLMMLLMLMLM"; int Arr2[] = {3,5,3,3,5,6,4,6,4,2,3,7,1,5,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; verify_case(4, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
    void test_case_5() { int Arr0[] = {1,18,4,7,19,7,7,1,4,8,10,5,14,13,8,22,6,3,13,5,3,4,2,1,3,15,19,4,5,9,4,11,2,7,12,20,11,26,22,7,2,10,9,20,13,20,2,9,11,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LLMLLLLMLLLLLLLLLLLLMLLLLLLLLLLMMLMLLLMLLLLLLLLMLL"; int Arr2[] = {44,59,29,53,16,23,13,14,29,42,13,15,66,4,47}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 210; verify_case(5, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }

    // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    ICPCBalloons ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
