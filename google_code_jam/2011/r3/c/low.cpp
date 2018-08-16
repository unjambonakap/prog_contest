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

const int maxr=12;
const int mod=1000003;

int r, c;
int mp[maxr][maxr];
int graph[maxr*maxr][maxr*maxr];
int deg[maxr*maxr];


int parent[maxr*maxr];
int root(int a){return (parent[a]==-1?a:parent[a]=root(parent[a]));}



int vr[]={1, 0, 1, 1};
int vc[]={0, 1, 1, -1};
map<char, int> rmp;

int main(){
    int tn;
    rmp['/']=3; rmp['|']=0; rmp['-']=1;
    rmp['\\']=2;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>r>>c;
        getchar();
        REP(i, r){
            string s;
            getline(cin, s);
            REP(j, c) mp[i][j]=rmp[s[j]];
        }

        if (ti!=1)continue;
        memset(graph, 0, sizeof(graph));
        memset(deg, 0, sizeof(deg));
        memset(parent, -1, sizeof(parent));
        REP(i, r) REP(j, c) for (int sgn=-1; sgn<=1; sgn+=2){
            int k=mp[i][j];
            int ra=(i+vr[k]*sgn+r)%r;
            int rb=(j+vc[k]*sgn+c)%c;
            int a=i*c+j, b=ra*c+rb;
            graph[a][b]=1;
            if (root(a)!=root(b)) parent[root(a)]=root(b);
            ++deg[b];
        }
        int n=r*c;
        int ok=1;
        int cnt=0;
        REP(i, n) if (deg[i]==0){ok=0; break;}
        if (ok){
            cnt=1;
            REP(i, n) if (parent[i]==-1){
                ll cnta=0;
                REP(j, n) if (root(j)==i) ++cnta;
                if (cnta==2) cnta*=2;
                cnt=cnt*cnta*2%mod;



            }

        }


        printf("Case #%d: %d", ti, cnt);
        printf("\n");

    }
    return 0;

}



