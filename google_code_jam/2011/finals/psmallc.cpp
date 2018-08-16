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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int inf=1e6+10;


struct action{
    int ns, nm, d;
    action(int ns, int nm, int d):ns(ns), nm(nm), d(d){}
    action(){}
};


string build(int s, int m, int d, int ns, int nm){return toStr(s)+" "+toStr(m)+" -> "+(d==1?"E":"W")+" "+toStr(ns)+" "+toStr(nm);}


void simul(const vs &vx, int n){
    string s;
    pii drop;
    map<pii, action> mp;
    //cout<<sx<<endl;
    FE(it, vx){
        istringstream ss(*it);
        int a, b; string sa;
        ss>>a>>b>>sa;
        ss>>sa;
        //cout<<a<<" "<<b<<" "<<sa<<endl;
        if (sa[0]=='R') drop=MP(a, b);
        else{
            int c, d;
            ss>>c>>d;
            mp[MP(a, b)]=action(c, d, sa[0]=='W'?-1:1);
        }
    }
    int state[2*inf];
    memset(state, 0, sizeof(state));
    int x, y;
    x=y=0;
    //printf("WANTING %d\n", n);
    REP(i, inf){
        int st=state[x+inf];
        //printf("<< on x %d, state %d, lamp %d\n", x, y, st);
        if (MP(y, st)==drop){
            fprintf(stderr, "found on %d %d\n", i, n);
            //printf("got %d , must have %d\n", x, n);
            assert(x==n);
            return;
        }
        if (!mp.count(MP(y, st))) assert(0);
        action c=mp[MP(y, st)];
        state[inf+x]=c.nm;
        x+=c.d;
        y=c.ns;
    }
    assert(0);
    return;

}

vs solve(int n){
    vs res;
    int W=-1, E=1;
    if (n<=10){
        REP(i, n) res.pb(build(i, 0, E, i+1, 0));
        res.pb(toStr(n)+" 0 -> R");
        return res;
    }
    int fx=42, dx=-42, FINAL=72;

    res.pb(toStr(FINAL)+" 0 -> R");
    res.pb(build(FINAL, 1, E, FINAL, 1));
    res.pb(build(FINAL, 2, E, FINAL, 2));
    res.pb(build(FINAL, 12, E, FINAL, 2));


    int k=0;
    int nd=9;
    n-=nd+1;
    REP(i, nd) res.pb(build(i, 0, E, i==nd-1?fx:i+1, 1+bool(n&two(nd-i-1))));

    res.pb(build(fx, 1, E, fx, 2));

    res.pb(build(fx, 0, W, dx, 12));//unvisited lamp => mark it, go backward
    res.pb(build(fx, 12, E, fx, 12));

    res.pb(build(dx, 12, W, dx, 12));
    res.pb(build(dx, 0, E, FINAL, 0));
    res.pb(build(dx, 2, E, fx, 1));
    res.pb(build(dx, 1, W, dx, 1));
    
    return res;
}



int main(){
    int tn;
    cin>>tn;
    REP(ti, tn){
        int n;
        cin>>n;
        //if (ti!=1) continue;
        vs res=solve(n);

        printf("Case #%d: %d\n", ti+1, res.size());

        FE(it, res) cout<<*it<<endl;
        simul(res, n);

    }


    return 0;
}


