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

const int maxn=82;
struct state{
    int c, s, t;
    state(int c, int s, int t):c(c), s(s), t(t){}
    state(){}
};
struct cmpT{
    bool operator()(const state &a, const state &b)const{
        return a.t>b.t;
    }
};
struct cmpC{
    bool operator()(const state &a, const state &b)const{
        if (a.c!=b.c) return a.c>b.c;
        return a.s>b.s;
    }
};
struct cmpS{
    bool operator()(const state &a, const state &b)const{
        return a.s>b.s;
    }
};

int mem[maxn][maxn][maxn][maxn];//pos, t, ca, cb
int nxt[maxn][2];
int addt[maxn][2];
int adds[maxn][2];
deque<state> hand;
deque<state> deck;
state cards[maxn];
int ea[maxn], eb[maxn], eo[maxn];
int nca, ncb, nco;
vi ma, mb, mo;
int n, m;


int proc(int p, int t, int ca, int cb){
    if (t==0) return 0;
    int &r=mem[p][t][ca][cb];
    if (r!=-1) return r;
    //printf("call %d %d %d %d, %d %d\n", p, t, ca, cb, eo[p], ea[p]);


    r=0;

    vi tmp;

    REP(i, eo[p]) tmp.pb(mo[i]);
    assert(ma.size()>=ea[p]);
    assert(mb.size()>=eb[p]);
    FOR(i, ca, ea[p]-1) tmp.pb(ma[i]);
    FOR(i, cb, eb[p]-1) tmp.pb(mb[i]);
    sort(ALL(tmp), greater<int>());
    //out(tmp);
    REP(i, min((int)tmp.size(), t)) r+=tmp[i];
    


    if (p==n+m) return r;
    if (t>1){
        FOR(i, ca, ea[p]-1) checkmax(r, ma[i]+proc(nxt[p][0], min(n+m, t-1+addt[p][0]), i+1, cb)+adds[p][0]);
        FOR(i, cb, eb[p]-1) checkmax(r, mb[i]+proc(nxt[p][1], min(n+m, t-1+addt[p][1]), ca, i+1)+adds[p][1]);
    }
    //printf("havin %d xx %d %d\n", r);
    return r;

}
int solve(){
    int ans=0;
    sort(ALL(hand), cmpT());
    int pos=0;
    int s=0;
    int t=1;
    while(!hand.empty() && hand[0].t){
        s+=hand[0].s;
        t+=hand[0].t-1;
        int c=hand[0].c;
     //   printf("take %d %d, %d\n", c, t, pos);
        hand.pop_front();
        REP(i, c) if (!deck.empty()){
            ++pos;
            if (deck[0].t) hand.push_front(deck[0]);
            else  hand.pb(deck[0]);
            deck.pop_front();
        }
    }
    int ep=n+pos;
    int na=deck.size();
    REP(i, na){

        REP(j, 2){
            int pos=i;
            deque<state> q;
            REP(k, j+1) if (pos<na){
                if (deck[pos].t) q.push_front(deck[pos]);
                else q.pb(deck[pos]);
                ++pos;
            }
            int nt, ns;
            nt=ns=0;

            while(!q.empty() && q[0].t){
                nt+=q[0].t-1;
                ns+=q[0].s;
                int c=q[0].c;
                q.pop_front();
                REP(i, c) if (pos<na){
                    if (deck[pos].t) q.push_front(deck[pos]);
                    else q.pb(deck[pos]);
                    ++pos;
                }
            }
            nxt[ep+i][j]=ep+pos;
            addt[ep+i][j]=nt;
            adds[ep+i][j]=ns;
        }
    }

    nca=ncb=nco=0;
    ma.clear(); mb.clear(); mo.clear();
    REP(i, n+m){
        ea[i]=nca; eb[i]=ncb; eo[i]=nco;
        if (cards[i].t==0){
            if (cards[i].c==0) mo.pb(cards[i].s), ++nco;
            else if (cards[i].c==1) ma.pb(cards[i].s), ++nca;
            else if (cards[i].c==2) mb.pb(cards[i].s), ++ncb;
        }
    }
    ea[n+m]=nca; eb[n+m]=ncb; eo[n+m]=nco;
    memset(mem, -1, sizeof(mem));

    //printf("end at %d, %d %d\n", ep, s, t);
    return proc(ep, min(n+m, t), 0, 0)+s;




}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        hand.clear();
        deck.clear();
        cin>>n;
        REP(i, n){
            int c, s, t;
            cin>>c>>s>>t;
            hand.pb(state(c, s, t));
            cards[i]=hand.back();
        }
        cin>>m;
        REP(i, m){
            int c, s, t;
            cin>>c>>s>>t;
            deck.pb(state(c, s, t));
            cards[i+n]=deck.back();
        }
    //    if (ti!=9)continue;
    //    printf("%d %d\n", n, m);
    //    REP(i, n+m) printf("%d %d %d\n", cards[i].s, cards[i].c, cards[i].t);
        printf("Case #%d: %d\n", ti, solve());

    }
    return 0;
}



