// BEGIN CUT HERE

// END CUT HERE
#line 5 "DoNotTurn.cpp"

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

const int maxn=512;
int mp[maxn][maxn];
int best[maxn*maxn*4];
int done[maxn*maxn*4];

int n;

int vx[]={-1,0,1,0};
int vy[]={0,1,0,-1};
int in(int x, int y){return x>=0&&y>=0&&x<n&&y<n;}

vector<queue<int> > lst;


struct cmp{ bool operator()(int a, int b)const{return best[a]>best[b];} };

int add(int p, int c){
    if (best[p]<=c) return 0;
    best[p]=c;
    if (c>=lst.size()) lst.pb(queue<int>());
    lst[c].push(p);
    return 1;
}

class DoNotTurn {
	public:
	int minimumTurns(int N, int X0, int A, int B, int Y0, int C, int D, int p, int m) {
        n=N;
        memset(mp,0,sizeof(mp));
        int px=X0%p, py=Y0%p;
        REP(i,m){
            mp[px%n][py%n]=1;
            px=(1ll*px*A+B)%p;
            py=(1ll*py*C+D)%p;
        }
        mp[0][0]=mp[n-1][n-1]=0;

        memset(best,0x7f,sizeof(best));
        memset(done,0,sizeof(done));
        lst.clear();
        REP(i,4) add(i,0);

        int pos=0;
        while(1){
            if (lst[pos].empty()) ++pos;
            if (lst.size()==pos) return -1;
            int p=lst[pos].front(); lst[pos].pop();
            int d=p&3;
            int xo=p>>2&0x1ff;
            int yo=p>>11;
            int c=best[p];
            if (done[p]) continue;
            done[p]=1;
            if (xo==n-1&&yo==n-1) return c;

            REP(i,4) if (i!=d){
                int np=(p^d)^i;
                add(np,c+1);
            }
            p^=(xo<<2)|(yo<<11);


            xo+=vx[d]; yo+=vy[d];
            while(in(xo,yo)&&!mp[xo][yo]){
                int np=p^(xo<<2)^(yo<<11);

                if (!add(np,c)) break;
                xo+=vx[d]; yo+=vy[d];
            }
        }

    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arg0 = 500; int Arg1 = 498; int Arg2 = 1; int Arg3 = 1; int Arg4 = 499; int Arg5 = 2; int Arg6 = 0; int Arg7 = 12345; int Arg8 = 2; int Arg9 = 1; verify_case(0, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
    //void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 0; int Arg3 = 1; int Arg4 = 0; int Arg5 = 0; int Arg6 = 1; int Arg7 = 10; int Arg8 = 2; int Arg9 = 1; verify_case(0, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
    void test_case_1() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 1; int Arg3 = 1; int Arg4 = 1; int Arg5 = 1; int Arg6 = 0; int Arg7 = 3; int Arg8 = 3; int Arg9 = -1; verify_case(1, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
    void test_case_2() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 1; int Arg3 = 1; int Arg4 = 1; int Arg5 = 1; int Arg6 = 1; int Arg7 = 3; int Arg8 = 3; int Arg9 = 3; verify_case(2, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
    void test_case_3() { int Arg0 = 10; int Arg1 = 911111; int Arg2 = 845499; int Arg3 = 866249; int Arg4 = 688029; int Arg5 = 742197; int Arg6 = 312197; int Arg7 = 384409; int Arg8 = 40; int Arg9 = 12; verify_case(3, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
    void test_case_4() { int Arg0 = 5; int Arg1 = 23; int Arg2 = 2; int Arg3 = 3; int Arg4 = 35; int Arg5 = 5; int Arg6 = 7; int Arg7 = 9; int Arg8 = 3; int Arg9 = 2; verify_case(4, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
    void test_case_5() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; int Arg5 = 0; int Arg6 = 0; int Arg7 = 1; int Arg8 = 0; int Arg9 = 1; verify_case(5, Arg9, minimumTurns(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    DoNotTurn ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
