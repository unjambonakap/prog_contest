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

const int mod=777777777;

const int maxn=1e5;
int M[3][3];
int n;

void mul(int a[][3], int b[][3], int c[][3]){
    REP(i,3) REP(j,3){
        ll v=0;
        REP(k,3) REP(l,3) if (M[k][l]) v=v+1ll*b[i][k]*c[l][j];
        a[i][j]=v%mod;
    }
}


struct node{
    int T,H;
    int tsf[3][3];
    int val;

    node *l,*r;
    node(int a, int b){
        l=r=0;
        T=a; H=b;

        if (T+1==H){
            val=0;
            memset(tsf,0,sizeof(tsf));
            REP(k,3) tsf[k][k]=1;
            return;
        }

        l=new node(a,a+b>>1);
        r=new node(a+b>>1,b);
        update();
    }
    void update(){ mul(tsf,l->tsf,r->tsf); }

    void update(int a, int b){
        if (a<T || a>=H) return;
        if (T+1==H){
            memset(tsf,0,sizeof(tsf));
            if (b==0) REP(k,3) tsf[k][k]=1;
            else tsf[b-1][b-1]=1;
            return;
        }
        l->update(a,b);
        r->update(a,b);
        update();

    }

    int count(){
        ll res=0;
        REP(i,3) REP(j,3) res+=tsf[i][j];
        return res%mod;
    }

};

int main(){
    int nq;
    while(scanf(" %d%d",&n,&nq)>0){
        REP(i,3) REP(j,3) scanf(" %d",M[i]+j);
        node root(0,n);

        REP(i,nq){
            int a,b; scanf(" %d%d",&a,&b);
            --a;
            root.update(a,b);
            printf("%d\n",root.count());
        }
    }
    return 0;

}

