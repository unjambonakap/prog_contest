// BEGIN CUT HERE

// END CUT HERE
#line 5 "AliceInWanderland.cpp"

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


const int maxn=11;
const int maxm=55;
const ll maxt=1000000000000000LL;

struct state{
    ll t;
    ll x, y;
};
int seen[maxn][two(maxn)];
state dp[maxn][two(maxn)];
int va[maxn][maxm];
int svax[maxn], svay[maxn];
int nva[maxn];
int vx[]={0, 1, 0, -1};
int vy[]={1, 0, -1, 0};
char letter[]={'U', 'R', 'D', 'L'};
int sx[maxn], sy[maxn];
int n;


void catchup(state &s, int a, ll x, ll y, ll t){
    //printf("\n\n\n");
    //printf("call catchup %Ld %Ld %Ld, %d, %d %d\n", x, y, t, a, svax[a], svay[a]);

    int m=nva[a];
    ll foo=t%m;
    ll rem=(m-t)%m;
    ll nt=t+rem;
    
    ll tx, ty;
    tx=sx[a]+svax[a]*(nt/m-1);
    ty=sy[a]+svay[a]*(nt/m-1);
    REP(i, foo) tx+=vx[va[a][i]], ty+=vy[va[a][i]];

    //printf("start finish cycle: %Ld %Ld\n", tx, ty);
    REP(i, rem+1){
        tx+=vx[va[a][(foo+i)%m]];
        ty+=vy[va[a][(foo+i)%m]];
        if (t+i>maxt){
            s.t=-1;
            return;
        }
        if (fabs(tx-x)<=i && fabs(ty-y)<=i){
            s.t=t+i;
            s.x=tx; s.y=ty;
            return;
        }
    }
    ll st=nt/m;
    ll L=nt/m, H=ceil(double(maxt)/m)+1;
    ll M;
    //printf("end current cycle => on pos %Ld %Ld\n", tx, ty);

    while(L<H){
        M=(L+H)/2;
        ll ntx=fabs(svax[a]*(M+1)+sx[a]-x), nty=fabs(svay[a]*(M+1)+sy[a]-y);
        if (ntx>(M+1)*m-t || nty>(M+1)*m-t){
            //printf("fail on %Ld => %Ld %Ld xxxx %Ld %Ld\n", M, ntx, nty, (M+1)*m-t, (M+1)*m-t);
            L=M+1;
        }
        else{ H=M;
            //printf("can for %Ld\n", M);


        }
    }
    //printf("found sol %Ld => %Ld\n", L, L*m);
    if (L*m>maxt){
        s.t=-1;
        return;
    }
    tx=svax[a]*L+sx[a], ty=svay[a]*L+sy[a];
    //printf("should have %Ld %Ld xxx %Ld %Ld, nmove %Ld => %d %d\n", tx+svax[a], ty+svay[a], x, y, (L+1)*m-t, fabs(tx+svax[a]-x)<=(L+1)*m-t, fabs(ty+svay[a]-y)<=(L+1)*m-t);

    tx+=vx[va[a][0]]; ty+=vy[va[a][0]];
    s.t=L*m;
    FOR(i, 1, m){
        if (++s.t>maxt){
            s.t=-1;
            return;
        }
     //   printf("can move %Ld, is %Ld %Ld xx %Ld %Ld\n", s.t, tx, ty, x, y);

        //printf("diff: %Ld %Ld\n", s.t-t-abs(tx-x) , s.t-t-abs(ty-y));
        if (s.t-t>=abs(tx-x) && s.t-t>=abs(ty-y)){
            s.x=tx; s.y=ty;
     //       printf("retting on pos %Ld %Ld time %Ld\n", tx, ty, s.t);
            return;
        }
        tx+=vx[va[a][i%m]], ty+=vy[va[a][i%m]];
    }
    s.t=-1;
    assert(0);
    return;
}

state proc(int a, int b){

    state &s=dp[a][b];
    if (seen[a][b]) return s;
    seen[a][b]=1;


    s.t=-1;
    //printf("try proc %d %d\n", a, b);
    if (b==0){
        catchup(s, a, 0, 0, 0);
        //printf("retting %Ld %Ld %Ld\n", s.x, s.y, s.t);
        return s;
    }

    state tmp;
    REP(j, n) if (b&two(j)){
        state tmp=proc(j, b^two(j));
        if (tmp.t==-1) continue;

        catchup(tmp, a, tmp.x, tmp.y, tmp.t);
        if (tmp.t!=-1 && (s.t==-1 || s.t>tmp.t)) s=tmp;
    }
    return s;

}


class AliceInWanderland {
	public:
	long long getMinimum(vector <int> rx, vector <int> ry, vector <string> moves) {
            n=rx.size();
            REP(i, n){
                sx[i]=rx[i]; 
                sy[i]=ry[i]; 
                nva[i]=moves[i].length();
                svax[i]=svay[i]=0;
                REP(j, nva[i]) REP(k, 4) if (moves[i][j]==letter[k]){va[i][j]=k; svax[i]+=vx[k]; svay[i]+=vy[k]; break;}
            }

            memset(seen, 0, sizeof(seen));
            state s, best;
            best.t=-1;
            REP(i, n){
                s=proc(i, two(n)-1-two(i));
                if (best.t==-1 || (s.t!=-1 && best.t>s.t)) best.t=s.t;
            }
            return best.t;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arr0[] = { 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "ULDR" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 3LL; verify_case(0, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_0() { int Arr0[] = {-2512, -3730, -4189, -3937, 374, 3468, -5217, -794, -1646, -2500, -2664}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-452, 4838, -4701, -4310, 5071, 2621, -5546, -4912, 1825, 1140, -4665}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"DLUDUR", "DDLRUUDDDDRLULLDDDURDDD", "ULUURDRULUUUDUUDLDUUDUUDUDLL", "UUDULUULUULURUUUDRUUL", "ULUUULULLUDULRUDULUUURLLULUU", "D", "RLRRLRRURRDRLRRD", "LRLDRDRDRLRRLRDLRRRRDRLR", "DUUDDDDUD", "RLLLRLLRRRLLLLRLLLLLLR", "RLRU"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 3LL; verify_case(0, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = { 10, -20 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "RL", "LULD" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 80LL; verify_case(1, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = { 30, -40 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "RL", "DLUL" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 188LL; verify_case(2, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = { 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = -1LL; verify_case(3, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = { 1000000000, 1000000000, -1000000000, -1000000000, 1000000000, 1000000000, -1000000000, -1000000000, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1000000000, 1000000000, -1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRU", 
  "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRD", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLU", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLD", 
  "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRUU", 
  "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRDD", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLUU", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLDD", 
  "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUR", 
  "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUL", 
  "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDR" }
; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = -1LL; verify_case(4, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = { 1, 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = { "L", "U" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = -1LL; verify_case(5, Arg3, getMinimum(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  AliceInWanderland ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
