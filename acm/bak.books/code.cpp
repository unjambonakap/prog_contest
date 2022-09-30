Cramer Rule:

A^-1=Adj(A)/det(A)

Adj(A)=Cofact(A)^(Transpose)
    Cofact((a b; c d))=(d -c; -b; d)


    Ax=b
xi=det(Ai)/det(A)
    Ai= A, replace ith column by b
    ++++++++++++++++++++++++
    MIS +MAXMATCH in bipartite = num of vertices

    +++++++++++++++++++ PRIMES
    9973 10007 19997 20011 39989 40009 49999
    50021 99991 100003 199999 200003 399989
    400009 499979 500009 999983 1000003
    1999993 2000003 3999971 4000037 4999999
    5000011 9999991 10000019 19999999
    20000003 39999983 40000003 49999991
    50000017 99999989 100000007 199999991
    200000033 399999959 400000009 499999993
    500000003 999999937 1000000007
    1999999973 2000000011 10240297597
    54193340731 90477650771 115499206703
    481778715169 1005680009767 5336435463727
    70139947146967 9876324585966499
    112272535095293 801258244502321
    2753565111483733 2452902601380727
    10818180001081819 98577541197976567
    79523954586701659 101210328665281103

    ++++++++++++++++++++++++++++++ CHINESE REMAINDERING +++++++++++++++++++
#include <stdio.h>
    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b,a%b);
    }
int solve(int k1,int m1,int k2,int m2) {
    int a,b,c = k2−k1;
    if (c%gcd(m1,m2)) return −1;
    for(a=b=0;a − b != c;) {
        a=(c+b+m1−1)/m1*m1;
        b=(a−c+m2−1)/m2*m2;
    }
    return (a+k1);
}
int main() {
    int k,m,k1,m1;
    k = 0; m = 1;
    while (2 == scanf("%d%d",&k1,&m1)) {
        k = solve(k,m,k1,m1);
        if (k == −1) {
            printf("No solution.\n");return 0;
        }
        m = m/gcd(m,m1)*m1;
    }
    printf("%d mod %d\n",k,m);
    return 0;
}

++++++ Dinic maxflow (V2*E)
    int px[maxN][maxN];

    int to[maxe], from[maxe], c[maxe], f[maxe], prev[maxe], last[maxn];
    int dist[maxn];
    int ne, n;
    int N;
    int par[maxn], vis[maxn];
    int q[maxn];

    void adde(int a, int b, int cx){
        from[ne]=a; to[ne]=b; c[ne]=cx; f[ne]=0; prev[ne]=last[a]; last[a]=ne++;
        swap(a,b); from[ne]=a; to[ne]=b; c[ne]=0; f[ne]=0; prev[ne]=last[a]; last[a]=ne++;
    }

int dfs(int a, int p=-1){
    par[a]=p;
    if (a==1) return 1;
    for (int i=last[a]; i!=-1; i=prev[i]) if (f[i]<c[i] && dist[to[i]]==dist[a]+1 && dfs(to[i],i)) return 1;
    return 0;
}

void bfs(){
    int qa=0, qe=0;
    dist[0]=0;
    q[qe++]=0;
    while(qa<qe){
        int a=q[qa++];
        for (int i=last[a]; i!=-1; i=prev[i]) if (f[i]<c[i] && dist[to[i]]>dist[a]+1) q[qe++]=to[i], dist[to[i]]=dist[a]+1;
    }
}

ll mf(){
    ll res=0;
    while(1){
        memset(par,-1,sizeof(par));
        memset(dist,0x7f,sizeof(dist));
        bfs();
        if (dist[1]>inf) break;
        while(dfs(0)){
            int p=1, x=inf;
            while(p!=0) x=min(x,c[par[p]]-f[par[p]]), p=from[par[p]];
            res+=x;
            p=1;
            while(p!=0) f[par[p]]+=x, f[par[p]^1]-=x, p=from[par[p]];
        }
    }

    return res;
}


+++++++++++++++ FFT

typedef complex<double> point;
typedef vector<point> vc;
const double pi=acos(-1.);

void fft(vc &a, vc &wl){
    int n=a.size();
    for (int i=2, l=1; i<=n; i<<=1, ++l){
        point w=wl[l];
        for (int j=0; j<n; j+=i){
            point pw=1;
            REP(k,i/2){
                point u=a[j+k], v=pw*a[j+k+i/2];
                a[j+k]=u+v;
                a[j+k+i/2]=u-v;
                pw*=w;
            }
        }
    }

}


