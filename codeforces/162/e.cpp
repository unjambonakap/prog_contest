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

const int maxb=18;
const int maxn=2<<maxb;
const int maxh=13;

int tree[maxn];
int tree2[maxn];
int last[maxn];
int h[maxn];
int n;

int my[maxn];

void update(int *tree, int a, int v){
    a+=1<<maxb;
    tree[a]=v;
    for (; a; a>>=1) tree[a>>1]=max(tree[a],tree[a^1]);
}

int query(int *tree, int a){
    a+=1<<maxb;
    int res=tree[a];
    for (; a>1; a>>=1) if (!(a&1)) res=max(res,tree[a^1]);
    return res;
}

int main(){
    int nq; cin>>n>>nq;
    set<int> have;

    memset(my,-1,sizeof(my));
    REP(t,nq){
        int type,a,b;
        scanf(" %d%d",&type,&a);
        if (type==1){
            scanf(" %d",&b);
            b=(1<<maxb)-t+b-maxh;
            h[a]=b;

            for (int i=0; i<maxh; ++i) if (my[b-i]!=-1) update(tree,my[b-i],0);
            my[b]=a;
            for (int i=0; i<maxh; ++i){
                int x=my[b-i];
                if (x==-1) continue;
                int v=query(tree,x)+1;
                update(tree,x,v);
                update(tree2,b-i,v);
            }
            have.insert(a);
        }else{


            set<int>::iterator it=have.begin(), it2;
            REP(i,a) update(tree2,h[*it++],0);
            --it;
            
            my[h[*it]]=-1;
            update(tree,*it,0);

            it2=it; --it;
            have.erase(it2);
            REP(i,a-1){
                int v=query(tree2,h[*it])+1;
                update(tree2,h[*it],v);
                update(tree,*it,v);
                --it;
            }
        }
        printf("%d\n",tree[1]);
    }
    return 0;
}

