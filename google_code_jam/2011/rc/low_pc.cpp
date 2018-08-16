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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

ll _gcd(ll a, ll b){return (b==0?a:_gcd(b, a%b));}
ll gcd(ll a, ll b){return _gcd(max(a, b), min(a, b));}


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int n; 
        ll l, h;
        set<ll> f;
        cin>>n>>l>>h;
        REP(i, n){
            ll a;
            cin>>a;
            f.insert(a);
        }
        //printf("%d %Ld %Ld\n", n, l, h);
        vector<ll> p(ALL(f));
        ll d, lcm;
        ll res=-1;
        vector<ll> lcml;
        n=p.size();

        lcml.pb(p[0]);
        REP(i, n) if (i){
            ll tmp=lcml.back()/gcd(lcml.back(), p[i]);
            if (double(tmp)*p[i]>h) break;
            lcml.pb(tmp*p[i]);
        }

        d=p.back();
        int na=lcml.size();
        FOR(i, na, n-1) d=gcd(d, p[i]);

        //printf("<< %d %d\n", n, na);
        REPV(i, na){
            ll lcm=lcml[i];
            if (d>lcm && d%lcm==0 && d>=l && lcm<=h){
                ll k=d/lcm;
                ll tmp=ceil((double)l/lcm);
                if (tmp>k) continue;
                ll ub=(h/lcm)*lcm;
                // x* lcm <=h , x>=tmp && x | k
                //printf("xxx %Ld %Ld\n", tmp, ub);
                //printf("%Ld %Ld %Ld\n", k, lcm, l/lcm);
                for (ll j=tmp; j<=ub; ++j) if (k%j==0){
                    ll nv=lcm*j;
                    assert(d%nv==0);
                    //printf("<< find %Ld\n", nv);
                    if (res==-1 || nv<res) res=nv;

                }

                

            }


            //printf("%Ld %Ld wxx gcd %Ld\n", d, p[i], gcd(d, p[i]));
            d=gcd(d, p[i]);
        }
        //printf("<< having %Ld\n", res);
        if (l==1) res=1;
        if (l<=d && d<=h) res=d;
        else if (l==2 && d%2==0) res=2;
        else{
            checkmin(h, (ll)ceil(sqrt(d)));
            for (ll i=l; i<=h; ++i) if (d%i==0){res=i; break;}
        }
        




        printf("Case #%d: ", ti);
        if (res==-1) printf("NO\n");
        else printf("%Ld\n", res);

    }
    return 0;
}

