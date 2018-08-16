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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxm=11;
const int maxn=1005+maxm;
const int mod=1e9+9;

set<string> s;
int n;
int dp[maxn][maxm][101];
pii next[101][maxm][4];
map<string, int> mp;
string rmp[101];
const char *vx="AGCT";


int solve(int p, int a, int x){

    if (p==n) return a==rmp[x].length();
    int &r=dp[p][a][x];
    if (r!=-1) return r;
    r=0;
    REP(k, 4){
        if (next[x][a][k].ST==-2);
        else if (next[x][a][k].ST!=-1) r=(r+solve(p+1, next[x][a][k].ST, next[x][a][k].ND))%mod;
        else{
            string sa=rmp[x];
            string nsa=vx[k]+sa;
            nsa=vx[k]+sa;
            int fd=0;
            REP(j, a+1){
                if (mp.count(nsa)){
                    string tmp=nsa;
                    int na=a-j;
                    for (; j<a+1; ++j){
                        if (s.count(tmp)){ na=nsa.length(); break;}
                        tmp.resize(tmp.size()-1);

                    }
                    next[x][a][k]=MP(na, mp[nsa]);
                    r=(r+solve(p+1, na, mp[nsa]))%mod;
                    fd=1;
                    break;
                }
                nsa.resize(nsa.size()-1);
            }
            if (!fd) next[x][a][k]=MP(-2, -2);
        }
    }
    return r;
}


int main(){
    int m;
    cin>>n>>m;

    int pos=1;
    rmp[0]=""; mp[string()]=0;
    memset(dp, -1, sizeof(dp));

    REP(i, m){
        string sa; cin>>sa;
        reverse(ALL(sa));
        s.insert(sa);
        REP(j, sa.length()){ rmp[pos]=sa.substr(j); mp[rmp[pos]]=pos++; }
    }
    REP(i, 101) REP(j, maxm) REP(k, 4) next[i][j][k]=MP(-1, -1);

    int res=solve(0, 0, 0);
    printf("%d\n", res);


    return 0;
}


