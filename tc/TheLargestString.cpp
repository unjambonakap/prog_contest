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
typedef pair<string,string> pss;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxn=55;
int cmp(pss &a, pss &b){ return a.ST+a.ND<b.ST+b.ND; }

void update(pss &a, pss b){
    if (cmp(a,b)) a=b;
}
pss go0(string a, string b);

pss go(string a, string b, string nd){
    int n=a.size();
    if (!n) return MP("","");

    cout<<a<<' '<<b<<endl;
    char besta=0;
    vi lsta;
    REP(i,n) besta=max(besta,a[i]);
    REP(i,n) if (a[i]==besta) lsta.pb(i);
    if (besta<nd[0]) return MP("","");
    if (besta==nd[0]){
        pii ans;
        int st=0;
        REP(j,nd.size()) if (nd[j]<nd[0]){st=-1; break;} else if (nd[j]>nd[0]){st=1; break;}
        if (st==1) return MP("","");
        else if (st==-1){
            string aa, bb;
            REP(i,lsta.size()) aa+=a[lsta[i]], bb+=b[lsta[i]];
            return MP(aa,bb);
        }else{
            string aa,bb;
            REP(i,lsta.size()) aa+=a[lsta[i]], bb+=b[lsta[i]];
            return go0(aa,bb);
        }
    }


    string aa,bb;
    REP(i,lsta.size()) aa+=besta, bb+=b[lsta[i]];
    string na,nb;
    FOR(i,lsta.back()+1,n) na+=a[i], nb+=b[i];
    pss tmp=go(na,nb,nd+bb);
    return MP(aa+tmp.ST,bb+tmp.ND);
}

pss go0(string a, string b){
    int n=a.size();
    if (!n) return MP("","");

    char besta=0;
    vi lsta;
    REP(i,n) besta=max(besta,a[i]);
    REP(i,n) if (a[i]==besta) lsta.pb(i);

    char bestb=0;
    vi lstb;
    REP(i,lsta.size()) bestb=max(bestb,b[lsta[i]]);
    REP(i,lsta.size()) if (bestb==b[lsta[i]]) lstb.pb(lsta[i]);

    printf("%c %c\n",besta,bestb);
    if (besta<bestb) return MP(string()+besta,string()+bestb);
    if (besta>bestb){
        string aa,bb;
        REP(i,lsta.size()) aa+=besta, bb+=b[lsta[i]];
        string na,nb;
        FOR(i,lsta.back()+1,n) na+=a[i], nb+=b[i];
        pss tmp=go(na,nb,bb);
        return MP(aa+tmp.ST,bb+tmp.ND);
    }

    pss ans;
    REP(i,lsta.size()){
        string aa, bb;
        REP(j,lstb.size()) if (lstb[j]<lsta[i]) aa+=besta, bb+=besta;
        FOR(j,i,lsta.size()) aa+=a[lsta[j]], bb+=b[lsta[j]];
        if (!i){
            string na,nb;
            FOR(i,lsta.back()+1,n) na+=a[i], nb+=b[i];
            pss tmp=go(na,nb,bb);
            aa+=tmp.ST;
            bb+=tmp.ND;
        }
        update(ans,MP(aa,bb));

    }
    return ans;

}


class TheLargestString{ 
    public: 
        string find(string s, string t){ 
            pss x=go0(s,t); 
            return x.ST+x.ND;
        } 

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //["",]:"yyhqrp"
        //void test_case_0() { string Arg0 = "azuxmhecthlegrpunkdmbppweqtgjoparmowzdqyoxytjbb"; string Arg1 =  "hawdydcprjbxphoohpkwqyuhrqzhnbnfuvqnqqlrzjpxiog"; string Arg2 = "by"; verify_case(0, Arg2, find(Arg0, Arg1)); }
        void test_case_0() { string Arg0 = "ebeda"; string Arg1 =  "azefa"; string Arg2 = "by"; verify_case(0, Arg2, find(Arg0, Arg1)); }
        //void test_case_0() { string Arg0 = "kmmkmnmlmnnkknmmknkmmmnllmkklmmnlnlkklnkkmnllkl"; string Arg1 =  "mmmlmlmllmmllmlmmlmllmmlmmlmllmmmmlmmmmlmmmmllm"; string Arg2 = "by"; verify_case(0, Arg2, find(Arg0, Arg1)); }
        //void test_case_0() { string Arg0 = "ab"; string Arg1 = "zy"; string Arg2 = "by"; verify_case(0, Arg2, find(Arg0, Arg1)); }
        void test_case_1() { string Arg0 = "abacaba"; string Arg1 = "zzzaaaa"; string Arg2 = "cbaaaa"; verify_case(1, Arg2, find(Arg0, Arg1)); }
        void test_case_2() { string Arg0 = "x"; string Arg1 = "x"; string Arg2 = "xx"; verify_case(2, Arg2, find(Arg0, Arg1)); }
        void test_case_3() { string Arg0 = "abbabbabbababaaaabbababab"; string Arg1 = "bababbaabbbababbbbababaab"; string Arg2 = "bbbbbbbbbbbbbbbbbbaaab"; verify_case(3, Arg2, find(Arg0, Arg1)); }

        // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    TheLargestString ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
