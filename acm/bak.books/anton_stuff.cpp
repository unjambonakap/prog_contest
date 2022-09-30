========    Java Template   ===========

public class Main
{
    BufferedReader reader;
    public Main() {
        reader = new BufferedReader(new FileReader(“gold.in”));
        int n = Integer.parseInt( reader.readLine() );
    }
    public static void main(String[] args) throws Exception {
        new Main();
    }
}


======== Directed MST  ================

int n,m,_x,_y,c;
vector<pii> v[511],w[511];
int nm;
bool u[511];

pii getM(int node){
    pii res(-1,INF);
    REP(i,w[node].size()) if(w[node][i].second<res.second)
        res=w[node][i];
    return res;
}

bool p[511];
bool D[511];
pii d[511];
int N[511];

int go(){
    int cost=0;
    FOR(i,1,n) if(!p[i]) d[i]=getM(i),cost+=d[i].second,p[i]=true;
    CL(u,false);
    vector<vi > cycle;
    FOR(i,1,n) if(!D[i] && !u[i]){
        int V=i;
        vi c;
        do{
            c.pb(V);
            u[V]=true;
            V=d[V].first;
        }while(!u[V]);
        while(c.size() && c[0]!=V)
            c.erase(c.begin());
        if(c.size()>1)
            cycle.pb(c);
    }
    if(cycle.size()){
        CL(N,-1);
        REP(i,cycle.size()) REP(j,cycle[i].size())
            N[cycle[i][j]]=i,D[cycle[i][j]]=true;
        FOR(i,1,n){
            if(N[d[i].first]!=-1) d[i].first=n+N[d[i].first];
            REP(j,w[i].size()){
                if(N[w[i][j].first]!=-1) w[i][j].first=n+N[w[i][j].first];
                if(N[i]!=-1){
                    w[i][j].second-=d[i].second;
                    if(w[i][j].first!=n+N[i])
                        w[n+N[i]].pb(w[i][j]);
                }
            }
            if(N[i]!=-1) w[i].clear();
        }
        n+=cycle.size();
        return cost+go();
    }
    return cost;
}

void dfs(int q){
    if(u[q]) return;
    u[q]=true;nm++;
    REP(i,v[q].size()) dfs(v[q][i].first);
}

Test code:
int main() {
    while(cin>>n>>m,n||m){
        REP(i,500) v[i].clear(),w[i].clear();
        REP(i,m) {
            scanf("%d %d %d",&_x,&_y,&c);
            _x--,_y--;
            v[_x].pb(pii(_y,c));
            w[_y].pb(pii(_x,c));
        }
        CL(u,false);
        CL(p,false);
        CL(D,false);
        nm=0;
        if(dfs(0),nm!=n)
            puts("impossible");
        else cout<<go()<<endl;
    }
    return 0;
}


========= Z-Algo ===========

vi ZAlgo(string vec) {
    int N = vec.sz;
    vi Z(N);
    int L = 0, R = 0;
    FOR(i, 1, N) {
        if (i <= R)
            Z[i] = min(Z[i-L], R-i+1);
        while ((i + Z[i] < N) && (vec[i+Z[i]] == vec[Z[i]]))
            Z[i]++;
        if (R < i + Z[i] - 1) {
            L = i;
            R = i + Z[i] - 1;
        };
    }
    return Z;
}


============ Extended Euclid ===============

template <typename T> void extGCD(T a, T b, T &x, T &y)
{
    if (!b) {
        x = 1;
        y = 0;
        return;
    }
    T x1, y1;
    extGCD(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a/b)*y1;
}

Note: in oder to avoid overflow
x = y1
y = x1 - (a/b)*y1;
int d = x/b;
x -= d*b;
y += d*a;




===========        Simplex-Method ==================

