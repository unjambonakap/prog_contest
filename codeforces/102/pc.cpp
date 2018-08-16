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

int patternx[4][5]={{0,1,1,1,2},{1,1,1,0,2},{0,0,0,1,2},{0,1,2,2,2}};
int patterny[4][5]={{0,0,1,2,0},{0,1,2,2,2},{0,1,2,1,1},{1,1,0,1,2}};
const int maxn=16;

int n, m;
int best;

int mp[maxn][maxn];
int cnt;
int res[maxn][maxn];
int id;


string A[]={"","","","","","","","","","","\n",".\n","..\n","...\n","....\n",".....\n","......\n",".......\n","........\n",".........\n","\n\n",".\n.\n","..\n..\n","...\n...\n","....\n....\n",".....\n.....\n","......\n......\n",".......\n.......\n","........\n........\n",".........\n.........\n","\n\n\n",".\n.\n.\n","..\n..\n..\n","A..\nAAA\nA..\n",".A..\n.AAA\n.A..\n","A.BBB\nAAAB.\nA..B.\n",".A.BBB\n.AAAB.\n.A..B.\n","A.BBB.C\nAAABCCC\nA..B..C\n",".A.BBB.C\n.AAABCCC\n.A..B..C\n","A.BBBC..D\nAAAB.CDDD\nA..BCCC.D\n","\n\n\n\n",".\n.\n.\n.\n","..\n..\n..\n..\n","...\nA..\nAAA\nA..\n","...A\nBAAA\nBBBA\nB...\n",".....\nA.BBB\nAAAB.\nA..B.\n","...AAA\nB..CA.\nBBBCA.\nB.CCC.\n","...ABBB\nCAAADB.\nCCCADB.\nC..DDD.\n",".....AAA\nB.CCCDA.\nBBBC.DA.\nB..CDDD.\n","...AAA..B\nC..DAEBBB\nCCCDAEEEB\nC.DDDE...\n","\n\n\n\n\n",".\n.\n.\n.\n.\n","..\n..\n..\n..\n..\n","A..\nAAA\nA.B\nBBB\n..B\n","....\n...A\nBAAA\nBBBA\nB...\n","A.BBB\nAAAB.\nAC.BD\n.CDDD\nCCC.D\n","...A..\nBBBAAA\n.BCA.D\n.BCDDD\n.CCC.D\n","..A.BBB\n..AAAB.\nC.AD.BE\nCCCDEEE\nC.DDD.E\n","...AAA.B\n.CCCABBB\n.DCEA.FB\n.DCEEEF.\nDDDE.FFF\n",".A.BBBC..\n.AAABDCCC\nEA.FBDCG.\nEEEFDDDG.\nE.FFF.GGG\n","\n\n\n\n\n\n",".\n.\n.\n.\n.\n.\n","..\n..\n..\n..\n..\n..\n","...\nA..\nAAA\nA.B\nBBB\n..B\n",".A..\n.AAA\n.A.B\nCBBB\nCCCB\nC...\n",".....\nA.BBB\nAAAB.\nAC.BD\n.CDDD\nCCC.D\n",".....A\nBBBAAA\n.BCCCA\nDB.CE.\nDDDCE.\nD..EEE\n","....AAA\nBBB.CA.\n.BCCCA.\nDB.EC.F\nDDDEFFF\nD.EEE.F\n",".......A\nB.CCCAAA\nBBBCDDDA\nBE.CFDG.\n.EFFFDG.\nEEE.FGGG\n",".....ABBB\nC.DDDA.B.\nCCCDAAABE\nCF.DGHEEE\n.FGGGHHHE\nFFF.GH...\n","\n\n\n\n\n\n\n",".\n.\n.\n.\n.\n.\n.\n","..\n..\n..\n..\n..\n..\n..\n","A..\nAAA\nA.B\nBBB\nC.B\nCCC\nC..\n","...A\nBAAA\nBBBA\nB..C\nDCCC\nDDDC\nD...\n","....A\nB.AAA\nBBBCA\nBCCC.\nDDDCE\n.DEEE\n.D..E\n","...A..\nBBBAAA\n.BCA.D\n.BCDDD\nECCCFD\nEEE.F.\nE..FFF\n","A.BBB.C\nAAABCCC\nAD.BE.C\n.DDDEEE\nFD.GE.H\nFFFGHHH\nF.GGG.H\n",".AAA.BBB\n.CADDDB.\n.CA.DEB.\nCCCFDEEE\nGFFFHE.I\nGGGFHIII\nG..HHH.I\n","..AAA.BBB\nCCCADDDB.\n.CEA.D.BF\n.CEEEDFFF\nG.EHIIIJF\nGGGH.I.J.\nG.HHHIJJJ\n","\n\n\n\n\n\n\n\n",".\n.\n.\n.\n.\n.\n.\n.\n","..\n..\n..\n..\n..\n..\n..\n..\n","...\nA..\nAAA\nA.B\nBBB\nC.B\nCCC\nC..\n","....\n...A\nBAAA\nBBBA\nB..C\nDCCC\nDDDC\nD...\n","....A\n.BAAA\n.BBBA\nCBDDD\nCCCD.\nCE.DF\n.EFFF\nEEE.F\n","...AAA\n.BBBA.\n.CB.AD\n.CBDDD\nCCCE.D\nFEEEG.\nFFFEG.\nF..GGG\n","...ABBB\nCAAADB.\nCCCADB.\nCE.DDDF\n.EEEFFF\nGEHHHIF\nGGGH.I.\nG..HIII\n","...A.BBB\nCCCAAAB.\n.C.A..BD\nECFFFDDD\nEEEFGGGD\nEH.FIGJ.\n.HIIIGJ.\nHHH.IJJJ\n","...ABBB.C\nDAAAEBCCC\nDDDAEBF.C\nD.GEEEFFF\nGGGHHHF.I\nJ.GKHLIII\nJJJKHLLLI\nJ.KKKL...\n","\n\n\n\n\n\n\n\n\n",".\n.\n.\n.\n.\n.\n.\n.\n.\n","..\n..\n..\n..\n..\n..\n..\n..\n..\n","A..\nAAA\nA.B\nBBB\nC.B\nCCC\nC.D\nDDD\n..D\n",".A..\n.AAA\n.A.B\nCBBB\nCCCB\nC..D\nEDDD\nEEED\nE...\n","....A\nB.AAA\nBBBCA\nBCCC.\nDDDCE\n.DEEE\nFD.GE\nFFFG.\nF.GGG\n",".....A\nBBBAAA\n.BCCCA\nDB.CE.\nDDDCE.\nD.FEEE\n.GFFFH\n.GFHHH\nGGG..H\n","..A.BBB\n.CAAAB.\n.CA.DB.\nCCCEDDD\nFEEED.G\nFFFEGGG\nFHIIIJG\n.H.I.J.\nHHHIJJJ\n",".AAABCCC\n.DA.B.C.\n.DABBBCE\nDDDFGEEE\nHFFFGGGE\nHHHFGIII\nHJKKKLI.\n.J.K.LI.\nJJJKLLL.\n","....AAA.B\nC.DDDABBB\nCCCDEA.FB\nC.GDEFFF.\nGGGEEEHF.\nI.GJJJHHH\nIIIKJLH.M\nIKKKJLMMM\n...KLLL.M\n"};
int B[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,3,3,4,0,0,0,1,2,2,3,4,4,5,0,0,0,2,2,4,4,5,6,7,0,0,0,2,3,4,5,6,7,8,0,0,0,3,4,5,6,8,9,10,0,0,0,3,4,6,7,9,10,12,0,0,0,4,5,7,8,10,12,13};


