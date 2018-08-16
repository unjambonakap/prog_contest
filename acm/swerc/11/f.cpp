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

const int mod=1e9+7;
const int maxn=5;
int n,m;
int rmp[256];
char buf[11111];
int val[maxn];
int p;


int eval(){
    char c=buf[p++];
    if (c=='('){
        int a=eval();
        char op=buf[p++];
        int b=eval();
        ++p;
        if (op=='*') return 1ll*a*b%mod;
        else if (op=='+') return (a+b)%mod;
        else return (a-b)%mod;
    }
    return val[c];
}

int main(){
    while(cin>>n,n){
        REP(i,n) scanf(" %d",val+i);
        int sol; scanf(" %d",&sol);


        scanf(" %s",buf);

        m=strlen(buf);
        memset(rmp,-1,sizeof(rmp));
        int pos=0;
        REP(i,m) if (buf[i]>='a' && buf[i]<='z'){
            if (rmp[buf[i]]==-1) rmp[buf[i]]=pos++;
            buf[i]=rmp[buf[i]];
        }

        sort(val,val+n);
        int res=0;
        do{
            p=0;
            if (eval()==sol){res=1; break;}
        }while(next_permutation(val,val+n));
        puts(res?"YES":"NO");

    }
    return 0;
}