const double eps = 1e-3;
const double SM_INF = 1e6; // objective function coefficient for artificial variables
typedef vector<double> vd;
struct SimplexM{
    int startN, N;
    vd old_c,c,b,res;
    vector<vd> system;
    double value;
    SimplexM(vd c):N(c.size()),c(c){ } // objective function (minimize)
    void add(vd r,double v,int sgn=0){ // v >= 0
        for(;c.size()<r.size();c.pb(0));
        for(;r.size()<c.size();r.pb(0));
        if(sgn)r.pb(-sgn),c.pb(0);
        system.pb(r),b.pb(v);
    }
    void refresh_c_func(int pos,int row){
        double begin=c[pos];
        REP(i,N) c[i]-=begin*system[row][i];
    }
    void gauss(int row,int col){
        double v=system[row][col];
        REP(i,N) system[row][i]/=v;
        b[row]/=v;
        REP(i,system.size()) if(i!=row){
            v=system[i][col];
            REP(j,N) system[i][j]-=v*system[row][j];
            b[i]-=v*b[row];
        }
    }
    // -2 - NO SOLUTION
    // -1 - minimum is infinity (minimum does not exists)
    // 1 - OK
    int solve(){
        N=c.size(),old_c=c;
        int m=system.size();
        REP(i,m)system[i].resize(N);
        startN=N;
        vi base(m,-1);
        REP(i,N){
            int nm=0,pos=-1;
            REP(j,m) if(fabs(system[j][i])>eps) nm++,pos=j;
            if(nm==1 && fabs(system[pos][i]-1)<eps && base[pos]==-1)
                base[pos]=i;
        }
        REP(i,m) if(base[i]==-1){
            N++;
            c.pb(SM_INF);
            REP(j,m) system[j].pb(j==i?1:0);
            base[i]=N-1;
        }
        REP(i,m) refresh_c_func(base[i],i);
        while(1){
            int pos=-1,row=-1;
            REP(i,N) if(c[i]<-eps && (pos==-1 || c[i]<c[pos])) pos=i;
            if(pos==-1) break;
            double min_teta=0;
            REP(i,m)
                if(system[i][pos]>eps &&
                        (row==-1 || min_teta>b[i]/system[i][pos]))
                    row=i,min_teta=b[i]/system[i][pos];
            if(row==-1) return -1;
            base[row]=pos;
            gauss(row,pos);
            refresh_c_func(pos,row);
        }
        REP(i,m) if(base[i]>=startN && fabs(b[i])>eps) return -2;
        res.resize(startN,0);
        REP(i,m) if(base[i]<startN) res[base[i]]=b[i];
        value=0;
        REP(i,startN) value+=res[i]*old_c[i];
        return 1;
    }
};


======= Restore the number given its reminders ========

// Requires the following operations over "bi":
// 1) bi + bi 2) bi * int 3) bi % int
bi restore(vi primes,vi mods){
    bi res=0,p=1;
    REP(i,primes.size()){
        ll temp=(mods[i]-(res%primes[i])+primes[i])%primes[i];
        temp=(temp*inv(p%primes[i],primes[i]))%primes[i];
        res=res+p*temp;
        p=p*primes[i];
    }
    return res;
}


============= FFT ============

typedef complex<double> cd;
cd W[1<<18];
template<class S>void fft(S p,cd*y,int n,int k=1){
    if(n>1){ cd q;
        fft(p,y,n/=2,k*2),fft(p+k,y+n,n,k*2);
        for(int i=0,j=0;i<n;++i,j+=k)
            y[i+n]=y[i]-(q=y[i+n]*W[j]),y[i]+=q;
    }else *y=*p;
}
vi mul(vector<int> a,vector<int> b){
    int n=a.size()+b.size();
    for(;n&n-1;++n);
    a.resize(n),b.resize(n);
    vector<cd> Y(n),Z(n);
    REP(i,n)W[i]=polar(1.,2*i*M_PI/n);
    fft(&a[0],&Y[0],n),fft(&b[0],&Z[0],n);
    REP(i,n)Z[i]*=Y[i],W[i]=cd(real(W[i]),-imag(W[i]));
    fft(&Z[0],&Y[0],n);
    REP(i,n)a[i]=(real(Y[i])+0.5)/n;
    for(;a.size() && !a.back();a.erase(a.end()-1));
    return a;
}



