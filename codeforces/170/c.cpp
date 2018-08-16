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
typedef unsigned int uint;
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


const int maxk=1e5+10;
map<int,int> rmpx, rmpy;
int mpx[maxk], mpy[maxk];
int posx, posy;
vector<pii> lx[maxk], ly[maxk];
int seenx[maxk], seeny[maxk];

int get(map<int,int> &rmp, int &pos, int x, int *tb){
    if (rmp.count(x)) return rmp[x];
    tb[pos]=x;
    return rmp[x]=pos++;
}

int go(vector<pii> &l, int u){
    sort(ALL(l));
    int res=0;
    for (int i=0; i<l.size();){
        int st=l[i].ST, nd=l[i].ND;
        for (++i; i<l.size() && l[i].ST<=nd; ++i) nd=max(nd,l[i].ND);
        u-=nd-st;
    }
    return u;
}

int go2(vector<pii> &l, int a){
    int pos=0;
    for (int i=0; i<l.size(); ++i){
        if (pos<l[i].ST){
            int have=l[i].ST-pos;
            if (have>=a) return pos+a;
            a-=have;
        }
        pos=max(pos,l[i].ND);
    }
    return pos+a;
}
void disp(int xa, int ya, int xb, int yb){printf("%d %d %d %d\n",xa,ya,xb,yb);}

int main(){
    int res=0;
    int n,m,k;
    cin>>n>>m>>k;
    REP(i,k){
        int xa,ya,xb,yb; scanf(" %d%d%d%d",&xa,&ya,&xb,&yb);
        if (xa==xb){
            if (xa<maxk) seenx[xa]=1;
            int rx=get(rmpx,posx,xa,mpx);
            if (ya>yb) swap(ya,yb);
            lx[rx].pb(MP(ya,yb));
        }else{
            if (ya<maxk) seeny[ya]=1;
            int ry=get(rmpy,posy,ya,mpy);
            if (xa>xb) swap(xa,xb);
            ly[ry].pb(MP(xa,xb));
        }
    }


    if (n-1-posx&1) res^=m;
    if (m-1-posy&1) res^=n;


    vector<pii> tx,ty;
    int sx=-1,sy=-1;
    FOR(i,1,n) if (!seenx[i]){sx=i; break;}
    FOR(i,1,m) if (!seeny[i]){sy=i; break;}

    if (sx!=-1) tx.pb(MP(m,posx)), mpx[posx]=sx;
    if (sy!=-1) ty.pb(MP(n,posy)), mpy[posy]=sy;


    REP(i,posx){
        int tmp=go(lx[i],m);
        tx.pb(MP(tmp,i));
        res^=tmp;
    }
    REP(i,posy){
        int tmp=go(ly[i],n);
        ty.pb(MP(tmp,i));
        res^=tmp;
    }

    if (res){
        puts("FIRST");
        REP(i,tx.size()){
            int want=tx[i].ST-(tx[i].ST^res);
            if (want<0) continue;
            int yb=go2(lx[tx[i].ND],want);
            disp(mpx[tx[i].ND],0,mpx[tx[i].ND],yb);
            goto done;
        }
        REP(i,ty.size()){
            int want=ty[i].ST-(ty[i].ST^res);
            if (want<0) continue;
            int yb=go2(ly[ty[i].ND],want);
            disp(0,mpy[ty[i].ND],yb,mpy[ty[i].ND]);
            goto done;
        }
done:;
    }else puts("SECOND");



    return 0;
}

