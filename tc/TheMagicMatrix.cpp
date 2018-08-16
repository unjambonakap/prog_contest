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

const int mod=1234567891;
const int maxn=1111;


int val[10][10];
int n;
int aa,bb;
int sumr[4], sumc[4];
int ans;
int ox[4], oy[4];
int U;


void go(int a, int b){
    if (a==aa) return go(a+1,b);
    if (b==bb) return go(a,b+1);
    if (a==n){
        memcpy(ox,sumr,sizeof(ox));
        memcpy(oy,sumc,sizeof(ox));

        REP(i,n) if (i!=bb){
            int u=val[aa][i]==-1?U-sumc[i]:val[aa][i];
            u=u%10+10;
            if ((sumc[i]+u)%10!=U) goto fail;
            sumr[aa]+=u;
            sumc[i]+=u;
        }
        REP(i,n) if (i!=aa){
            int u=val[i][bb]==-1?U-sumr[i]:val[i][bb];
            u=u%10+10;
            if ((sumr[i]+u)%10!=U) goto fail;
            sumc[bb]+=u;
            sumr[i]+=u;

        }
        if (sumr[aa]%10!=sumc[bb]%10) goto fail;
        if (val[aa][bb]!=-1 && (sumr[aa]+val[aa][bb])%10!=U) goto fail;
        ++ans;
fail:
        memcpy(sumr,ox,sizeof(ox));
        memcpy(sumc,oy,sizeof(ox));
        return;
    }
    if (b==n) return go(a+1,0);
    int v=val[a][b];
    REP(u,10){
        if (v==-1 || v==u){
            sumr[a]+=u;
            sumc[b]+=u;
            go(a,b+1);
            sumr[a]-=u;
            sumc[b]-=u;
        }
    }
}


class TheMagicMatrix{ 
    public: 
    int find(int _n, vector <int> rows, vector <int> columns, vector <int> values){ 
        n=_n;
        int m=rows.size();
        int x=n*n-2*n-m;

        cout<<x<<endl;
        if (x>0){

            if (n<=5){
                memset(val,-1,sizeof(val));
                REP(i,m) val[rows[i]][columns[i]]=values[i];
                int seen=-1;
                REP(i,n){
                    int s=0;
                    REP(j,n) if (val[i][j]==-1){s=-1; break;} else s+=val[i][j];
                    if (s!=-1 && s!=seen) return 0;
                    seen=s;
                }
                REP(j,n){
                    int s=0;
                    REP(i,n) if (val[i][j]==-1){s=-1; break;} else s+=val[i][j];
                    if (s!=-1 && s!=seen) return 0;
                    seen=s;
                }


            }
            ll ans=100;
            REP(i,x) ans=ans*10%mod;
            return ans;
        }


        int res=0;
        memset(val,-1,sizeof(val));
        REP(i,m) val[rows[i]][columns[i]]=values[i];

        int best=-1, besta, bestb=0;
        REP(i,n){
            REP(j,n){
                int cnt=0;
                REP(a,n) REP(b,n) if (a!=i && b!=j && val[a][b]!=-1) ++cnt;
                if (best<cnt) best=cnt, besta=i, bestb=j;
            }
        }
        aa=besta; bb=bestb;
        memset(sumr,0,sizeof(sumr));
        memset(sumc,0,sizeof(sumc));
        ans=0;
        REP(i,10){
            U=i;
            go(0,0);
        }
        return ans;
    } 

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arg0 = 2; int Arr1[] = {0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4, 4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 10; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
    void test_case_1() { int Arg0 = 2; int Arr1[] = {0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4, 7}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
    void test_case_2() { int Arg0 = 4; int Arr1[] = {0, 0, 0, 1, 2, 2, 2, 3, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1, 2, 3, 0, 1, 2, 0, 1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3, 5, 1, 9, 5, 1, 8, 6, 7, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
    void test_case_3() { int Arg0 = 474; int Arr1[] = {44, 77}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {47, 74}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4, 7}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 83494518; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

    // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    TheMagicMatrix ___test;
    ___test.run_test(2);
} 
// END CUT HERE
