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

const int maxb=14;
const int maxn=2222;
const ll oo=1e18;
const int maxsz=1e6;

int b,s;
char buf[maxsz];
int ns;
int m;

struct matrix{
    ll m[maxb][maxb];
    matrix(){memset(m,0,sizeof(m));}
    void ident(){ REP(i,b) REP(j,b) m[i][j]=i==j?0:oo; }

    matrix(const matrix &a){memcpy(m,a.m,sizeof(m));}
    matrix operator*(const matrix &a)const{
        matrix res;
        REP(i,b) REP(j,b){
            ll v=oo;
            REP(k,b) v=min(v,m[i][k]+a.m[k][j]);
            res.m[i][j]=v;
        }
        return res;
    }
};

matrix faste(matrix a, ll p){
    matrix x; x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=x*a;
    return x;
}

struct data{
    int v;
    vi next;
    ll rep;

    void init(){v=b; next.clear();}
}tb[maxn];
int pos;

void skip(int &a){while(buf[a]<'A' || buf[a]>'Z') ++a;}

int dfs(int a, int x){
    skip(a);
    tb[x].init();

    if (buf[a]=='V'){
        sscanf(buf+a+1,"%d",&tb[x].v);
        m=max(m,--tb[x].v+1);
        return a+1;
    }else{
        sscanf(buf+a+1,"%Ld",&tb[x].rep);
        ++a; skip(a);

        while(buf[a]!='E'){
            int nx=pos++;

            a=dfs(a,nx);
            tb[x].next.pb(nx);

            skip(a);
        }
        ++a;
    }
    return a;
}

matrix dp[maxn];
int vis[maxn];

int with[maxb];
ll res;




void go(int a){
    if (vis[a]) return;
    vis[a]=1;

    matrix &x=dp[a];

    if (tb[a].next.size()==0){
        REP(i,b) REP(j,b){
            int u=with[tb[a].v];
            int val=1;
            if (i!=j) ++val;
            if (u==i || u==j || u==0); 
            else val+=2;
            x.m[i][j]=val;
        }
    }else{
        x.ident();

        REP(i,tb[a].next.size()){
            int na=tb[a].next[i];
            go(na);
            x=x*dp[na];
        }
        x=faste(x,tb[a].rep);
    }
}

int cnt=0;

void gen(int bp, int sp, int prev=0){
    int avail=-1;
    REP(i,m) if (with[i]==-1){avail=i; break;}

    if (avail==-1){
        memset(vis,0,sizeof(vis));
        go(0);
        REP(i,b) res=min(res,dp[0].m[b-1][i]);
    }
    if (bp==b-1) return;
    if (sp==s) ++bp, sp=0, prev=0;
    if (sp>0 && bp>0){
        gen(bp+1,0);
    }

    if (bp>0 && sp==0){
        with[avail]=bp;
        gen(bp,sp+1);
        with[avail]=-1;
    }else{
        FOR(i,prev,m) if (with[i]==-1){
            with[i]=bp;
            gen(bp,sp+1,i);
            with[i]=-1;
        }
    }
}

int main(){

    while(cin>>b>>s,!cin.eof()){
        string ss;
        getline(cin,ss);
        buf[0]='R';
        buf[1]='1';
        buf[2]=' ';

        fgets(buf+3,maxsz-10,stdin);
        ns=strlen(buf);
        buf[ns++]=' ';
        buf[ns++]='E';

        m=0;
        pos=0;
        dfs(0,pos++);

        memset(with,-1,sizeof(with));
        ++b;

        res=oo;
        gen(0,0);

        cout<<res<<endl;
    }

    return 0;
}

