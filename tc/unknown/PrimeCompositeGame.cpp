// BEGIN CUT HERE

// END CUT HERE
#line 5 "PrimeCompositeGame.cpp"

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

const int maxn=555555;
int isp[maxn];
int pl[maxn];
int np;

int A[maxn];

class PrimeCompositeGame {
	public:
	int theOutcome(int N, int K) {
        if (N<=2) return 0;
        checkmin(K, N-2);
        np=0;
        memset(isp, -1, sizeof(isp));
        isp[0]=isp[1]=0;
        FOR(i, 2, maxn) if (isp[i]){pl[np++]=i; for (int j=i+i; j<maxn; j+=i) isp[j]=0;}
        
        multiset<int> X[2], Y[2];//X0 => loosing pos, prime, X1 => winning pos prime
        int T=2;

        A[2]=0;
        X[0].insert(0);

        FOR(i, 3, N-1){
            printf("on %d\n", i);
            while(i-K>T){ 

                if (isp[T]){
                    if (A[T]>0){
                        X[1].erase(X[1].find(A[T]));
                    }
                    else{
                        X[0].erase(X[0].find(-A[T]));
                    }
                }else{
                    if (A[T]>0){
                        Y[1].erase(Y[1].find(A[T]));
                    }
                    else {
                        Y[0].erase(Y[0].find(-A[T]));
                    }
                }
                ++T; 
            }

            if (isp[i]){
                if (!Y[0].size() && !Y[1].size()) A[i]=0, X[0].insert(0);
                else if (Y[0].size()){//has a winning pos
                    A[i]=*Y[0].begin()+1;
                    X[1].insert(A[i]);
                }else{
                    A[i]=*(--Y[1].end())+1;
                    X[0].insert(A[i]);
                    A[i]=-A[i];
                }
            }else{
                if (!X[0].size() && !X[1].size()) A[i]=0, Y[0].insert(0);
                else if (X[0].size()){//has a winning pos
                    A[i]=*X[0].begin()+1;
                    Y[1].insert(A[i]);
                }else{
                    A[i]=*(--X[1].end())+1;
                    Y[0].insert(A[i]);
                    A[i]=-A[i];
                }

            }
        }



        int res=maxn;
        FOR(i, 1, K) if (isp[N-i] && A[N-i]<=0) checkmin(res, 1-A[N-i]);
        
        
        
        if (res==maxn){
            res=0;
            FOR(i, 1, K) if (isp[N-i] && A[N-i]>0) checkmax(res, 1+A[N-i]);
            
            res=-res;
        }
        return res;


    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 1; verify_case(0, Arg2, theOutcome(Arg0, Arg1)); }
    void test_case_0() { int Arg0 =239679; int Arg1 = 35554; int Arg2 = 1; verify_case(0, Arg2, theOutcome(Arg0, Arg1)); }
    void test_case_1() { int Arg0 = 58; int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, theOutcome(Arg0, Arg1)); }
    void test_case_2() { int Arg0 = 30; int Arg1 = 3; int Arg2 = -2; verify_case(2, Arg2, theOutcome(Arg0, Arg1)); }
    void test_case_3() { int Arg0 = 6; int Arg1 = 3; int Arg2 = 1; verify_case(3, Arg2, theOutcome(Arg0, Arg1)); }
    void test_case_4() { int Arg0 = 526; int Arg1 = 58; int Arg2 = 19; verify_case(4, Arg2, theOutcome(Arg0, Arg1)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    PrimeCompositeGame ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
