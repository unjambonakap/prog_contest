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
const int maxn=2e6+10;



int n;
char s[maxn];
int st[maxn];
int has[maxn];

int m[maxn];
int pos;

struct node{
    int next[13];
    int cnt;
    int is;

    void init(){
        memset(next,-1,sizeof(next));
        cnt=is=0;
    }

}tb[maxn];

node tb2[maxn];

int N;


int main(){

    while(cin>>n,!cin.eof()){
        pos=0;
        REP(i,n){
            scanf(" %s",s+pos);
            st[i]=pos;
            m[i]=strlen(s+pos);
            REP(j,m[i]) s[st[i]+j]-='a';
            pos+=m[i];
        }


        N=1;
        tb[0].init();

        REP(i,n){
            int x=0;
            REP(j,m[i]){
                int c=s[st[i]+j];
                if (tb[x].next[c]==-1){
                    tb[N].init();
                    tb[x].next[c]=N++;
                }
                x=tb[x].next[c];
            }
            tb[x].is=1;
        }

        REP(i,n){
            int x=0;
            REP(j,m[i]){
                int c=s[st[i]+j];
                has[st[i]+j]=tb[x].is;
                x=tb[x].next[c];
            }
        }

        N=1;
        tb[0].init();
        REP(i,n){
            int x=0;
            REPV(j,m[i]){
                int c=s[st[i]+j];
                if (tb[x].next[c]==-1){
                    tb[N].init();
                    tb[x].next[c]=N++;
                }
                x=tb[x].next[c];
                if (has[st[i]+j]) ++tb[x].cnt;
            }
        }


        ll res=0;
        REP(i,N) res+=1ll*tb[i].cnt*(tb[i].cnt-1)/2;

        cout<<res<<endl;
    }
    return 0;
}


