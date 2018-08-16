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

struct point{
    int x,y,z;
    point(int x, int y, int z):x(x),y(y),z(z){}
    point(){}
    bool operator<(const point &p)const{
        if (x!=p.x) return x<p.x;
        if (y!=p.y) return y<p.y;
        return z<p.z;
    }
    point operator-(const point &p)const{return point(x-p.x,y-p.y,z-p.z);}
    bool operator==(int a)const{return x==a&&y==a&&z==a;}
    bool operator!=(int a)const{return !(*this==a);}
    bool operator==(const point &p)const{return x==p.x&&y==p.y&&z==p.z;}
};

point dotprod(point a, point b){return point(a.y*b.z-b.y*a.z,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}
ll det(point a, point b, point c){return 1ll*a.x*(b.y*c.z-b.z*c.y)-1ll*a.y*(b.x*c.z-b.z*c.x)+1ll*a.z*(b.x*c.y-b.y*c.x);} 

vector<point> tb;
point ask;
int go(){
    if (tb.size()==1) return tb[0]==ask;
    else if (tb.size()==2){
        point p=dotprod(ask-tb[0],tb[1]-tb[0]);
        if (p!=0) return 0;
        return tb[0]<ask && ask<tb[1];
    }else{
        point p=dotprod(tb[1]-tb[0],tb[2]-tb[0]);
        if (p!=0){
            point u=dotprod(ask-tb[0],tb[1]-tb[0]);
            point v=dotprod(p,u);
            if (v!=0) return 0;

            tb.pb(tb[0]);
            ll A=det(tb[0],tb[1],tb[2]);
            ll B=0;
            REP(i,3){
                if (dotprod(ask-tb[i],ask-tb[i+1])==0) return 0;
                B+=abs(det(ask,tb[i],tb[i+1]));
            }
            return abs(A)==B;

        }else{
            tb.erase(tb.begin()+1);
            return go();
        }
    }
}
int main(){
    int a,b,c;
    while(cin>>a>>b>>c,a||b||c){

        tb.clear();
        tb.pb(point(a,b,c));
        cin>>a>>b>>c;
        tb.pb(point(a,b,c));
        cin>>a>>b>>c;
        tb.pb(point(a,b,c));
        cin>>a>>b>>c;
        ask=point(a,b,c);

        sort(ALL(tb));
        tb.resize(unique(ALL(tb))-tb.begin());
        puts(go()?"YES":"NO");


    }
    return 0;
}

