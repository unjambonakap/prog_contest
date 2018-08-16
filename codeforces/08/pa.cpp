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

const int maxn=1e5+10;
int tb[maxn];
int px[maxn];

int checkit(string s, string a, string b){
    int A=0, B=0;
    int n=s.length();
    REP(i, a.length()) A=A*53+a[i]-'a';
    REP(i, b.length()) B=B*53+b[i]-'a';

    px[0]=1;
    REP(i,n-1) px[i+1]=px[i]*53;
    tb[0]=0;
    REP(i, n) tb[i+1]=tb[i]*53+s[i]-'a';

    REP(i, n-a.length()+1){
        if (tb[i+a.length()]-px[a.length()]*tb[i]==A){
            FOR(j, i+a.length(), n-b.length()+1) if (tb[j+b.length()]-px[b.length()]*tb[j]==B) return 1;
            
            return 0;
        }
    }

    return 0;

}

int main(){
    string s, a, b;
    cin>>s>>a>>b;
    int f=0, fb=0;
    f=checkit(s, a, b);
    reverse(ALL(s));
    fb=checkit(s, a, b);
    if (f&fb) printf("both\n");
    else if (f) printf("forward\n");
    else if (fb) printf("backward\n");
    else printf("fantasy\n");
    return 0;
}


