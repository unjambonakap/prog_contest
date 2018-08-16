// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulMaze.cpp"

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

const int maxn=50, maxc=7;
double dpa[maxn][maxn][1<<maxc];
double dpb[maxn][maxn][1<<maxc][maxc];
int seena[maxn][maxn][1<<maxc];
int seenb[maxn][maxn][1<<maxc][maxc];
int mp[maxn][maxn];
int n, m;
int xi, yi, xe, ye;
double prob[maxc];
int vx[]={0,0,1,-1};
int vy[]={1,-1,0,0};

int in(int x, int y){return x>=0&&y>=0&&x<n&&y<m;}

double go2(int x, int y, int f, int w){
    if (seenb[x][y][f][w]) return dpb[x][y][f][w];
    vector<int> lst;
    int can[n][m]; memset(can,0,sizeof(can));
    can[x][y]=1;
    int qa=0;
    lst.pb(x*m+y);
    vector<int> reach;



    if (mp[x][y]==w){
        double res=0.;
        REP(k,4){
            int nx=x+vx[k], ny=y+vy[k];
            if (!in(nx,ny) || mp[nx][ny]==-2) continue;
            
            if (mp[nx][ny]!=-1 && !(f>>mp[nx][ny]&1)){
                if (mp[nx][ny]!=w) checkmax(res,(1-prob[mp[nx][ny]])*go2(nx,ny,f^two(mp[nx][ny]),w));
            }else checkmax(res,go2(nx,ny,f,w));
        }
        seenb[x][y][f][w]=1;
        dpb[x][y][f][w]=res;
        return res;
    }


    while(qa<lst.size()){
        int xa=lst[qa]/m, ya=lst[qa]%m; ++qa;
        REP(k,4){
            int nx=xa+vx[k], ny=ya+vy[k];
            if (!in(nx,ny) || mp[nx][ny]==-2 || can[nx][ny]) continue;
            
            if (mp[nx][ny]!=-1 && !(f>>mp[nx][ny]&1)) can[nx][ny]=2, reach.pb(nx*m+ny);
            else can[nx][ny]=1, lst.pb(nx*m+ny);
        }
    }
    double res;
    if (can[xe][ye]==1) res=1.;
    else{
        res=0.;
        REP(i,reach.size()){
            int xa=reach[i]/m, ya=reach[i]%m;
            int c=mp[xa][ya];
            assert(c>=0);
            assert(!(f>>c&1));
            if (c==w) continue;
            double px=prob[c];
            checkmax(res,(1-px)*go2(xa,ya,f^two(c),w));
        }
    }

    REP(i,lst.size()){
        int xa=lst[i]/m, ya=lst[i]%m;
        seenb[xa][ya][f][w]=1;
        dpb[xa][ya][f][w]=res;
    }
    return res;

}
double go1(int x, int y, int f){
    if (seena[x][y][f]) return dpa[x][y][f];
    vector<int> lst;
    int can[n][m]; memset(can,0,sizeof(can));
    can[x][y]=1;
    int qa=0;
    lst.pb(x*m+y);
    vector<int> reach;
    while(qa<lst.size()){
        int xa=lst[qa]/m, ya=lst[qa]%m; ++qa;
        REP(k,4){
            int nx=xa+vx[k], ny=ya+vy[k];
            if (!in(nx,ny) || mp[nx][ny]==-2 || can[nx][ny]) continue;

            if (mp[nx][ny]!=-1 && !(f>>mp[nx][ny]&1)) can[nx][ny]=2, reach.pb(nx*m+ny);
            else can[nx][ny]=1, lst.pb(nx*m+ny);
        }
    }
    double res;
    if (can[xe][ye]==1) res=1.;
    else{
        res=0.;
        REP(i,reach.size()){
            int xa=reach[i]/m, ya=reach[i]%m;
            int c=mp[xa][ya];
            assert(c>=0);
            assert(!(f>>c&1));
            double px=prob[c];
            checkmax(res,(1-px)*go1(xa,ya,f^two(c))+px*go2(xa,ya,f,c));
        }
    }
    REP(i,lst.size()){
        int xa=lst[i]/m, ya=lst[i]%m;
        seena[xa][ya][f]=1;
        dpa[xa][ya][f]=res;
    }
    return res;
}


