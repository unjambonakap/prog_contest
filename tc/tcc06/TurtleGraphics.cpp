// BEGIN CUT HERE

// END CUT HERE
#line 5 "TurtleGraphics.cpp"

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

struct vec{
    vector<double> v;
    vec(){ v=vector<double>(3, 0.); }
    vec(double a, double b, double c){v.pb(a); v.pb(b); v.pb(c);}

    vec operator-()const{
        vec u;
        REP(i, 3) u.v[i]=-v[i];
        return u;
    }
    vec& operator+=(vec &u){
        REP(i, 3) v[i]+=u.v[i];
        return *this;
    }

    vec crossprod(vec &u)const{
        return vec(v[1]*u.v[2]-v[2]*u.v[1],
                v[2]*u.v[0]-v[0]*u.v[2],
                v[0]*u.v[1]-v[1]*u.v[0]);
    }

};
struct state{
    vec da, db, p;
    state(){
        da=vec(1, 0, 0);
        db=vec(0, 1, 0);
        p=vec(0, 0, 0);
    }
    state &operator+=(const state &s){
        state ns=*this;
        vec z=da.crossprod(db);
        double sgn[3]; int perm[3];
        REP(i, 3) if (fabs(da.v[i])>0.5){perm[0]=i; sgn[0]=da.v[i]; break;}
        REP(i, 3) if (fabs(db.v[i])>0.5){perm[1]=i; sgn[1]=db.v[i]; break;}
        REP(i, 3) if (fabs(z.v[i])>0.5){perm[2]=i; sgn[2]=z.v[i]; break;}
        REP(i, 3) ns.p.v[perm[i]]+=s.p.v[i]*sgn[i];
        REP(i, 3) ns.da.v[perm[i]]=s.da.v[i]*sgn[i];
        REP(i, 3) ns.db.v[perm[i]]=s.db.v[i]*sgn[i];
        p=ns.p;
        da=ns.da;
        db=ns.db;
        return *this;
    }
};

int pos;
string cmd;
state proc(){

    state s;
    while(pos<cmd.length()){

        if (cmd[pos]=='('){
            ++pos;
            state ns=proc();
            int rep=1;
            if (pos<cmd.length() && cmd[pos]>='0' && cmd[pos]<='9') rep=cmd[pos++]-'0';
            REP(i, rep) s+=ns;
        }else if(cmd[pos]==')'){
            ++pos;
            break;
        }else{
            char c=cmd[pos++];
            int rep=1;
            if (pos<cmd.length() && cmd[pos]>='0' && cmd[pos]<='9') rep=cmd[pos++]-'0';
            REP(i, rep){
                if (c=='F'){
                    s.p+=s.da;
                }else if (c=='U'){
                    vec tmp=-s.da;
                    s.da=s.db;
                    s.db=tmp;
                }else if (c=='D'){
                    vec tmp=-s.db;
                    s.db=s.da;
                    s.da=tmp;
                }else if (c=='R'){
                    s.da=s.db.crossprod(s.da);
                }else if (c=='L'){
                    s.da=s.da.crossprod(s.db);
                }
            }
        }
    }
    return s;
}


class TurtleGraphics {
    public:
        double distance(string command) {
            cmd=command;
            pos=0;
            state s=proc();
            return sqrt(s.p.v[0]*s.p.v[0]+s.p.v[1]*s.p.v[1]+s.p.v[2]*s.p.v[2]);
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { string Arg0 = "FRF"; double Arg1 = 1.4142135623730951; verify_case(0, Arg1, distance(Arg0)); }
        void test_case_0() { string Arg0 = "((((((((((((((((F9)9)9)9)9)9)9)9)9)9)9)9)9)9)9)9)9"; double Arg1 = 1.4142135623730951; verify_case(0, Arg1, distance(Arg0)); }
        //void test_case_0() { string Arg0 = "UDRDD"; double Arg1 = 1.4142135623730951; verify_case(0, Arg1, distance(Arg0)); }
        void test_case_1() { string Arg0 = "FUFUFUF"; double Arg1 = 0.0; verify_case(1, Arg1, distance(Arg0)); }
        void test_case_2() { string Arg0 = "FRFUF"; double Arg1 = 1.7320508075688772; verify_case(2, Arg1, distance(Arg0)); }
        void test_case_3() { string Arg0 = "F(((D)4)4)9F"; double Arg1 = 2.0; verify_case(3, Arg1, distance(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    TurtleGraphics ___test; 
    ___test.run_test(0); 
} 
// END CUT HERE
