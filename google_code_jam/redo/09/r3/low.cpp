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

const int maxn=1100;
const int maxr=15;
int n;
set<int> mp[maxr];
map<pii, int> rmp;
int x[maxn], y[maxn];
char col[maxn];
int graph[maxn][maxn];

char ubit(char a, char b){ return (a|b)^b; }

struct cmpA{ bool operator()(int a, int b)const{return x[a]>x[b];} };

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>n;
        REP(i, maxr) mp[i].clear();
        rmp.clear();
        REP(i, n){
            cin>>x[i]>>y[i];
            --y[i]; --x[i];
            rmp[MP(x[i], y[i])]=i;
            mp[y[i]].insert(x[i]);
        }


        int ym[maxr];
        int ny=0;
        int res=1;
        REP(i, maxr) if (mp[i].size()){
            if (i<maxr-1 && mp[i+1].size()){res=-1; break;}
            if (mp[i].size()>=2){res=-1; break;}
        }
        if (res==1) goto out;

        

        memset(graph, 0, sizeof(graph));
        REP(i, n){
            if (mp[y[i]].lower_bound(x[i]+1)!=mp[y[i]].end()){
                int j=rmp[MP(*mp[y[i]].lower_bound(x[i]+1), y[i])];;
                graph[i][j]=graph[j][i]=1;
            }
            if (y[i]>0 && mp[y[i]-1].lower_bound(x[i]+1)!=mp[y[i]-1].end()){
                int j=rmp[MP(*mp[y[i]-1].lower_bound(x[i]+1), y[i]-1)];
                graph[i][j]=graph[j][i]=1;
            }
            if (y[i]<maxr-1 && mp[y[i]+1].lower_bound(x[i]+1)!=mp[y[i]+1].end()){
                int j=rmp[MP(*mp[y[i]+1].lower_bound(x[i]+1), y[i]+1)];
                graph[i][j]=graph[j][i]=1;
            }
        }
        res=2;
        REP(i, n){
            int cnta=0, cntb=0;
            REP(j, n) if (y[j]==y[i]-1 && graph[i][j]) ++cnta; else if (y[j]==y[i]+1 && graph[i][j]) ++cntb;
            if (cnta>=2 || cntb>=2) {res=-1; break;}

        }
        if (res==2) goto out;
        res=4;
        REP(i, maxr) if (mp[i].size()) ym[ny++]=i;

        REP(m, two(ny)){
            memset(col, two(3)-1, sizeof(col));
            priority_queue<int, vi, cmpA> q;
            int no=rmp[MP(*mp[ym[0]].begin(), ym[0])];


            REP(i, n) q.push(i);
            col[no]=1;
            REP(j, n) if (graph[no][j]) col[j]=ubit(col[j], col[no]);
            

            REP(i, ny) if (i){
                no=rmp[MP(*mp[ym[i]].begin(), ym[i])];

                if (m&two(i)) col[no]=low_bit(col[no]);
                else col[no]=col[no]^low_bit(col[no]);
                assert(col[no]);

                col[no]=low_bit(col[no]);
                REP(j, n) if (graph[no][j]) col[j]=ubit(col[j], col[no]);
                
            }

            int fd=1;
            while(!q.empty()){
                int no=q.top(); q.pop();
                if (col[no]==0) {fd=0; break;}
                int fda=0;
                REP(k, 3) if (col[no]&two(k)){
                    int ok=1;
                    REP(j, n) if (graph[no][j] && ubit(col[j], two(k))==0){ok=0; break;}
                    if (ok){ col[no]=two(k); fda=1; break;}
                }
                if (!fda){fd=0; break;}
                REP(j, n) if (graph[no][j]) col[j]=ubit(col[j], col[no]);
            }



            if (fd){res=3; break;}
        }

out:
        printf("Case #%d: %d\n", ti, res);

    }
    return 0;

}