============ Splay tree =====================

template<class T,void F(T&,const T&,const T&)>struct splay_tree{
    vector<T> a;
    vi l,r,p,q;
    vector<char> rev;
    int root,n;
    splay_tree(const vector<T>&a):a(a){
        n=a.size(),l=r=p=vi(n),q=vi(n,1),q[0]=0;
        rev.resize(n),root=build(1,--n);
    }
    void change(int x){ if(x)q[x]=1+q[l[x]]+q[r[x]],F(a[x],a[l[x]],a[r[x]]); }
    void upd(int x){
        if(x && rev[x])
            swap(l[x],r[x]),rev[x]=0,
                rev[l[x]]^=1,rev[r[x]]^=1;
    }
    int build(int i,int j){
        int x=i>j?0:i+j>>1;
        if(i<j)p[l[x]=build(i,x-1)]=p[r[x]=build(x+1,j)]=x;
        return change(x),x;
    }
    void pop(int x){
        if(!x) return;
        bool sw=false;
        for(int y;y=p[x];){
            if(upd(x),x!=l[y])sw^=1,l.swap(r);
            (l[p[x]=p[y]]==y?l:r)[p[y]]=x;
            change(p[l[y]=r[x]]=y);
            change(p[r[x]=y]=x);
        }
        root=x; if(sw)l.swap(r);
    }
    int find(int k){
        if(k<0 || k>=n) return 0;
        for(int x=root,y;;)
            if(upd(x),k<q[y=l[x]])x=y;
            else if((k-=q[y]+1)<0) return x;
            else x=r[x];
    }
    void rv(int i,int j,int x){
        if(i<1 && j+2>q[x]) rev[x]^=1; else
            if(j>=0 && i<q[x])upd(x),rv(i,j,l[x]),rv(i-q[l[x]]-1,j-q[l[x]]-1,r[x]);
    }
    T sum(int i,int j,int x){
        if(i<1 && j+2>q[x]) return a[x];
        int z=q[upd(x),l[x]];
        T res=a[i<=z && z<=j?x:0];
        if(j>=0 && i<q[x])F(res,sum(i,j,l[x]),sum(i-z-1,j-z-1,r[x]));
        return res;
    }
    void change(int x,const T&v){ if(x=find(x))for(a[x]=v;x;change(x),x=p[x]); }
    const T& operator[](int i){ return a[find(i)]; }
    T operator()(int i,int j){ return sum(i,j,root); }
    void reverse(int i,int j){ pop(find(i-1)),pop(find(j+1)),rv(i,j,root); }
};


========== Assignment ============

#define C(i,j) (A[i][j]-pr[i]-pc[j])
int A[N][N],pr[N],pc[N],f[N];
bool b[N],bx[N],by[N];
bool dfs(int x){
    bx[x]=true;
    REP(y,n)if(!C(x,y) && (by[y]=true,f[y]<0 || !bx[f[y]] && dfs(f[y])))
        return f[y]=x,true;
    return false;
}
int assignment(){
    for(CL(pr,0),CL(pc,0);CL(f,-1);){
        REP(i,n)CL(bx,0),b[i]=dfs(i);
        CL(bx,0),CL(by,0);
        REP(i,n)if(!b[i])dfs(i);
        int p=-1u/2;
        REP(i,n)REP(j,n)if(bx[i] && !by[j])p=min(p,C(i,j));
        if(p==-1u/2) return accumulate(pr,pr+n,accumulate(pc,pc+n,0));
        REP(i,n)pr[i]+=bx[i]?p:0,pc[i]-=by[i]?p:0;
    }
}

========== Suffix Array ============

