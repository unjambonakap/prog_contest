// BEGIN CUT HERE

// END CUT HERE
#line 5 "Monopolies.cpp"

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


const double eps=1e-10;
const double pe=1/36.;
const int n=40, maxt=22, maxm=11, maxk=3;
int nxt[]={11,24,29,39};
set<int> draw;

double pm[maxm][2];
double p[n][maxt][maxk];
double pz[n][maxt][maxk];
void proc(){
    memset(pz, 0, sizeof(pz));
    memset(p, 0, sizeof(p));
    p[0][0][0]=1.;
    REP(i, n)  REP(j, maxt-1) REP(k, maxk){
        double pa=p[i][j][k];
        if (i==30) continue;
        REP(m, maxm) if (i+m+2<n) REP(f, 2){
            int ni=i+m+2, nk=f?k+1:0, nj=j+1-f;
            if (nk==maxk) continue;
            double px=pa*pm[m][f];
            pz[ni][j][nk]+=px;
            if (draw.count(ni)){
                REP(l, 4) if (nxt[l]>ni) p[nxt[l]][nj][nk]+=px*1./20, pz[nxt[l]][j][nk]+=px*1./20;;
                px*=14./20;
            }
            p[ni][nj][nk]+=px;
        }

    }

}

class Monopolies {
    public:
        double probability(int square) {
            memset(pm, 0, sizeof(pm));
            REP(i, 6) REP(j, 6) if (i!=j) pm[i+j][0]+=pe;
            REP(i, 6) pm[2*i][1]=pe;
            draw.clear();
            draw.insert(7);
            draw.insert(22);
            draw.insert(36);


            proc();


            double suma[maxt+1];
            suma[0]=1.;
            REP(i, maxt){
                suma[i+1]=suma[i];
                REP(k, maxk) suma[i+1]-=pz[square][i][k];
            }
            double res=0.;
            REP(i, maxt) REP(k, maxk) res+=pz[square][i][k]*suma[i+1];
            printf("<< %.10lf\n", res);
            return res;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { int Arg0 = 1; double Arg1 = 0.0; verify_case(0, Arg1, probability(Arg0)); }
        void test_case_0() { int Arg0 = 11; double Arg1 = 0.0; verify_case(0, Arg1, probability(Arg0)); }
        void test_case_1() { int Arg0 = 22; double Arg1 = 0.12122739832411301; verify_case(1, Arg1, probability(Arg0)); }
        void test_case_2() { int Arg0 = 30; double Arg1 = 0.11905533142891316; verify_case(2, Arg1, probability(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    Monopolies ___test; 
    ___test.run_test(0); 
} 
// END CUT HERE
