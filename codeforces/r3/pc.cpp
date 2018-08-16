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
int solve(){
    int mp[3][3];
    int cnt[2]={0, 0};
    REP(i, 3){
        string s; cin>>s;
        REP(j, 3){
            if (s[j]=='.') mp[i][j]=-1;
            else cnt[mp[i][j]=s[j]=='0']++;
        }
    }
    if (cnt[1]>cnt[0] || cnt[0]-cnt[1]>1) return -1;
    int fd;
    vi win;
    int type=0;
    int na=two(9)-1;
    REP(i, 3){
        fd=1;
        if (mp[i][0]!=-1){
            REP(j, 3) if (mp[i][j]!=mp[i][0]){fd=0; break;}
            if (fd) type|=two(mp[i][0]), na&=7<<(3*i);
        }
        fd=1;
        if (mp[0][i]!=-1){
            REP(j, 3) if (mp[j][i]!=mp[0][i]){fd=0; break;}
            if (fd) type|=two(mp[0][i]), na&=(two(0)|two(3)|two(6))<<i;
        }
    }
    fd=1;
    if (mp[0][0]!=-1){
        REP(i, 3) if (mp[i][i]!=mp[0][0]){fd=0; break;}
        if (fd) type|=two(mp[0][0]), na&=(two(0)|two(4)|two(8));
    }

    fd=1;
    if (mp[2][0]!=-1){
        REP(i, 3) if (mp[2-i][i]!=mp[2][0]){fd=0; break;}
        if (fd) type|=two(mp[2][0]), na&=two(2)|two(4)|two(6);
    }


    if (type==3) return -1;
    if (type){
        if (!na) return -1;
        if (type==2 && cnt[0]>cnt[1]) return -1;
        if (type==1 && cnt[0]==cnt[1]) return -1;
        return type+1;
        
    }


    if (cnt[0]+cnt[1]==9) return 4;
    return cnt[0]>cnt[1];


}

int main(){
    int res=solve();
    if (res==-1) printf("illegal\n");
    else if (res==0) printf("first\n");
    else if (res==1) printf("second\n");
    else if (res==2) printf("the first player won\n");
    else if (res==3) printf("the second player won\n");
    else printf("draw\n");



    return 0;
}