int n,f[N],p[N],q[N],L[N+N];
bool b[N];
int lcp(int i,int j){
    if(i>j)swap(i,j);
    int res=n;
    for(i+=n,j+=n-1;i<=j;i=i+1>>1,j=j-1>>1)
        res=min(res,min(L[i],L[j]));
    return res;
}
void setlcp(int i,int v){ for(i+=n;L[i]>v;i/=2)L[i]=v; }
bool scmp(int x,int y){ return f[x]<f[y]; }
void suff_sort(){
    REP(i,n)b[i]=0,p[i]=i; b[n]=true;
    for(int i,j,x,h=0;h<n;){
        for(i=j=0;j<=n;++j)if(b[j])sort(p+i,p+j,scmp),i=j;
        for(i=0,j=1;j<n;++i,++j)b[j]|=f[p[i]]!=f[p[j]];
        for(h=h?h*2:1,i=x=0;i<n;f[j]=x+=b[i++])if((j=p[i]-h)<0)j+=n;
    }
}
void suff_sort_withlcp(){
    REP(i,n)b[i]=0,p[i]=i,L[i+1]=L[i+n]=n; b[n]=true;
    for(int i,j,x,y,h=0;h<n;){
        for(i=j=0;j<=n;++j)if(b[j])sort(p+i,p+j,scmp),i=j;
        REP(i,n)q[p[i]]=i;
        for(i=0,j=1;j<n;++i,++j)
            if(!b[j] && f[p[i]]!=f[p[j]])
                b[j]=true,x=p[i]+h,y=p[j]+h,
                    setlcp(i,h?h+lcp(q[x<n?x:x-n],q[y<n?y:y-n]):0);
        for(h=h?h*2:1,i=x=0;i<n;f[j]=x+=b[i++])if((j=p[i]-h)<0)j+=n;
    }
}

======== Min cyclic shift ==============

int min_cyclic_shift(char*s){
    for(int n=strlen(s),i=0,j,k,r;;){
        for(k=i,j=i+1;s[k<n?k:k-n]<=s[j<n?j:j-n];++j)
            s[k<n?k:k-n]<s[j<n?j:j-n]?k=i:++k;
        for(r=i;i<=k;i+=j-k);
        if(i>=n) return r;
    }
}

========== Min suffix ==============

int min_suffix(char*s){
    for(int i=0,j,k,r;;){
        for(k=i,j=i+1;s[k]<=s[j];s[k]<s[j++]?k=i:++k);
        for(;i<=k;i+=j-k)r=i;
        if(!s[i]) return r;
    }
}

=========== Max flow ==============
template<int N>struct net{
    int a[N][N],p[N],q[N],z[N],f[N],g[N];
    bool b[N];
    int flow(int s,int t,int n){
        for(int x,h,res=0;memset(p,0,N*21);){
            queue<int> Q;
            for(z[s]=1,Q.push(s);Q.size() && (x=Q.front())!=t;Q.pop())
                REP(y,n)if(a[x][y] && !z[y])z[y]=z[x]+1,Q.push(y);
            if(!z[t]) return res;
            REP(i,n)REP(j,n)if(i!=t && j!=s && z[i]+1==z[j])
                p[i]+=a[i][j],q[j]+=a[i][j];
            for(q[s]=-1u/2,p[t]=-1u/2;;){
                REP(i,n)if(!b[i] && !(p[i]&&q[i]))b[i]=true,Q.push(i);
                for(;Q.size();){
                    x=Q.front(),Q.pop();
                    if(b[x])REP(y,n)if(!b[y]){
                        if(z[x]+1==z[y])q[y]-=a[x][y];
                        else if(z[y]+1==z[x])p[y]-=a[y][x];
                        if(!p[y]||!q[y])b[y]=true,Q.push(y);
                    }
                }
                if(b[s])break; int d=-1u/2;
                REP(i,n)if(!b[i] && (p[i]<d || q[i]<d))d=min(p[x=i],q[i]);
                for(res+=(f[x]=g[x]=d),Q.push(x);Q.size();){
                    x=Q.front(),Q.pop();
                    for(int y=0;y<n;++y)if(!b[y])
                        if(z[x]+1==z[y] && (d=min(a[x][y],f[x]))){
                            if(!f[y])Q.push(y);
                            p[x]-=d,a[x][y]-=d,q[y]-=d;
                            f[y]+=d,a[y][x]+=d,f[x]-=d;
                        }else if(z[y]+1==z[x] && (d=min(a[y][x],g[x]))){
                            if(!g[y])Q.push(y);
                            p[y]-=d,a[y][x]-=d,q[x]-=d;
                            g[x]-=d,a[x][y]+=d,g[y]+=d;
                        }
                }
            }
        }
    }
};

