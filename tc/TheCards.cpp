// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheCards.cpp"

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

const int maxn=37;
const int maxm=1e6+3;
const int mod=1234567891;
int d[maxn];
int n, m;
int *da, *xla, *xha, *db, *xlb, *xhb;
int *ida, *idb;
int na, nb;
ll *dp[2];

int cmpa(int a, int b){ return da[a]<da[b]; }
int cmpb(int a, int b){ return db[a]<db[b]; }





void dfsa(int u, int p, int b, int xl, int xh){
    if (xh-xl>=m) return;
    if (p==b){ da[na]=u; xla[na]=-xl; xha[na]=m-xh-1; ++na; return; }
    int nv=u+d[p];
    dfsa(nv,p+1,b,xl,max(nv,xh));
    nv=u-d[p];
    dfsa(nv,p+1,b,min(nv,xl),xh);
}
void dfsb(int u, int p, int b, int xl, int xh){
    if (xh-xl>=m) return;
    if (p==b){ db[nb]=u; xlb[nb]=-xl; xhb[nb]=m-xh-1; ++nb; return; }
    int nv=u+d[p];
    assert(p>=b);
    dfsb(nv,p-1,b,xl,max(nv,xh));
    nv=u-d[p];
    dfsb(nv,p-1,b,min(nv,xl),xh);
}


void go(vi &a, int *x){
    int p=0, np=1;
    REP(i,m) dp[p][i]=1;
    REP(i,a.size()){
        memset(dp[np],0,sizeof(ll)*m);
        FOR(j,a[i],m) dp[np][j-a[i]]=dp[p][j]%mod;
        REP(j,m-a[i]) dp[np][j+a[i]]+=dp[p][j]%mod;
        p=np; np^=1;
    }
    REP(i,m) x[i]=dp[p][i]%mod;
}
ll npaths(int u, int v){
    vi a; FOR(i,u,v) a.pb(d[i]);
    int p=0, np=1;
    REP(i,m) dp[p][i]=1;
    REP(i,a.size()){
        memset(dp[np],0,sizeof(ll)*m);
        FOR(j,a[i],m) dp[np][j-a[i]]=dp[p][j]%mod;
        REP(j,m-a[i]) dp[np][j+a[i]]+=dp[p][j]%mod;
        p=np; np^=1;
    }
    ll res=0;
    REP(i,m) res+=dp[p][i];
    return res%mod;
}

class TheCards {
    public:
        int find(vector <int> dist, int _m) {
            m=_m;
            n=0;
            vi tb;
            na=nb=0;
            REP(i,dist.size()){
                if (dist[i]==0);
                else if (dist[i]==-1) tb.pb(n);
                else d[n++]=dist[i];
            }
            ll res;
            if (tb.size()){
                dp[0]=new ll[m]; dp[1]=new ll[m];
                int *A=new int[m];
                int *B=new int[m];
                
                //all middle paths
                ll mul=1;
                REP(i,tb.size()-1) mul*=npaths(tb[i],tb[i+1]), mul%=mod;

                //last path
                vi nd;
                REP(i,tb[0]) nd.pb(d[i]); reverse(ALL(nd));
                go(nd,A);
                nd.clear();
                FOR(i,tb.back(),n) nd.pb(d[i]);
                go(nd,B);

                res=0;
                REP(i,m) res+=1ll*A[i]*B[i]%mod;
                res=res%mod*mul%mod;

                delete[] dp[0]; delete[] dp[1];
                delete[] A; delete[] B;
            }else{
                if (n==0) return m;
                int mid=n/2;
                ida=new int[maxm];
                idb=new int[maxm];
                da=new int[maxm];
                db=new int[maxm];
                xla=new int[maxm];
                xlb=new int[maxm];
                xha=new int[maxm];
                xhb=new int[maxm];

                res=0;
                dfsa(0,0,mid+1,0,0);
                dfsb(0,n-1,mid,0,0);
                REP(i,na) ida[i]=i;
                REP(i,nb) idb[i]=i;
                sort(ida,ida+na,cmpa); sort(idb,idb+nb,cmpb);
                for (int ia=0, ib=0; ia<na&&ib<nb;){
                    int aa=ia;
                    for (; aa<na && da[ida[aa]]==da[ida[ia]]; ++aa);
                    for (; ib<nb && db[idb[ib]]<da[ida[ia]]; ++ib);
                    if (db[idb[ib]]==da[ida[ia]]){
                        int bb=ib;
                        for (; bb<nb && db[idb[bb]]==db[idb[ib]]; ++bb);

                        int last=0;
                        vector<pii> el;
                        FOR(i,ia,aa) el.pb(MP(xla[ida[i]],0)), el.pb(MP(xha[ida[i]]+1,1));
                        FOR(i,ib,bb) el.pb(MP(xlb[idb[i]],2)), el.pb(MP(xhb[idb[i]]+1,3));
                        sort(ALL(el));
                        int s[2]={0,0};

                        REP(i,el.size()){
                            if (last!=el[i].ST)  res+=1ll*s[0]*s[1]%mod*(el[i].ST-last);
                            s[el[i].ND>>1]+=el[i].ND&1?-1:1;
                            last=el[i].ST;
                        }
                        res%=mod;
                        ib=bb;
                    }
                    ia=aa;
                }
                delete[] da; delete[] db; delete[] ida; delete[] idb;
                delete[] xla; delete[] xlb; delete[] xha; delete[] xhb;
            }
            return res;

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arr0[] = {3, 1, 2, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 8; verify_case(0, Arg2, find(Arg0, Arg1)); }
        void test_case_1() { int Arr0[] = {4, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 47; int Arg2 = 0; verify_case(1, Arg2, find(Arg0, Arg1)); }
        void test_case_2() { int Arr0[] = {1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 32; verify_case(2, Arg2, find(Arg0, Arg1)); }
        //void test_case_3() { int Arr0[] = {5, -1, -1, 4, 0, 2, -1, 8, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 11; int Arg2 = 4224; verify_case(3, Arg2, find(Arg0, Arg1)); }
        //void test_case_3() { int Arr0[] = {-1,2,1,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 4224; verify_case(3, Arg2, find(Arg0, Arg1)); }
        void test_case_3() { int Arr0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 555774; int Arg2 = 4224; verify_case(3, Arg2, find(Arg0, Arg1)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    TheCards ___test; 
    ___test.run_test(3); 
} 
// END CUT HERE
