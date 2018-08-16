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


const int maxn=2555;
const int maxk=333;

vi e[maxn];

int n,na,K;
int mark[maxn];
int vx[]={1,-1,0,0};
int vy[]={0,0,1,-1};

int lst[maxk];
int nk;
int have[maxn];

double cnk[maxk][maxk];

int F[2*maxk];

int rmp[maxn];

int is[2*maxk];
int depth[2*maxk];
int par[2*maxk];
int can[2*maxk];
int ord[2*maxk];
int pos;

int dist[maxn][maxn];

vi cnd;
double dp[maxk][maxk];
int vis[maxk][maxk];

double go(int x, int n){
    if (n-x<K-2) return 0;
    if (x==0) return 1;

    double &r=dp[x][n];
    if (vis[x][n]) return r;
    vis[x][n]=1;

    r=go(x-1,n)*(n-x-(K-2)+1)/(n-x+1);
    return r;
}

int dfs0(int a, int p, int *d){
    d[a]=p==-1?0:d[p]+1;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b!=p) dfs0(b,a,d);
    }
}


int dfs1(int a, int dx=0, int p=-1){
    int aa=-1;
    if (mark[a]){ aa=rmp[a]=na++; par[aa]=-1; is[aa]=1;}

    vi tb;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        b=dfs1(b,dx+1,a);
        if (b!=-1) tb.pb(b);
    }

    if (tb.size()>1 && aa==-1) aa=rmp[a]=na++;

    if (aa!=-1){
        depth[aa]=dx;
        ord[pos++]=aa;
        REP(i,tb.size()) par[tb[i]]=aa;
        return aa;
    }
    return tb.size()?tb[0]:-1;
}




