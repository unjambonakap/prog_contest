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

const int maxn=1e5+10;
const int maxb=19;
int n,m,nk;
int x[5*maxn], y[5*maxn];
int xo,yo;
int seen[5*maxn][4];

int cmp(int a, int b){ return x[a]<x[b]; }
vi la[2*maxn], lb[2*maxn];
map<pii,int> have;

vi op[2*maxn], cl[2*maxn];
vector<pii> tb[2*maxn];


int vx[]={-1,1,1,-1};
int vy[]={1,1,-1,-1};
vector<pair<pii,int> > tx,ty;


int tree[(1<<maxb)+1];
int cnt[2*maxn];

void update(int a, int v){
    cnt[a]+=v;
    if (!cnt[a]) v=-1;
    else if (cnt[a]==1 && v==1) v=1;
    else return;
    for (++a; a<=1<<maxb; a+=a&-a) tree[a]+=v;
}

int get(int a){
    int res=0;
    for (++a; a; a&=a-1) res+=tree[a];
    return res;
}



int go(vi &l, int xx){
    int T=0, H=l.size()-1;
    int best=-1;
    while(T<=H){
        int M=T+H>>1;
        if (x[l[M]]<=xx) T=M+1, best=M;
        else H=M-1;
    }
    return best;

}

int main(){
    cin>>n>>m>>nk;
    map<string,int> mp;
    mp["NE"]=0; mp["SW"]=2;
    mp["SE"]=1; mp["NW"]=3;

    REP(i,nk) scanf(" %d%d",x+i,y+i);

    REP(i,n+2){
        x[nk]=i; y[nk++]=0;
        x[nk]=i; y[nk++]=m+1;
    }
    REP(i,m){
        x[nk]=0; y[nk++]=i+1;
        x[nk]=n+1; y[nk++]=i+1;
    }

    REP(i,nk) have[MP(x[i],y[i])]=i;
    REP(i,nk){
        la[x[i]+y[i]].pb(i);
        lb[x[i]-y[i]+maxn].pb(i);
    }

    REP(i,2*maxn) sort(ALL(la[i]),cmp);
    REP(i,2*maxn) sort(ALL(lb[i]),cmp);

    scanf(" %d%d",x+nk,y+nk);
    string ss; cin>>ss;
    int s=nk, d=mp[ss];
    int first=1;
    while(1){
        if (seen[s][d]) break;
        seen[s][d]=1;
        if (d&1){
            int e=x[s]-y[s]+maxn;
            int u=go(lb[e],x[s]+vx[d]);
            while((x[lb[e][u]]-x[s])*vx[d]<=0) u+=vx[d];

            
            u=lb[e][u];
            tx.pb(MP(MP(x[s]+(1-first)*vx[d],y[s]+(1-first)*vy[d]),x[u]-x[s]+vx[d]*(-2+first)));
            int fa=have.count(MP(x[u]-vx[d],y[u])), fb=have.count(MP(x[u],y[u]-vy[d]));

            if (!(fa^fb)) d^=2, s=u;
            else if (fa) s=have[MP(x[u]-vx[d],y[u])], d=(d+1)%4;
            else s=have[MP(x[u],y[u]-vy[d])], d=(d+3)%4;
        }else{
            int e=x[s]+y[s];
            int u=go(la[e],x[s]+vx[d]);
            while((x[la[e][u]]-x[s])*vx[d]<=0) u+=vx[d];

            u=la[e][u];
            ty.pb(MP(MP(x[s]+(1-first)*vx[d],y[s]+(1-first)*vy[d]),x[u]-x[s]+vx[d]*(-2+first)));
            int fa=have.count(MP(x[u]-vx[d],y[u])), fb=have.count(MP(x[u],y[u]-vy[d]));
            if (!(fa^fb)) d^=2, s=u;
            else if (fa) s=have[MP(x[u]-vx[d],y[u])], d=(d+3)%4;
            else s=have[MP(x[u],y[u]-vy[d])], d=(d+1)%4;

        }
        first=0;
    }

    ll res=0;

    REP(ff,2){
        REP(i,n+m+3) tb[i].clear();
        REP(i,tx.size()){
            int aa,bb,cc;
            bb=tx[i].ST.ST+tx[i].ST.ND;
            if ((bb&1)!=ff) continue;

            aa=tx[i].ST.ST-tx[i].ST.ND+maxn;
            cc=bb+2*tx[i].ND;
            if (bb>cc) swap(bb,cc);
            op[bb].pb(aa);
            cl[cc].pb(aa);
        }
        REP(i,ty.size()) if ((ty[i].ST.ST+ty[i].ST.ND&1)==ff){
            int aa=ty[i].ST.ST+ty[i].ST.ND;
            if ((aa&1)!=ff) continue;
            int bb=ty[i].ST.ST-ty[i].ST.ND+maxn, cc=bb+ty[i].ND*2;
            if (bb>cc) swap(bb,cc);
            tb[aa].pb(MP(bb,cc));
        }
        memset(cnt,0,sizeof(cnt)); memset(tree,0,sizeof(tree));
        for (int i=ff; i<n+m+1; i+=2){
            vector<pii> &lst=tb[i];
            sort(ALL(lst));
            REP(j,op[i].size()) update(op[i][j],1);
            res+=tree[1<<maxb];

            REP(j,lst.size()){
                int st=lst[j].ST, nd=lst[j].ND;

                while(j<lst.size() && lst[j].ST<=nd) nd=max(nd,lst[j].ND), ++j;
                res+=(nd-st)/2+1;
                res-=get(nd)-get(st-1);
                --j;
            }
            REP(j,cl[i].size()) update(cl[i][j],-1);
        }

    }

    cout<<res<<endl;

    return 0;
}

