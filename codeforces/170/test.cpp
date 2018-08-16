
++++++++ AHO CORASICK +++++++++++++++
const int maxn=1000001;
const int maxb=1<<22;

struct node{
    int next[26];
    int val, prev;
    node(){memset(next,-1,sizeof(next));prev=-1; val=0;}
} tb[maxn];

int na;
int n, k;
string w[111111];
int q[2*maxn];
int A[maxb];
int pos[2][maxn];
int wh;
int m;
int rmp[111111];
char on[111111];
vi e[maxn];


void build(int a){
    int p=0;
    REP(b,w[a].length()){
        node &x=tb[p];
        char c=w[a][b]-'a';
        if (tb[p].next[c]==-1) tb[p].next[c]=na++;
        p=tb[p].next[c];
    }
    rmp[a]=p; ++tb[p].val;
}

void bfs(){
    int qa=0, qb=0;
    q[qb++]=0;
    while(qa<qb){
        int x=q[qa++];
        REP(i,26){
            int b=tb[x].next[i];
            if (b==-1) continue;
            int pos=tb[x].prev;
            while(pos!=-1 && tb[pos].next[i]==-1) pos=tb[pos].prev;
            tb[b].prev=pos==-1?0:tb[pos].next[i];
            e[tb[b].prev].pb(b);
            q[qb++]=b;
        }
    }
}

void update(int x, int v){ assert(x);for (; x<maxb; x+=x&-x) A[x]+=v;}
int query(int x){int v=0; for (; x; x^=x&-x) v+=A[x]; return v;}
char buf[1111111];

void dfs(){
    int qa=0;
    q[qa++]=0;

    while(qa){
        int a=q[--qa];
        int f=a&1; a>>=1;
        if (f){ update(wh,-tb[a].val); pos[1][a]=wh++; continue;}
        update(wh,tb[a].val);
        pos[0][a]=wh++;
        q[qa++]=a<<1|1;
        REP(i,e[a].size()) q[qa++]=e[a][i]<<1;
    }
}


int dfsb(){
    int a=0;
    int res=0;
    FOR(b,1,m){
        res+=query(pos[0][a]);
        node &x=tb[a];
        char c=buf[b]-'a';
        if (x.next[c]!=-1){ a=x.next[c]; continue;}
        int p=x.prev;
        while(p!=-1 && tb[p].next[c]==-1) p=tb[p].prev;
        a=p==-1?0:tb[p].next[c];
    }
    return res+query(pos[0][a]);
}

int main(){
    cin>>n>>k;
    REP(i,k) cin>>w[i];
    na=1; REP(i,k) build(i);
    wh=1;

    bfs(); dfs();
    REP(i,k) on[i]=1;

    REP(i,n){
        scanf(" %s", buf);
        m=strlen(buf);
        if (buf[0]=='?') printf("%d\n", dfsb());
        else if (buf[0]=='+'){
            int x; sscanf(buf+1,"%d",&x); --x;
            if (on[x])continue;
            int a=rmp[x];
            update(pos[0][a],1); update(pos[1][a],-1);
            on[x]=1;
        }else{
            int x; sscanf(buf+1,"%d",&x); --x;
            if (!on[x]) continue;
            int a=rmp[x];
            update(pos[0][a],-1); update(pos[1][a],1);
            on[x]=0;
        }
    }
    return 0;
}


++++++++++++++++++ HEAVY LIGHT DECOMP


const int maxn=111111;
const int maxm=maxn*20;
vi e[maxn];
int n;
int vis[maxn], par[maxn];
int d[maxn];
int type[maxn];
vi cycle;
int A[maxn];
int skip[maxn];

int cyclePos[maxn];


struct segTree{
    int T, H;
    segTree *l,*r;
    int val, sw;
    void init(int T, int H);
    int getv(){return sw?H-T-val:val;}

