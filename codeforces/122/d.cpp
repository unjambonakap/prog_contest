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

const int maxn=333333;
const int inf=1e9;

int a[maxn], perm[maxn];
int n;

struct node{
    int T, H;
    int na[2], va[2];
    node *l, *r;
    int S;

    node(int t, int h){
        na[0]=1; va[0]=3;
        na[1]=0; va[1]=inf;
        S=0;

        T=t; H=h;
        l=r=0;
        if (T+1==H) return;
        l=new node(t,t+h>>1);
        r=new node(t+h>>1,h);
        update();
    }


    void update(){
        if (!l) return;
        for (int i=0,j=0,k=0; k<2; ++k){
            int lv=l->va[i]+l->S, rv=r->va[j]+r->S;
            if (lv<rv) va[k]=lv, na[k]=l->na[i], ++i;
            else if (lv>rv) va[k]=rv, na[k]=r->na[j], ++j;
            else va[k]=lv, na[k]=l->na[i]+r->na[j], ++i, ++j;
        }
    }

    void add(int a, int b, int v){
        if (a<=T && b>=H){S+=v; return;}
        if (b<=T || a>=H) return;
        l->add(a,b,v);
        r->add(a,b,v);
        update();
    }

};

int main(){
    cin>>n;
    REP(i,n) scanf(" %d", perm+i), --perm[i], a[perm[i]]=i;
    ll res=0;
    node r(0,n);
    for (int i=n-1; i>=0; --i){
        r.add(i,i+1,-3);//start on 2 >> go on 1
        r.add(i,n,1);
        for (int u=-1; u<=1; u+=2) if (a[i]+u>=0 && a[i]+u<n && perm[a[i]+u]>i) r.add(perm[a[i]+u],n,-1);
        REP(i,2) if (r.va[i]+r.S<=2) res+=r.na[i];
    }
    cout<<res-n<<endl;
    return 0;
}

