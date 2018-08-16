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

const int maxn=1<<11;
const int leaf=maxn>>1;
const int inf=1e9+10;

int A[maxn];

void checka(int &a, int b){if (b!=-1) if (a==-1 || A[a]>A[b]) a=b;}
void checkb(int &a, int b){if (b!=-1) if (a==-1 || A[a]<A[b]) a=b;}
struct segTree{
    segTree *l, *r;
    int T, H;
    int a, b;
    set<int> tmp;


    segTree():l(0),r(0){}
    void init(int x, int y){
        T=x; H=y;
        a=-1; b=-1;
        tmp.clear();
        l=r=0;
        if (T+1==H) return;
        l=new segTree();
        r=new segTree();
        l->init(T, (T+H)/2);
        r->init((T+H)/2, H);
    }
    void clear(){
        tmp.clear();
        if (l){
            l->clear(); r->clear();
            delete l; delete r;
        } 
        l=r=0;
    }
    void update(){
        if (!l){
            if (tmp.size())  a=b=*tmp.begin();
            else a=b=-1;
        }else{
            a=b=-1;
            checka(a, l->a); checka(a, r->a);
            checkb(b, l->b); checkb(b, r->b);
        }

    }

    void rem(int p){
        if (A[p]<T||A[p]>=H) return;
        if (!l) tmp.erase(p);
        else l->rem(p), r->rem(p);
        update();
    }

    void add(int p){
        if (A[p]<T||A[p]>=H) return;
        if (!l) tmp.insert(p);
        else l->add(p), r->add(p);
        update();
    }

    int querya(int x, int y){
        if (x>=H||y<=T) return -1;
        if (x<=T&&y>=H) return a;
        int u=l->querya(x,y);
        checka(u,r->querya(x,y));
        return u;

    }


    int queryb(int x, int y){
        if (x>=H||y<=T) return -1;
        if (x<=T&&y>=H) return b;
        int u=l->queryb(x,y);
        checkb(u,r->queryb(x,y));
        return u;
    }





};

segTree tree[5];

int rmp[5];
int res[5];
string B;

int cmp(int a, int b){return B[a]<B[b];}




int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        int n; cin>>n>>B;
        int fd=0;
        REP(i,n) scanf("%d", A+i);
        vi na;
        REP(i,n) na.pb(A[i]);
        sort(ALL(na));
        REP(i,n) A[i]=lower_bound(ALL(na), A[i])-na.begin();

        REP(i,5) rmp[B[i]-'1']=i;
        int x=0,y=2,z=4;
        REP(i,5) tree[i].clear(), tree[i].init(0, n);
        
        FOR(i,1,n-3){
            tree[x].add(i-1);
            res[1]=i;

            tree[y].clear(); tree[z].clear();
            tree[y].init(0,n); tree[z].init(0,n);

            FOR(j,i+2,n) tree[z].add(j);
            
            FOR(j,i+2,n-1){
                tree[z].rem(j);
                tree[y].add(j-1);
                if (A[i]>=A[j]) continue;
                res[3]=j;

                int fdl=-1, fdh=-1;
                int lp, hp;
                lp=0; hp=4;
                while(rmp[lp]&1) fdl=res[rmp[lp++]];
                while(rmp[hp]&1) fdh=res[rmp[hp--]];
                fdh=tree[rmp[hp]].queryb(fdh==-1?0:A[fdh],n);
                fdl=tree[rmp[lp]].querya(0,fdl==-1?n:A[fdl]);
                res[rmp[hp]]=fdh; res[rmp[lp]]=fdl;
                ++lp; --hp;
                if (fdh==-1||fdl==-1) continue;

                int ok=1;
                while(rmp[lp]&1){
                    if (A[fdl]>=A[res[rmp[lp]]]){ok=0; break;}
                    fdl=res[rmp[lp++]];
                }
                while(rmp[hp]&1){
                    if (A[fdh]<=A[res[rmp[hp]]]){ok=0; break;}
                    fdh=res[rmp[hp--]];
                }
                if (!ok)continue;
                fdl=res[rmp[lp]]=tree[rmp[lp]].querya(A[fdl]+1, A[fdh]);
                if (fdl!=-1){fd=1; goto done;}
            }
            
        }
done:
        if (fd) out(res,5);
        else puts("-1");
    }
    return 0;
}


