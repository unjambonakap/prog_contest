// BEGIN CUT HERE

// END CUT HERE
#line 5 "CosmicBlocks.cpp"

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

int ma, mb;
vi have;
int from[44], to[44];
int ne;
int n;
int res;
int bitp[1<<6+1];

int checkit(){
    int perm[6];
    REP(i,n) perm[i]=i;
    int cnt=0;
    do{
        ++cnt;
        REP(i,ne) if (perm[from[i]]>perm[to[i]]){--cnt; break;}
    }while(next_permutation(perm,perm+n));
    return cnt;
}

void go(int rem, int last);
void go2(int rem, int a, int last, vi &tb, vi &lst){
    if (!a){
        vi b;
        REP(i,n) if (last&1<<i) b.pb(i);
        int ca=0, cb=0;
        int na=lst.size(), nb=b.size();
        REP(i,na) ca+=have[lst[i]];
        REP(i,nb) cb+=have[b[i]];

        int u[6];
        REP(i,n) u[i]=have[i];
        vector<vi> x(na);
        int old=ne;
        vi y;
        int aa=0;

        if (ca>cb) goto fail;
        REP(i,na){
            REP(j,n) if (tb[i]&1<<j) x[i].pb(j), --u[lst[i]], --u[j];
            if (u[lst[i]]<0) goto fail;
        }
        REP(i,na) if (x[i].size()==1) u[x[i][0]]-=u[lst[i]]; else if (x[i].size()!=nb) y.pb(i);
        REP(i,nb) if (u[b[i]]<0) goto fail;
        REP(i,y.size()) REP(j,i) if (tb[y[i]]==tb[y[j]]){
            u[lst[y[j]]]+=u[lst[y[i]]];
            y.erase(y.begin()+i);
            break;
        }

        if (y.size()==1){
            int e=y[0];
            int s=0;
            REP(i,x[e].size()) s+=u[x[e][i]];
            if (s<u[lst[e]]) goto fail;

        }else if (y.size()==2){
            int sa=0, sb=0, sc=0;
            int xa=lst[y[0]], xb=lst[y[1]];
            int ua=tb[y[0]], ub=tb[y[1]], uc=ua&ub;
            ua^=uc; ub^=uc;
            REP(i,n){
                if (ua&1<<i) sa+=u[i];
                if (ub&1<<i) sb+=u[i];
                if (uc&1<<i) sc+=u[i];
            }
            if (max(0,u[xa]-sa)+max(0,u[xb]-sb)>sc) goto fail;

        }else if (y.size()==3){
            int V=u[lst[0]];
            REP(i,2) REP(j,2) if (x[1][i]==x[2][j]){if (i) swap(x[1][0],x[1][1]); if (j) swap(x[2][0],x[2][1]); break;}
            printf("HERE\n");
            assert(x[1][0]==x[2][0]);
            assert(x[1][1]!=x[2][1]);
            int fd=0;
            REP(i,V+1) if (u[x[0][0]]>=i && u[x[0][1]]>=V-i){
                u[x[0][0]]-=i;
                u[x[0][1]]-=V-i;
                if (max(0,u[lst[1]]-u[x[1][1]])+max(0,u[lst[2]]-u[x[2][1]])<=u[x[1][0]]){fd=1; break;}
                u[x[0][0]]+=i;
                u[x[0][1]]+=V-i;
            }
            if (!fd) goto fail;
        }


        REP(i,na) REP(j,x[i].size()) from[ne]=lst[i], to[ne++]=x[i][j];
        REP(i,lst.size()) aa|=1<<lst[i];
        go(rem,aa);
        ne=old;

fail:
        return;
    }

    for (int m=last; m; m=(m-1)&last){
        tb.pb(m);
        go2(rem,a&a-1,last,tb,lst);
        tb.pop_back();
    }
}
int CNT=0;

void go(int rem, int last){
    if (!rem){int x=checkit(); if (x>=ma && x<=mb) ++res; return;}

    for (int m=rem; m; m=(m-1)&rem){
        vi lst;
        REP(i,n) if (m&1<<i) lst.pb(i);
        vi tb;
        go2(rem^m,m,last,tb,lst);
    }
}

class CosmicBlocks {
    public:
        int getNumOrders(vector <int> bt, int minWays, int maxWays) {
            ma=minWays; mb=maxWays;
            have=bt;
            n=have.size();
            REP(i,6) bitp[1<<i]=i;
            res=0;
            ne=0;
            REP(i,1<<n) if (i) go((1<<n)-1^i,i);
            return res;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arr0[] = {2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 6; verify_case(0, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
        void test_case_1() { int Arr0[] = {1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 720; int Arg2 = 720; int Arg3 = 1; verify_case(1, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
        void test_case_2() { int Arr0[] = {2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 3; verify_case(2, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
        void test_case_3() { int Arr0[] = {1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; verify_case(3, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
        void test_case_4() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; verify_case(4, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
        void test_case_5() { int Arr0[] = {1,2,4,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 30; int Arg3 = 27; verify_case(5, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
        void test_case_6() { int Arr0[] = {1,2,3,4,5,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 720; int Arg3 = 4445; verify_case(6, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
        void test_case_7() { int Arr0[] = {7500,1000,7500,1000,7500}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 88; int Arg3 = 448; verify_case(7, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    CosmicBlocks ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
