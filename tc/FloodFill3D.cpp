// BEGIN CUT HERE

// END CUT HERE
#line 5 "FloodFill3D.cpp"

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

const int maxn=2510;
int n,m,nu;
const char *cx="xo";
char a[maxn][maxn];
int cnt[2], cnt2[2];
int par[maxn*maxn];
char vis[maxn*maxn];

int vx[]={1,-1,0,0};
int vy[]={0,0,1,-1};


int root(int a){return par[a]<0?a:par[a]=root(par[a]);}
void join(int a, int b){a=root(a); b=root(b); if (a!=b) par[a]+=par[b], par[b]=a;}
int in(int a, int b){return a>=0&&b>=0&&a<n&&b<m;}
int add(int a){a=root(a); if (vis[a]) return 0; vis[a]=1; return -par[a];}



class FloodFill3D
{ 
    public: 
        long long countBlack(vector <string> SArray, vector <string> TArray, vector <string> UArray){ 
            string s, t, u;
            FE(it,SArray) s+=*it;
            FE(it,TArray) t+=*it;
            FE(it,UArray) u+=*it;
            n=s.size(); m=t.size();
            nu=u.size();

            REP(z,2){
                cnt[z]=cnt2[z]=0;
                memset(a,0,sizeof(a));
                memset(par,-1,sizeof(par));
                REP(i,n) REP(j,m) if (s[i]==t[j] && s[i]==cx[z]) a[i][j]=1, ++cnt[z];

                REP(i,n) REP(j,m) if (a[i][j]) REP(k,4){
                    int x=i+vx[k], y=j+vy[k];
                    if (in(x,y) && a[x][y]) join(i*m+j,x*m+y);
                }
                memset(vis,0,sizeof(vis));
                REP(i,n){
                    if (a[i][0]) cnt2[z]+=add(i*m);
                    if (a[i][m-1]) cnt2[z]+=add(i*m+m-1);
                }
                REP(i,m){
                    if (a[0][i]) cnt2[z]+=add(i);
                    if (a[n-1][i]) cnt2[z]+=add((n-1)*m+i);
                }
            }

            ll res=1ll*n*m*nu;
            int na, nb;

            for (na=0; na<nu && u[0]==u[na]; ++na);
            for (nb=nu-1; nb>=0 && u[nu-1]==u[nb]; --nb);

            int ca=u[0]=='o', cb=u[nu-1]=='o';
            if (na!=nu){
                res-=1ll*na*cnt[ca];
                res-=1ll*(nu-nb-1)*cnt[cb];
                FOR(i,na,nb+1) res-=cnt2[u[i]=='o'];
            }else res-=1ll*cnt[ca]*nu;
            return res;
        } 

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {"oxo"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"oxo"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"oxo"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 19LL; verify_case(0, Arg3, countBlack(Arg0, Arg1, Arg2)); }
        void test_case_1() { string Arr0[] = {"ooo"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"oo"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"o"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, countBlack(Arg0, Arg1, Arg2)); }
        void test_case_2() { string Arr0[] = {"xxo", "oox", "o"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"x", "o", "x", "o"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"ooo", "xxxoo", "oxx"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 242LL; verify_case(2, Arg3, countBlack(Arg0, Arg1, Arg2)); }
        void test_case_3() { string Arr0[] = {"xxxxxxxxxxxxxxxxxxxx"
            ,"xxooooooooooooooooxx"
                ,"xxooooooooooooooooxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxooooxxxxxxxx"
                ,"xxxxxxxxxxxxxxxxxxxx"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"xxxxxxxxxxxxxxxxxxxx"
            ,"xxxxxxxoooooooxxxxxx"
                ,"xxxxxoooooooooooxxxx"
                ,"xxxxooooooooooooxxxx"
                ,"xxxxooooxxxxxoooxxxx"
                ,"xxxxoooxxxxxxxxxxxxx"
                ,"xxxxoooxxxxxxxxxxxxx"
                ,"xxxxoooxxxxxxxxxxxxx"
                ,"xxxxooooxxxxoooxxxxx"
                ,"xxxxoooooooooooxxxxx"
                ,"xxxxxooooooooooxxxxx"
                ,"xxxxxxoooooooxxxxxxx"
                ,"xxxxxxxxxxxxxxxxxxxx"}
        ; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"xxxxxxxxxxxxxxxxxxxx"
            ,"xxxxxxxoooooxxxxxxxx"
                ,"xxxxoooooooooooxxxxx"
                ,"xxoooooooooooooooxxx"
                ,"xxoooooxxxxxoooooxxx"
                ,"xxooooxxxxxxxooooxxx"
                ,"xxooooxxxxxxxooooxxx"
                ,"xxooooxxxxxxxooooxxx"
                ,"xxooooxxxxxxxooooxxx"
                ,"xxoooooxxxxxoooooxxx"
                ,"xxxxoooooooooooxxxxx"
                ,"xxxxxxxoooooxxxxxxxx"
                ,"xxxxxxxxxxxxxxxxxxxx"}
        ; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 15027148LL; verify_case(3, Arg3, countBlack(Arg0, Arg1, Arg2)); }

        // END CUT HERE

}; 

// BEGIN CUT HERE 
int main()
{
    FloodFill3D ___test;
    ___test.run_test(-1);
} 
// END CUT HERE

