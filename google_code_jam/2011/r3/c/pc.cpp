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

const int maxr=101;
const int maxn=maxr*maxr;
const int mod=1000003;

int r, c;
int mp[maxr][maxr];
set<int> eo[maxn], ei[maxn];
int visited[maxn];





int vr[]={1, 0, 1, 1};
int vc[]={0, 1, 1, -1};
map<char, int> rmp;


int dfsa(int a, int b){
    //do not take edge a->b
    int x, y;
    x=*eo[a].begin();
    y=*++eo[a].begin();
    int c=(x==b?y:x);

    //printf("not take %d %d but %d %d\n", a, b, a, c);
    if (visited[a]!=-1) return visited[a]==c;

    visited[a]=c;
    x=*ei[c].begin();
    y=*++ei[c].begin();
    return dfsa(x==a?y:x, c);


}

int dfsb(int a, int b){
    //printf("take %d %d\n", a, b);
    //take edge a->b
    if (visited[a]!=-1) return visited[a]==b;
    visited[a]=b;

    int x, y;
    x=*ei[b].begin();
    y=*++ei[b].begin();
    int c=(x==a?y:x);

    x=*eo[c].begin();
    y=*++eo[c].begin();
    return dfsb(c, x==b?y:x);
}


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

        int n=r*c;
        REP(i, n) eo[i].clear();
        REP(i, n) ei[i].clear();
        REP(i, r) REP(j, c) for (int sgn=-1; sgn<=1; sgn+=2){
            int k=mp[i][j];
            int ra=(i+vr[k]*sgn+r)%r;
            int rb=(j+vc[k]*sgn+c)%c;
            int a=i*c+j, b=ra*c+rb;
            eo[a].insert(b);
            ei[b].insert(a);
        }
        memset(visited, 0, sizeof(visited));
        int fd=1;
        while(fd){
            fd=0;
            REP(i, n){
                if (eo[i].size()==1 && !bit_set(visited[i], 0)){
                    visited[i]|=1;
                    fd=1;
                    int a=*eo[i].begin();
                    ei[a].clear();
                    ei[a].insert(i);
                }
                if (ei[i].size()==1 && !bit_set(visited[i], 1)){
                    visited[i]|=2;
                    fd=1;
                    int a=*ei[i].begin();
                    if (eo[a].size()==2){
                        int b=*eo[a].begin();
                        if (b==i) b=*(++eo[a].begin());
                        eo[a].erase(b);
                        ei[b].erase(a);
                    }
                }
            }
        }
        memset(visited, -1, sizeof(visited));
        int cnt=1;
        REP(i, n) if (visited[i]==-1){
            if (eo[i].size()==0){cnt=0; break;}
            if (eo[i].size()==2){
                if (!dfsa(i, *eo[i].begin())){assert(0);cnt=0; break;}
                if (!dfsb(i, *++eo[i].begin())){assert(0);cnt=0; break;}
                cnt=cnt*2%mod;
            }
        }

        //REP(i, r){ REP(j, c) printf("%d ", ei[i*c+j].size()); printf("\n"); }
        //REP(i, r){ REP(j, c) printf("%d ", eo[i*c+j].size()); printf("\n"); }
        //REP(i, r) REP(j, c) FE(it, eo[i*c+j]) printf("%d %d => %d %d\n", i, j, *it/c, *it%c);
        //REP(i, n) assert(ei[i].size()<=2);





out:


        printf("Case #%d: %d\n", ti, cnt);

    }
    return 0;

}



