// BEGIN CUT HERE

// END CUT HERE
#line 5 "YetAnotherBingoProblem.cpp"

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

const int maxn=10, m=25, v=75;
int ca[maxn][v];
int na, nb, n;
int used[v];
int nx;
int perm[maxn];
int dp[two(maxn)];

class YetAnotherBingoProblem {
	public:
	int longestWinningSequence(vector <string> cards1, vector <string> cards2) {
        na=nb=1;

        string s;


        memset(ca, 0, sizeof(ca));

        FE(it, cards1) s+=*it;
        REP(i, s.length()) if (s[i]==',') ++na, s[i]=' ';
        istringstream ss(s);
        REP(i, na) REP(j, m){ int a; ss>>a; ca[i][a-1]=1; }

        s="";
        FE(it, cards2) s+=*it;
        REP(i, s.length()) if (s[i]==',') ++nb, s[i]=' ';
        istringstream ssa(s);
        REP(i, nb) REP(j, m){ int a; ssa>>a; ca[na+i][a-1]=1;}



        n=na+nb;
        int ans=-1;
        REP(k, two(na)) if (k){
            memset(used, 0, sizeof(used));
            int fd=0;
            int tmp=count_bit(k);
            REP(i, v){
                int x=0;
                REP(j, na) if ((k&two(j)) && ca[j][i]) used[i]=1, ++x;
                if (x==tmp) fd=1;
            }
            if (!fd) continue;

            nx=0;
            REP(i, n) if (!(k&two(i))) perm[nx++]=i;
            memset(dp, 0x7f, sizeof(dp));
            dp[0]=0;
            REP(i, v) if (!used[i]){
                int mk=0;
                REP(j, nx) if (ca[perm[j]][i]) mk|=two(j);
                REPV(j, two(nx)) checkmin(dp[j|mk], dp[j]+1);
            }
            if (dp[two(nx)-1]<v) checkmax(ans, v-dp[two(nx)-1]);
        }
        return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"37 48 11 19 29 20 70 4 30 34 24 12 3 46 5 58 38 63", " 65 16 33 50 21 61 73,23 16 56 45 40 24 54 72 47 2", "8 50 26 5 30 43 48 17 39 32 67 36 37 66 46 70,62 8", " 13 64 57 33 22 17 72 58 27 43 19 47 53 68 2 40 45", " 42 69 14 1 38 55,61 63 44 29 12 50 39 32 5 25 51 ", "38 10 31 27 60 28 37 1 66 42 70 45 67 36,32 9 42 4", "6 75 6 74 49 25 37 52 51 29 54 12 20 43 50 1 34 72", " 4 21 35 69"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"69 19 58 48 7 22 64 3 18 75 54 38 17 62 21 51 5 57", " 34 55 27 29 46 6 53,45 36 25 22 28 39 50 2 41 40 ", "13 17 61 53 1 69 48 23 70 29 63 71 37 59 7,4 32 9 ", "20 52 25 64 6 26 10 49 42 73 14 74 37 8 15 16 72 2", "4 44 35 50 63,31 43 23 73 18 36 46 6 72 1 42 11 60", " 32 44 19 49 33 39 45 15 47 54 61 2,57 21 27 67 10", " 24 12 65 75 34 9 55 52 4 35 51 41 14 59 38 8 71 2", "6 11 31"}
	//void test_case_0() { string Arr0[] = {"60 28 ","8 25 54"," 31 13 26 71 20 66 55 72 67 18 51 52 48 63 53 ","42 16 ","1 30 56,", "27 43 70 48 54 24 73 37 41 51 58 55"," 71 12 60 49 64 47 35 4 ","16 69 14 40 50"}
//; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"5 48 26 64 12 47 39 29 63 50 15 51 33 5","8 49 73 13 61 69 16 53 41 60 ","59 55,", "16 55 57 43 20 3 74 12 4","2 ","35 19 65 51 17 1 15 69 56"," 31 13 9 24 58"," ","38 75"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 74; verify_case(0, Arg2, longestWinningSequence(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"34 ","56"," 7 22 21 43 57 38 ","12 5 32"," 39 15 13"," 75 20 ","55 69 70 2","3 65 48 33 9 44"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"46 18 3 33 34 58 24 36 30 50 ","45 11 56 25 57 60 54 74 42 8 70 40 20 2 1,26 61 20",
" 43 52 ","2 22 33 53 44 60 27 57 12 7 15 29 73 50 ","2","8 56 34 75 67 37,47 61 36 75 45 22 17 49 33 59",
" 48 39 69 27 3 70 12 46 54 1","1 67 ","43 73 5","2 68"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 73; verify_case(1, Arg2, longestWinningSequence(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"70 29 47 73 17 49 13 64 42 71 63 28 9 54 ","74 20 69 16 14 66 12 25 4","5 41 68"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"4","7 16 68 74 71 42 49 66 45 25 13 9 12"," 17 ","20"," 5","4 70 28 64 69 73 63 14 41"," 29"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, longestWinningSequence(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"2 21 15 48 50 ","75 67 33 60 52 1","4 72 64 25 8 23 39 12 11 74 65 63 56 44 13,",
"13 3","3 52 72 39 63 44 14 21 48 3","8 65 12 56"," 74 60 23 8 15 50 75",
" 67 25 11 2,67 38 14 48 56 52 72 50 23 21 15 13 ","64 39 2 11 25 8 33 44 12 60",
" 65 75 74,38 15 50 11 13 12 44 60 74 21 25"," 48 67 39 72 14 8 63 64 56 75 33 ","52 31 23"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"7","4 21 12 60 25 38 15 11 49 ","54 8 63 33 65 56 52 13 14 72 75 23 48 50 67 3",
"9,52 14 25 39 64 50 21 33 2 15 67 13 48 ","56 12 7","5 63 60 11 65 44 74 ",
"23 72 29,25 12 74 2 64 31 39 33 ","14"," 21 13 72 15 23 8 60 5","6 50 38 75 ","44 46 67 1","1 48"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 73; verify_case(3, Arg2, longestWinningSequence(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  YetAnotherBingoProblem ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
