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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=8;
const int maxm=2000;

int order[maxn];
int n, m;
int mp[maxm][maxn];

int can[maxn];
pii dfs(int p, const vi &b, int f){
    if (b.size()==1) return MP(p+1, f?b[0]:INT_MAX);

    pii ans=MP(INT_MAX, 0);
    REP(i, n-p){
        vi nb[n];
        FE(it, b)  nb[mp[*it][can[i]]].pb(*it);
        int nf=order[p]==can[i]?f:0;
        swap(can[i], can[n-p-1]);
        pii res=MP(0, 0);
        REP(j, n) if (j && nb[j].size()){
            pii x=dfs(p+1, nb[j], nf);
            checkmax(res, x);
        }
        checkmin(ans, res);
        swap(can[i], can[n-p-1]);
        if (ans.ST<n) return ans;
    }
    return ans;
}

void solve(){

    vi tmp(n);
    REP(i, n) tmp[i]=i;
    m=0;
    vector<vi> sl;
    do{
        REP(i, n) REP(j, i) REP(k, j) if (tmp[k]>tmp[j] && tmp[j]>tmp[i]) goto fail;
        sl.pb(tmp);
fail:;
    }while(next_permutation(ALL(tmp)));


    sort(ALL(sl));
    m=sl.size();
    REP(i, m) REP(j, n) mp[i][j]=sl[i][j];
    vi b;
    REP(i, m) b.pb(i);
    REP(i, n) can[i]=i;
    int ans=dfs(0, b, 1).ND;

    REP(i, n) printf(" %d", mp[ans][i]+1);


}


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){

        cin>>n;
        REP(i, n) cin>>order[i];
        REP(i, n) --order[i];
        //if (ti!=16) continue;
        printf("Case #%d:", ti);
        solve();
        printf("\n");
    }

    return 0;


}