class ColorfulMaze {
    public:
        double getProbability(vector <string> maze, vector <int> trap) {
            REP(i,maxc) prob[i]=trap[i]/100.;
            n=maze.size(); m=maze[0].length();
            memset(mp,-1,sizeof(mp));
            REP(i,n) REP(j,m){
                char c=maze[i][j];
                if (c=='#') mp[i][j]=-2;
                else if (c=='.')  mp[i][j]=-1;
                else if (c=='$') xi=i, yi=j;
                else if (c=='!') xe=i, ye=j;
                else mp[i][j]=c-'A';
            }
            memset(seena,0,sizeof(seena));
            memset(seenb,0,sizeof(seenb));
            return go1(xi,yi,0);
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {"#BAAA##AG#GDD#B#BDDDED#FBFFBBFD#EEEF#EEE#EBBB##BAE", "EEE#EEEECCFF#DD#DD#DEEEE##FFFFFDDE#GGG#AB#BEA#A#DD", "C#CCC#CF#EE#AAAAEE#EEEEEE#EF#F#FFF#FGF#FAB#BBBBBAF", "FF#EEBG#GEA##CFFFFCFFEEEDDDAA#GGEEBCCBBB#B#DDCCC##", "GG#GC##CCGGG#G#F#FFD#AAEAFGG##F#FFF#FFEDBBBBB#BCE#", "EBB#GAAA#DG#GGACC#DCCFFFDDC##BB#EBBBFCCEEEE##CF#BB", "BBBCEE##EEEEEE#AA##A#GGB#DEDC#CG#GD#FFF#FF#FFGGADA", "AAB#B#DDGGGGGBB#FFFAEGGEEGD#DDDFF#F#E#EEE##DDCCE#B", "B##GGCCFBABBBBBCC#C#D#G#GGGGG##AAA#GGCCGGGGGG#GCEE", "#EE##EEE##CAA#B##BCC#EEEGACCC####C#E#EEEE#EEEE#BBB", "BBD#DDA##AABB#C#CCCCEE#CC#CCCECFF##F#FCCCC#CAA#AAA", "AAADFF#EEEEEE##EEE#E#BEGGAEE#GFFBACEE#EC#G#GGGGFFF", "#F##AAAE#BGGCFFAA###AAAA#A##AAACGGGGGEFG#GG#G##B#A", "AAGGGG#GA#AFDD#AGG##FFFFFFF#FF##F#FF##CCCE#EFFFBB#", "#B#B#BBGGEEEF#FFGCCCC#FFFGGG##AAEEEDGG#GGGG#FFCCF#", "GFFFF##FBBBG#G#GD###GGDEE##EAGAA#A##AA##AAA#A#ABBF", "#FFFCDE#EDACCCCCCE#DDDFC#CDAACGGCG#GAAE#GCCBA##A##", "#GEEAAABDDCE#FFFF##FAAAEEDDGG#FFF#FFACAAAGGGDFFFGB", "DDEE#ECCB##FFCCBGB#BDFFFF#E#EE#EEEEEDDDDCB##BBDDD#", "CCD##DDD##GGA#CA#AAA#FFD#DDFFF#EEE##ECCEEE#EB#BDDE", "#AAFFAA#A#A#AA#FF#F#A#A##AAA#A#AC#AAAAAAAACCDC#CCC", "E#E#DEG#FF#FFF#AAAABCF#DDDDG##GGBBB##ED#AABBBE#EC#", "#F#F##DDBAFFFFAAEEBFBBG#D#D#DEEEE#BB###EEF#GGAA#AA", "ACCCCEEDFCGDDDCCC##CBBBCGGFFFAFDEDDG#GG#G#GGD#D#F#", "C##GGDDDEEEBBFE##EGAAA###CCCEEEEBEGBCACEDEEDF#G#GG", "#GC#AAAA#AABBBB##BDBBA#A#AB#BEEEEE#EEE#EEEBBDEEEEE", "EAAAEEBAFFFFFFEEECCC#C#GG#AAA#A#AAC##DDEA##ACCAAD#", "#EFFFF##BAAAAGGEEEE#EE#EE#EAA#AAG#B#B##BBDF#FA#GGA", "#AA##BCBEBB##BBDGCFF#EEFF#F#FF#FBEE##BBCGG#C#CC##D", "D##DAGADBBCDDD#DEEDDDCC#CEDDDD#BDG#G#ACC#CCCCF##FF", "FBBBFCC##CCFFFFFFC#C#GDF#F#GC#CCAAAEEAEEFDDDBBEB#D", "D##DDD#DDDCCEEFFF##F##FEE##EBBGF#FCDDD#DD##CCDA#AA", "AB#CCC#DDDAAFFFGGGGG#GGG#GG#BDEGGC##GGGDCCC##DBB#B", "BBB#C#BBFFCCC##CCFCGDCCFEC#GGGGGEEA##D#EGAD#DDDDEE", "D##C#BBD#FF#FE#BBEEGADCCC#FCAAD#DDDC#CFFD#DEGGGABB", "BD#CCC#DCB#FBGEBG##D#D#DDCCG#GGFF#FFAC#DDGGG#F#AAA", "ACF#F#F#FFFFFDDCFFFFFFGCB#F#EEABCCCCGGG$#CC#E#AAAC", "DAAA#AEEE#GDD#FFBBDF#FADDD#EE##E#EF##FA#DBE#AACDDD", "DD#FEEBBC#CA#G#AAA#AA#AADEFFB#E#GGDBBBBAA#ACFB#BC#", "ACCFFFFFFFF#FBCCGGG#FAAAADDGG###GGGBBGGAAAAAAEE###", "E#EEAFGGFFFGCCBCB#BBGBE#FGGG#ABCC#CCBDDD#DDDDD#DAA", "A#D#D#GGG#CCCCGGCAEE#EE#GDCCC#CAAAAADGGGGGCCCGGAA#", "AGG#EC#CGFFE#E#EEEECCCDDADDDCCCCC#GGGCCCBGAEEEFBBB", "#BGGGCEECCCCC#BEBF##DBFDAAABB#FFA#A#AAAEEEEE#EEFC#", "CFFDDDBEEAAAAAAGGFDDDDD#DFDFD#FDDBBAAAACFEEEDEBFGG", "###GG#GB#GEEBDCCC#A##AAAAA#A#ABBBBDDD#DDCDDDDDEEFF", "FFFBBA##AB#DDDD#FFFFFGCC#CDEF#EGGAFFBBBEFBBDDB#EDD", "DADDADAFF#CCAAE#EE#DDGGGECEEF#FFF##FFBFFCE#EDD#DDD", "GBBBB##BBBBBCDEEEE##A#AEDDAGFGGAAA#F##BEEEB#BFBACD", "F#BBFGEEB#FCCCCFEEEBBCC#CC#C!CEEEEEDAA##CCCCEED#DC"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {96, 41, 23, 17, 14, 68, 42}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.8; verify_case(0, Arg2, getProbability(Arg0, Arg1)); }
        //void test_case_0() { string Arr0[] = { ".$.", "A#B", "A#B", ".!." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 50, 40, 0, 0, 0, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.8; verify_case(0, Arg2, getProbability(Arg0, Arg1)); }
        void test_case_1() { string Arr0[] = { ".$.",
            "A#B",
            "A#C",
            ".!." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 20, 70, 40, 0, 0, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.86; verify_case(1, Arg2, getProbability(Arg0, Arg1)); }
        void test_case_2() { string Arr0[] = { "$A#",
            ".#.",
            "#B!" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 10, 10, 10, 10, 10, 10, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(2, Arg2, getProbability(Arg0, Arg1)); }
        void test_case_3() { string Arr0[] = { "$A..",
            "##.A",
            "..B!" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 50, 50, 0, 0, 0, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.75; verify_case(3, Arg2, getProbability(Arg0, Arg1)); }
        void test_case_4() { string Arr0[] = { "$C..",
            "##.A",
            "..B!" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 50, 50, 100, 0, 0, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.5; verify_case(4, Arg2, getProbability(Arg0, Arg1)); }
        void test_case_5() { string Arr0[] = { ".$.D.E.F.G.!." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 10, 20, 30, 40, 50, 60, 70 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.23400000000000004; verify_case(5, Arg2, getProbability(Arg0, Arg1)); }
        void test_case_6() { string Arr0[] = { "CC...AA",
            "C##.##A",
            "!.E.E.$",
            "D##.##B",
            "DD...BB" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 90, 90, 25, 50, 75, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.8125; verify_case(6, Arg2, getProbability(Arg0, Arg1)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    ColorfulMaze ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
