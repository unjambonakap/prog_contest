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

const int maxn=11111;
char s[maxn];
int n;
int cnt[27];
int x1[maxn], x2[maxn];

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %s",s);
        n=strlen(s);
        REP(i,n) s[i]=s[i]=='#'?26:s[i]-'a';

        memset(cnt,0,sizeof(cnt));
        REP(i,n) x1[i+1]=max(x1[i],s[i]==26?0:++cnt[s[i]]);

        memset(cnt,0,sizeof(cnt));
        x2[n]=0;
        REPV(i,n) x2[i]=max(x2[i+1],s[i]==26?0:++cnt[s[i]]);
        int res=0;

        REP(i,n) if (s[i]==26){
            int j,k;
            memset(cnt,0,sizeof(cnt));
            int best=0;
            for (j=i+1; j<n && s[j]!=26; ++j) best=max(best,++cnt[s[j]]);
            memset(cnt,0,sizeof(cnt));
            if (j==n) break;
            int best2=0;
            for (k=j+1; k<n && s[k]!=26; ++k) best2=max(best2,++cnt[s[k]]);
            if (k==n) break;
            if (best==0 ||best2==0 ||x1[i]==0||x2[k]==0) continue;
            res=max(res,3+best+best2+x1[i]+x2[k]);
        }
        printf("%d\n",res);

    }
    return 0;
}


