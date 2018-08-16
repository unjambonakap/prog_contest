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


const int maxn=1e4;
const int maxs=1e5;

struct state{
    vector<pii> nxt;
    vi eps;
} tb[maxs];



char sa[maxn], sb[maxn];
int vis[maxn], vis2[maxn];
int WHEN;

int par[maxs], with[maxs];

char *s;
int na,nb;
int POS;

int n;
int P;
int NX,NY;
vi lst1, lst2;
int rmp1[maxs], rmp2[maxs];

void build(int aa, int bb);
void build2(int aa, int bb);

void build2(int aa, int bb){
    int x=-1, y=aa;
    while(1){
        if (P==n) break;
        char c=s[P];
        if (c=='|') break;

        if (c==')') break;
        ++P;
        if (c=='('){
            int nx=POS++, ny=POS++;
            tb[y].eps.pb(nx);
            build(nx,ny);
            x=nx; y=ny;
            ++P;
        }else if (islower(c)){
            int nx=POS++, ny=POS++;
            tb[y].eps.pb(nx);
            tb[nx].nxt.pb(MP(c-'a',ny));
            x=nx; y=ny;
        }else if (c=='*') tb[y].eps.pb(x), tb[x].eps.pb(y);
    }
    tb[y].eps.pb(bb);
}

void build(int aa, int bb){
    int xa, ya;
    while(1){
        xa=POS++; ya=POS++;
        build2(xa,ya);
        tb[aa].eps.pb(xa); tb[ya].eps.pb(bb);

        if (P==n) return;
        if (s[P]==')') return;
        assert(s[P]=='|');
        ++P;
    }

}

vi lst;

void dfs2(int a){
    if (vis2[a]==WHEN) return;
    vis2[a]=WHEN;
    lst.pb(a);
    REP(i,tb[a].eps.size()) dfs2(tb[a].eps[i]);
}

void dfs3(int a){
    if (vis2[a]==WHEN) return;
    vis2[a]=WHEN;
    lst.pb(a);
    REP(i,tb[a].nxt.size()) dfs3(tb[a].nxt[i].ND);
}


void dfs1(int a){
    if (vis[a]) return;
    vis[a]=1;

    lst.clear();
    ++WHEN;
    dfs2(a);
    REP(i,lst.size()) if (lst[i]!=a){
        vector<pii> &uu=tb[lst[i]].nxt;
        REP(j,uu.size()) tb[a].nxt.pb(uu[j]);
    }
    sort(ALL(tb[a].nxt));
    tb[a].nxt.resize(unique(ALL(tb[a].nxt))-tb[a].nxt.begin());
}

void bfs(int aa, int bb){
    queue<int> q;
    q.push(rmp1[aa]+rmp2[bb]*NX);
    par[q.front()]=-2;
    while(q.size()){
        int S=q.front();
        aa=lst1[q.front()%NX], bb=lst2[q.front()/NX]; q.pop();

        if (aa==3 && bb==3){
            puts("Wrong");
            S=par[S];
            string res;
            while(par[S]!=-2) res+=with[S]+'a', S=par[S];
            reverse(ALL(res));
            cout<<res<<endl;

            return;
        }

        REP(i,tb[aa].nxt.size()) REP(j,tb[bb].nxt.size()){
            pii &va=tb[aa].nxt[i], &vb=tb[bb].nxt[j];
            if (va.ST!=vb.ST) continue;
            if (va.ST==-1 && par[S]==-2) continue;
            int ca=rmp1[va.ND], cb=rmp2[vb.ND];

            int NS=ca+cb*NX;
            if (par[NS]!=-1) continue;
            par[NS]=S; with[NS]=va.ST;
            q.push(NS);
        }
    }
    puts("Correct");
}


int main(){
    freopen("disjoint.in","r",stdin);
    freopen("disjoint.out","w",stdout);
    scanf(" %s",sa); scanf(" %s",sb);
    na=strlen(sa); nb=strlen(sb);

    tb[2].nxt.pb(MP(-1,3));
    POS=4;

    s=sa; n=na; 
    build(0,2);

    P=0;
    s=sb; n=nb;
    build(1,2); 

    REP(i,POS) dfs1(i);
    memset(par,-1,sizeof(par));

    memset(rmp1,-1,sizeof(rmp1));
    memset(rmp2,-1,sizeof(rmp2));

    lst.clear();++WHEN;
    dfs3(0); NX=lst.size();
    REP(i,NX) rmp1[lst[i]]=i;
    lst1=lst;

    lst.clear();++WHEN;

    dfs3(1); NY=lst.size();
    REP(i,NY) rmp2[lst[i]]=i;
    lst2=lst;



    //REP(_i,NX){int i=lst1[_i]; REP(j,tb[i].nxt.size()) printf("%d >> %d %d\n",i,tb[i].nxt[j].ST,tb[i].nxt[j].ND);}
    assert(NX*NY<=maxs);

    bfs(0,1);
    return 0;
}

