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

int oa[10], ob[10];
int a[10], b[10];

int main(){
    string s; cin>>s;
    int n=s.length();
    REP(i, n) ++a[s[i]-'0'];
    memcpy(b, a, sizeof(a)); memcpy(ob, a, sizeof(a)); memcpy(oa, a, sizeof(a));

    vector<pii> tb;
    int best=a[0];
    string res[2];
    REP(i, 10) res[0]+=string(a[i], i+'0');
    reverse(ALL(res[0]));
    res[1]=res[0];
    FOR(i, 1, 10) if (a[i] && b[10-i]){

        --a[i], --b[10-i];
        string sa, sb;
        int ans=1;
        sa+=i+'0'; sb+=10-i+'0';
        REP(j, 10){
            int z=min(a[j], b[9-j]);
            ans+=z;
            REP(k, z) sa+=j+'0', sb+=9-j+'0';
            a[j]-=z; b[9-j]-=z;

        }
        int z=min(a[0], b[0]);
        ans+=z;
        sa=string(z, '0')+sa;
        sb=string(z, '0')+sb;
        a[0]-=z; b[0]-=z;
        REP(j, 10) REP(k, a[j]) sa+=j+'0';
        REP(j, 10) REP(k, b[j]) sb+=j+'0';
        if (best<ans){ reverse(ALL(sa)); reverse(ALL(sb));res[0]=sa, res[1]=sb, best=ans;}
        memcpy(a, oa, sizeof(a)); memcpy(b, ob, sizeof(b));
    }
    REP(i, 2) cout<<res[i]<<endl;

    return 0;
}


