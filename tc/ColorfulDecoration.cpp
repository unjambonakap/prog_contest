// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulDecoration.cpp"

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

const int maxn=222;
int g[maxn][maxn];
int inv[maxn];

int dm[maxn][maxn];
int n;
int id[maxn];
int pos;
vi qx;
int par[maxn], ncomp;
int backe[maxn];
int in[maxn];

int dfs(int a, int p=-1){
    id[a]=pos++;
    qx.pb(a);
    in[a]=1;
    backe[a]=id[a];
    REP(i,n) if (g[a][i]){
        if (id[i]==-1) checkmin(backe[a],dfs(i,a));
        else if (in[i]) checkmin(backe[a],backe[i]);
        
    }

    if (backe[a]==id[a]){
        par[a]=ncomp;
        while(qx.back()!=a) in[qx.back()]=0, par[qx.back()]=ncomp, qx.pop_back();
        ++ncomp;
        in[qx.back()]=0;
        qx.pop_back();
    }
    return backe[a];
}

int checkit(){
    qx.clear();
    ncomp=0;
    memset(in,0,sizeof(in));
    memset(id,-1,sizeof(id));

    int pos=0;
    REP(i,n) if (id[i]==-1) dfs(i);

    REP(i,n) if (par[i]==par[inv[i]]) return 0;
    

    return 1;

}

class ColorfulDecoration {
	public:

	int getMaximum(vector <int> xa, vector <int> ya, vector <int> xb, vector <int> yb) {
        n=xa.size();
        int T=0, H=1e9;
        int best=0;

        REP(i,n) REP(j,i) if (i!=j) REP(ka,2) REP(kb,2){
            int xu,yu,xv,yv;
            if (ka) xu=xa[i],yu=ya[i]; else xu=xb[i],yu=yb[i];
            if (kb) xv=xa[j],yv=ya[j]; else xv=xb[j],yv=yb[j];
            dm[i+n*ka][j+n*kb]=dm[j+n*kb][i+n*ka]=max(abs(xu-xv),abs(yu-yv));
        }

        REP(i,n) inv[i]=i+n, inv[i+n]=i;

        n*=2;
        while(T<=H){
            int M=(T+H)/2;
            memset(g,0,sizeof(g));
            REP(i,n) REP(j,i) if (i!=inv[j] && dm[i][j]<M) g[i][inv[j]]=1, g[j][inv[i]]=1;


            if (checkit()){
                best=M, T=M+1;
            }
            else H=M-1;
        }
        return best;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {429091892, 961267218, 756714985, 47984358, 136994546, 89874083, 778861426, 728600972, 893628814, 947939762, 808594497, 101768992, 396652807, 929734353, 423069827, 979278465, 77822758, 623543069, 360381508, 642010937, 737295718, 666929661, 657575060, 382890716, 482943139, 357339003, 507800086, 780818544, 3225843, 588898556, 713359688, 952110140, 735719, 828442655, 488907844, 337929261, 90030746, 344408985, 69466155, 393051878, 269099537, 358416117, 571776379, 474929348, 370016280, 349140080, 442762483, 453767881, 548002499, 418603553}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {196140058, 24811155, 329748650, 149104151, 394336022, 954128145, 290766635, 717119809, 699047606, 361550233, 299007548, 596365342, 569164866, 726007220, 501019003, 14972080, 16643617, 807540573, 225102734, 402343694, 818952756, 348896798, 41267625, 147255482, 432653731, 906620370, 286613694, 710476245, 158593368, 343954466, 62616237, 497030804, 119223753, 737501743, 77084643, 228775641, 765569362, 437158223, 174243289, 748758058, 171165683, 16331167, 178152769, 752084574, 873785083, 644232356, 550815516, 153131303, 276168326, 256577155}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {755411973, 870194955, 77998094, 598609271, 561609657, 936256770, 443022738, 939452709, 858915255, 957614867, 877389930, 992790003, 317691663, 552687972, 755530796, 545124886, 241695476, 185775121, 361943944, 417648732, 646178940, 730194017, 669944403, 907464485, 644584943, 7495736, 615217694, 291079048, 286118484, 546778867, 720950657, 219600111, 435916612, 465812997, 539610755, 377069428, 713566767, 572399342, 711405433, 977464649, 933319057, 691189179, 342889336, 294863439, 585760694, 299072369, 212666162, 621393734, 195593170, 958507094}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] ={407417209, 759859399, 270092967, 735013130, 795115938, 853283426, 198813857, 51721306, 846346358, 175468203, 267264813, 972006122, 631494080, 859969717, 202797784, 462806107, 495633850, 45220992, 815136162, 667731287, 444878135, 641194304, 803250907, 464242305, 453739176, 420207457, 973347120, 98381715, 680123828, 524144040, 275637841, 180470934, 782842787, 301902829, 906172752, 847828411, 704771404, 425662110, 454317645, 156044624, 319353091, 468961822, 327355805, 973517226, 425193876, 669205888, 549571613, 488806237, 462018770, 390120061};  vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 19; verify_case(0, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3)); }

	//void test_case_0() { int Arr0[] = { 10,  0,  7 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {  0, 19,  6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 20, 10, 25 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 20, 35, 25 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 19; verify_case(0, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = { 464, 20 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 464, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 464,  3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 464, 16 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 461; verify_case(1, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = { 0, 0, 1, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0, 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 1, 0, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 1, 1, 0, 0 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(2, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = { 0, 3, 0, 5, 6 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 1, 6, 0, 8, 5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 6, 1, 7, 4, 7 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 5, 9, 2, 8, 9 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 3; verify_case(3, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = { 1000000000, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 1000000000 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 0, 1000000000 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 0, 1000000000 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1000000000; verify_case(4, Arg4, getMaximum(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  ColorfulDecoration ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