============= Min cost max flow ================
struct mcnet {
    vector< vector< pair<int,pii> > > a;
    vector< pair<int,pii> >::iterator i;
    mcnet(int n):a(n){}
    void add(int x,int y,int w,int c=1){
        for(i=a[x].begin();i!=a[x].end();++i)
            if(i->first==y && i->second.second==w){
                if(!(i->second.first+=c))
                    *i=a[x].back(),a[x].pop_back();
                return;
            }
        a[x].pb(make_pair(y,pii(c,w)));
    }
    pii flow(int s,int t){
        vi p(a.size());
        for(pii res;;){
            priority_queue<pii> Q;
            vi f(a.size(),-1u/2),prev(a.size(),-1);
            f[s]=0,Q.push(pii(0,s));
            for(int x,d;Q.size();){
                pii cur=Q.top(); Q.pop();
                if(f[x=cur.second]!=(d=-cur.first))continue;
                for(i=a[x].begin();i!=a[x].end();++i){
                    int y=i->first,z=i->second.second;
                    if(d+z+p[x]-p[y]<f[y])
                        f[y]=d+z+p[x]-p[y],prev[y]=x,
                            Q.push(pii(-f[y],y));
                }
            }
            if(prev[t]<0) return res;
            int flow=-1u/2;
            for(int x,y=t;~(x=prev[y]);y=x)
                for(i=a[x].begin();i!=a[x].end();++i)
                    if(i->first==y && f[x]+i->second.second+p[x]==f[y]+p[y])
                        flow=min(flow,i->second.first);
            res.first+=flow,res.second+=(f[t]+p[t]-p[s])*flow;
            for(int x,y=t;~(x=prev[y]);y=x)
                add(x,y,f[y]+p[y]-f[x]-p[x],-flow),
                    add(y,x,f[x]+p[x]-f[y]-p[y],+flow);
            REP(i,a.size())p[i]+=f[i];
        }
    }
};


==================  General max matching =======================
struct gmm {
    int n; vi X,Y,q,f,v,h;
    vector<vi> a;
    gmm(int n):n(++n),a(n,vi(n)),f(n),h(n){}
    void add(int x,int y){ a[x][y]=a[y][x]=X.size()+n,X.pb(x),Y.pb(y); }
    void lsub(int x,int e,int r)
    { for(;x!=r;x=h[v[f[x]]])v[x]=e,h[x]=r,q.pb(x); }
    void rematch(int x,int y){
        int z=f[x]; f[x]=y;
        if(f[z]!=x) return;
        if(v[x]<n) rematch(f[z]=v[x],z);
        else z=v[x]-n,rematch(X[z],Y[z]),rematch(Y[z],X[z]);
    }
    void dolabel(int x,int y){
        int r=h[x],s=h[y],e=a[x][y];
        if(r==s) return;
        v[s]=-e;
        do if(v[r]=-e,s)swap(s,r);
        while(v[r=h[v[f[r]]]]+e);
        lsub(h[x],e,r),lsub(h[y],e,r);
        REP(i,q.size())if(v[h[q[i]]]>0)h[q[i]]=r;
    }
    vector<pii> solve(){
        FOR(i,1,n)if(!f[i]){
            v=vi(n,-1),q=vi(1,i),v[i]=0;
            REP(j,q.size())
                for(int x=q[j],y=1;y<n;++y)if(a[x][y]){
                    if(!f[y] && y!=i)rematch(f[y]=x,y),j=y=n;
                    else if(v[y]>=0)dolabel(x,y);
                    else if(v[f[y]]<0)v[f[y]]=x,h[f[y]]=y,q.pb(f[y]);
                }
        }
        vector<pii> res;
        FOR(i,1,n)if(f[i]>i)res.pb(pii(i,f[i]));
        return res;
    }
};


