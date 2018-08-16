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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxr=80;
int r, c;
int na, nb;

int match[maxr*maxr/2];
int visited[maxr*maxr/2];
int graph[maxr*maxr/2][maxr*maxr/2];
int mp[maxr][maxr];
int id(int i, int j){return (j/2)*r+i;}


int dfs(int a){
    if (visited[a]) return 0;
    visited[a]=1;
    REP(i, nb) if (graph[a][i] && (match[i]==-1 || dfs(match[i]))){
        match[i]=a;
        return 1;

    }

    return 0;
}
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>r>>c;
        REP(i, r){
            string s;
            cin>>s;
            REP(j, c) mp[i][j]=(s[j]=='.');
        }
        memset(graph, 0, sizeof(graph));
        int res=0;
        REP(i, r) REP(j, c) if (mp[i][j]){
            ++res;
            if (j%2){
                if (j){
                    if (i && mp[i-1][j-1]) graph[id(i-1, j-1)][id(i, j)]=1;
                    if (mp[i][j-1]) graph[id(i, j-1)][id(i, j)]=1;
                }
                if (j+1<c){
                    if (i && mp[i-1][j+1]) graph[id(i-1, j+1)][id(i, j)]=1;
                    if (mp[i][j+1]) graph[id(i, j+1)][id(i, j)]=1;
                }
            }else{
                if (j){
                    if (i && mp[i-1][j-1]) graph[id(i, j)][id(i-1, j-1)]=1;
                    if (mp[i][j-1]) graph[id(i, j)][id(i, j-1)]=1;
                }
                if (j+1<c){
                    if (i && mp[i-1][j+1]) graph[id(i, j)][id(i-1, j+1)]=1;
                    if (mp[i][j+1]) graph[id(i, j)][id(i, j+1)]=1;
                }
            }

        }
        na=r*((c+1)/2);
        nb=r*(c/2);
        memset(match, -1, sizeof(match));
        REP(i, r) for (int j=0; j<c; j+=2) if (mp[i][j]){
            memset(visited, 0, sizeof(visited));
            if (dfs(id(i, j))) --res;
        }
        printf("Case #%d: %d\n", ti, res);
    }
    return 0;

}