void go(int x, int y){
    if (y+2>=m){++x, y=0;} 
    if (x+2>=n){
        if (best<cnt){
            best=cnt;
            memcpy(res, mp, sizeof(res));
        }
        return;
    }
    if ((n-x)*m/5+cnt<=best) return;


    go(x,y+1);
    ++id;
    REP(i, 4){
        int fd=1;
        REP(j, 5) if (mp[x+patternx[i][j]][y+patterny[i][j]]){fd=0; break;}
        if (fd){
            REP(j, 5) mp[x+patternx[i][j]][y+patterny[i][j]]=id;
            ++cnt;
            go(x,y+1);
            --cnt;
            REP(j, 5) mp[x+patternx[i][j]][y+patterny[i][j]]=0;
        }
    }
    --id;

}

vi tba;
vector<string> tbb;

void doit(){
    best=0; cnt=0; id=0;
    memset(mp, 0, sizeof(mp));
    memset(res,0,sizeof(res));
    if (n>=3 && m>=3) go(0,0);
    tba.pb(best);
    string s;
    REP(i, n){
        REP(j,m) s+=res[i][j]?res[i][j]+'A'-1:'.';
        s+="\\n";
    }
    tbb.pb(s);
}

void gen(){
    REP(i,10) REP(j,10){
        n=i; m=j;
        doit();
    }
    FE(it,tba) printf("%d,",*it); puts("");
    FE(it,tbb) printf("\"%s\",",it->c_str()); puts("");

}

void solve(){
    cin>>n>>m;
    printf("%d\n", B[n*10+m]);
    cout<<A[n*10+m]<<endl;
}

int main(){
    //gen();
    solve();
    return 0;
}


