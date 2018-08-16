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


const int maxn=25;
const int maxm=1e6+11;

int n;
char buf[maxn+11];

int cost[maxn];
vector<int> options[maxn];
int res[maxn][maxn];


int main(){
    cin>>n;
    REP(i,n){
        int m; cin>>m;
        REP(j,m){
            scanf(" %s", buf);
            int x=strlen(buf);
            int u=0;
            REP(k,x) u|=1<<(buf[k]-'a');
            options[i].push_back(u);
        }
    }


    REP(i,n){
        memset(cost,-1,sizeof(cost));
        cost[i]=0;
        queue<int> can;
        can.push(i);

        int curmask=0;

        while(can.size()){
            int a=can.front(); can.pop();
            curmask|=1<<a;

            REP(j,n) if (cost[j]==-1){
                int has=0;
                REP(k,options[j].size()) if ((options[j][k]&curmask)==options[j][k]) {has=1; break;}
                if (!has) continue;

                can.push(j);
                cost[j]=cost[a]+1;
            }
        }
        REP(j,n) res[i][j]=cost[j];
    }
    REP(i,n) REP(j,n) printf("%d%c",res[j][i]," \n"[j==n-1]);

    return 0;
}

