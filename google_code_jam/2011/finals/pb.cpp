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

const int maxr=21;
const int maxn=maxr*maxr;
const ll inf=2e16;
int r, c, n;
int vx[]={-1, 0, 1, 0}, vy[]={0, 1, 0, -1};

ll m;
int next[maxn][4];
ll mp[maxn];
ll wl[maxn];
int ne;
int el[4*maxr-4];
int visited[maxn];
int prev[maxn];


int in(int x, int y){return x>=0 && y>=0 && x<r && y<c;}

struct data{
    ll wl;
    int a;
    data(ll wl, int a):wl(wl), a(a){}
    bool operator<(const data &d)const{
        if (wl!=d.wl) return wl>d.wl;
        return a>d.a;
    }

};

int checkit(){ REP(i, n) if (mp[i]) return 1; return 0; }


ll doit(){

    ll res=0;
    int cnt=0;
    while(checkit()){
        priority_queue<data> q;
        memset(visited, 0, sizeof(visited));
        memset(wl, -1, sizeof(wl));
        visited[n]=1; wl[n]=0;

        REP(i, ne) q.push(data(wl[el[i]]=0, el[i])), prev[el[i]]=n;

        ll nr=inf;

        while(!q.empty()){
            data pa=q.top(); q.pop();
            int p=pa.a;
            visited[p]=1;
            if (mp[p]>pa.wl){
                q.push(data(wl[p]=mp[p], p));
                continue;
            }

            if (mp[p] && wl[p]==mp[p] && wl[prev[p]]==wl[p]) nr=0;
            


            REP(k, 4){
                int a=next[p][k];
                if (!visited[a] && (wl[a]==-1 || wl[a]>wl[p])) q.push(data(wl[a]=wl[p], a)), prev[a]=p;
            }
        }


        REP(i, n) if (wl[i]){
            if (wl[i]==mp[i]){
                if (mp[i]-wl[prev[i]]<m){nr=0; break;}
                if (wl[prev[i]]==0) checkmin(nr, mp[i]);
            }else checkmin(nr, wl[i]-mp[i]);
        }

        if (nr<=m){
            ++res;
            REP(i, n) if (mp[i]) mp[i]-=min(m, wl[i]-wl[prev[i]]);
        }else{
            ll tmp=nr/m;
            res+=tmp;
            tmp*=m;
            REP(i, n) if (mp[i]==wl[i] && mp[i]) mp[i]-=tmp, wl[i]-=tmp;
        }

    }


    return res;

}



int main(){
    int tn, ti;
    cin>>tn;

    for (ti=1; ti<=tn; ++ti){
        cin>>r>>c>>m;
        n=r*c;
        mp[n]=0;
        REP(i, r) REP(j, c){
            int id=i*c+j;
            cin>>mp[id];
            REP(k, 4) next[id][k]=in(i+vx[k], j+vy[k])?(i+vx[k])*c+j+vy[k]:n;
        }
        ne=0;
        REP(i, r) el[ne++]=i*c, el[ne++]=i*c+c-1;
        REP(i, c-2) el[ne++]=i+1, el[ne++]=r*c-c+i+1;

        ll res=doit();

        printf("Case #%d: %Ld\n", ti, res);
    }
    return 0;


}


