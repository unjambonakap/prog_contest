// BEGIN CUT HERE

// END CUT HERE
#line 5 "OverlappingConcatenation.cpp"

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


const int maxn=37;
double prob[maxn];
int n, m;
string A, B;
int cnta, cntb;
double pwa, pwb;
double pw[2*maxn+2];

map<unsigned int, double> pa;
int parent[maxn*2];
char val[2*maxn];

int high_bit(unsigned int a){return (a==0?0:high_bit(a>>1)+1);}

int root(int a){return (parent[a]==-1?a:parent[a]=root(parent[a]));}
void rec(int p, unsigned int bm){
    if (p==n+1 || (p==n && !(bm&(unsigned int )(two(n-1)))))return;

    rec(p+1, bm);
    memset(parent, -1, sizeof(parent));
    REP(i, n) if (bm&two(i)) REP(j, i+1) if (root(n+j)!=root(n-i+j-1)) parent[root(n+j)]=root(n-i+j-1);
    memset(val, -1, sizeof(val));
    int cnt=0;
    REP(i, 2*n){
        char c=(i>=n?B[i-n]:A[i]), &nc=val[root(i)];
        if (nc==-1) nc=c;
        else if (nc=='*' && c!='*') nc=c;
        else if (c!='*' && c!=nc &&nc!='*') return;
    }
    REP(i, 2*n) if (i==root(i) && val[root(i)]=='*') ++cnt;
    assert(cnt>=0);

    //map<int, vi> sets;
    //REP(i, n) sets[root(i+n)].pb(i+n), sets[root(i)].pb(i);

    //FE(it, sets){
    //	char c=-1;
    //	FE(ita, it->ND){
    //		char nc=(*ita>=n?B[*ita-n]:A[*ita]);
    //		if (nc!='*'){
    //			if (c!=-1 && nc!=c) return;
    //			c=nc;
    //		}
    //	}
    //	if (c==-1) prob*=m;
    //}
    REP(i, p) if (!(bm&two(i))){
        bool fd=false;
        REP(j, i+1) if (root(n+j)!=root(n-i+j-1)){fd=true; break;}
        if (!fd)return;
    }
    double prob=1./pw[cnta+cntb-cnt];
    assert(prob<='1');
    pa[bm]=prob;

    rec(p+1, bm|two(p));
}


class OverlappingConcatenation {
    public:
        double shortestExpected(string _A, string _B, string alphabet) {
            pa.clear();
            A=_A, B=_B;
            n=A.length();
            m=alphabet.length();

            cnta=cntb=0;
            REP(i, n){ cnta+=(A[i]=='*'); cntb+=(B[i]=='*'); }
            pwa=pow((double)m, cnta), pwb=pow((double)m, cntb);
            pw[0]=1.;
            REP(i, 2*n) pw[i+1]=pw[i]*m;


            rec(0, 0);
            double res=0.;
            map<unsigned int, double>::reverse_iterator ita;
            FEV(it, pa){
                for (ita=it, ++ita; ita!=pa.rend(); ++ita){
                    if ((it->ST&ita->ST)==ita->ST){
                        ita->ND-=it->ND;
                    }
                }
                res+=it->ND*(2*n-high_bit(it->ST));
            }
            return res;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { string Arg0 = "aa*aa"; string Arg1 = "a*aaa"; string Arg2 = "ab"; double Arg3 = 7.0; verify_case(0, Arg3, shortestExpected(Arg0, Arg1, Arg2)); }
        void test_case_0() { string Arg0 = "********************************"; string Arg1 = "********************************"; string Arg2 = "abcdefghijklmnopqrstuvwxyz"; double Arg3 = 7.0; verify_case(0, Arg3, shortestExpected(Arg0, Arg1, Arg2)); }
        void test_case_1() { string Arg0 = "**"; string Arg1 = "**"; string Arg2 = "ab"; double Arg3 = 3.125; verify_case(1, Arg3, shortestExpected(Arg0, Arg1, Arg2)); }
        void test_case_2() { string Arg0 = "**a*cd"; string Arg1 = "cde***"; string Arg2 = "abcdefghijklmnopqrstuvwxyz"; double Arg3 = 10.0; verify_case(2, Arg3, shortestExpected(Arg0, Arg1, Arg2)); }
        void test_case_3() { string Arg0 = "h*phz*"; string Arg1 = "hzph*p"; string Arg2 = "zph"; double Arg3 = 10.555555555555557; verify_case(3, Arg3, shortestExpected(Arg0, Arg1, Arg2)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    OverlappingConcatenation ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
