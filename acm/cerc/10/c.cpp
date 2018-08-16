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

const int maxn=333333;
char buf[maxn];
int n;
int A[maxn];

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %s", buf);
        //if (ti!=4)continue;
        n=strlen(buf);
        //cout<<buf<<endl;
        memset(A,0,sizeof(A));
        A[0]=0;
        for (int i=1,j=1,last=0; i<n; ++i){
            checkmax(j,i);
            if (j>i) A[i]=min(A[2*last-i],min(n-i,j-i));
            for (;i+A[i]==j && i-A[i]-1>=0 && i+A[i]<n && buf[i-A[i]-1]==buf[i+A[i]]; ++A[i],last=i,++j);
            //printf("%d >> %d %d >> %d\n", i, j, last, A[i]);
        }
        //REP(i,25) printf("%c", buf[i]); puts("");

        //REP(i,n) REP(j,A[i]) assert(buf[i-j-1]==buf[i+j]);
        

        set<int> s;
        priority_queue<pii> q;
        int res=0;
        FOR(i,1,n){
            while(!q.empty() && -q.top().ST<i) s.erase(q.top().ND), q.pop();
            set<int>::iterator it=s.lower_bound(i-A[i]/2);
            //printf(">> HAVE %d fufu %d>> %d >> %d FU %d\n", s.size(),q.size(), i-A[i], it==s.end(), i);
            if (it!=s.end()) checkmax(res,i-*it);
            
            s.insert(i);
            q.push(MP(-i-A[i],i));
        }

        cout<<res*4<<endl;
    }
    return 0;
}




