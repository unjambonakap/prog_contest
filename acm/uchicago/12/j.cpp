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

const int maxn=1111;

struct edge{
    int rev;
    int a, b;
    edge(){}
    edge(int a, int b, int rev):a(a),b(b),rev(rev){}
};


typedef list<edge>::iterator ITE;
vector<ITE> revl;

struct face{
    int a, b, c;
    int id;
    face(int a, int b, int c, int id):a(a),b(b),c(c),id(id){}
    int getother(int u, int v){
        int fa=(u==a||v==a);
        int fb=(u==b||v==b);
        int fc=(u==c||v==c);
        return fa?fb?c:b:a;
    }

};
int x[maxn], y[maxn], z[maxn];
int n;
int id[maxn];
int vis[maxn];
vector<list<edge>* > ea, eb;
list<face> fl;
vector<list<face>::iterator > rmp;
vi U;
int step, step2;
int idf;

int faces[maxn][maxn][2];


void pba(){ ea.pb(new list<edge>); }
void pbb(){ eb.pb(new list<edge>); }
void cla(){FE(it,ea) delete *it; ea.clear();}
void clb(){FE(it,eb) delete *it; eb.clear();}



int getf(int a, int b, int id){ assert(faces[a][b][0]==id||faces[a][b][1]==id);return faces[a][b][0]==id?0:1;}
void _addface(int a, int b, int id){
    if (faces[a][b][0]==-1) faces[a][b][0]=id;
    else{
        assert(faces[a][b][1]==-1);
        faces[a][b][1]=id;
    }
}

void addface(int a, int b, int c, int id){
    _addface(a,b,id); _addface(b,a,id);
    _addface(a,c,id); _addface(c,a,id);
    _addface(b,c,id); _addface(c,b,id);
}
void _remface(int a, int b, int id){assert(faces[a][b][0]==id||faces[a][b][1]==id);faces[a][b][getf(a,b,id)]=-1;assert(faces[a][b][0]==-1||faces[a][b][1]==-1);}


void remface(int a, int b, int c, int id){
    _remface(a,b,id); _remface(b,a,id);
    _remface(a,c,id); _remface(c,a,id);
    _remface(b,c,id); _remface(c,b,id);
}


void adde(int a, int b){//a face, b vertex

    //assert(ea[a]->empty() || ea[a]->begin()==revl[revl[ea[a]->begin()->rev]->rev]);
    //assert(eb[b]->empty() || eb[b]->begin()==revl[revl[eb[b]->begin()->rev]->rev]);
    //assert(eb[b].begin()==eb[b].begin()->rev->rev);
    ea[a]->pb(edge(a,b,revl.size()));
    eb[b]->pb(edge(b,a,revl.size()+1));
    revl.pb(--eb[b]->end()); revl.pb(--ea[a]->end());
    //assert(ea[a]->empty() || ea[a]->begin()==revl[revl[ea[a]->begin()->rev]->rev]);
    //assert(eb[b]->empty() || eb[b]->begin()==revl[revl[eb[b]->begin()->rev]->rev]);
}


void crossp(double xa, double ya, double za, double xb, double yb, double zb, double &xc, double &yc, double &zc){ xc=ya*zb-za*yb; yc=-xa*zb+xb*za; zc=xa*yb-xb*ya; }
double scalarp(double xa, double ya, double za, double xb, double yb, double zb){return xa*xb+ya*yb+za*zb;}
int sgn(double a){return a>=0?1:-1;}
int dir(int a, int b, int c, int d){
    double xu, yu, zu; crossp(x[b]-x[a],y[b]-y[a],z[b]-z[a], x[c]-x[a],y[c]-y[a],z[c]-z[a], xu,yu,zu);
    return sgn(scalarp(x[d]-x[a],y[d]-y[a],z[d]-z[a],xu,yu,zu));
}


void disp(int i){printf("POINT: %d %d %d\n", x[i],y[i],z[i]);}


double go(double xo, double yo, double zo, face &f){
    double xa,xb,xc,ya,yb,yc,za,zb,zc;
    xa=x[f.b]-x[f.a]; ya=y[f.b]-y[f.a]; za=z[f.b]-z[f.a];
    xb=x[f.c]-x[f.a]; yb=y[f.c]-y[f.a]; zb=z[f.c]-z[f.a];
    crossp(xa,ya,za,xb,yb,zb,xc,yc,zc);
    double D=xc*xc+yc*yc+zc*zc; D=sqrt(D);
    xc/=D; yc/=D; zc/=D;
    double M[3][4];
    M[0][0]=xa; M[0][1]=xb; M[0][2]=xc; M[0][3]=xo-x[f.a];
    M[1][0]=ya; M[1][1]=yb; M[1][2]=yc; M[1][3]=yo-y[f.a];
    M[2][0]=za; M[2][1]=zb; M[2][2]=zc; M[2][3]=zo-z[f.a];
    REP(i,3){
        int p=i;
        FOR(j,i,3) if (fabs(M[j][i])>fabs(M[p][i])) p=j;
        REP(j,4) swap(M[p][j],M[i][j]);
        double c=M[i][i];
        assert(fabs(c)>1e-9);
        REP(j,4) M[i][j]/=c;
        REP(j,3) if (j!=i){
            double c=M[j][i];
            REP(k,4) M[j][k]-=M[i][k]*c;
        }
    }
    return fabs(M[2][3]);
}

