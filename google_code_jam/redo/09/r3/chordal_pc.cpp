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

const int maxn=1100;
const int maxr=34;
int n;
set<int> mp[maxr];
map<pii, int> rmp;
int x[maxn], y[maxn];
int graph[maxn][maxn];
vi adj[maxn];

struct nodea{
    struct node *parent;
    int f, a;
    nodea *next, *prev;
    nodea(node *p);
    void sent();
    int empty();
    ~nodea();
    nodea *add(int v);
    void remove();
};

struct node{
    int f;
    node *next, *prev;
    struct nodea *a;
    int cid;

    node();
    node *add(node *b);
    void sent();

    void remove();
    ~node();


    int empty();

};
nodea *posa[maxn];



node::node(){f=0; next=prev=0; a=0; cid=-1;}
node::~node(){remove();}
node *node::add(node *b){
    node *tmp=next;
    next->prev=b;
    next=b;
    b->prev=this;
    b->next=tmp;
    return b;
}

void node::sent(){
    f=1;
    next=prev=this;
}

void node::remove(){
    prev->next=next;
    next->prev=prev;
}

int node::empty(){return f && next->f; }

nodea::nodea(node *p){f=0; parent=p; prev=next=0; a=-1;}
nodea::~nodea(){remove();}
void nodea::sent(){
    f=1;
    next=prev=this;
}
int nodea::empty(){return f && next->f; }
nodea *nodea::add(int v){
    nodea *b=new nodea(parent);
    b->a=v;

    nodea *tmp=next;
    next->prev=b;
    next=b;
    b->prev=this;
    b->next=tmp;
    return b;
}
void nodea::remove(){
    if (f){
        delete parent;
        return;
    }
    prev->next=next;
    next->prev=prev;
    if (next->empty()) delete next;
}


int col(){
    int visited[maxn];
    memset(visited, 0, sizeof(visited));
    node r;

    r.sent();
    node *a=r.add(new node());
    a->a=new nodea(a);
    a->a->sent();
    REP(i, n) posa[i]=a->a->add(i);

    vi order;

    REP(i, n){
        node *a=r.next;
        assert(!a->f);
        assert(!a->a->empty());
        int e=a->a->next->a;
        order.pb(e);
        visited[e]=1;
        delete posa[e];


        FE(it, adj[e]) if (!visited[*it]){
            nodea *b=posa[*it];
            node *p=b->parent;
            if (p->cid==i){
                posa[*it]=p->prev->a->add(*it);
                delete b;
            }else{
                p->cid=i;
                node *c=p->prev->add(new node());
                c->a=new nodea(c); c->a->sent();

                posa[*it]=c->a->add(*it);
                delete b;
            }
        }

    }
    reverse(ALL(order));
    int deg[n];
    REP(i, n) deg[i]=adj[i].size();
    int c=0;
    REP(i, n){
        checkmax(c, deg[order[i]]+1);
        FE(it, adj[order[i]]) --deg[*it];
    }
    memset(visited, 0, sizeof(visited));
    REP(i, n) out(graph[i], n);
    out(order, n);
    REP(i, n){
        int a=order[i];
        visited[a]=1;
        int na=adj[a].size();
        printf("checking %d\n", a);
        printf("%d\n", na);
        REP(j, na) REP(k, na) if (!visited[adj[a][j]] && !visited[adj[a][k]] && j!=k) assert(graph[adj[a][j]][adj[a][k]]);

    }
    return c;



}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        REP(i, maxr) mp[i].clear();
        rmp.clear();
        REP(i, n){
            cin>>x[i]>>y[i];
            --y[i]; --x[i];
            rmp[MP(x[i], y[i])]=i;
            mp[y[i]].insert(x[i]);
        }

        memset(graph, 0, sizeof(graph));
        REP(i, n){
            if (mp[y[i]].lower_bound(x[i]+1)!=mp[y[i]].end()){
                int j=rmp[MP(*mp[y[i]].lower_bound(x[i]+1), y[i])];;
                graph[i][j]=graph[j][i]=1;
            }
            if (y[i]>0 && mp[y[i]-1].lower_bound(x[i]+1)!=mp[y[i]-1].end()){
                int j=rmp[MP(*mp[y[i]-1].lower_bound(x[i]+1), y[i]-1)];
                graph[i][j]=graph[j][i]=1;
            }
            if (y[i]<maxr-1 && mp[y[i]+1].lower_bound(x[i]+1)!=mp[y[i]+1].end()){
                int j=rmp[MP(*mp[y[i]+1].lower_bound(x[i]+1), y[i]+1)];
                graph[i][j]=graph[j][i]=1;
            }
        }
        REP(i, n) adj[i].clear();
        REP(i, n) REP(j, n) if (graph[i][j]) adj[i].pb(j);
        int res=col();

        printf("Case #%d: %d\n", ti, res);

    }
    return 0;

}




