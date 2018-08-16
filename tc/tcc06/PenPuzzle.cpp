// BEGIN CUT HERE

// END CUT HERE
#line 5 "PenPuzzle.cpp"

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

const int maxm=4, maxn=3;
const int maxs=5e6;
map<int, int> rmp[maxm];
char d[maxs];
int mp[maxs];
int ns;
int n, m;
int rota[two(8)];
int rotb[two(8)];

int qa, qe;
int q[maxs];


inline void add(int nv, int y, int c){
    int tmp=(nv<<2)|y;
    if (rmp[y].count(tmp)) return;
    assert(ns<maxs);
    rmp[y][mp[ns]=tmp]=ns;
    d[ns]=c;
    q[qe++]=ns;
    ++ns;
}


class PenPuzzle {
	public:
	int solve(vector <string> puzzle) {

        qa=qe=0;

        n=puzzle.size();
        m=puzzle[0].length();
        int mask=two(8*n)-1;
        REP(i, two(2*m)){
            rota[i]=(i>>2)|((i&3)<<2*(m-1));
            rotb[i]=(i<<2&(two(2*m)-1))|(i>>2*(m-1));
        }



        REP(i, n) rmp[i].clear();
        ns=0;
        int tmp[maxn];
        REP(i, n){
            tmp[i]=0;
            REP(j, m) tmp[i]|=(puzzle[i][j]-'A')<<2*j;
        }

        REP(j, m){
            int v=0;
            REP(i, n) v|=tmp[i]<<8*i;
            REP(i, n){
                int nv=v<<2|i;
                tmp[i]=rota[tmp[i]];
                if (!rmp[i].count(nv)){
                    rmp[i][mp[ns]=nv]=ns;
                    d[ns]=0;
                    q[qe++]=ns;
                    ++ns;
                }
            }

        }

        while(qa<qe){
            int k=q[qa++];
            int c=d[k];
            int v=mp[k];
            int y=v&0x3;
            v>>=2;
            if ((((v<<8)^v)&mask)==(v&0xff)){
                return c;
            }
            ++c;

            int tmp[maxn];
            REP(i, n) tmp[i]=(v>>8*i)&0xff;
            int ov=v;

            int pad=8*y;
            int ka=v&(0x3<<pad);
            ov^=ka;
            if (y){
                int kb=v&(0x3<<(pad-8));
                add((ov^kb)|(ka>>8|kb<<8), y-1, c);
            }if (y+1<n){
                int kb=v&(0x3<<(pad+8));
                add((ov^kb)|(ka<<8|kb>>8), y+1, c);
            }

            ov^=ka;
            REP(i, n) if (i!=y){
                ov^=tmp[i]<<8*i;
                add(ov|(rota[tmp[i]]<<8*i), y, c);
                add(ov|(rotb[tmp[i]]<<8*i), y, c);
                ov^=tmp[i]<<8*i;
            }
            ov=tmp[y]<<8*y;
            REP(i, n) if (i!=y) ov|=rotb[tmp[i]]<<8*i;
            add(ov, y, c);
            ov=tmp[y]<<8*y;
            REP(i, n) if (i!=y) ov|=rota[tmp[i]]<<8*i;
            add(ov, y, c);



        }
        assert(0);


    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { string Arr0[] = {"ABC", "ABC"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, solve(Arg0)); }
    void test_case_1() { string Arr0[] = {"ABC", "BCA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, solve(Arg0)); }
    void test_case_2() { string Arr0[] = {"ABA", "BCC"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, solve(Arg0)); }
    //void test_case_3() { string Arr0[] = {"CBBC", "DCAB", "ADAD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(3, Arg1, solve(Arg0)); }
    void test_case_3() { string Arr0[] = {"ABAB", "CDBA", "DCDC"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(3, Arg1, solve(Arg0)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    PenPuzzle ___test; 
    ___test.run_test(3);
} 
// END CUT HERE
