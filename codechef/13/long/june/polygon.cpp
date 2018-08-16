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

const int maxn=1111;
int tb[maxn];
int perm[maxn];
int cmp(int a, int b){return tb[a]<tb[b];}

int n;
int K;
int lst[22];
ll A[1<<20];
int cntb[1<<20];
void solve(){
    FOR(i,K-1,n) FOR(j,max(2*K-1,i+1),n){
        vi t1,t2;
        ll s1=tb[perm[j]], s2=tb[perm[i]];
        int c1=K-1, c2=K-1;
        t1.pb(j);
        t2.pb(i);
        for (int k=j-1; k>i && c1; --k) s1-=tb[perm[k]], --c1, t1.pb(k);
        for (int k=i-1; i>=0 && c1+c2>0; --k){
            if (!c2)  s1-=tb[perm[k]], --c1, t1.pb(k);
            else if (!c1) s2-=tb[perm[k]], --c2, t2.pb(k);
            else if (s1<s2) s2-=tb[perm[k]], --c2, t2.pb(k);
            else  s1-=tb[perm[k]], --c1, t1.pb(k);
        }
        if (s1<0 && s2<0){
            puts("Yes");
            REP(i,K) printf("%d ", perm[t1[i]]+1);
            REP(i,K) printf("%d%c", perm[t2[i]]+1," \n"[i==K-1]);
            return;
        }
    }
    if (1){
        for (int j=1; j<1<<2*K; ++j) cntb[j]=1+cntb[j&j-1];

        FOR(i,2*K-1,n){
            int sum=0;
            REP(j,2*K) lst[j]=tb[perm[i-j]];
            REP(j,2*K) sum+=lst[j];

            int sum2=0;
            REP(j,K) sum2+=lst[2*K-1-j];
            //if (tb[i]>sum-tb[i]-sum2) continue;

            memset(A,0,sizeof(A));
            REP(j,2*K) A[1<<j]=lst[j];
            int ub=1<<2*K;
            for (int j=1; j<ub; ++j) if (A[j]==0 && cntb[j]<=K)
                A[j]=A[j&j-1]+A[j&-j];

            int M=(1<<2*K)-1;
            for (int j=1; j<ub; ++j) if (cntb[j]==K){
                int lb=j&-j;
                int j2=M^j, lb2=j2&-j2;
                if (A[j]-A[lb]>A[lb] && A[j2]-A[lb2]>A[lb2]){
                    puts("Yes");
                    REP(u,2*K) if (j&1<<u) printf("%d ",perm[i-u]+1);
                    int cnt=K;
                    REP(u,2*K) if (j2&1<<u) printf("%d%c",perm[i-u]+1," \n"[--cnt==0]);
                    return;
                }
            }
        }
    }
    puts("No");
}

int main(){
    cin>>n>>K;
    REP(i,n) perm[i]=i;
    REP(i,n) scanf(" %d",tb+i);
    sort(perm,perm+n,cmp);
    solve();
    return 0;
}

