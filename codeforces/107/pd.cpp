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

const int maxn=155;
int n;
string s;
int w[maxn];

int A[maxn][maxn][maxn];
int B[maxn][maxn];
int C[maxn][maxn];

int goa(int a, int b, int k);
int gob(int a, int b);
int goc(int a, int b);



int goa(int a, int b, int k){
    assert(a<=b);
    if (k==0) return gob(a,b);
    if (a==b) return -2;
    int &r=A[a][b][k];
    if (r!=-1) return r;
    r=-2;

    if (k==1){
        int u=gob(a+1,b);
        if (u!=-2) checkmax(r,u);
    }else{
        FOR(i,a+1,b) if (s[i]==s[a]){
            int u=gob(i+1,b), v=goa(a+1,i,k-2);
            if (u!=-2&&v!=-2) checkmax(r,u+v);
        }
    }


    FOR(i,a+1,b){
        int u=gob(a,i), v=goa(i,b,k);
        if (u!=-2&&v!=-2) checkmax(r,u+v);
    }
    return r;
}

int gob(int a, int b){
    assert(a<=b);
    if (a==b) return 0;
    int &r=B[a][b];
    if (r!=-1) return r;
    r=-2;
    REP(i,b-a) if (w[i]!=-1){
        int u=goa(a,b,i+1);
        if (u!=-2) checkmax(r,w[i]+u);
    }
    return r;
}

int goc(int a, int b){
    assert(a<=b);
    if (a==b) return 0;
    int &r=C[a][b];
    if (r!=-1) return r;
    r=0;
    checkmax(r,gob(a,b));
    REP(i,b-a){
        int u=goa(a,b,i+1);
        if (u!=-2) checkmax(r,u+w[i]);
    }
    FOR(i,a+1,b) checkmax(r,goc(a,i)+goc(i,b));
    return r;
}

int main(){
    cin>>n;
    REP(i,n) cin>>w[i];
    cin>>s;

    memset(A,-1,sizeof(A));
    memset(B,-1,sizeof(B));
    memset(C,-1,sizeof(C));

    int res=goc(0,n);
    cout<<res<<endl;
    return 0;
}




