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

const int maxn=111111;
const int maxb=320;
int X[maxb][maxb];
int step[maxb];
int na[maxb];
int leader[maxb];
int D[maxn], R[maxn], G[maxn], P[maxn], wh[maxn];
ll aa[maxn], bb[maxn];//aa*t + bb
int n, c, d;
int pos;

struct event{
    double t;
    int type, id;//0 > new item, 1 > intersect
    int step;
    event(double t, int type, int id, int step=-1):t(t),type(type),id(id), step(step){}
    bool operator<(const event &e)const{
        if (t!=e.t) return t>e.t;
        return type<e.type;
    }
};
priority_queue<event> q;

void update(int b){
    int i=leader[b];
    ++step[b];
    REP(jx,na[b]){
        int j=X[b][jx];
        if (j==i) continue;
        if (aa[j]>aa[i]){
            double nt=1.*(bb[i]-bb[j])/(aa[j]-aa[i])+1;
            if (nt<=1e9+10) q.push(event(nt,1,j,step[b]));
        }
    }

}

void addb(ll a, ll b, int i, int t){
    if (na[pos]==maxb) ++pos;
    X[pos][na[pos]++]=i;
    wh[i]=pos;
    aa[i]=a; bb[i]=b;
    if (leader[pos]==-1) leader[pos]=i;
    else{
        ll v=aa[leader[pos]]*t+bb[leader[pos]];
        ll nv=a*t+b;
        if (nv>v || nv==v&&a>leader[pos]){ 
            leader[pos]=i;
            update(pos);
        }else{
            int j=leader[pos];
            update(pos);
        }
    }
}

int main(){
    int tn=0;
    while(cin>>n>>c>>d, n|c|d){
        while(!q.empty()) q.pop();
        q.push(event(d+1,-1,-1));
        ++n;
        FOR(i,1,n) scanf("%d%d%d%d", D+i,P+i,R+i,G+i), q.push(event(D[i],0,i));
        
        memset(na,0,sizeof(na));
        pos=0;

        memset(step,0,sizeof(step));
        memset(leader,-1,sizeof(leader));
        addb(0,c,0,0);

        printf("Case %d: ", ++tn);

        while(!q.empty()){
            event e=q.top(); q.pop();
            if (e.type==-1){
                ll ans=0;
                REP(i,pos+1){
                    int id=leader[i];
                    checkmax(ans, aa[id]*ll(e.t-1)+bb[id]);
                }
                cout<<ans<<endl;
                break;
            }else if (e.type==0){
                ll best=0;
                REP(i,pos+1) checkmax(best,aa[leader[i]]*ll(e.t-1)+bb[leader[i]]);
                if (best<P[e.id]) continue;
                ll a=G[e.id], b=best-P[e.id]+R[e.id]-a*e.t;
                addb(a,b,e.id,e.t);

            }else{
                if (step[wh[e.id]]!=e.step) continue;
                leader[wh[e.id]]=e.id;
                update(wh[e.id]);

            }

        }

    }
    return 0;
}



