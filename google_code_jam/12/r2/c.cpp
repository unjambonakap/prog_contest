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

const int maxn=2222;
const int maxv=1e9;
const double pi=acos(-1);

int next[maxn];
int res[maxn];
int n;

ll crossp(ll a, ll b, ll c, ll d){return a*d-b*c;}
int checkit2(int x){
    REP(i,n-1) if (i==x){
        int besta=-1;
        FOR(j,i+1,n) if (besta==-1 || crossp(besta-i,res[besta]-res[i],j-i,res[j]-res[i])>0) besta=j;
        
        if (next[i]!=besta){
            printf("%d sees %d, shold %d\n", i,besta,next[i]);
            printf("FUUU %d %d %d\n",res[i], res[besta], res[next[i]]);
            return 0;
        }
    }

    return 1;
}


void go(int a, int b, int v, vi lst, vi lst2){
    if (a+1==b) return;
    assert(v>=0);
    int u=0;
    FOR(i,a+1,b){
        if (next[i]==b && u<=i){
            int T=0, H=maxv, best=-1;
            while(T<=H){
                int M=T+H>>1;
                int ok=1;
                REP(j,lst.size()){
                    int f=lst[j];
                    if (crossp(b-i,res[b]-M,f-i,res[f]-M)>0){ok=0; break;}
                }
                if (ok) REP(j,lst2.size()){
                    int f=lst2[j], nf=next[f];
                    if (crossp(nf-f,res[nf]-res[f],i-f,M-res[f])>0){ok=0; break;}
                }
                if (ok) T=M+1, best=M;
                else H=M-1;
            }

            //printf("ON %d\n", i);
            //REP(j,lst.size()) printf("%d ", res[lst[j]]); puts("");
            //REP(j,lst2.size()) printf("%d ", res[lst2[j]]); puts("");
            //REP(j,lst2.size()) printf("%d ", next[lst2[j]]); puts("");
            //printf(">>> %d\n", res[26]);
            //out(lst);
            //out(lst2);
            //printf("%d %d %d\n",res[64],res[65], res[77]);

            assert(best!=-1);
            best-=2;
            res[i]=best;
            assert(best>=0);


            lst2.pb(i);
            go(i,b,best,lst,lst2);
            lst2.pop_back();

            lst.pb(b);
            go(a,i,best-1,lst,lst2);
        }
        u=max(u,next[i]);
    }
}

int checkit(){
    REP(i,n-1){
        int besta=-1;
        FOR(j,i+1,n) if (besta==-1 || crossp(besta-i,res[besta]-res[i],j-i,res[j]-res[i])>0) besta=j;
        
        if (next[i]!=besta){
            printf("%d sees %d, shold %d\n", i,besta,next[i]);
            printf("FUUU %d %d %d\n",res[i], res[besta], res[next[i]]);
            return 0;
        }
    }

    return 1;
}
void gen(int a, int b){
    if (a>=b) return;
    if (a+1==b){next[a]=b; return;}
    int x=a+1+rand()%(b-a);
    next[a]=x;
    gen(a+1,x);
    gen(x,b);
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        //start:
        //n=2000;
        //gen(0,n-1);
        cin>>n;
        REP(i,n-1) scanf(" %d", next+i), --next[i];

        int ok=1;
        memset(res,-1,sizeof(res));
        REP(i,n-1) for (int j=i+1; j<next[i]; ++j) if (next[j]>next[i]) ok=0;

        for (int i=0; i!=n-1; ){
            int ni=next[i];
            res[i]=res[ni]=maxv;
            go(i,ni,maxv,vi(),vi());
            i=ni;
        }
        //if (!ok) goto start;


        printf("Case #%d:", ti+1);
        if (ok){
            REP(i,n) printf(" %d", res[i]); puts("");
            assert(checkit());
            //if (!checkit()) return 0;
        }
        else puts(" Impossible");
        //goto start;
    }
    return 0;
}

