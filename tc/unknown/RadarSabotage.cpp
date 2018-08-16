// BEGIN CUT HERE

// END CUT HERE
#line 5 "RadarSabotage.cpp"

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


const int inf=1e5;
const int maxp=32;
const int maxn=2*maxp*30+10;
const double eps=1e-5;

int graph[maxn][maxn], rn[maxn][maxn];
int visited[maxn];
int n, s, t;
int ans;
int e[maxn][maxn];
int ne[maxn];

void adde(int a, int b){e[a][ne[a]++]=b; e[b][ne[b]++]=a;}


int dfs(int a, int v){ 
    if (a==t){ans+=v; return v;}
    REP(i, ne[a]){
        int x=e[a][i];
        if (!visited[x] && rn[a][x]<graph[a][x]){
            visited[x]=1; 
            int k=dfs(x, min(v, graph[a][x]-rn[a][x]));
            if (k){
                rn[a][x]+=k; rn[x][a]-=k;
                return k;
            }
        }
    }
    return 0;
}

int augment(){
    memset(visited, 0, sizeof(visited));
    visited[s]=1;
    return dfs(s, inf);
}

int checkit(int x, int y, int a, int b){ return x*x+y*y<=(a+b)*(a+b); }


class RadarSabotage {
    public:
        int minimumDifference(int W, int H, vector <int> rx, vector <int> ry, vector <int> rp) {

            int na=rx.size();
            ans=0;
            REP(i, na) if (rp[i]>=maxp) ans+=rp[i]-maxp+1, rp[i]=maxp-1;

            memset(graph, 0, sizeof(graph));
            int mx=na*maxp;
            memset(ne, 0, sizeof(ne));
            REP(i, na) REP(j, i) REP(a, rp[i]+1) REP(b, rp[j]+1) if (checkit(rx[i]-rx[j], ry[i]-ry[j], a*a, b*b)){
                int x=i*maxp+a, y=j*maxp+b;
                graph[mx+x][y]=graph[mx+y][x]=1;
                adde(mx+x, y);
                adde(mx+y, x);
            }


            s=2*mx; t=s+1; n=t+1;
            REP(i, na) REP(j, rp[i]+1){
                graph[i*maxp+j][mx+i*maxp+j]=1;
                adde(i*maxp+j, mx+i*maxp+j);
                if (rx[i]-j*j<=0) graph[s][i*maxp+j]=1, adde(s, i*maxp+j); 
                if (rx[i]+j*j>=W) graph[mx+i*maxp+j][t]=1, adde(mx+i*maxp+j, t);
            }


            memset(rn, 0, sizeof(rn));
            while(augment());

            return ans;

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { int Arg0 = 1000; int Arg1 = 1000; int Arr2[] = {565, 37, 344, 542, 529, 306, 99, 661, 323, 139, 883, 284, 583, 312, 644, 265}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {110, 743, 165, 580, 793, 977, 356, 8, 798, 270, 675, 137, 799, 125, 649, 596}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {53, 68, 35, 40, 73, 88, 67, 61, 76, 35, 43, 79, 68, 38, 76, 71}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 9; verify_case(0, Arg5, minimumDifference(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_0() { int Arg0 = 9; int Arg1 = 944; int Arr2[] = {8, 1, 8, 4, 2, 8, 8, 7, 8, 1, 2, 6, 5, 7, 7, 4, 2, 6, 6, 1, 6, 3, 5, 3, 2, 6, 3, 6, 1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {582, 318, 261, 435, 762, 458, 281, 551, 889, 213, 910, 103, 777, 248, 706, 880, 865, 818, 712, 706, 292, 807, 843, 631, 162, 587, 71, 578, 329, 747}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {64, 141, 84, 76, 78, 58, 78, 24, 53, 61, 57, 19, 76, 157, 118, 120, 191, 176, 7, 194, 94, 57, 29, 95, 67, 188, 76, 139, 62, 88}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 9; verify_case(0, Arg5, minimumDifference(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        //void test_case_0() { int Arg0 = 8; int Arg1 = 20; int Arr2[] = {4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {10}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 9; verify_case(0, Arg5, minimumDifference(Arg0, Arg1, Arg2, Arg3, Arg4)); }


        void test_case_1() { int Arg0 = 3; int Arg1 = 5; int Arr2[] = {1,1,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,2,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,1,1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 1; verify_case(1, Arg5, minimumDifference(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_2() { int Arg0 = 6; int Arg1 = 16; int Arr2[] = {1,3,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {8,8,8}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {2,2,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 3; verify_case(2, Arg5, minimumDifference(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_3() { int Arg0 = 51; int Arg1 = 4; int Arr2[] = {46,8}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {8,8}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 8; verify_case(3, Arg5, minimumDifference(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_4() { int Arg0 = 24; int Arg1 = 32; int Arr2[] = {3,6,10,18,13}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {18,23,10,13,26}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {2,2,2,3,1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 0; verify_case(4, Arg5, minimumDifference(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_5() { int Arg0 = 20; int Arg1 = 30; int Arr2[] = {1,1,5,5,15,15,19,19,19}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5,10,4,11,3,9,1,8,17}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {5,4,3,5,4,3,2,2,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 10; verify_case(5, Arg5, minimumDifference(Arg0, Arg1, Arg2, Arg3, Arg4)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    RadarSabotage ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
