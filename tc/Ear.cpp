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

const int maxn=303;
const double pi=acos(-1);
const double eps=1e-9;
const int maxc=11111;


vi xa,xb,yb;

vector<pii> tmp;

int na, nb;
int have[maxn];
int is[maxn];
int prev[maxc];



class Ear{ 
    public: 
    long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY){ 
        xa.clear(); xb.clear(); yb.clear();
        string s;
        int a;

        FE(it,redX) s+=*it;
        istringstream ss(s);
        while(ss>>a) xa.pb(a);

        s="";
        FE(it,blueX) s+=*it;
        istringstream ssa(s);
        while(ssa>>a) xb.pb(a);

        s="";
        FE(it,blueY) s+=*it;
        istringstream ssb(s);
        while(ssb>>a) yb.pb(a);

        na=xa.size(); nb=xb.size();
        sort(ALL(xa));
        tmp.clear();
        REP(i,nb) tmp.pb(MP(xb[i],yb[i]));
        sort(ALL(tmp));
        REP(i,nb) xb[i]=tmp[i].ST, yb[i]=tmp[i].ND;

        
        int last=0;
        REP(i,maxc){
            if (last<na && xa[last]==i) ++last;
            prev[i]=last-1;
        }
        

        ll res=0;
        REP(i,nb) REP(j,nb){
            double ang=atan2(yb[j]-yb[i],xb[j]-xb[i]);
            if (ang>-eps) continue;
            double nx=xb[i]-yb[i]/tan(ang);
            if (nx<eps) continue;
            if (nx>=maxc) continue;
            pii li,lj,ri,rj;
            li=MP(0,prev[xb[i]-1]);
            ri=MP(prev[xb[i]]+1,na-1);
            lj=MP(0,prev[xb[j]-1]);
            rj=MP(prev[xb[j]]+1,na-1);

            if (nx<xb[i]) li.ND=min(li.ND,prev[(int)(nx-eps)]);
            else ri.ST=max(ri.ST,prev[(int)(nx+eps)]+1);

            li.ND=min(li.ND,lj.ND);
            lj.ST=max(lj.ST,li.ST);

            ri.ST=max(ri.ST,rj.ST);
            rj.ND=min(rj.ND,ri.ND);

            int ua=li.ND-li.ST+1, ub=lj.ND-lj.ST+1;
            int sa=0,sb=0;
            if (ua>0 && ub>0) sa+=ua*ub;
            ua=li.ND-lj.ST+1;
            if (ua>0) sa-=ua*(ua+1)/2;

            ua=ri.ND-ri.ST+1, ub=rj.ND-rj.ST+1;
            if (ua>0 && ub>0) sb+=ua*ub;
            ua=rj.ND-ri.ST+1;
            if (ua>0) sb-=ua*(ua+1)/2;



            res+=1ll*sa*sb;
        }


        return res;
    } 

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { string Arr0[] = {"3 2 8 7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"5 4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 1LL; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
    void test_case_0() { string Arr0[] = {"1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"12 9 6 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 2 3 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 1LL; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }


    void test_case_1() { string Arr0[] = {"3 2 8 7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"2 8"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"3 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
    void test_case_2() { string Arr0[] = {"1 2 6 9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"3 6 8 5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 5 4 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 4LL; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
    void test_case_3() { string Arr0[] = {"10000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"10000 9999"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10000 9999"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
    void test_case_4() { string Arr0[] = {"100 2", "00", " 39", "9", " 800 900 9", "99"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"15", "0 250 ", "349"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 3 1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 12LL; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
    void test_case_5() { string Arr0[] = {"1", " ", "2", " ", "3", " ", "4 5 6", " 7 8 9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"4", " ", "5", " ", "6", " 7 ", "8"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1", " 2 ", "3 4", " 5"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 204LL; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }

    // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    Ear ___test;
    ___test.run_test(0);
} 
// END CUT HERE
