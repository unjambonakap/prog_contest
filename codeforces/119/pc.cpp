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

const int maxn=2e5+10;

vi e[maxn];
int A[maxn];
int par[maxn];
int dist[maxn];
int with[maxn];
int n, m;
int s, t;
int x;


int root(int a){return par[a]==-1?a:par[a]=root(par[a]);}
int join(int a, int b){a=root(a); b=root(b); if (a!=b) par[a]=b;}

int checkit(int D){
    queue<int> q;
    memset(with,-1,sizeof(with));
    memset(dist,-1,sizeof(dist));
    REP(i,m) q.push(A[i]), dist[A[i]]=0, with[A[i]]=i;

    memset(par,-1,sizeof(par));

    while(!q.empty()){
        int a=q.front(); q.pop();
        int d=dist[a];
        if (d>D/2+1) break;
        REP(i,e[a].size()){
            int b=e[a][i];
            if (dist[b]==-1) dist[b]=d+1, with[b]=with[a], q.push(b);
            else if (dist[b]+d+1<=D) join(with[b],with[a]);
        }
    }
    return root(x)==root(m-1);
}


int main(){
    int ne; cin>>n>>ne>>m;
    REP(i,m) scanf(" %d", A+i),--A[i];
    REP(i,ne){ int a, b; scanf(" %d%d", &a,&b); --a; --b; e[a].pb(b); e[b].pb(a); } 
    
    cin>>s>>t; --s; --t;
    REP(i,m) if (A[i]==s) x=i;
    A[m++]=t;


    int T=0, H=n;
    int best=n;
    while(T<=H){
        int M=T+H>>1;
        if (checkit(M)) best=M, H=M-1;
        else T=M+1;
    }
    cout<<(best==n?-1:best)<<endl;


    return 0;
}


