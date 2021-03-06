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
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxn=1111;
int pl[maxn];
int type[maxn];
int np;

int main(){
    string s;
    cin>>s;
    np=0;
    int xa=1;
    int n=s.length();
    FOR(i, 2, n){
        int fd=1;
        REP(j, np) if (i%pl[j]==0){fd=0; break;}
        if (fd){
            pl[np++]=i;
            if (i*2>n) ++xa;
        }
    }


    vector<pair<int,char> > tb;
    REP(i, 26) tb.pb(MP(0,i));
    REP(i, n) ++tb[s[i]-'a'].ST;
    sort(ALL(tb), greater<pair<int,char> >());
    if (tb[0].ST<s.length()-xa){printf("NO\n"); return 0;}

    tb[0].ST-=s.length()-xa;
    string res(n, tb[0].ND+'a');
    int pos=0;
    REP(i, np) if (pl[i]*2>n){
        if  (!tb[pos].ST) ++pos;
        --tb[pos].ST;
        res[pl[i]-1]=tb[pos].ND+'a';
    }
    if  (!tb[pos].ST) ++pos;
    res[0]=tb[pos].ND+'a';
    printf("YES\n");
    cout<<res<<endl;


    

    return 0;
}



