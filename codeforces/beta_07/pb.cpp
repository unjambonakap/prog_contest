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

const int maxn=111;
int mem[maxn];
int pos[maxn];
int id[maxn];
int len[maxn];
int main(){
    memset(pos, -1, sizeof(pos));
    memset(mem, 0, sizeof(mem));
    int m, t;
    cin>>t>>m;
    int cnt=1;

    REP(ti, t){
        string s; cin>>s;
        if (s=="alloc"){
            int n; cin>>n;
            REP(i, m-n+1){
                int fd=1;
                REP(j, n) if (mem[i+j]){fd=0; break;}
                if (fd){
                    REP(j, n) mem[i+j]=1;
                    pos[cnt]=i;
                    len[i]=n;
                    id[i]=cnt++;
                    printf("%d\n", id[i]);
                    goto done;
                }
            }
            printf("NULL\n");
done:;
        }else if (s=="erase"){
            int x; cin>>x;
            if (x<0 || x>=cnt || pos[x]==-1) printf("ILLEGAL_ERASE_ARGUMENT\n");
            else{
                int n=len[pos[x]];
                REP(i, n) mem[pos[x]+i]=0;
                pos[x]=-1;
            }
        }else{
            int prev=0;
            for (int i=0; i<m;){
                if (mem[i]){
                    if (prev<i){
                        id[prev]=id[i]; 
                        assert(id[i]!=-1);
                        pos[id[i]]=prev;
                        REP(j, len[i]) mem[i+j]=0, mem[prev+j]=1;
                        len[prev]=len[i];
                        id[i]=-1;

                    }
                    prev+=len[i];
                    i+=len[i];
                }else ++i;
            }

        }

    }


}
