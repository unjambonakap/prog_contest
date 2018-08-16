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

const int maxs=3e6;
const int maxn=5;
const double eps=1e-9;

map<int,int> rmp;
int U;
int xx[maxs][maxn];
double px[maxs];
int n,k;
int ao[maxn];
int q[maxs], na,ne;
int dx[maxs];
double res[maxn];

int add(int *a){
    int h=0;
    REP(i,n) h=51*h+a[i];
    if (rmp.count(h)) return rmp[h];
    REP(i,n) xx[U][i]=a[i];
    q[ne++]=U;
    return rmp[h]=U++;
}

int main(){
    while(scanf(" %d%d",&n,&k)>0){
        REP(i,n) scanf(" %d",ao+i), k-=ao[i];

        memset(res,0,sizeof(res));
        memset(px,0,sizeof(px));

        U=0; rmp.clear();
        na=ne=0;
        q[ne++]=add(ao);
        dx[0]=0; px[0]=1;

        while(na<ne){
            int sx=q[na++];
            int *a=xx[sx];
            double p=px[sx];
            if (p<eps) continue;

            if (dx[sx]==k){
                int mx=0, cnt=0;

                REP(i,n){
                    if (mx<a[i]) mx=a[i], cnt=0;
                    if (mx==a[i]) ++cnt;
                }
                REP(i,n) if (mx==a[i]) res[i]+=p/cnt;
                continue;
            }

            int ss=0;
            REP(i,n) ss+=a[i];
            REP(i,n){
                ++a[i];
                int b=add(a);
                dx[b]=dx[sx]+1;
                --a[i];
                px[b]+=p*a[i]/ss;
            }
        }

        REP(i,n) printf("pub %d: %.2lf %%\n",i+1,res[i]*100);

    }

    return 0;
}