======= 2-connected components ===========

vi v[111111];
int p[111111];
int b[111111];
int u[111111];
int now,cnt;
vi c;

int dfs(int ver,int par=-1){
    c.pb(ver);
    u[ver] = now;
    p[ver] = ++cnt;
    int val = cnt;
    REP(i,v[ver].size()){
        int nv = v[ver][i];
        if(nv==par) continue;
        c.pb(ver);
        if(u[nv]==now) val = min(val, p[nv]);
        else{
            int t = dfs(nv, ver);
            val = min(val, t);
            if(t>=p[ver]){
                vi z;
                while(c.size() && c.back()!=ver) z.pb(c.back()),c.pop_back();
                z.pb(ver);
                UN(z);

                ADD_COMPONENT(z);
            }
        }
    }
    return b[ver]=val;
}

============================== MFMC

const int maxn=2*1111;
const int maxk=55;
const int maxe=maxn*maxn;

int to[maxe], from[maxe], u[maxe], f[maxe], last[maxn], prev[maxe];
int c[maxe];
int P[maxn];
int d[maxn];
int par[maxn];
int vis[maxn];

int ne;
int n;
int cnt;
const int inf=1e9;

int adde(int a, int b, int _u, int _c){
    int x=ne; 
    to[ne]=b; from[ne]=a; u[ne]=_u; f[ne]=0; c[ne]=_c;prev[ne]=last[a]; last[a]=ne++;
    to[ne]=a; from[ne]=b; u[ne]=0; f[ne]=0; c[ne]=-_c; prev[ne]=last[b]; last[b]=ne++;
    return x;
}

void init(){
    memset(P,0x7f,sizeof(P));
    P[0]=0;

    priority_queue<pii,vector<pii>, greater<pii> > q;
    q.push(make_pair(0,0));
    while (!q.empty())
    {
        int v=q.top().second;
        if (q.top().first!=P[v])
        {
            q.pop();
            continue;
        }
        q.pop();
        for (int w=last[v];w>=0;w=prev[w])
        {
            if (f[w]<u[w] && P[v]+c[w]<P[to[w]])
            {
                P[to[w]]=P[v]+c[w];
                q.push(make_pair(P[to[w]],to[w]));
            }
        }
    }

}

int augment(){
    REP(i,n) d[i]=1e9;
    d[0]=0;
    par[0]=-1;
    priority_queue<pii,vector<pii>, greater<pii> > q;
    q.push(MP(0,0));
    memset(vis,0,sizeof(vis));
    while(!q.empty()){
        int dx=q.top().ST;
        int p=q.top().ND;
        q.pop();
        if (vis[p]) continue;
        vis[p]=1;

        for (int i=last[p]; i!=-1; i=prev[i]) if (u[i]>f[i] && !vis[to[i]]){
            int nd=dx+c[i]+P[p]-P[to[i]];
            //printf("EDGE %d %d >> %d\n", from[i], to[i], nd);
            //assert(c[i]+P[p]-P[to[i]]>=0.);
            if (d[to[i]]>nd) d[to[i]]=nd, par[to[i]]=i, q.push(MP(nd,to[i]));
        }
    }
    if (!vis[1]) return 0;
    REP(i,n) P[i]+=d[i];

    int x=par[1];
    while(x!=-1){ ++f[x]; --f[x^1]; x=par[from[x]]; }
    return P[1]-P[0];
}


