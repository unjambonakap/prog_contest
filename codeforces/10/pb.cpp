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

const int maxk=111;
int mp[maxk][maxk];
int cost[maxk][maxk+1];



int main(){
    int n, K; cin>>n>>K;
    string ans;
    memset(mp, 0, sizeof(mp));
    int mid=K/2;
    REP(i, K) FOR(j, 1, K) if (i+j<=K) REP(k, j) cost[i][j]+=abs(i+k-mid);
    REP(fuu, n){
        int m; cin>>m;
        int best=INT_MAX;
        int bestx, besty;

        REP(i, K){
            int cnt=0;
            REP(j, m) if (mp[i][j]) ++cnt;
            REP(j, K-m+1){
                if (!cnt){
                    int nc=m*abs(mid-i)+cost[j][m];
                    if (nc<best) best=nc, bestx=j, besty=i;
                }
                cnt+=mp[i][j+m]-mp[i][j];
            }

        }
        if (best==INT_MAX) ans+="-1\n";
        else{
            REP(i, m) mp[besty][bestx+i]=1;
            ans+=toStr(besty+1)+" "+toStr(bestx+1)+" "+toStr(bestx+m)+"\n";
        }
    }
    cout<<ans<<endl;
    return 0;
}


