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


