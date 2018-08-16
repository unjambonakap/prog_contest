// BEGIN CUT HERE

// END CUT HERE
#line 5 "TaylorAlgebra.cpp"

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


const int minv=1, maxv=100;
const int maxn=50;
string s;
int n;
int pos;
int cnt;


struct formula{
    int type;
    formula *next;
    int num;

    void build();
    int update();
    void copy(const formula &s){ type=s.type; next=s.next; num=s.num; }
    int finda(){
        if (type==2) return maxv;
        if (type==3 || type==1) return minv;
        return min(next->finda(), num);
    }
    int findb(){
        if (type==1) return minv;
        if (type==3 || type==2) return maxv;
        return max(next->findb(), num);
    }

    void updatea(){
        if (type==2){ 
            copy(*next);
            return;
        }
        printf("<< %d\n", type);
        assert(type==0);
        --num;
        next->updatea();


    }

    void updateb(){
        if (type==1){
            copy(*next);
            return;
        }
        assert(type==0);
        ++num;
        next->updateb();

    }
    string disp(){
        if (type==3) return "f";
        if (type==1) return "D("+next->disp()+")";
        if (type==2) return "I("+next->disp()+")";
        return "T("+toStr(num)+","+next->disp()+")";


    }

    int nest(){
        if (type==3) return 0;
        if (next->type==0){
            if ((type==1 && next->num>minv) || (type==2 && next->num<maxv)){
                next->type=type;
                num=next->num+(type==1?-1:1);type=0;
                return 1;
            }
        }
        return next->nest();

    }
};

formula tb[maxn];


void formula::build(){
    if (s[pos]=='D'){
        type=1; pos+=2;
        next=tb+cnt++;
        next->build();
        ++pos;
    }else if (s[pos]=='I'){
        type=2; pos+=2;
        next=tb+cnt++;
        next->build();
        ++pos;
    }else if (s[pos]=='f'){
        type=3;
        ++pos;
    }else{
        type=0; pos+=2;
        num=toInt(s.substr(pos));
        while(s[pos]!=',') ++pos;
        ++pos;
        next=tb+cnt++;
        next->build();
        ++pos;
    }
}


int formula::update(){
    if (type==3) return 0;
    if (type==2 && next->type==1){
        copy(*next->next);
        return 1;
    }
    if (type==1 && next->type==2){
        copy(*next->next);
        return 1;
    }

    if (type==1){
        int p=next->finda();
        if (p>minv){
            copy(*next);
            assert(num>minv);
            --num;
            next->updatea();
            return 1;
        }
    }else if (type==2){
        int p=next->findb();
        if (p<maxv){
            copy(*next);
            assert(num<maxv);
            ++num;
            next->updateb();
            return 1;
        }
    }
    return next->update();
}



class TaylorAlgebra {
    public:
        string getCanonical(string _s) {
            s=_s;
            formula root;
            pos=0; n=s.length();
            cnt=1;
            tb[0].build();
            assert(pos==n);

            while(tb[0].update());
            while(tb[0].nest());
            return tb[0].disp();

        }


        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arg0 = "T(100,f)"; string Arg1 = "T(100,f)"; verify_case(0, Arg1, getCanonical(Arg0)); }
        void test_case_1() { string Arg0 = "D(T(50,f))"; string Arg1 = "T(49,D(f))"; verify_case(1, Arg1, getCanonical(Arg0)); }
        void test_case_2() { string Arg0 = "D(T(1,f))"; string Arg1 = "D(T(1,f))"; verify_case(2, Arg1, getCanonical(Arg0)); }
        void test_case_3() { string Arg0 = "I(T(100,f))"; string Arg1 = "I(T(100,f))"; verify_case(3, Arg1, getCanonical(Arg0)); }
        void test_case_4() { string Arg0 = "D(T(40,I(f)))"; string Arg1 = "T(39,f)"; verify_case(4, Arg1, getCanonical(Arg0)); }
        void test_case_5() { string Arg0 = "I(T(40,D(f)))"; string Arg1 = "T(41,f)"; verify_case(5, Arg1, getCanonical(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    TaylorAlgebra ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
