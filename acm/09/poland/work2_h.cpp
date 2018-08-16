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

const int maxn=111111;
const int maxm=222222;
const ll inf=1e9;
const double ths=2;


int last[maxn], to[maxm], prev[maxm], ne;
int rlast[maxn], rto[maxm], rprev[maxm], nre;
int vis[maxn];
int step;
int n, m;
int B,C;

int rem[maxn], la[maxn], lb[maxn], na, nb;
int ord[maxn];

int cmp(int a, int b){return ord[a]<ord[b];}




int adde(int a, int b){prev[ne]=last[a]; last[a]=ne; to[ne]=b; ++ne;}
int addre(int a, int b){rprev[nre]=rlast[b]; rlast[b]=nre; rto[nre]=a; ++nre;}

void dfs(int a, vi &lst){
    if (vis[a]==step) return;
    vis[a]=step;
    for (int i=last[a]; i!=-1; i=prev[i]) dfs(to[i], lst);
    lst.pb(a);
}

void go(int a){
    if (ord[a]>=ord[B]) return;
    vis[a]=step;
    for (int i=last[a]; i!=-1; i=prev[i]) if (vis[to[i]]!=step) go(to[i]);
    la[na++]=a;
}

void gob(int a){
    if (ord[a]<=ord[C]) return;
    vis[a]=step;
    for (int i=rlast[a]; i!=-1; i=rprev[i]) if (vis[rto[i]]!=step) gob(rto[i]);
    lb[nb++]=a;
}

int main(){
    int tn; cin>>tn;
    //bench();
    REP(ti,tn){
        ne=nre=0;
        memset(last,-1,sizeof(last));
        memset(rlast,-1,sizeof(rlast));
        cin>>n>>m;
        REP(i,m){int a, b; scanf("%d%d", &a,&b); adde(a,b); addre(a,b);}
        step=1; memset(vis,0,sizeof(vis));

        vi lst;
        REP(i,n) dfs(i+1, lst);

        REP(i,lst.size()) ord[lst[i]]=lst.size()-i;
        cerr<<ti<<endl;


        int a, b, c;
        int sw=0;
        int cnt=0;
        while(scanf("%d%d%d", &a,&b,&c), a|b|c){
            ++cnt;
//            if (ti==6 && cnt%100==0){
//                cerr<<cnt<<endl;
//                fprintf(stderr, "%d \n", ne);
//            }
            if (a){
                if (sw) swap(b,c);
                if (ord[b]>=ord[c]){
                    na=nb=0;
                    //fprintf(stderr, "a\n");
                    B=b; C=c;
                    ++step; go(c);
                    ++step; gob(b);
                    //fprintf(stderr, "b\n");


                    sort(la,la+na,cmp);
                    sort(lb,lb+nb,cmp);

                    //REP(i,la.size()-1) assert(ord[la[i]]<ord[la[i+1]]);
                    //REP(i,lb.size()-1) assert(ord[lb[i]]<ord[lb[i+1]]);
                    int nrem=0;

                    int i, j;
                    for (i=j=0; i<na&&j<nb;){
                        if (ord[la[i]]<ord[lb[j]]) rem[nrem++]=ord[la[i++]];
                        else rem[nrem++]=ord[lb[j++]];
                    }
                    for (; i<na; ++i) rem[nrem++]=ord[la[i]];
                    for (; j<nb; ++j) rem[nrem++]=ord[lb[j]];
                    
                    REP(i,nb) ord[lb[i]]=rem[i];
                    REP(i,na) ord[la[i]]=rem[i+nb];
                }
                adde(b,c); addre(b,c);
            }else{
                if (ord[b]<ord[c]) puts("YES");
                else puts("NO"), sw^=1;
            }
        }
    }
    return 0;
}



