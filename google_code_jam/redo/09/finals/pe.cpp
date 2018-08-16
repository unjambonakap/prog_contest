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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=510;
const int inf=1e5;
int n;
int pos;
map<string, int> rmp;
int st[maxn], nd[maxn];
int data[2*maxn];
int graph[maxn][maxn];
int mark[maxn];

int mem[2*maxn][maxn];

int dfsa(int a, int m){
    if (mark[a]==-1) mark[a]=m;
    else return mark[a]==m;
    REP(i, n) if (graph[a][i] && !dfsa(i, m^1)) return 0;
    return 1;
}

int proc(int p, int d){
    if (p==2*n) return 0;
    int &r=dp[p][d];
    if (r!=-1) return r;
    r=inf;

    int a=data[p];
    int b=data[p+1];
    if (a==b) return r=(d?0:1);

    ++p;
    while(1){
        if (graph[a][b]){

        }else{

        }
    }


    return r;

}


int solve(){
    memset(mark, -1, sizeof(mark));
    REP(i, n) if (mark[i]==-1 && !dfsa(i, 0)) return -1;
    int ans=inf;
    memset(mem, -1, sizeof(mem));
    REP(i, n+1) checkmin(ans, i+proc(0, i));
}


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        pos=0;
        rmp.clear();
        cin>>n;
        REP(i, 2*n){
            string s;
            cin>>s;
            if (rmp.count(s)) nd[rmp[s]]=i;
            else st[rmp[s]=pos++]=i;
            data[i]=rmp[s];
        }
        memset(graph, 0, sizeof(graph));

        REP(i, n) REP(j, n) if (st[i]<st[j] && nd[i]>st[j] && nd[i]<nd[j]) graph[i][j]=graph[j][i]=1;

        int res=solve();
        printf("Case #%d: %d\n", ti, res);
    }

    return 0;
}


