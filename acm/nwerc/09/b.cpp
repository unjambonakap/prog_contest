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


const int maxn=55555;
const int P=1e6+37;

char buf[1111111];
char res[1111111];
int pw[maxn];
int m,n;
int X,Y,pos;
char *c,*end;

int rmp[555555];
char tmp[11];

map<ll,int> h;

int get(int a){
    if (rmp[a]==-1) rmp[a]=X++;
    return rmp[a];
}


struct node{
    ll H, nx, aa;
    node *l,*r;
    void go();
    void build();
}tb[maxn];

node *getnode(){return tb+Y++;}
void node::go(){
    aa=0; l=r=0;
    H=0; nx=1;
    while(c!=end && *c>='a' && *c<='z') aa=27*aa+(*c-'a'+1), ++c;
    H=aa;

    if (c==end || *c!='('){
        if (!h.count(H)) h[H]=this-tb;
        return;
    }

    ++c;
    l=getnode(); r=getnode();
    l->go(); ++c;
    r->go(); ++c;

    H=l->H*pw[r->nx+1]+r->H*P+aa;
    nx=r->nx+l->nx+1;
    if (!h.count(H)) h[H]=this-tb;
}

void node::build(){
    int v=h[H];
    if (v<0) printf("%d",-v);
    else{
        h[H]=-(++pos);
        int nu=0;
        int x=aa;
        while(x) tmp[nu++]=x%27+'a'-1, x/=27;
        for (; nu; --nu) printf("%c",tmp[nu-1]);

        if (!l) return;
        printf("(");
        l->build();
        printf(",");
        r->build();
        printf(")");
    }
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %s",buf);
        n=strlen(buf);
        h.clear();
        memset(rmp,-1,sizeof(rmp));
        pw[0]=1;
        REP(i,maxn-1) pw[i+1]=pw[i]*P;

        Y=X=0;
        end=buf+n; c=buf;

        getnode()->go();
        pos=0;
        tb->build();
        puts("");

    }

    return 0;
}

