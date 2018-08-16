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
double todouble(string s){double a; istringstream(s)>>a; return a;}
ll toll(string s){ll a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=110;
const int maxd=50;
typedef long double ld;
const ld eps=1e-12;

map<int, set<string> > res;

ll gcd(ll a, ll b){return (b==0?a:gcd(b, a%b));}

struct frac{
    ld a, b;
    frac(){}
    frac(ld a, ld b):a(a), b(b){}
    bool operator<(const frac &s)const{ return ld(a)*s.b<ld(s.a)*b; }
    bool operator<=(const frac &s)const{ return ld(a)*s.b<=eps+ld(s.a)*b; }

};
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int n;
        cin>>n;
        res.clear();
        REP(i, n){
            string s;
            cin>>s;

            string ns=s;
            ns.erase(0, 2);

            ll pt=1;
            REP(i, ns.size()) pt*=10;

            ll d=gcd(pt, toll(ns));
            frac a(toll(ns)/d, pt/d);
            frac H(1, 1), T(0, 1), L, R;

            int p=0;
            //printf("try %Ld %Ld, %s\n", a.a, a.b, s.c_str());
            while(1){
                L=frac(T.a*3+1, T.b*3);
                R=frac(T.a*3+2, T.b*3);
                if ((L<=a && a<=R) || p==28){ res[p].insert(s); break;}

                if (a<L) H=L, T.b*=3, T.a*=3;
                else T=R, H.b*=3, H.a*=3;
                ++p;
            }


        }



        printf("Case #%d:\n", ti);
        FE(it, res) FE(ita, it->ND) printf("%s\n", ita->c_str());
        

    }
    return 0;

}




