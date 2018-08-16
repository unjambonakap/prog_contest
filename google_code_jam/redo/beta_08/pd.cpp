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

const int maxn=75;
int graph[maxn][maxn];
int n, p;
int lst[3][maxn];
int pos[maxn];
int score[maxn];
int ng[maxn*maxn][maxn*maxn];
int id[2*maxn][maxn];
int dist[maxn*maxn];

int m[3][maxn][maxn];

int km(int m[][maxn]){
    int lx[maxn], ly[maxn];
    int dx[maxn], dy[maxn];
    int tx[maxn], ty[maxn];
    int slack[maxn];
    int parent[maxn];

    memset(ly, 0, sizeof(ly));
    REP(i, n) lx[i]=*max_element(m[i], m[i]+n);


    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy));

    int nstep=n;
    REP(i, n) REP(j, n) if (dy[j]==-1 && lx[i]+ly[j]==m[i][j]){ dx[i]=j; dy[j]=i; --nstep; break;}
    REP(step, nstep){
        int q[n], qa, qe;
        int p;
        memset(parent, -1, sizeof(parent)); memset(slack, -1, sizeof(slack));
        memset(tx, 0, sizeof(tx)); memset(ty, 0, sizeof(ty));
        qa=qe=0;
        REP(i, n) if (dx[i]==-1) q[qe++]=i;
        while(1){
            while(qa<qe){
                int a=q[qa++];
                tx[a]=1;
                REP(j, n) if (!ty[j] && (slack[j]==-1 || lx[a]+ly[j]-m[a][j]<slack[j])){
                    if ((slack[j]=lx[parent[j]=a]+ly[j]-m[a][j])==0){
                        ty[j]=1;
                        if (dy[j]==-1){p=j; goto augment;}
                        q[qe++]=dy[j]; 
                    }
                }
            }
            int v=INT_MAX;
            REP(j, n) if (!ty[j]) checkmin(v, slack[j]);
            p=-1;
            REP(i, n){
                if (tx[i]) lx[i]-=v;
                if (ty[i]) ly[i]+=v;
                else if ((slack[i]-=v)==0){
                    ty[i]=1;
                    if (dy[i]==-1) p=i;
                    else q[qe++]=dy[i];
                }
            }
            if (p!=-1) goto augment;
            assert(qa<qe);


        }
augment:
        while(p!=-1){int np=dx[parent[p]]; dx[parent[p]]=p; dy[p]=parent[p]; p=np;}



    }
    int res=0;
    REP(i, n) assert(dx[i]!=-1);
    REP(i, n) assert(m[i][dx[i]]==lx[i]+ly[dx[i]]);
    REP(i, n) res+=m[i][dx[i]];
    return res;

}



int solve(){
    REP(i, n){
        memset(dist, -1, sizeof(dist));
        int q[p];
        int qa, qe;
        qa=qe=0;
        dist[pos[i]]=0;
        q[qe++]=pos[i];
        while(qa<qe){
            int a=q[qa++];
            REP(j, p) if (dist[j]==-1 && ng[a][j])  q[qe++]=j, dist[j]=dist[a]+1;
        }
        REP(step, 3) REP(k, n) m[step][i][k]=-dist[lst[step][k]]*score[i];
    }


    int res=INT_MAX;
    REP(step, 3) checkmin(res, -km(m[step]));
    return res;


}

int main(){
    int ti, tn;
    cin>>tn;
    scanf("\n");

    FOR(ti, 1, tn){
        n=0;
        char buf[1043];
        assert(fgets(buf, 1040, stdin));
        istringstream ss(buf);
        int a;
        while(ss>>a) pos[n++]=a;
        REP(i, n) cin>>score[i];
        scanf("\n");
        REP(i, n) --pos[i];

        memset(id, -1, sizeof(id));
        int ni=n-n/2;
        p=0;
        memset(ng, 0, sizeof(ng));
        FOR(i, ni, n) REP(j, i) id[i][j]=p++;
        FOR(i, n+1, 2*n-ni) REP(j, 2*n-i) id[i][j]=p++;


        FOR(i, ni, n-1) REP(j, i){
            if (j) ng[id[i][j-1]][id[i][j]]=1;
            ng[id[i][j]][id[i+1][j]]=1, ng[id[i][j]][id[i+1][j+1]]=1;
        }
        REP(j, n)  if (j) ng[id[n][j-1]][id[n][j]]=1;
        FOR(i, n+1, n+n/2) REP(j, 2*n-i){
            if (j) ng[id[i][j-1]][id[i][j]]=1;
            ng[id[i][j]][id[i-1][j]]=1, ng[id[i][j]][id[i-1][j+1]]=1;
        }

        REP(i, p) REP(j, p) if (ng[i][j]) ng[j][i]=1;
        REP(i, n) lst[0][i]=id[n][i];
        REP(i, n/2+1) lst[1][i]=id[i+ni][i];
        FOR(i, n/2+1, n-1) lst[1][i]=id[i+ni][n/2];

        FOR(i, n/2, n-1) lst[2][i]=id[i+ni][n-1-i];
        REP(i, n/2) lst[2][i]=id[i+ni][n/2];





        int res=solve();
        printf("Case #%d: %d\n", ti, res);
    }


    return 0;
}



