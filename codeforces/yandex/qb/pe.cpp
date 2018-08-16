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
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxn=510;
const double eps=1e-9;
double x;
struct line{ 
    double a, b; int v;
    double y;
    line(){}
    line(double a, double b):a(a), b(b), v(0){y=f(x);}
    double f(double x)const{assert(!v); return a*x+b;}
    bool operator<(const line &l)const{
        double ya=f(x), yb=l.f(x);
        if (fabs(ya-yb)>eps) return ya<yb;
        return a<l.a;
    }
};//y=ax+b

struct event{
    line l;
    int type;//first bit: opening or ending point of line
    //2/3 intersection 
    double x;
    line lb;
    int c;
    bool operator<(const event &e)const{
        if (fabs(x-e.x)>eps) return x>e.x;
        if (type>=2 || e.type>=2) return type>e.type;
        if (type!=e.type) return type>e.type;
        return c<e.c;

    }
    event(line l, int type, double x, int c):l(l), type(type), x(x), c(c){}
};


set<line> s;
priority_queue<event> el;
int n, h, f;

void addline(const line &a){
    set<line>::iterator it=s.insert(a);
    if (a.a>eps){
        ++it;
        if (it!=s.end() && it->a<-eps) 
        

    }else if (a.a<-eps){

    }

}
int main(){
    cin>>n>>h>>f;
    vector<pii> tx[2];
    REP(i, n){
        int a, b;
        cin>>a>>b;
        if (a<0 && b<=0) tx[0].pb(MP(-b, -a));
        else if (a>=0 && b>0) tx[1].pb(MP(a, b));
        else tx[0].pb(MP(0, -a)), tx[1].pb(MP(0, b));
    }
    double res=0.;
    REP(i, 2){
        FE(it, tx[2]){
            line l;
            if (it->ST==0){
                l.v=1;
                l.a=1;
                el.push(event(l, 0, 0, 0));
                el.push(event(l, 1, 0, 1));
                l.a=-1;
                el.push(event(l, 0, 0, 0));
                el.push(event(l, 1, 0, 1));

            }else{
                l.v=0;
                l.a=double(f-h)/it->ST;
                l.b=-h-l.a*it->ST;
                el.push(event(l, 0, it->ST, 0));
                el.push(event(l, 1, (h-l.b)/l.a, 1));


                l.a=double(h-f)/it->ST;
                l.b=h-l.a*it->ST;
                el.push(event(l, 0, it->ST, 0));
                el.push(event(l, 1, (-h-l.b)/l.a, 1));
            }
            l.v=0;
            l.a=double(f-h)/it->ND;
            l.b=-h-l.a*it->ND;
            el.push(event(l, 0, it->ND, 0));
            el.push(event(l, 1, (h-l.b)/l.a, 1));


            l.a=double(h-f)/it->ND;
            l.b=h-l.a*it->ND;
            el.push(event(l, 0, it->ND, 0));
            el.push(event(l, 1, (-h-l.b)/l.a, 1)); 

        }
        double px=0;
        set<line> s;
        set<line>::iterator it;
        while(!el.empty()){
            event e=el.top(); el.pop();
            x=e.x;
            if (px+eps<x){
                assert(s.size()%2==0);
                it=s.begin();
                while(it!=s.end()){

                    ++it; ++it;
                }

            }

            if (e.type>=2){

            }else{
                if (e.type==0){
                    if (e.l.a>0){
                        addline(line(0, -h));
                        e.l.f(x);
                        addline(el);
                    }else{

                    }

                }else{

                }

            }
            px=x;



        }

        

    }
    printf("%lf\n", res);

    return 0;
}