int main(){

    int tn=0;
    while(cin>>n,n){
        ++tn;
        fprintf(stderr,"%d\n", n);
        REP(i,n) scanf(" %d%d%d", x+i,y+i,z+i);
        memset(faces,-1,sizeof(faces));
        memset(vis,0,sizeof(vis));
        cla(); clb();
        REP(i,4) pba();
        REP(i,n) pbb();

        revl.clear();
        U.clear(); U.resize(4,0);
        step=step2=0;
        fl.clear();
        rmp.clear();
        idf=0;
        REP(i,4){
            int a=(i+1)%4, b=(i+2)%4, c=(i+3)%4;
            fl.pb(face(a,b,c,idf));
            rmp.pb(--fl.end());
            addface(a,b,c,idf);
            int u=dir(a,b,c,i);
            FOR(j,4,n) if (dir(a,b,c,j)!=u) adde(i,j);
            ++idf;
        }
        FOR(i,4,n) id[i]=i;
        random_shuffle(id+4,id+n);
        step=step2=0;
        //assert(U.size()==idf); assert(ea.size()==idf); assert(rmp.size()==idf);

        FOR(i,4,n){
            int x=id[i];
            ++step;
            FE(it,*eb[x]) U[it->b]=step, remface(rmp[it->b]->a,rmp[it->b]->b,rmp[it->b]->c,it->b);


            for (ITE it=eb[x]->begin(); it!=eb[x]->end(); ){
                ITE next=it; ++next;
                edge e=*it;
                int F=e.b;

                //assert(revl[revl[e.rev]->rev]==it);
                ea[F]->erase(revl[e.rev]);
                eb[x]->erase(it);

                vi tb; 
                tb.pb(rmp[F]->a); tb.pb(rmp[F]->b); tb.pb(rmp[F]->c);
                tb.pb(rmp[F]->a); tb.pb(rmp[F]->b);

                REP(j,3){

                    int a=tb[j], b=tb[j+1], c=tb[j+2];
                    int fa=faces[a][b][0], fb=faces[a][b][1];
                    int u=-1;
                    if (fa!=-1 && U[fa]!=step) u=fa;
                    if (fb!=-1 && U[fb]!=step) u=fb;
                    if (u!=-1){
                        fl.pb(face(a,b,x,idf));
                        rmp.pb(--fl.end());

                        pba();
                        ++step2;
                        int ND=dir(a,b,x,c);
                        FE(it,*ea[F]) if (vis[it->b]!=step2){
                            vis[it->b]=step2;
                            if (dir(a,b,x,it->b)!=ND) adde(idf,it->b);
                        }
                        FE(it,*ea[u]) if (vis[it->b]!=step2){
                            vis[it->b]=step2;
                            if (dir(a,b,x,it->b)!=ND) adde(idf,it->b);
                        }
                        U.pb(step);
                        addface(a,b,x,idf);
                        ++idf;

                        //assert(U.size()==idf); assert(ea.size()==idf); assert(rmp.size()==idf);
                    }
                }
                while(!ea[F]->empty()){
                    eb[ea[F]->front().b]->erase(revl[ea[F]->front().rev]), ea[F]->pop_front();
                }
                fl.erase(rmp[F]);
                it=next;
            }

                    //assert(fl.size());
        }
        if (0)FE(it,fl){
            vi has(n,0);
            FE(ita,*ea[it->id]) has[ita->b]=1;
            int a=it->a, b=it->b, c=it->c;
            int d=0;
            while(d==a||d==b||d==c) ++d;
            REP(j,n) if (j!=a&&j!=b&&j!=c){
                if (has[j]==has[d]){

                    if (dir(a,b,c,j)!=dir(a,b,c,d)) fprintf(stderr,"FAIL 1 %d\n",tn);
                }
                else  if (dir(a,b,c,j)==dir(a,b,c,d)) fprintf(stderr,"FAIL 2\n");

            }
        }

        fprintf(stderr,"here\n");
        if (0)FE(it,fl){
            int a=it->a, b=it->b, c=it->c;
            disp(a);
            disp(b);
            disp(c);
            REP(i,n) if (i!=a&&i!=b&&i!=c){
                printf("%d\n", dir(a,b,c,i));
            }
            puts("");
        }

        int nq; cin>>nq;
        REP(_step,nq){
            int x, y, z; scanf(" %d%d%d",&x,&y,&z);
            double res=1e18;
            FE(it,fl) checkmin(res,go(x,y,z,*it));
            printf("%.4lf\n", res);
        }
    }
    return 0;
}