class Orienteering{ 
    public: 
        double expectedLength(vector <string> field, int _K){ 
            K=_K;
            memset(vis,0,sizeof(vis));

            int N,M;
            N=field.size(); M=field[0].size();

            //REP(i,N) cout<<field[i]<<endl;

            REP(i,maxk) cnk[i][0]=cnk[i][i]=1;
            FOR(i,1,maxk) FOR(j,1,i) cnk[i][j]=cnk[i-1][j]+cnk[i-1][j-1];

            memset(mark,0,sizeof(mark));
            nk=0;

            REP(i,N) REP(j,M) if (field[i][j]!='#'){
                REP(k,4){
                    int nx=i+vx[k], ny=j+vy[k];
                    if (nx>=0 && nx<N && ny>=0 && ny<M) if (field[nx][ny]!='#') e[i*M+j].pb(nx*M+ny);
                }
                if (field[i][j]=='*') mark[i*M+j]=1, lst[nk++]=i*M+j;
            }
            n=N*M;

            REP(i,nk) dfs0(lst[i],-1,dist[i]);

            double res=0;


            REP(i,nk){
                memset(rmp,-1,sizeof(rmp));
                memset(is,0,sizeof(is));
                pos=0;
                na=0;
                dfs1(lst[i]);

                REP(j,i){
                    int D=dist[i][lst[j]];
                    int cnt=0;
                    memset(can,0,sizeof(can));
                    REP(k,nk){
                        int a=lst[k];
                        if (dist[i][a]>D || dist[j][a]>D) continue;
                        if (dist[j][a]==D && k<=i) continue;
                        if (dist[i][a]==D && k<=j) continue;
                        can[rmp[a]]=1; ++cnt;
                    }

                    if (cnt<K-2) continue;

                    memset(F,0,sizeof(F)); memset(have,0,sizeof(have));
                    F[rmp[lst[j]]]=1;
                    can[rmp[lst[j]]]=1;

                    REP(i,na){
                        int a=ord[i], p=par[a];
                        if (p==-1) continue;
                        can[a]|=is[a]^1;
                        if (!can[a]) continue;
                        have[a]+=is[a];


                        F[p]|=F[a];
                        have[p]+=have[a];
                    }

                    double tmp=D;

                    //puts("=========");
                    //REP(i,n) if (rmp[i]!=-1) printf("%d >> %d\n",i,rmp[i]);
                    REP(k,na) if (can[k] && !F[k]){
                        int dx=depth[k]-depth[par[k]];
                        tmp+=2*dx*(1-go(have[k],cnt));
                        //printf("TAKE %d >> prob %lf, depth %d xx %d\n",k,1-go(have[k],cnd.size()),dx,have[k]);
                    }
                    double cx=cnk[cnt][K-2]/cnk[nk][K];

                    res+=tmp*cx;

                }
            }

            REP(i,n) e[i].clear();

            return res;
        } 

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {
            "*#..#",
            ".#*#.",
            "*...*"
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arg2 = 3.8333333333333353; verify_case(0, Arg2, expectedLength(Arg0, Arg1)); }
        //    "##*##",
        //    "*...*",
        //    "##*##"
        void test_case_1() { string Arr0[] = {
            "*#..#",
            ".#*#.",
            "*...*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 8.0; verify_case(1, Arg2, expectedLength(Arg0, Arg1)); }
        void test_case_2() { string Arr0[] = {"#.#**",
            "....#",
            "#*#**",
            "**#*#",
            "#..##",
            "*#..#",
            ".#.#.",
            "....*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; double Arg2 = 10.825000000000024; verify_case(2, Arg2, expectedLength(Arg0, Arg1)); }
        void test_case_3() { string Arr0[] = {"###################",
            "#*###############*#",
            "#.....#######.....#",
            "#*###*.#.*.#.*###*#",
            "#*####*.*#*.*####*#",
            "#*#####*###*#####*#",
            "###################"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; double Arg2 = 30.272233648704244; verify_case(3, Arg2, expectedLength(Arg0, Arg1)); }
        void test_case_4() { string Arr0[] = {"**##*.**#..#.*...*#...*#..#.##..#..#.#*...#.##*##.",
            ".#..###..#..#.#.##..#.#.*#.*..#..#.#*..##.#*...*..",
            "..#.....###.#*.##..#.#.#*..#.#..#....#..#...#*####",
            ".#.##*#.*#..#*#*.#.#...*.#.*#.#.##.#*.##.#.#..*...",
            "..*.*#*.###.#..#.#..##.##.*#..#.....#.....#..#.#.#",
            ".#.##.#..##..*#..#.#...#*##*#*..#.#.#.#.##.##.#.#*",
            "..##....#..#.#*#...*.##...#.#.####...#.#*.....#...",
            ".#.*#.##.*#*.#*.#.#.#..#.#..#.#*#.###..##.##.#.##*",
            ".*.#*..*.#.#...#.*##.#.**.#.*...**..*#..#.#.#*.#..",
            ".#*.#*##....##.#.#*..*.###.#.##.##.#.#.#....#.#*.#",
            "*.#..#*#.#*#*....#.#.#..*#**...##.#.#.**#*##.*.#..",
            ".#*.##..##..##.#.#..#.#.###.###...#...#*#..##*#.#.",
            "#..#*.#..*.###..#.#...#.###.#.#*#.#.#**##.#...*.#*",
            "..#..#.#.##.#..#.**.##*#.#**.**..#.#..#...#.##*#..",
            ".#*#.#.*..#.*#...#.#...#...#.##.#..*#*.##*....###.",
            ".*.#.#.#.#*#..*##.**.##*##..#.*#.#*###..*.#.##.#..",
            ".#......#...#.#.*#.#.#..#..#.#*#....#*.#*#.*#..*.#",
            "#..####..#*#...#*.#..#.###...#.#.#.###*#..##*##.#.",
            ".#.*..#.#...#.#..#.##...#..#.#.#.#.###..##..*.*.*.",
            ".#.#.#.#..##.*..#.*.#.##.#..##*...#.#..#.#.##.#.##",
            ".#..#*.#.#..#.##..##..#.*..#.*#.#...##....#...###.",
            ".#.#.#.#*.#.#..#.#..#..#.#.*#...#.##...#.##.##.*..",
            ".#...#.#.##.#.#..*#.*#..###..#.#.#*###.##...#*.##.",
            ".#.##.*.......*.#.*#.#.#*###..*...*..#.*.##.#.#..#",
            "...###*####*#.#..##*...#..#..##.#.#.#..##*#*.*.*#.",
            "#.#.#....*#..#.#.#.#.##..#*.#...#..#.#*#...#.##.*.",
            "..*.#*##.#.#*#.###...#..##.#.#.#*###*#.*#.#.*###.#",
            "##*##..##...#.....##.#.#.**#..#*.....##.#..#*.#.*.",
            ".....#.*.##..##.##*.*#...#.#.#.##.#*#.**..#..#.#.#",
            "##.#.#*##.#.#.*.*.#.#*#.#.#....*...#*##*##.#....#.",
            "*.**#**....*..##.#*.*.**..##.###.##.....##...##.**",
            "#.####.##*#*##..#.*#*#.##*...#.##..#.##....#*..##.",
            "....#...##.#...#*.#..##.##.#*..*.#....##.#.*##...#",
            "#.#..*##*..#.#..#..#..#*....#.##..##.#*##.##.*##..",
            "..#.#*.*.##.#.#*#.#*##.###.##...#............#*.#.",
            "#.#.##.#....*....*..##..*#.#.#.###.#.#.#.###..#..#",
            ".#**..#*#.#*#*#.#.#...*##....##.#*..#..#*..*#..#..",
            "...#*#.....#..#.#..#*#.*##.#..#.#.##..#.*#*#.#...#",
            ".#*.###.#.#.#.#.*#*##.##..#.#*..#...#.#.#..#*.*#..",
            "#*.#.#.#..#..#..#....*#.*##..##.#.#..#...##.#.#..#",
            "*.#..#..#...#..##.#*#..#.#*#.#.#.###..#.#*...#.#..",
            "#...#.#...#.#.#..#.*.#*.....**.*..#*##.#*.##....##",
            "#*#....#*#..#.*.###*#..#*##.##.#.#...#.*.##.##.##.",
            "..##*##*..#*#.#..#*.*##*.##.#...#.#.#.#.#..*#.##..",
            "#...#*##.#*#**.##.*#.*.##..*.#*#**....#**##...*.*#",
            "*#.##......*#.##.#.#.##**.#.#.#.#.#.##..#...#*#*#*",
            "*....##.#.#..#.....#..##.#....*....#.#.##.#.#.##**",
            "#.##*#...#..#.#.##..#..##.##.##.##........##.#*#.#",
            "..#...#.#*#*..*#..*#.*#.#......##.#.#.#*#..#..****",
            ".###.#..#...#.#..#..#.#...#.#.#...**.#..*#*.*##*#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 150; double Arg2 = 1309.4951033725558; verify_case(4, Arg2, expectedLength(Arg0, Arg1)); }

        // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    Orienteering ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
