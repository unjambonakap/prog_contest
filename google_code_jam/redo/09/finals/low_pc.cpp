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

const int maxn=4;
const int maxv='z'-'a';
const int mod=1e4+7;
int r, c;
int mp[maxn][maxn];
struct state{
    vi v;
    int ra, ca;
    state &operator=(const state &s){
        v=s.v;
        ra=s.ra;
        ca=s.ca;
        return *this;
    }
    bool operator<(const state &s)const{
        if (ra!=s.ra) return ra<s.ra;
        if (ca!=s.ca) return ca<s.ca;
        return v<s.v;
    }
};
map<state, int> mem;
int solve(const state &s){
    if (s.ca==c) return 1;
    if (mem.count(s)) return mem[s];
    int &res=mem[s];
    res=0;
    state ns=s;
    if (++ns.ra==r) ns.ra=0, ++ns.ca;
    assert(ns.ra<r);
    int a, b;
    a=s.ra, b=s.ca;
    int mv=(a>0?max(s.v[a-1], s.v[a]):s.v[a]);
    if (mp[a][b]=='.'){
        FOR(i, mv, maxv){
            ns.v[a]=i;
            res+=solve(ns);
        }
        res%=mod;
    }else if (mp[a][b]>=mv){
        ns.v[a]=mp[a][b];
        res=solve(ns);
    }




    return res;
}


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>r>>c;
        REP(i, r){
            string s;
            cin>>s;
            REP(j, c){
                mp[i][j]=s[j];
                if (s[j]!='.') mp[i][j]-='a';
            }

        }

        int res;
        state s;
        s.v.assign(r, 0);
        s.ca=s.ra=0;
        mem.clear();
        res=solve(s);
        printf("Case #%d: %d\n", ti, res);

    }
    return 0;
}



