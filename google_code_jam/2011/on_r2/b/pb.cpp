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

const int maxn=13;
int mp[maxn][maxn];
int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int r, c, d;
        cin>>r>>c>>d;
        getchar();
        REP(i, r){
            string s;
            cin>>s;
            REP(j, c) mp[i][j]=s[j]-'0';
        }
        int res=0;
        FOR(i, 1, r-2) FOR(j, 1, c-2){
            ll vx, vy;
            int md=min(i, j);
            checkmin(md, r-1-i);
            checkmin(md, c-1-j);
            for (int k=1; k<=md; ++k){
                vx=vy=0;
                FOR(u, i-k, i+k){
                    int tmp=(u==i-k || u==i+k);
                    FOR(v, j-k+tmp, j+k-tmp){
                        vx+=(mp[u][v])*(i-u);
                        vy+=(mp[u][v])*(j-v);
                    }
                }
                if (!vx && !vy){
                    printf("on %d %d\n", i, j);
                    checkmax(res, 2*k+1);
                }
            }
        }
        FOR(i, 1, r-3) FOR(j, 1, c-3){
            ll vx, vy;
            int md=min(i, j)+1;
            checkmin(md, r-1-i);
            checkmin(md, c-1-j);
            for (int k=2; k<=md; ++k){
                vx=vy=0;
                FOR(u, i-k+1, i+k){
                    int tmp=(u==i-k+1 || u==i+k);
                    FOR(v, j-k+tmp+1, j+k-tmp){
                        vx+=(mp[u][v])*(1+2*(i-u));
                        vy+=(mp[u][v])*(1+2*(j-v));
                    }
                }
                if (!vx && !vy) checkmax(res, 2*k);
            }
        }
        printf("Case #%d:", ti);
        if (res==0) printf(" IMPOSSIBLE");
        else printf(" %d", res);
        printf("\n");

    }
    return 0;

}