vi go(vc a, vc b){

    int n=a.size();
    int bx=1;
    while(bx<n) bx<<=1;
    n=bx<<1;
    vi rev(n);
    int nb=0;
    while(1<<nb<n) ++nb;
    REP(i,n){
        int ni=0;
        REP(j,nb) if (i&two(j)) ni|=1<<nb-j-1;
        rev[i]=ni;
    }
    a.resize(n,0);
    b.resize(n,0);


    point w(cos(2*pi/n),sin(2*pi/n));
    vc wl(nb+1);
    wl[0]=w;
    REP(i,nb) wl[i+1]=wl[i]*wl[i];
    reverse(ALL(wl));

    vc x(n), y(n);
    REP(i,n) x[rev[i]]=a[i];
    REP(i,n) y[rev[i]]=b[i];
    fft(x,wl); fft(y,wl);



    REP(i,n) x[i]=x[i]*y[i];

    REP(i,nb+1) wl[i]=conj(wl[i]);

    vc res(n);
    REP(i,n) res[rev[i]]=x[i];
    fft(res,wl);

    vi ans(n);
    REP(i,n) ans[i]=res[i].real()/n+0.3;
    return ans;
}

+++++++++++++++++++++++++++++++++++++++++++++++++ SUFFIX ARRAY WITH COUNT SORT++++++++++++++++++++++++ 
const int maxb=20;
const int maxn=1<<maxb;
const int oo=1e9;
const int minv='a'-1;


int rmp[2*maxn], tmp[maxn];
int lcp[maxb][maxn];
int A[2*maxn];
int NB;
int X;
int n;
int V;
char buf[maxn];
char S[maxn];
int pos[maxn];
int F[maxn];

int nA[maxn];
int cnt[maxn];
int val[maxn];
int px[maxn];



int cmp(int a, int b){
    int u=rmp[a], v=rmp[b];
    if (u!=v) return u<v;
    u=X+a<n?rmp[a+X]:-oo;
    v=X+b<n?rmp[b+X]:-oo;
    return u<v;
}


void rsort(int *a, int n){
    memset(cnt,0,sizeof(int)*V);
    //REP(i,n) val[i]=(a[i]+X<n?1+rmp[a[i]+X]:0), ++cnt[val[i]];
    REP(i,n) val[i]=rmp[a[i]+X], ++cnt[val[i]];
    REP(i,V) cnt[i+1]+=cnt[i];
    for (int i=n-1; i>=0; --i) nA[--cnt[val[i]]]=a[i];

    memset(cnt,0,sizeof(int)*V);
    REP(i,n) val[i]=rmp[nA[i]], ++cnt[val[i]];
    REP(i,V) cnt[i+1]+=cnt[i];
    for (int i=n-1; i>=0; --i) a[--cnt[val[i]]]=nA[i];
}

void doit(int n){
    REP(i,n-1) S[i+n]=S[i];
    n+=n-1;
    px[0]=-1;
    int u=0;
    for (int i=1; i<n; ++i){
        while(u>=0 && S[u]!=S[i]) u=px[u];
        px[i+1]=++u;
    }
}

int can(int a, int na){ return px[a+na]<na; }

int go(int na, int &p){
    int l=0, r=0;
    char *s=S+na-1;
    for (; l<na && s[l]==buf[A[0]+l]; ++l);
    if (l==na || s[l]<buf[A[0]+l]){p=0; return l;}

    int T=0;
    for (int b=NB-1; b>=0; --b){
        int m=0, M=T+(1<<b);
        if (l>=r){
            if (lcp[b][T]<l) m=lcp[b][T];
            else for (m=l; m<na && s[m]==buf[A[M]+m]; ++m);
        }else{
            if (lcp[b][M]<r) m=lcp[b][M];
            else for (m=r; m<na && s[m]==buf[A[M]+m]; ++m);
        }
        if (m==na || s[m]<buf[A[M]+m]) r=m;
        else T=M, l=m;
    }

    if (r>=l) l=r, ++T;
    p=T;
    return l;
}