    int query(int a, int b){
        if (b<=T || a>=H) return 0;

        if (T>=a && H<=b) return getv();
        if (sw){ val=H-T-val; sw=0; l->sw^=1, r->sw^=1; }
        return l->query(a,b)+r->query(a,b);
    }
    void update(int a, int b){
        assert(a<=b);
        if (b<=T || a>=H) return;
        if (T>=a && H<=b){sw^=1; return; }

        if (sw){ val=H-T-val; sw=0; l->sw^=1, r->sw^=1; }
        l->update(a,b);
        r->update(a,b);
        val=l->getv()+r->getv();
    }
};


segTree tbl[maxm];
int rmp[maxn];
int pos;


int getseg(){
    assert(pos<maxm);
    return pos++;
}

void segTree::init(int _T, int _H){
    l=r=0; val=0; sw=0;
    T=_T; H=_H;
    if (T+1==H) return;
    l=tbl+getseg(); r=tbl+getseg();
    int M=(T+H)/2;
    l->init(T,M);
    r->init(M,H);
}


int dfs(int a, int p){
    par[a]=p;
    if (vis[a]){cycle.pb(a); while(p!=a) cycle.pb(p), p=par[p]; cycle.pb(a); return 1;}
    vis[a]=1;
    REP(i,e[a].size()) if (e[a][i]!=p && dfs(e[a][i],a)) return 1;
    return 0;
}

void dfsb(int a, int p){
    A[a]=1;
    par[a]=p;
    d[a]=p==-1?0:d[p]+1;

    REP(i,e[a].size()){
        int b=e[a][i];
        if (b!=p){type[b]=type[a]; dfsb(b,a); A[a]+=A[b];}
    }
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b!=p) skip[b]=A[b]>(A[a]-1)/2?a:-2;
    }
}


void dfsc(int a, int c){
    if (c==-1) c=a;
    int fd=0;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b!=par[a]){
            if (skip[b]<0) dfsc(b,-1);
            else skip[b]=c, dfsc(b,c), fd=1;
        }
    }
    if (!fd && c!=a){
        rmp[c]=getseg();
        tbl[rmp[c]].init(d[c],d[a]);
    }
}
int query(int a, int b){
    int res=0;
    while(a!=b){
        if (skip[a]<0) res+=skip[a]+2, a=par[a];
        else{
            if (d[skip[a]]<d[b]) res+=tbl[rmp[skip[a]]].query(d[b],d[a]), a=b;
            else res+=tbl[rmp[skip[a]]].query(d[skip[a]], d[a]), a=skip[a];
        }
    }
    return res;
}
void update(int a, int b){
    while(a!=b){
        if (skip[a]<0) skip[a]=-3-skip[a], a=par[a];
        else{
            if (d[skip[a]]<d[b]) tbl[rmp[skip[a]]].update(d[b],d[a]), a=b;
            else tbl[rmp[skip[a]]].update(d[skip[a]], d[a]), a=skip[a];

        }
    }
}
int lca(int a, int b){
    int last=-1;
    while(a!=b){
        if (d[a]>d[b]) swap(a,b);
        if (skip[b]<0) b=par[b], last=-1;
        else last=a, b=skip[b];
    }
    if (last==-1) return a;
    return last;
}

int main(){
    int m;
    cin>>n>>m;
    REP(i,n){ int a, b; scanf("%d %d", &a,&b); --a; --b; e[a].pb(b); e[b].pb(a); }
    dfs(0,-1);
    memset(type,-1,sizeof(type));
    REP(i,cycle.size()-1){
        int a=cycle[i], b=cycle[i+1];
        type[a]=a;

        REP(i,e[a].size()) if (e[a][i]==b) swap(e[a][i], e[a].back()), e[a].pop_back();
        swap(a,b);
        REP(i,e[a].size()) if (e[a][i]==b) swap(e[a][i], e[a].back()), e[a].pop_back();
    }

    pos=0;
    int na=cycle.size()-1;
    REP(i,na) dfsb(cycle[i],-1), dfsc(cycle[i],-1), cyclePos[cycle[i]]=i;

    segTree &ctree=tbl[getseg()];

    ctree.init(0,na);
    int res=n;
    REP(q,m){
        int a, b; scanf("%d %d", &a,&b); --a; --b;
        if (type[a]==type[b]){
            int c=lca(a,b);
            res+=query(a,c)+query(b,c);


