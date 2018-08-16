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
int A[maxn];
string B;
int n;
int dp[maxn][maxn];
int dpb[maxn][maxn];
int res[5];


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>B;
        REP(i,n) scanf("%d", A+i);
        vi na;
        REP(i,n) na.pb(A[i]); sort(ALL(na)); 
        REP(i,n) A[i]=lower_bound(ALL(na), A[i])-na.begin();
        REP(i,n+1) dp[0][i]=dpb[0][i]=0;
        FOR(i,1,n+1) REP(j,n+1) dp[i][j]=dp[i-1][j]+(A[i-1]>=j);
        FOR(i,1,n+1) REP(j,n+1) dpb[i][j]=dpb[i-1][j]+(A[i-1]<=j);

        vi idx; REP(i,3) idx.pb(i);
        REP(i,3) REP(j,i) if (B[2*idx[i]]<B[2*idx[j]]) swap(idx[i],idx[j]);

        int fd=0;
        FOR(i,1,n-3) FOR(j,i+2,n-1){
            int xa[]={0,i,j}, xb[3]={i,j,n};
            int va=-1, vb=-1; 

            int prev=-1, next;
            for (int k=0; k!=B[2*idx[1]]-'1'; ++k){

                if (k==B[1]-'1'){ if (prev>=A[i]) goto fail; prev=A[i];}
                else if (k==B[3]-'1'){if (prev>=A[j]) goto fail; prev=A[j];}
                else{
                    int last=-1;
                    int T=prev+1, H=n;
                    int nc=prev==-1?0:dpb[xb[idx[0]]][prev]-dpb[xa[idx[0]]][prev];
                    while(T<=H){
                        int M=(T+H)/2;
                        if (dpb[xb[idx[0]]][M]-dpb[xa[idx[0]]][M]!=nc) last=M, H=M-1;
                        else T=M+1;
                    }

                    if (last==-1) goto fail;
                    prev=va=last;
                }
            }
            next=n;
            for (int k=4; k!=B[2*idx[1]]-'1'; --k){
                if (k==B[1]-'1'){ if (next<=A[i]) goto fail; next=A[i];}
                else if (k==B[3]-'1'){if (next<=A[j]) goto fail; next=A[j];}
                else{
                    int last=-1;
                    int T=0, H=next-1;
                    int nc=dp[xb[idx[2]]][next]-dp[xa[idx[2]]][next];
                    while(T<=H){
                        int M=(T+H)/2;
                        if (dp[xb[idx[2]]][M]-dp[xa[idx[2]]][M]!=nc) last=M, T=M+1;
                        else H=M-1;
                    }
                    if (last==-1) goto fail;
                    next=vb=last;
                }
            }

            assert(vb!=-1);
            if (dp[xb[idx[1]]][prev+1]-dp[xa[idx[1]]][prev+1]>dp[xb[idx[1]]][next]-dp[xa[idx[1]]][next]){
                res[1]=i; res[3]=j;
                FOR(k,xa[idx[0]],xb[idx[0]]) if (A[k]==va){res[2*idx[0]]=k; break;}
                FOR(k,xa[idx[1]],xb[idx[1]]) if (A[k]>prev&&A[k]<next){res[2*idx[1]]=k; break;}
                FOR(k,xa[idx[2]],xb[idx[2]]) if (A[k]==vb){res[2*idx[2]]=k; break;}

                fd=1; goto done;
            }
fail:;
        }

done:
        if (fd) out(res,5);
        else puts("-1");
    }
    return 0;
}


