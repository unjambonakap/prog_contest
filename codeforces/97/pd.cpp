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

int norm(pii a){return a.ST*a.ST+a.ND*a.ND;}


int checkit(vector<pii> x, int f){
    sort(ALL(x));
    do{
        pii va, vb;
        va=MP(x[1].ST-x[0].ST, x[1].ND-x[0].ND);
        vb=MP(x[2].ST-x[0].ST, x[2].ND-x[0].ND);
        if (va!=MP(x[3].ST-x[2].ST, x[3].ND-x[2].ND) 
                || vb!=MP(x[3].ST-x[1].ST, x[3].ND-x[1].ND));
        else{

            if (va.ST*vb.ST+va.ND*vb.ND==0 && (!f||norm(va)==norm(vb))) return 1;
        }


    }while(next_permutation(ALL(x)));
    return 0;
}


int main(){

    int n=8;
    vector<pii> l(n);
    REP(i, n) cin>>l[i].ST>>l[i].ND;
    REP(i, two(n)) if (count_bit(i)==4){
        vector<pii> a, b;
        REP(j, n) if (i&two(j)) a.pb(l[j]); else b.pb(l[j]);
        if (checkit(a, 1) && checkit(b, 0)){
            printf("YES\n");
            REP(j, n) if (i&two(j)) printf("%d ", j+1); printf("\n");
            REP(j, n) if (!(i&two(j))) printf("%d ", j+1); printf("\n");
            return 0;

        }

    }
    printf("NO\n");

    return 0;
}

