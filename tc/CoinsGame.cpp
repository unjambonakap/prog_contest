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

const int maxn=44;
const int mod=1e9+9;

int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};

int A[maxn][maxn];
int tmp[maxn][maxn];
int n,m;
int p2[maxn*maxn];
int vis[maxn][maxn];
int vis2[maxn][maxn];
int seen[maxn][maxn];
int cnty[maxn];


int nc;


struct data{
    data():K(0),H(0),xo(0),yo(0),cnt(0){}
    int K; ll H;
    int xo,yo;
    int cnt;
    vi pl[4];
    bool operator<(const data &d)const{
        if (K!=d.K) return K<d.K;
        REP(i,2) if (pl[i]!=d.pl[i]) return pl[i]<d.pl[i];
        return 0;
    }
    bool operator==(const data &d)const{ return !(*this<d) && !(d<*this); }
};

data dx;

int in(int a, int b){return a>=0 && a<n && b>=0 && b<m;}
void dfs(int a, int b){
    if (!in(a,b)) return;
    if (!A[a][b]) return;
    if (vis[a][b]) return ;
    vis[a][b]=1;
    REP(k,4) dfs(a+vx[k],b+vy[k]);
}


void dfs2(int a, int b){
    if (vis2[a][b]==nc) return;
    vis2[a][b]=nc;
    dx.H=10007*dx.H+(maxn+a-dx.xo)*2*maxn+maxn+b-dx.yo;
    ++dx.cnt;

    REP(k,4){
        int x=a+vx[k], y=b+vy[k];
        if (in(x,y)){
            if (!A[x][y]) dx.pl[k].pb(y);
            else dfs2(x,y);
        }else dx.K|=1<<k;
    }
}

void dfs3(int a, int b){
    if (seen[a][b]) return;
    seen[a][b]=1;
    ++cnty[b];
    REP(k,4){
        int x=a+vx[k], y=b+vy[k];
        if (in(x,y) && A[x][y]) dfs3(x,y);
    }
}

