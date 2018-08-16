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

int isNum(char c){return c<=9;}
struct state{
    int x, y, v;
    state(int x, int y, int v):x(x), y(y), v(v){}
};


const int maxw=20;
const int maxv=2001;
int w;
char m[maxw][maxw];
string mem[maxw][maxw][maxv];
int visited[maxw][maxw][maxv];
int vx[]={-1, 1, 0, 0};
int vy[]={0, 0, 1, -1};
int in(int x, int y){return x>=0 && y>=0 && x<w && y<w;}

void solve(){
    memset(visited, 0, sizeof(visited));
    REP(i, w) REP(j, w) REP(k, maxv) mem[i][j][k]="";
    queue<state> q;
    REP(i, w) REP(j, w) if (isNum(m[i][j])){
        mem[i][j][m[i][j]+maxv/2]=string(1, m[i][j]+'0');
        q.push(state(i, j, m[i][j]+maxv/2));
    }

    while(!q.empty()){
        state s=q.front(); q.pop();
        if (visited[s.x][s.y][s.v]) continue;
        visited[s.x][s.y][s.v]=1;
        string ts=mem[s.x][s.y][s.v];
        REP(k, 4){
            int tx=s.x+vx[k], ty=s.y+vy[k];
            if (in(tx, ty)){
                REP(nk, 4){
                    state ns=state(tx+vx[nk], ty+vy[nk], s.v);
                    if (in(ns.x, ns.y)){
                        string tmp=ts;
                        if (m[tx][ty]=='+') ns.v+=m[ns.x][ns.y], tmp+=string(1, '+')+string(1, m[ns.x][ns.y]+'0');
                        else ns.v-=m[ns.x][ns.y], tmp+=string(1, '-')+string(1, m[ns.x][ns.y]+'0');
                        if (ns.v<0 || ns.v>=maxv) continue;
                        string &old=mem[ns.x][ns.y][ns.v];
                        if (old.length()==0) old=tmp, q.push(ns);
                        else if (tmp.length()<old.length() || (tmp.length()==old.length() && tmp<old)) old=tmp;
                    }
                }

            }

        }


    }

}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int q;
        cin>>w>>q;;
        REP(i, w){
            string s;
            cin>>s;
            REP(j, w) m[i][j]=s[j]-(s[j]!='+' && s[j]!='-'?'0':0);;
        }

        solve();
        printf("Case #%d:\n", ti);

        REP(i, q){
            string best(1000, '0');
            int v;
            v=0;
            cin>>v;
            REP(x, w) REP(y, w){
                string s=mem[x][y][v+maxv/2];
                if (isNum(m[x][y]) && s.length()!=0  && (s.length()<best.length() || (s.length()==best.length() && s<best))) best=s;
            }
            cout<<best<<endl;

        }

    }
    return 0;



}



