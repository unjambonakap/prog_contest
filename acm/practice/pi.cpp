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



const int maxn=111111;
vi e[maxn];
int n;
int done[maxn];

int change(int a, int b, int c){
    REP(i, e[b].size()) if (e[b][i]==c){
        REP(j, e[b].size()) if (e[b][i]==a){swap(e[b][j], e[b][e[b].size()-1]); e[b].pop_back(); break;}
        return 1;
    }
    REP(j, e[b].size()) if (e[b][i]==a){e[b][j]=c; break;}
}

int main(){
    cin>>n;
    int m; cin>>m;
    REP(i, m){
        int a, b; scanf(" %d %d", &a, &b);
        e[a].pb(b);
        e[b].pb(a);
    }

    memset(done, 0, sizeof(done));
    queue<int> q;
    int resa=0, resb=0;
    REP(i, n){
        if (e[i].size()==0) done[i]=1, ++resa;
        if (e[i].size()<3) q.push(i), done[i]=1;
    }
    while(!q.empty()){
        int a=q.front(); q.pop();
        int x=e[a][0], y=e[a][1], z=e[a][2];
        change(a,x,y); 
        change(a,y,x);
        
        change(a,x,y); 
        change(a,y,x);

    }

    return 0;
}
