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

const int maxn=5e4+10;
const ll inf=1e12;
string res;
ll cost;
ll val[maxn];
int n;


int doit(){
    set<pair<ll, int> > A, B;
    A.clear(); B.clear();
    REP(i, n) if (res[i]=='(') B.insert(MP(val[i], i));
    int bx=0;
    REP(i, n){
        cout<<res<<endl;
        if (res[i]==')') --bx;
        else ++bx;

        if (res[i]==')') A.insert(MP(val[i], i));
        else B.erase(MP(val[i], i));

        if (bx<0){
            if (A.empty() || B.empty()) return 0;
            pair<ll, int> x=*A.begin(), y=*B.begin();
            A.erase(x); B.erase(y);
            res[x.ND]='('; res[y.ND]=')';

            cost+=x.ST+y.ST;
            val[x.ND]=x.ST=-x.ST;
            val[y.ND]=y.ST=-y.ST;
            bx+=2;
        }
    }

    return 1;
}

ll solve(){
    string s; cin>>s;
    n=s.length();
    if (n%2) return 0;

    set<pair<ll, int> > A, B;
    res=s;
    int bx=0;
    cost=0;
    REP(i, n){
        val[i]=inf;
        if (s[i]==')') --bx, B.insert(MP(inf, i));
        else if (s[i]=='(') ++bx, A.insert(MP(inf, i));
        else{
            int x, y; cin>>x>>y;
            if (x<y) cost+=x, res[i]='(', A.insert(MP(val[i]=y-x, i)), ++bx;
            else cost+=y, res[i]=')', B.insert(MP(val[i]=x-y, i)), --bx;
        }
    }
    if (bx>0){
        while(bx){
            pair<ll, int> p=*A.begin(); A.erase(p);
            res[p.ND]=')';
            cost+=p.ST;
            p.ST=val[p.ND]=-p.ST;
            B.insert(p);
            bx-=2;
        }
    }else{
        while(bx){
            pair<ll, int> p=*B.begin(); B.erase(p);
            res[p.ND]='(';
            cost+=p.ST;
            p.ST=val[p.ND]=-p.ST;
            A.insert(p);
            bx+=2;
        }
    }
    if (cost>=inf) return 0;

    if (bx) return 0;
    if (!doit()) return 0;
    
    return cost<inf;

}



int main(){

    if (solve()){
        cout<<cost<<endl;
        cout<<res<<endl;
    }else printf("-1\n");

    return 0;
}


