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

const int maxn=15;
const int maxm=51;

double graph[maxm][maxm];
int n, m;
map<string, int> mp;

int flag[maxn];
int nitems[maxm];
pii items[maxm][maxn];
double proc[two(maxn)][maxm];

int xpos[maxm];
int ypos[maxm];
int ftb[maxm][two(maxn)];
int ctb[maxm][two(maxn)];
int mtb[maxm][two(maxn)];

int sqr(int a){return a*a;}

struct state{
    int pos;
    double c;
    int l;
    
    state(int pos, double c, int l):pos(pos), c(c), l(l){}
    state &operator=(const state &s){
        pos=s.pos;
        c=s.c;
        l=s.l;
    }
    bool operator<(const state &s)const{
        if (c!=s.c) return c>s.c;
        if (l!=s.l) return l<s.l;
        return pos<s.pos;
    }
};

inline void pushQ(priority_queue<state> &q, int pos, double c, int l){
    if (c<proc[l][pos]){
        //set<state>::iterator it=q.find(state(pos, proc[l][pos], l));

        //if (it!=q.end()) q.erase(it);
        //
        proc[l][pos]=c;
        q.push(state(pos, c, l));
    }
}

double solve(){
    priority_queue<state> q;
    q.push(state(m, 0, 0));


    REP(i, two(n)) REP(j, m+1) proc[i][j]=1e9;
    int cnt=0;
    while(!q.empty()){
        state s=q.top(); q.pop();
        if (s.l==two(n)-1){
            if (s.pos!=m) continue;
            return s.c;
        }
        if (proc[s.l][s.pos]<s.c) continue;
        
        ++cnt;

        int remap[maxn];
        int sz=0;
        REP(j, nitems[s.pos]) if (!(s.l&two(items[s.pos][j].ST))) remap[sz++]=j;
        int lim=two(sz);
        for (int j=1; j<lim; ++j){
            int nj=0;

            for (int k=0; j>>k; ++k) if (j>>k&1) nj|=two(remap[k]);
            double nc=s.c+ctb[s.pos][nj];
            int nm=s.l|mtb[s.pos][nj];
            if (proc[nm][s.pos]<nc) continue;
            if (!ftb[s.pos][nj]){
                REP(i, m) if (i!=s.pos){
                    double fc=nc+graph[s.pos][i];
                    if (proc[nm][i]>fc){
                        q.push(state(i, fc, nm)), proc[nm][i]=fc;
                    //pushQ(q, i, nc+graph[s.pos][i], nm);
                    }
                }
            }
            double fc=nc+graph[s.pos][m];
            if (proc[nm][m]>fc)
            q.push(state(m, fc, nm)), proc[nm][m]=fc;
            //pushQ(q, m, nc+graph[s.pos][m], nm);
        }

        if (s.pos==m){
            REP(i, m){
                double fc=s.c+graph[m][i];
                if (proc[s.l][i]>fc) q.push(state(i, fc, s.l)), proc[s.l][i]=fc;
                //pushQ(q, i, s.c+graph[m][i], s.l);
            }

        }




    }
    assert(0);

}

int main(){

    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int p;
        cin>>n>>m>>p;
        mp.clear();

        REP(i, n){
            string s;
            cin>>s;
            if (s[s.length()-1]=='!'){
                flag[i]=1;
                s.erase(s.length()-1);
            }else flag[i]=0;
            mp[s]=i;
        }
        REP(i, m){
            cin>>xpos[i]>>ypos[i];
            string s;
            getline(cin, s);

            REP(j, s.length()) if (s[j]==':') s[j]=' ';
            istringstream ss(s);
            string sa, sb;

            nitems[i]=0;
            while(ss>>sa){
                ss>>sb;
                items[i][nitems[i]++]=MP(mp[sa], toInt(sb));
            }
            REP(j, two(nitems[i])){
                ctb[i][j]=mtb[i][j]=ftb[i][j]=0;
                REP(k, nitems[i]) if (two(k)&j){
                    ftb[i][j]|=flag[items[i][k].ST];
                    mtb[i][j]|=two(items[i][k].ST);
                    ctb[i][j]+=items[i][k].ND;
                }

            }
        }
        nitems[m]=0;
        graph[m][m]=0.;
        REP(i, m) REP(j, m) graph[i][j]=graph[j][i]=sqrt(sqr(xpos[i]-xpos[j])+sqr(ypos[i]-ypos[j]))*p;
        REP(i, m) graph[i][m]=graph[m][i]=sqrt(xpos[i]*xpos[i]+ypos[i]*ypos[i])*p;
        printf("Case #%d: %lf\n", ti, solve());


    }

}



