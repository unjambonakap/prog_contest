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

const int maxn=1e5+10;
vi e[maxn];
int id[maxn];
int pos;
int n, m;
vector<vi> decomp;
int cut[maxn];
int backe[maxn];
vi stk;

int dfs(int a, int p=-1){
    int cnt=0;
    id[a]=pos++;
    int res=id[a];

    REP(i,e[a].size()){
        int b=e[a][i];
        if (p==b) continue;
        if (id[b]==-1){
            ++cnt;
            int sz=stk.size();
            int x=dfs(b,a);
            checkmin(res,x);
            if (x>=id[a]){
                assert(stk.size()>=sz);
                vi tb;
                while(stk.size()>sz) tb.pb(stk.back()), stk.pop_back();
                tb.pb(a);
                decomp.pb(tb);
                if (a||cnt>1) cut[a]=1;
            }
        }else checkmin(res,id[b]);
    }
    stk.pb(a);
    backe[a]=res;
    return res;
}



int main(){
    int tn=0;
    while(cin>>m,m){
        ++tn;

        n=0;
        REP(i,m){int a, b; scanf("%d%d", &a,&b); --a; --b; checkmax(n,max(a+1,b+1)); e[a].pb(b); e[b].pb(a);}
        decomp.clear();
        stk.clear();
        memset(cut,0,sizeof(int)*n);
        memset(id,-1,sizeof(id));
        pos=0;
        dfs(0);
        ll nways;
        int res;
        if (decomp.size()==1){
            res=2;
            nways=1ll*n*(n-1)/2;
        }else{
            nways=1;
            res=0;
            FE(it,decomp){
                int cnt=0;
                FE(ita,*it) if (cut[*ita]) ++cnt;
                assert(cnt>=1);
                if (cnt==1) ++res, nways*=it->size()-1;
            }
        }

        printf("Case %d: %d %Ld\n", tn, res,nways);
        REP(i,n) e[i].clear();
    }
}

