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
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

pii& operator+=(pii &a, const pii &b){a.ST+=b.ST, a.ND+=b.ND; return a;}
pii operator-(const pii &a, const pii &b){pii c=a; c.ST-=b.ST, c.ND-=b.ND ; return c;}
pii operator+(const pii &a, const pii &b){pii c=a; c.ST+=b.ST, c.ND+=b.ND ; return c;}

const int maxn=1e5+10;

int type[maxn];
int next[maxn];
int visited[maxn];
int cycle[maxn];
vi e[maxn];

pii mem[maxn][2][2];
int seen[maxn][2][2];
int sc;





int res[maxn];
pii fx(int a, int b){return MP(1, type[a]^type[b]); }

int dfs(int a){
    if (visited[a]) return a;
    visited[a]=1;
    return dfs(next[a]);
}

void dfsa(int a){
    if (visited[a]==2) return;
    visited[a]=2;
    FE(it, e[a]) dfsa(*it);
}


void dfsb(int a, int p){
    if (a==p) return;
    cycle[a]=1;
    dfsb(next[a], p==-1?a:p);
}

pii proc(int a, int f, int p, int fa){
    if (a==sc && p) return MP(fa&&f?-2:0, 0);
    if (seen[a][f][fa]) return mem[a][f][fa];
    seen[a][f][fa]=1;
    pii &r=mem[a][f][fa];
    r=MP(0, 0);


    if (cycle[a]){
        pii tmp=r;
        FE(it, e[a]) if (!cycle[*it]) tmp+=proc(*it, 0, 1, 0);
        r=tmp+proc(next[a], 0, 1, a==sc?0:fa);
        
        if (!f){
            checkmax(r, tmp+proc(next[a], 1, 1, a==sc?1:fa)+fx(a, next[a]));
            tmp+=proc(next[a], 0, 1, a==sc?1:fa);
            FE(it, e[a]) if (!cycle[*it]) checkmax(r, tmp-proc(*it, 0, 1, 0)+proc(*it, 1, 1, 0)+fx(a, *it));
        }
    }else{
        FE(it, e[a]) r+=proc(*it, 0, 1, 0);
        if (!f){
            pii tmp=r;
            FE(it, e[a]){
                pii nr=tmp-proc(*it, 0, 1, 0)+proc(*it, 1, 1, 0)+fx(a, *it);
                checkmax(r, nr);
            }
        }
    }
    //printf("%d %d %d =>> %d %d\n", a, f, fa, r.ST, r.ND);
    return r;
}

void build(int a, int f, int p, int fa){
    if (a==sc && p) return;
    pii ans=proc(a, f, p, fa);

    pii r=MP(0, 0);
    if (cycle[a]){
        pii tmp=r;
        FE(it, e[a]) if (!cycle[*it]) tmp+=proc(*it, 0, 1, 0);
        r=tmp+proc(next[a], 0, 1, a==sc?0:fa);
        if (r==ans){
            build(next[a], 0, 1, a==sc?0:fa);
            FE(it, e[a]) if (!cycle[*it]) build(*it, 0, 1, 0);
            return;
        }
        
        if (!f){
            if (ans==tmp+proc(next[a], 1, 1, a==sc?1:fa)+fx(a, next[a])){
                FE(it, e[a]) if (!cycle[*it]) build(*it, 0, 1, 0);
                res[a]=next[a];
                res[next[a]]=a;
                build(next[a], 1, 1, a==sc?1:fa);
                return;
            }
            tmp+=proc(next[a], 0, 1, a==sc?1:fa);
            FE(it, e[a]) if (!cycle[*it] && ans==tmp-proc(*it, 0, 1, 0)+proc(*it, 1, 1, 0)+fx(a, *it)){
                build(next[a], 0, 1, a==sc?1:fa);
                FE(ita, e[a]) if (!cycle[*ita] && *it!=*ita) build(*ita, 0, 1, 0);
                
                res[a]=*it;
                res[*it]=a;
                build(*it, 1, 1, 0);
                return;
            }
        }
    }else{
        FE(it, e[a]) r+=proc(*it, 0, 1, 0);
        if (r==ans){
            FE(it, e[a]) build(*it, 0, 1, 0);
            return;
        }
        if (!f){
            pii tmp=r;
            FE(it, e[a]){
                pii nr=tmp-proc(*it, 0, 1, 0)+proc(*it, 1, 1, 0)+fx(a, *it);
                if (nr==ans){
                    FE(ita, e[a]) if (*it!=*ita) build(*ita, 0, 1, 0);
                    res[*it]=a;
                    res[a]=*it;
                    build(*it, 1, 1, 0);
                    return;
                }
            }
        }
        assert(0);
    }
    //printf("%d %d %d =>> %d %d\n", a, f, fa, r.ST, r.ND);
    assert(0);
}


int main(){
    int n;
    cin>>n;
    REP(i, n){
        cin>>next[i]>>type[i];
        --type[i];
        --next[i];
        e[next[i]].pb(i);

    }

    memset(visited, 0, sizeof(visited));

    memset(seen, 0, sizeof(seen));
    memset(cycle, 0, sizeof(cycle));
    memset(res, -1, sizeof(res));

    pii tmp=MP(0, 0);
    REP(i, n) if (!visited[i]){
        sc=dfs(i);
        dfsa(sc);
        dfsb(sc, -1);
        pii ans=proc(sc, 0, 0, 0);
        build(sc, 0, 0, 0);
        tmp+=ans;
        //   printf("xx %d %d\n", tmp.ST, tmp.ND);
    }

    printf("%d %d\n", tmp.ST, tmp.ND);
    REP(i, n) if (i<res[i]) printf("%d %d\n", i+1, res[i]+1);
    return 0;

}



