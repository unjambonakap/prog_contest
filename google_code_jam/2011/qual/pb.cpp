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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

string list="QWERASDF";
map<pair<char, char>, char> cmb;
set<pair<char, char> > opp;

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int c, d, n;
        cin>>c;
        cmb.clear();
        opp.clear();
        REP(i, c){
            string sa;
            cin>>sa;
            cmb[MP(sa[0], sa[1])]=sa[2];
            cmb[MP(sa[1], sa[0])]=sa[2];
        }
        cin>>d;
        REP(i, d){
            string sa;
            cin>>sa;
            opp.insert(MP(sa[0], sa[1]));
            opp.insert(MP(sa[1], sa[0]));
        }
        cin>>n;
        string s;
        cin>>s;

        vector<char> tmp;
        REP(i, n){
            if (tmp.size()>0){
                if (cmb.count(MP(s[i], tmp.back()))) tmp.back()=cmb[MP(s[i], tmp.back())];
                else{
                    int clr=0;
                    FE(it, tmp) if (opp.count(MP(*it, s[i]))){clr=1; break;}
                    if (clr) tmp.clear();
                    else tmp.pb(s[i]); 

                }
            }else tmp.pb(s[i]); 
        }

        printf("Case #%d: ", ti);
        printf("[");
        string res;
        REP(i, tmp.size()) res+=(!i?"":", ")+string(1, tmp[i]);
        cout<<res;

        printf("]\n");
    }
    return 0;


}


