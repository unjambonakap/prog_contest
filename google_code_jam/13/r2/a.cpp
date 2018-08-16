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
typedef unsigned char uchar;
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

const int mod=1000002013;
const int maxm=1111;
int n,m;

int cost(int a){
    return (1ll*a*(n-a+1)+1ll*a*(a-1)/2)%mod;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n>>m;
        vector<pair<int,pii> > el;

        int tot=0;
        REP(i,m){
            int a, b, c;
            scanf(" %d%d%d",&a,&b,&c);
            tot=(tot+1ll*cost(b-a)*c)%mod;

            el.pb(MP(a,MP(0,c)));
            el.pb(MP(b,MP(1,c)));
        }
        sort(ALL(el));
        priority_queue<pii> q;
        
        int res=0;
        REP(i,el.size()){
            if (el[i].ND.ST==0) q.push(MP(el[i].ST,el[i].ND.ND));
            else{
                int need=el[i].ND.ND;
                int u=el[i].ST;
                while(need){
                    pii a=q.top(); q.pop();
                    int x=min(a.ND,need);
                    need-=x;
                    a.ND-=x;
                    if (a.ND) q.push(a);
                    
                    int v=1ll*cost(u-a.ST)*x%mod;
                    res=(res+v)%mod;
                }
            }
        }


        printf("Case #%d: ",ti+1);
        printf("%d\n",(mod+tot-res)%mod);
    }
    return 0;
}


