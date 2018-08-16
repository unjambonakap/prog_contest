// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxBomb.cpp"

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

const int maxn=55;
int mp[maxn][maxn];
int r, c;
int dp[maxn][maxn][3];//0> nothing,1 need, 2 covered
int vx[]={-1,0,1,0};
int vy[]={0,1,0,-1};


int in(int a, int b){return a>=0&&a<r&&b>=0&&b<c;}
int go(int a, int b, int f, int par=-1){
    int &r=dp[a][b][f];
    if (r!=-1) return r;
    r=INT_MAX;
    vi next;
    int has=0;
    REP(k,4) if (k!=(par^2)){
        int nx=a+vx[k], ny=b+vy[k]; 
        if (in(nx,ny) && !mp[nx][ny]) next.pb(k), has|=k==par;
    }
    if (next.size()==0) return r=f==2?0:1;
    int tmp=1;
    REP(i,next.size()) tmp+=go(a+vx[next[i]],b+vy[next[i]],2,next[i]);
    checkmin(r,tmp);

    if (f==2){
        tmp=0;
        REP(i,next.size()) tmp+=go(a+vx[next[i]],b+vy[next[i]],next[i]==par?2:0,next[i]);
        checkmin(r,tmp);
    }

    REP(j,4) REP(j2,5) if (j!=j2){
        if (j!=par && f==1) continue;
        tmp=0;
        int fd=0, fd2=0;
        REP(i,next.size()){
            int nf;
            if (next[i]==j) nf=1, fd=1;
            else if (next[i]==j2) nf=1, fd2=1;
            else if (next[i]==(j^2) || next[i]==(j2^2)) nf=2;
            else nf=next[i]==par?f:0;
            tmp+=go(a+vx[next[i]],b+vy[next[i]],nf,next[i]);
        }
        if (j2==4) fd2=1;

        if (fd&&fd2) checkmin(r,tmp);
    }
    return r;
}



