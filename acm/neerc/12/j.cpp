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

const int maxn=15555;
int a,b,c;
int u,p;
int res[maxn];
int seen[maxn];

void add(int x){
    if (fabs(x)==1) --a;
    if (fabs(x)==2) --b;
    if (fabs(x)==3) --c;
    res[u++]=p+=x;
    seen[p]++;
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %d%d%d",&a,&b,&c);
        int n=a+b+c;

        u=0; p=0;
        res[u++]=0;
        memset(seen,0,sizeof(seen));
        seen[0]=1;

        while(b>=4 && c>=2) add(2),add(2),add(-3),add(2),add(2);
        while(b>=2 && c>=3) add(3),add(-2),add(3),add(-2),add(3);

        if (c==2&&b==3){while(a) add(1); add(2); add(3); add(-2); add(-2); add(3);}
        else if (c==1 && b>=2){add(3); add(-2); add(1); add(2);}
        else if (b==2) add(2), add(-1), add(2);
        else if (c==2) add(3), add(-1),add(-1),add(3);
        printf("%d %d %d\n",a,b,c);

        if (b&&!c){
            int ob=b;
            int b2=(b+1)/2;
            while(a>1) add(1);
            REP(i,b2) add(2);

            if (ob&1) add(-1);
            else add(1);
            while(b) add(-2);
        }else if (c){

            int c3=c/3;

            if (c%3==0){
                int hasb=b;
                while(a>2) add(1);
                if (hasb) add(1);

                REP(i,c3) add(3);
                add(hasb?2:1);
                REP(i,c3) add(-3);
                add(hasb?-1:1);
                REP(i,c3) add(3);
            }else{
                if (!b){
                    while(a>2) add(1);
                    REP(i,c3+1) add(3);
                    add(-1);
                    REP(i,c3) add(-3);
                    add(-1);
                    while(c) add(3);
                }else if (c%3==1){
                    while(a>1) add(1);
                    REP(i,c3+1) add(3);
                    add(-2);
                    REP(i,c3) add(-3);
                    add(1);
                    while(c) add(3);
                }else{
                    while(a>2) add(1);
                    REP(i,c3+1) add(3);
                    add(-2);
                    REP(i,c3) add(-3);
                    add(1);
                    while(c) add(3);
                    add(-1);
                }
            }

        }else while(a) add(1);

        assert(!a && !b && !c);

        REP(i,n){
            if (seen[i]!=1) printf("%d >> %d\n",i,seen[i]);
            assert(seen[i]==1);
        }
        REP(i,n) printf("%d%c",res[i]," \n"[i==n-1]);
    }

    return 0;
}

