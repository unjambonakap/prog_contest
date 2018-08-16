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

const int maxn=7010;
int mem[maxn][maxn][3][2];
string s;
int n;
const char *sa[3][2]={{"ABC", "ACB"}, {"BCA", "BAC"}, {"CAB", "CBA"}};

int solve(int a, int b, int c, int d){
    if (a==n) return 0;
    if (b==0) c=d=0;
    if (b==1) d=0;
    int &r=mem[a][b][c][d];
    if (r!=-1) return r;
    if (b==0) return r=solve(a+1, 1, s[a]-'A', 0)+2;
    
    int v=(b-1)%3;
    int nv=(v+1)%3;
    if (sa[c][d][v]==s[a]) r=solve(a+1, b, c, d);
    else if (b==1) r=solve(a+1, 2, c, sa[c][0][nv]==s[a]?0:1)+2;
    else if (sa[c][d][nv]==s[a]) r=min(b==2?2*maxn:solve(a+1, b-2, c, d), solve(a+1, b+1, c, d)+2);
    else r=solve(a+1, b-1, c, d);
    assert(r!=-1);

    return r;
}

int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        cin>>s;
        n=s.length();

        memset(mem, -1, sizeof(mem));
        int res=solve(0, 0, 0, 0)+s.length();
        printf("Case #%d: %d\n", ti, res);
    }

    return 0;
}