class FoxBomb {
    public:
        int getMinimumCost(vector <string> grid) {
            r=grid.size(); c=grid[0].length();
            REP(i,r) REP(j,c) mp[i][j]=grid[i][j]=='#';
            memset(dp,-1,sizeof(dp));
            REP(i,r) REP(j,c) if (!mp[i][j]){
                int x=0;
                REP(k,4){int nx=i+vx[k], ny=j+vy[k]; if (in(nx,ny) && !mp[nx][ny]) ++x;}
                if (x<=1) return go(i,j,0);
                
            }
            assert(0);
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = 
            {   "......#.#............#.......#...#..#......#...#.."
                , ".#.#.#...##.##.#####.#.#####.#.#.#.#..####...#.#.#"
                , "#..#.#.#.....#.....##..#...#...#....#....#.##..#.."
                , "..##.#.##.##..#.##...#...#..###.###.#.#.#..#.#.##."
                , "#...##...#..#.###.##..#.##.#......#..#..#.#..#..#."
                , "..#.#.#.#..###.......###...#.####.#.#..##..#..#.#."
                , ".#....#.#.#.#..#####..#..#.#....#.#.#.#...#..##.#."
                , "#..##.#...#...#.....##..#.#.##.#..#.###.##.#.#..#."
                , "..##...##..#.#.#.##....#..#.#..#.##.....#......#.."
                , "#...##..#.#..#.#...#.#.##...#.#..#.####.#.#####.#."
                , "..#...###..#....#.#..#..#.#####.#..#...#..#.....#."
                , ".#.##....#..###.#..##..##...#.....#..#.#.#.##.#.#."
                , ".#...#.#..#...#..#...#...##.#.###.#.#..#......#..."
                , "##.#.##.#..##.#.#.##.####...#.#...#.##..#.####..#."
                , "...#......#.#.#...##......##...##.#..#.#.#....#..#"
                , ".##.#.###...#.#.#...#######.##.#..##.#.....##.##.."
                , ".....#..#.##..#..#.#...........#.#...#.####.#...#."
                , ".#.#..#.#..#.#.#.#.#.#.#######..##.##..#....#.#.#."
                , ".#..#.#.#.#..#.#.#...##......###...#..#.#.###..##."
                , "..###.#....#...#..##..#.####.....##..#........#..."
                , ".#....#.#.#.##.##...#.#.#...##.#...#.#.##.#####.##"
                , ".#.###.#..#..#...#.#.#...#.#..#.###..###..#.....#."
                , ".#......#.#.#.##.#....#.#....#.....#....#.#.####.."
                , ".######.#.....#...###.#.##.###.#.#..###..#..#....#", "......#.#.####..##..#.#....#...#.#.#...#..#.##.#..", "#####.#..#....#....#...###.#.####....#...##...#..#", "....#..#.#.##..###.##.#....#...#..###.##...##.#.#.", ".##.##.#.#.###......#.##.##.##.###......##..#.#...", ".##..#.#....#.#####.#........#.....#.##.#.#.#..#.#", "...#....##.#.......#..####.#..#####.#...#.#.##.#..", "##.##.#...##.#####.###....#.###.......###....#...#", ".....#.###...#...#.....#.#......##.#.#....###.##..", "#####......###.#.####.##.#.#####....#.####.....#.#", "......#.###....#.....#...#.#...#.###.......##.##..", ".#####.#....###..#.#.#.##...##.....#.##.###.#.#..#", ".#...#...#.#...#.#.#.#.##.#.##.#####...#....#...#.", ".###..##.##..#.#.#.#.#...#....##....##..###.####..", "....#.....#.##..##..#.##..#.#....##...#...#.....#.", "###..#.####.#..#...#....#..#..#.##.##..##..#.##...", "...#.#.#....#.#..##..##.##.#####......####.#..#.#.", ".#...#.#.###...#....#....#....#..#.##.###..#.#..#.", "..###.##.#..#.#..#######..#.#..#.##....#..#..#.#..", ".#.......##.#.#.#...#...#....#.#...#.#.#.#.##...#.", ".#.##.###...#.#...##..#.#####..###.#.#.#.....#.#..", ".#...#..#.#.#.#.#..#.##......#.....#..######.#.###", "..##.##...#.#..#.#.#...#####.#.#.#..#..#...#.#....", ".#.#....#..#.#.#....##.#...#.#..#.##.#.#.###.#.##.", "...###.###.#.#..#.#.##.#.#.#.#.#.....#...#....#...", ".##...#.##.#..#.##.#.....#.#.###.###.####..#.##.#.", "....#........#.......##.#..#.......#......#.....#."}
            ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, getMinimumCost(Arg0)); }
        //void test_case_0() { string Arr0[] = {
        //    "#..."
        //    ,"..##"
        //        ,"#.##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, getMinimumCost(Arg0)); }
        void test_case_1() { string Arr0[] = {".#.#.#."
            ,"......."
                ,".#.#.#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, getMinimumCost(Arg0)); }
        //        void test_case_2() { string Arr0[] = {
        //                 "..."
        //                ,".##"
        //                ,"..."
        //                ,"##."
        //                ,"..."
        //           }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, getMinimumCost(Arg0)); }
        void test_case_2() { string Arr0[] = {"######################################"
            ,"######################################"
                ,"###.....................##############"
                ,"###.###################.###....#...###"
                ,"###.###################.###.######.###"
                ,"###.###################.###.######.###"
                ,"###.###################.###.######.###"
                ,"###.###################.###.######.###"
                ,"###.###################.###.######.###"
                ,"###.........####........###.######.###"
                ,"###########.###########.###........###"
                ,"###########.###########.##########.###"
                ,"###########.###########.##########.###"
                ,"###########.###########.##########.###"
                ,"###########.###########.##########.###"
                ,"##..........##..........##########.###"
                ,"#######################............###"
                ,"######################################"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, getMinimumCost(Arg0)); }

        void test_case_3() { string Arr0[] = {".#."
            ,"..."
                ,"#.#"
                ,"..."
                ,".#."}
            ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, getMinimumCost(Arg0)); }
            void test_case_4() { string Arr0[] = {"."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, getMinimumCost(Arg0)); }

            // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    FoxBomb ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