class CoinsGame{ 
    public: 
    int ways(vector <string> board){ 
        n=board.size(); m=board[0].size();
        REP(i,n) REP(j,m) A[i][j]=board[i][j]=='.';
        p2[0]=1;
        REP(i,maxn*maxn-1) p2[i+1]=p2[i]*2%mod;

        int cnt1=0;
        REP(i,n) REP(j,m) cnt1+=A[i][j];
        ll res=p2[cnt1]-cnt1-1;

        memset(vis,0,sizeof(vis));
        REP(i,n) dfs(i,0),dfs(i,m-1);
        REP(i,m) dfs(0,i),dfs(n-1,i);

        //cant go out
        int cnt2=0;
        REP(i,n) REP(j,m) if (A[i][j] && !vis[i][j]) ++cnt2;
        res-=p2[cnt2]-cnt2-1;

        REP(rot,4){
            memset(vis2,-1,sizeof(vis2));
            nc=0;

            vector<data> tb;

            REP(i,n) if (A[i][0] && vis2[i][0]==-1){
                dx=data();
                dx.xo=i; dx.yo=0;
                dfs2(i,0);

                if (dx.K&12);
                else{
                    if (dx.K==3) dx.pl[0].pb(m);
                    sort(ALL(dx.pl[0])), dx.pl[0].resize(unique(ALL(dx.pl[0]))-dx.pl[0].begin());
                    tb.pb(dx);
                }
                ++nc;
            }
            sort(ALL(tb));
            nc=tb.size();
            REP(i,nc){
                int j=i;
                for (; j<nc && tb[i]==tb[j]; ++j);
                int na=tb[i].pl[0].size(), nb=tb[i].pl[1].size();

                if (na>=2 || nb){//can diff at same height except for equiv cc
                    vector<pair<ll,int> > hl;
                    FOR(k,i,j) hl.pb(MP(tb[k].H,tb[k].cnt));
                    sort(ALL(hl));
                    int u=0;
                    ll ans=0;
                    for (;u<hl.size();){
                        int v=u;
                        for (; v<hl.size() && hl[v].ST==hl[u].ST;++v);
                        ans+=1ll*(p2[v-u]-(v-u)-1)*hl[u].ND%mod;
                        u=v;
                    }
                    if (tb[i].K==3)
                        ans=1ll*(mod+1)/2*ans%mod;
                    
                    res=res-ans;
                }else{//wont be able to diff if same height, count number of points at each heights
                    memset(seen,0,sizeof(seen));
                    memset(cnty,0,sizeof(cnty));
                    int ans=0;
                    FOR(k,i,j) dfs3(tb[k].xo,tb[k].yo);
                    REP(k,m) ans+=p2[cnty[k]]-cnty[k]-1;

                    if (tb[i].K==3) ans=1ll*(mod+1)/2*ans%mod;
                    res=res-ans;
                }
                i=j-1;
            }



            //rotate board
            REP(i,n) REP(j,m) tmp[j][n-i-1]=A[i][j];
            memcpy(A,tmp,sizeof(A));
            swap(n,m);
        }

        res=(res%mod+mod)%mod;
        return res;
    } 

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { string Arr0[] = {".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, ways(Arg0)); }
    void test_case_0() { string Arr0[] = 
        {
            "........#..#.#..#.#....#....#..#.#......", 
            "........#..#.#....#.#..#.#..#....#......", 
            "#####...#....#....#.#..#.#..#....#......", 
            ".#..#...#....#....#....#....#....#......", 
            ".#..#...#....#....#....#....#....#......", 
            ".##.##############################......", 
            "....#.......................#...........", 
            "#####.......................############", 
            ".#..#.......................#...........", 
            ".#..#.......................#....##.....", 
            ".##.#########################....##.....", 
            "....#.......................#....##.....", 
            "#####.......................#...........", 
            "....#.......................############", 
            ".####.......................#...........", 
            ".#..#.......................#....##.....", 
            "....#.......................#....##.....", 
            "#####.......................#....##.....", 
            "....#.......................#...........", 
            ".####.####.....#............############", 
            ".#..#.#..#.....#............#...........", 
            "....#.#..#.....#............#....##.....", 
            "#####.#..#.....#............#....##.....", 
            "......####.....#............#....##.....", 
            ".####.......................#...........", 
            ".#..#.......................############", 
            "....#.......................#...........", 
            "#####.......................#...........", 
            "....#.......................#.#########.", 
            ".####.......................#...........", 
            ".#..#...######..............#...........", 
            "....#...#....#..............############", 
            "#####...#....#..............#...........", 
            "....#...#....#####..........#...........", 
            ".####...#....#...#..........#.#########.", 
            ".#..#...#....#...#..........#...........", 
            "....#...#....#...#########..#...........", 
            "#####...#.#..#.#.#...#...#..############", 
            "....#...#....#...#...#.#.#..#...........", 
            "....#...#....#...#...#...#..#..........."}
        
        ;vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, ways(Arg0)); }
    void test_case_1() { string Arr0[] = 
        {
            ".#.#.#.#.#.########.##...#...#.........#", 
            ".#.#.#.#.#.#..#..#...#...##.##.........#", 
            "...#...#...#..#..#...##.##...#####.#####", 
            "############..#..#...#...#...#.........#"}
        
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, ways(Arg0)); }
    //void test_case_0() { string Arr0[] = {
    //void test_case_0() { string Arr0[] = {
    //    "###", 
    //    ".##", 
    //    "..#", 
    //    "###", 
    //    ".##", 
    //    "..#", 
    //    "###"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, ways(Arg0)); }
    //void test_case_1() { string Arr0[] = {"##.#",
    //    ".###",
    //    "###.",
    //    "#.##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 11; verify_case(1, Arg1, ways(Arg0)); }
    void test_case_2() { string Arr0[] = {"####",
        "#..#",
        "#..#",
        "####"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, ways(Arg0)); }
    void test_case_3() { string Arr0[] = {"#.#.#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, ways(Arg0)); }
    void test_case_4() { string Arr0[] = {"........",
        "........",
        "........",
        "........",
        "........",
        "........",
        "........",
        "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 688856388; verify_case(4, Arg1, ways(Arg0)); }

    // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    CoinsGame ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
