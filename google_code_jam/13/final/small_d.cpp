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
typedef unsigned int uint;
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

const int maxn=1e5+10;
const int maxd=4;
const int maxv=maxn*maxd;

int n,d;
int tb[maxn][maxd];
vector<pair<int,pii> > jmp[maxn];

int l,r;
void eval(int a, int b){ if (b-a>r-l || (b-a==r-l && a<l)) l=a, r=b; }



int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        l=r=0;

        int k;
        cin>>n>>d>>k;
        vi lst;
        REP(i,n) REP(j,d) scanf(" %d",tb[i]+j);

        REP(i,n) REP(j,d) lst.pb(tb[i][j]);

        sort(ALL(lst));
        lst.resize(unique(ALL(lst))-lst.begin());

        REP(i,n) REP(j,d) tb[i][j]=lower_bound(ALL(lst),tb[i][j])-lst.begin();

        REP(i,n){
            REP(j,d) jmp[i].pb(MP(tb[i][j],MP(1,1)));
            sort(ALL(jmp[i]));
            jmp[i].resize(unique(ALL(jmp[i]))-jmp[i].begin());
        }
        FOR(i,1,n) REP(j,jmp[i].size()) REP(k,jmp[i-1].size()) if (jmp[i][j].ST==jmp[i-1][k].ST) jmp[i][j].ND.ST+=jmp[i-1][k].ND.ST;
        REPV(i,n-1) REP(j,jmp[i].size()) REP(k,jmp[i+1].size()) if (jmp[i][j].ST==jmp[i+1][k].ST) jmp[i][j].ND.ND+=jmp[i+1][k].ND.ND;

        vector<pii> pos;
        REP(i,n){
            sort(tb[i],tb[i]+d);
            REP(j,d) pos.pb(MP(tb[i][j],i));
        }
        sort(ALL(pos));

        REP(i,pos.size()){
            int j=i;

            vector<pair<int,int> > can,ncan;//val,st
            int u=pos[i].ST;
            int last=-2;
            int lrun=-2;
            //printf("new\n");
            for (; j<pos.size() && u==pos[j].ST; ++j){
                //printf("proc %d %d\n",pos[j].ST,pos[j].ND);
                int x=pos[j].ND;

                if (last+1<x){

                    if (x) REP(k,jmp[x-1].size()){
                        pair<int,pii> a=jmp[x-1][k];
                        int lv;

                        if (a.ND.ST>=x-last-1){
                            lv=lrun;
                            REP(kk,can.size()) if (can[kk].ST==a.ST) lv=min(lv,can[kk].ND);
                        }else lv=x-a.ND.ST;
                        ncan.pb(MP(a.ST,lv));
                    }
                    can=ncan;
                    ncan.clear();
                    lrun=x;
                }
                REP(k,can.size()){
                    int v=0;
                    if (x<n-1) REP(kk,jmp[x+1].size()) if (jmp[x+1][kk].ST==can[k].ST) v=jmp[x+1][kk].ND.ND;
                    //printf("%d >> %d\n",can[k].ND,x+v);
                    eval(can[k].ND,x+v);
                }
                eval(lrun,x);
                last=x;

            }
            i=j-1;
        }

        assert(r<n);
        printf("Case #%d: %d %d\n",ti+1,l,r);
        REP(i,n) jmp[i].clear();
    }
    return 0;

}

