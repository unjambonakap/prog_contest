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


const int maxn=1e6+10;
const int inf=maxn;
int A[maxn], B[maxn];
int can[maxn];

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        int r, l; cin>>r>>l;
        memset(A,0,sizeof(A));

        memset(can,1,sizeof(can));
        REP(u,r){
            int n; scanf("%d", &n);
            REP(i,l) B[i]=inf;
            vi x(n); REP(i,n) scanf("%d", &x[i]);
            vi y;
            int pos=0;
            int last=0;
            REP(i,n){
                if (x[i]==0){y.pb(last); B[pos++]=0; last=0; continue;}
                ++last;
                int s=last;
                for (int j=pos+x[i]-1, k=y.size()-1; k>=0 && j>=pos; --j,s+=y[k--]) if (B[j]>s) B[j]=s;
                pos+=x[i];
            }
            y.clear();
            pos=l-1; last=0;
            REPV(i,n){
                if (x[i]==0){y.pb(last); B[pos--]=0; last=0; continue;}
                ++last;
                int s=last;
                for (int j=pos-x[i]+1, k=y.size()-1; k>=0 && j<=pos; ++j,s+=y[k--]) if (B[j]>s) B[j]=s;
                pos-=x[i];
            }
            REP(i,l) if (B[i]>=inf) can[i]=0; else A[i]+=B[i];
        }
        vi res; 
        REP(i,l) if (can[i]){
            if (!res.size() || A[i]<A[res[0]]) res.clear(), res.pb(i);
            else if (!res.size() || A[i]==A[res[0]]) res.pb(i);
        }
        printf("%d\n", A[res[0]]);
        out(res);
    }

    return 0;
}



