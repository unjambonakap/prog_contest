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

const int maxn=222;
const int oo=1e8;

int n;
vi e[maxn];
int c[maxn];
int cx[2], dx[2];

int bestc;
int aa,bb,cc;

vi tx;
int mark[maxn];
int dp[maxn][maxn][2];
int C,D;
int STEP;
int BLOCK;
int BUILD;

void dfs(int a, vi &lst, int p=-1){
    lst.pb(a);
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        dfs(b,lst,a);
    }
}

int dfs2(int a, int p, int d){
    if (a==BLOCK) return 0;
    if (d==0){tx.pb(a); return 0;}
    int res=c[a];

    mark[a]=STEP;
    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        res+=dfs2(b,a,d-1);
    }
    return res;
}

int cmp(const pii &a, const pii &b){return c[a.ST]>c[b.ST];}
int go(int C, vector<pii> &tb){
    sort(ALL(tb),cmp);
    int rem=C;
    int diff=-1;

    int ans=0;


    REP(j,tb.size()){
        if (!rem) break;
        if (rem==1 && diff==tb[j].ND) continue;
        --rem;

        if (diff==-1) diff=tb[j].ND;
        else if (diff!=tb[j].ND) diff=-2;

        mark[tb[j].ST]=STEP;
        ans+=c[tb[j].ST];
    }
    if (diff!=-2) return -oo;
    return ans;
}


int solve(int a0, int b0, int f){//n times
    C=cx[f], D=dx[f];

    vi lst;
    dfs(a0,lst,b0);

    int res=-oo;

    BLOCK=b0;
    STEP=2;
    int fd=0;

    if (D&1){

        REP(ii,lst.size()){
            int i=lst[ii];
            REP(jj,e[i].size()){
                ++STEP;
                int j=e[i][jj];
                if (j>i) continue;
                if (j==b0) continue;

                int ans=0;
                vector<pii> tb;
                REP(k,2){
                    tx.clear();
                    ans+=dfs2(i,j,D/2);
                    REP(uu,tx.size()) tb.pb(MP(tx[uu],k));
                    swap(i,j);
                }
                res=max(res,ans+go(C,tb));
                if (BUILD && res==dp[b0][a0][f]){fd=1; goto out;}
            }
        }
    }else{

        REP(ii,lst.size()){
            ++STEP;
            int i=lst[ii];

            int ans=c[i];
            mark[i]=STEP;

            vector<pii> tb;
            if (D) REP(jj,e[i].size()){
                int j=e[i][jj];
                if (j==BLOCK) continue;

                tx.clear();
                ans+=dfs2(j,i,D/2-1);
                REP(uu,tx.size()) tb.pb(MP(tx[uu],jj));
            }
            if (D) ans+=go(C,tb);

            res=max(res,ans);
            if (BUILD && res==dp[b0][a0][f]){fd=1; goto out;}
        }
    }
out:
    assert(!BUILD || fd);


    REP(i,n) if (mark[i]>1) mark[i]=mark[i]==STEP;
    return res;
}


int main(){

    int tn=0;
    while(cin>>n,!cin.eof()){
        ++tn;
        REP(i,n) e[i].clear();

        REP(i,2) scanf(" %d%d",dx+i,cx+i);
        REP(i,n) scanf(" %d",c+i);
        REP(i,n-1){
            int a,b; scanf(" %d%d",&a,&b);
            --a; --b;
            e[a].pb(b); e[b].pb(a);
        }

        BUILD=0;
        REP(i,n) REP(j,e[i].size()) REP(f,2) dp[i][e[i][j]][f]=solve(e[i][j],i,f);

        bestc=-1;
        REP(i,n){
            int best1=-1, best2=-1;
            REP(j,e[i].size()){
                int k=e[i][j];
                if (best1==-1 || dp[i][k][0]>dp[i][best1][0]) best2=best1, best1=k;
                else if (best2==-1 || dp[i][k][0]>dp[i][best2][0]) best2=k;
            }

            REP(j,e[i].size()){
                int k=e[i][j];
                int k2=best1==k?best2:best1;
                if (k2==-1) continue;

                int ans=dp[i][k][1]+dp[i][k2][0];
                if (bestc<ans) bestc=ans, aa=i,bb=k2,cc=k;
            }
        }

        if (bestc==-1) puts("-1");
        else{
            bestc=-bestc;
            REP(i,n) bestc+=c[i];

            printf("%d\n",bestc);


            memset(mark,0,sizeof(mark));
            BUILD=1;
            solve(bb,aa,0);
            solve(cc,aa,1);
            assert(bb!=cc);

            vi res;
            REP(i,n) assert(mark[i]==0 || mark[i]==1);
            REP(i,n) if (!mark[i]) res.pb(i);

            int sum=0;
            REP(i,res.size()) sum+=c[res[i]];
            assert(sum==bestc);

            REP(i,res.size()) printf("%d%c",res[i]+1," \n"[i==res.size()-1]);
        }
        break;
    }


    return 0;
}


