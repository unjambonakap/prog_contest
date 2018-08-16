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


int ta[1<<22], tb[1<<22], tx[1<<22], ty[1<<22];
int H[1<<22];
int T[1<<22];
int sw[1<<22];
string s;

#define qa(p) (sw[p]?tb[p]:ta[p])
#define qb(p) (sw[p]?ta[p]:tb[p])
#define qx(p) (sw[p]?ty[p]:tx[p])
#define qy(p) (sw[p]?tx[p]:ty[p])
void init(int p, int a, int b){
    T[p]=a; H[p]=b;
    sw[p]=0;

    if (a+1==b){
        ta[p]=s[a]=='4';
        tb[p]=s[a]=='7';
        tx[p]=ty[p]=1;
        return;
    }

    int M=(a+b)/2;
    init(2*p, a, M);
    init(2*p+1, M, b);
    ta[p]=qa(2*p)+qa(2*p+1);
    tb[p]=qb(2*p)+qb(2*p+1);
    tx[p]=0;
    ty[p]=0;
    checkmax(tx[p], max(qa(2*p)+qx(2*p+1),qa(2*p)+qa(2*p+1)));
    checkmax(tx[p], max(qx(2*p)+qb(2*p+1), qb(2*p)+qb(2*p+1)));
    checkmax(ty[p], max(qb(2*p)+qy(2*p+1), qb(2*p)+qb(2*p+1)));
    checkmax(ty[p], max(qy(2*p)+qa(2*p+1), qa(2*p)+qa(2*p+1)));

}




void swx(int p, int l, int r){
    if (l>=H[p] || r<=T[p]) return;
    if (l<=T[p] && r>=H[p]){sw[p]^=1; return;}
    if (sw[p]){
        sw[2*p]^=1;
        sw[2*p+1]^=1;
        sw[p]=0;
    }
    swx(2*p, l, r);
    swx(2*p+1, l, r);

    ta[p]=qa(2*p)+qa(2*p+1);
    tb[p]=qb(2*p)+qb(2*p+1);
    ty[p]=0;
    tx[p]=0;
    checkmax(tx[p], max(qa(2*p)+qx(2*p+1),qa(2*p)+qa(2*p+1)));
    checkmax(tx[p], max(qx(2*p)+qb(2*p+1), qb(2*p)+qb(2*p+1)));
    checkmax(ty[p], max(qb(2*p)+qy(2*p+1), qb(2*p)+qb(2*p+1)));
    checkmax(ty[p], max(qy(2*p)+qa(2*p+1), qa(2*p)+qa(2*p+1)));
    
}


int main(){
    int n, m;
    cin>>n>>m;
    cin>>s;
    init(1, 0, n);


    char buf[15];
    REP(i, m){
        scanf("%s", buf);
        if (buf[0]=='c'){
            int res=0;
            checkmax(res, qa(1));
            checkmax(res, qb(1));
            checkmax(res, qx(1));
            printf("%d\n", res);

        }else{
            int x, y;
            scanf("%d %d", &x,&y);
            swx(1, x-1, y);
        }
    }


    return 0;
}


