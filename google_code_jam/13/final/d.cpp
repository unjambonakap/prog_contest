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

const int maxn=1e5+10;
const int maxd=4;
const int maxv=maxn*maxd;
const int maxx=1e8;

int n,d;
int tb[maxn][maxd];

int l,r;
void eval(int a, int b){ if (b-a>r-l || (b-a==r-l && a<l)) l=a, r=b; }


struct data{
    vi lst;
    int st;
};

int cmp(const vi &a, const vi &b){
    int j=0;
    REP(i,a.size()){
        for(; j<b.size() && b[j]!=a[i]; ++j);
        if (j==b.size()) return -1;
    }
    return a.size()==b.size();
}

void add(data x, vector<data> &u){

    sort(ALL(x.lst));
    REP(uu,u.size()){
        data &y=u[uu];
        vi &l1=x.lst, &l2=y.lst;

        int tmp=cmp(y.lst,x.lst);
        if (tmp==1){
            y.st=min(y.st,x.st);
            return;
        }else if (tmp==0) if (y.st<=x.st) return;
    }
    u.pb(x);
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        l=r=0;

        int K;
        cin>>n>>d>>K;
        vi lst;
        REP(i,n) REP(j,d) scanf(" %d",tb[i]+j);

        vector<data> u,nu;
        REP(i,n){
            vi fd(u.size(),0);

            REP(uu,u.size()){
                data &x=u[uu];
                REP(k,d) REP(j,x.lst.size()) if (x.lst[j]==tb[i][k]){nu.pb(x); fd[uu]=1; goto out;}
out:;
            }

            REP(k,d){
                data tmp;
                tmp.lst.pb(tb[i][k]);
                tmp.st=i;
                add(tmp,nu);
            }

            REP(uu,u.size()) if (!fd[uu]){
                data &x=u[uu];
                if (x.lst.size()==K) continue;
                REP(k,d){
                    x.lst.pb(tb[i][k]);
                    add(x,nu);
                    x.lst.pop_back();
                }
            }

            u=nu;
            nu.clear();

            REP(uu,u.size()) eval(u[uu].st,i);
        }

        assert(r<n);
        printf("Case #%d: %d %d\n",ti+1,l,r);
    }
    return 0;

}

