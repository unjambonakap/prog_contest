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


const int maxn=two(17);
ll tree[2*maxn][5];
int cnt[2*maxn];


void upd(int a){
    int l=2*a, r=l+1;
    cnt[a]=cnt[l]+cnt[r];
    REP(i, 5) tree[a][i]=tree[l][i]+tree[r][(i-cnt[l]%5+5)%5];
    if (a>1) upd(a/2);

}
 
map<int, int> rmp;
int main(){
    int n;
    cin>>n;
    vector<pii> q;
    memset(cnt, 0, sizeof(cnt));
    memset(tree, 0, sizeof(tree));
    REP(i, n){
        string s; cin>>s;
        if (s[0]=='s') q.pb(MP(2, 0));
        else{
            int a; cin>>a;
            rmp[a]=0;
            q.pb(MP(s[0]=='d', a));
        }
    }
    int pos=0;
    FE(it, rmp) it->ND=pos++;
    REP(i, q.size()){
        if (q[i].ST==2) cout<<tree[1][2]<<endl;
        else{
            int v=rmp[q[i].ND];
            int id=maxn+v;
            cnt[id]=1^q[i].ST;
            tree[id][0]=q[i].ND*cnt[id];
            upd(id/2);
        }
    }


}


