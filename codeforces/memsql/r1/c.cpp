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

const int oo=314000000;
const int maxn=1e5+10;
int n,m;
vi lst[maxn];
int cnt[maxn];
int id[maxn];

int is[maxn];

int best[maxn];
int best2[maxn];
int vis[maxn];
vi ine[maxn];
int deg[maxn];
int bad[maxn];

int cost[maxn];

int ns[maxn];



int ans1[maxn], ans2[maxn];


void go1(){
    priority_queue<pii> q;
    memset(cost,0,sizeof(cost));
    memset(ans1,0x7f,sizeof(ans1));
    memset(deg,0,sizeof(deg));

    REP(i,n) if (is[i]) q.push(MP(-(ans1[i]=best[i]),i));
    REP(i,m) cost[i]=cnt[i];

    while(q.size()){
        pii pp=q.top(); q.pop();
        int a=pp.ND, c=-pp.ST;
        if (c!=ans1[a]) continue;

        REP(i,ine[a].size()){
            int b=ine[a][i];
            ++deg[b];
            cost[b]=min(cost[b]+ans1[a],oo);

            if (deg[b]==lst[b].size() && ans1[id[b]]>cost[b]) ans1[id[b]]=cost[b], q.push(MP(-cost[b],id[b]));
        }
    }
    REP(i,n) if (ans1[i]>oo) ans1[i]=-1;
}


void go2(){
    memset(cost,0,sizeof(cost));
    memset(ans2,-1,sizeof(ans1));
    memset(deg,0,sizeof(deg));
    memset(vis,0,sizeof(vis));


    memset(bad,0,sizeof(bad));

    queue<int> q2;
    REP(i,n) if (ans1[i]==-1) q2.push(i);
    while(q2.size()){
        int a=q2.front(); q2.pop();
        REP(i,ine[a].size()){
            int b=ine[a][i];
            if (bad[b]) continue;
            bad[b]=1;
            if (!--ns[id[b]] && !is[id[b]]) q2.push(id[b]);
        }
    }

    queue<int> q;
    REP(i,n) if (best2[i]) ans2[i]=best2[i];
    REP(i,n) if (is[i] && !ns[i]) q.push(i);
    REP(i,m) cost[i]=cnt[i];

    while(q.size()){
        int a=q.front(); q.pop();
        vis[a]=1;

        REP(i,ine[a].size()){
            int b=ine[a][i];
            ++deg[b];
            cost[b]=min(cost[b]+ans2[a],oo);

            if (deg[b]==lst[b].size()){
                ans2[id[b]]=max(ans2[id[b]],cost[b]);
                if (!--ns[id[b]]) q.push(id[b]);
            }
        }
    }

    REP(i,n) if (!vis[i]) ans2[i]=-2;

}

int main(){
    int st=0;
    while(cin>>m>>n,!cin.eof()){
        if (st++) puts("");
        memset(cnt,0,sizeof(cnt));

        memset(ns,0,sizeof(ns));
        memset(is,0,sizeof(is));

        REP(i,n) ine[i].clear();
        REP(i,n) best[i]=oo, best2[i]=0;

        REP(i,m){
            int a,na; scanf(" %d%d",&a,&na);
            --a;
            id[i]=a;
            lst[i].clear();

            REP(j,na){
                int b; scanf(" %d",&b);
                if (b==-1) ++cnt[i];
                else --b, lst[i].pb(b), ine[b].pb(i);
            }


            if (na==cnt[i]) is[a]=1, best[a]=min(best[a],cnt[i]), best2[a]=max(best2[a],cnt[i]);
            else ++ns[a];
        }
        memset(vis,0,sizeof(vis));
        go1();
        go2();

        REP(i,n) printf("%d %d\n",ans1[i],ans1[i]==-1?-1:ans2[i]);
    }

    return 0;
}