int main(){
    scanf(" %s", buf);
    int m; cin>>m;
    n=strlen(buf);
    int oldn=n;
    buf[n++]='a'-1;
    buf[n++]='z'+2;
    V=256;

    REP(i,n) rmp[i]=buf[i];

    for (int b=1; b<maxb+1; ++b){
        REP(i,n) A[i]=i;
        X=1<<(b-1);
        rsort(A,n);
        //sort(A,A+n,cmp);
        tmp[A[0]]=1;
        REP(i,n-1){
            tmp[A[i+1]]=tmp[A[i]];
            if (cmp(A[i],A[i+1])) ++tmp[A[i+1]];
        }
        V=tmp[A[n-1]]+2;
        memcpy(rmp,tmp,sizeof(tmp));
    }
    REP(i,n) --rmp[i];
    REP(i,n) F[i+1]=F[i]+(A[i]<oldn);

    int u=0;
    A[n]=n-1;
    for (NB=0; 1<<NB<n; ++NB);
    FOR(i,n,1<<NB) A[i]=n-1;

    REP(i,n-2){
        int j=A[rmp[i]+1];

        if (i==j){printf("-1 on %d %d xx %d\n",i,j,n); return 0;}

        for (; buf[i+u]==buf[j+u]; ++u);
        lcp[0][rmp[i]]=u;
        if (u) --u;
    }
    for (int i=1; i<maxb; ++i) REP(j,n) lcp[i][j]=min(lcp[i-1][j],(j+(1<<i-1)>=n-1?0:lcp[i-1][j+(1<<i-1)]));


    return 0;
    REP(step,m){
        scanf(" %s",S);
        int na=strlen(S);
        doit(na);
        int p,x; x=go(na,p);

        int res=0;
        for (int i=na-1; i>=0; --i){
            int st=p, nd=p;
            for (int b=maxb-1; b>=0; --b) if (lcp[b][nd]>=na) nd+=1<<b;
            for (int b=maxb-1; b>=0; --b) if (st-(1<<b)>=0 && lcp[b][st-(1<<b)]>=na) st-=1<<b;

            if (can(i,na) && x>=na) res+=F[nd+1]-F[st];

            if (i){
                int np=0;
                int T=0, H=n-1;
                while(T<=H){
                    int M=T+H>>1;
                    char sa=buf[A[M]], sb=S[i-1];
                    if (sa<sb || (sa==sb && rmp[A[M]+1]<=p)) np=M, T=M+1;
                    else H=M-1;
                }

                int bestx=-1, bestp=-1;
                FOR(pp,np,np+2){
                    if (pp==n || buf[A[pp]]!=S[i-1]) continue;
                    int aa=p, bb=rmp[A[pp]+1];
                    if (aa>bb) swap(aa,bb);

                    int uu=oo;
                    for (int b=maxb-1; b>=0; --b) if (aa+(1<<b)<=bb) uu=min(uu,lcp[b][aa]), aa+=1<<b;
                    int nx=1+min(uu,x);
                    if (nx>bestx) bestx=nx, bestp=pp;
                }
                if (bestp==-1) break;
                x=bestx, p=bestp;
            }

        }
        printf("%d\n",res);
    }
    return 0;
}


++++++++++++++++++++++ TREAP+ ++++++++++++++++

const int maxn=111111;

struct node{
    node():l(0),r(0),cnt(1),f(0){}
    node *l, *r;
    int v, cnt;
    int w; int f;
};

node nl[maxn];
int pos;


void norm(node *x){
    if (x->f){
        x->f=0, swap(x->l, x->r);
        if (x->l) x->l->f^=1;
        if (x->r) x->r->f^=1; 
    }
}
void disp(node *x){
    if (!x) return;
    norm(x);
    disp(x->l); printf("%d ", x->v+1); disp(x->r);
}

int count(node *x){return x?x->cnt:0;}

void split(node *p, node *&A, node *&B, int cnt){
    if (!p){A=B=0; return;}

    norm(p);
    if (cnt<=count(p->l)){
        node *u;
        split(p->l, A, u, cnt);
        p->l=u;
        B=p;
        p->cnt-=count(A);
    }else{
        node *u;
        split(p->r, u, B, cnt-count(p->l)-1);
        p->cnt-=count(B);
        p->r=u;
        A=p;
    }
}


node *merge(node *root, node *a){
    if (!root) return a;
    if (!a) return root;
    norm(root); norm(a);

    if (root->w>=a->w){
        root->cnt+=count(a);
        root->l=merge(root->l, a);
        return root;
    }else{
        a->cnt+=count(root);
        a->r=merge(root, a->r);
        return a;
    }
}



int main(){
    int n, m;
    cin>>n>>m;
    tr1::mt19937 prng;
    prng.seed(316);
    pos=0;
    node *root=nl;
    root->v=0;
    REP(i,n-1){
        node *a=nl+i+1;
        a->v=i+1;
        a->w=prng();
        root=merge(a, root);
    }
    REP(i, m){
        int a, b, c;
        scanf(" %d %d %d", &a, &b, &c);

        node *an, *bn;
        an=bn=0;
        split(root, an, root, a);
        split(root, bn, root, b);
        if (bn) bn->f^=1;

        root=merge(root, an);
        an=0;
        split(root, an, root, c);
        root=merge(root, bn);
        root=merge(root, an);
    }
    disp(root); printf("\n");
    return 0;
}

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KMP ++++++++++++++++++

p[0]=-1;
FOR(i,0,n){
    int px=p[i];
    while(px>=0 && ta[px]!=ta[i]) px=p[px];
    p[i+1]=px+1;
}


