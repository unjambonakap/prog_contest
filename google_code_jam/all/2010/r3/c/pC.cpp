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



#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

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

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(ll x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;

vector<pii> l;


ll solve(){
	vector<pii> cur;
	int x, i, j, n;
	pii pa, pc;
	ll s, c;


	c=0;
	FE(it, l){
		x=it->ST;

		REP(i, it->ND){
			//printf("on %d\n", x);
			//REP(j, SZ(cur))
			//	printf("int %d %d\n", cur[j].ST, cur[j].ND);
			REP(j, SZ(cur)-1)
				assert(cur[j+1].ST-cur[j].ND>1);

			if (SZ(cur)<=1){
				if (SZ(cur)==0)
					cur.pb(MP(x, x));
				else{
					pa=cur[0];
					if (x<=pa.ND){

						assert(x>=pa.ST);
						cur.pop_back();

						n=pa.ND-pa.ST;
						j=pa.ST+(n-(x-pa.ST)); //new hole
						cur.pb(MP(pa.ST-1, j-1));
					   	cur.pb(MP(j+1, pa.ND+1));

						c+=ll(1+n+n*ll(x-pa.ST))-sqr(x-pa.ST);
						assert(c>=0);
					}else if (x==pa.ND+1){
						++cur[0].ND;
					}else{
						cur.pb(MP(x, x));
					}
				}
			}else{
				pa=cur[SZ(cur)-2], pc=cur.back();
				assert(x>=pa.ST);
				if (x<=pa.ND){
					cur.pop_back();
					cur.pop_back();

					n=pa.ND-pa.ST;
					j=pa.ST+(n-(x-pa.ST)); //new hole

					if (cur.back().ND==pa.ST-2)
						cur.back().ND=j-1;
					else
						cur.pb(MP(pa.ST-1, j-1));

					if (pc.ST==pa.ND+2)
						cur.pb(MP(j+1, pc.ND));
					else{
						cur.pb(MP(j+1, pa.ND+1));
						cur.pb(pc);
					}
					c+=ll(1+n+n*ll(x-pa.ST))-sqr(x-pa.ST);
						assert(c>=0);

				}else if (x<pc.ST){
					cur.pop_back();
					cur.back().ND=pc.ND;
				}else if (x<=pc.ND){
					cur.pop_back();

					n=pc.ND-pc.ST;
					j=pc.ST+(n-(x-pc.ST)); //new hole
					if (cur.back().ND==pc.ST-2)
						cur.back().ND=j-1;
					else
						cur.pb(MP(pc.ST-1, j-1));

					cur.pb(MP(j+1, pc.ND+1));
					c+=ll(1+n+n*ll(x-pc.ST))-sqr(x-pc.ST);
					if (c<0)
					printf("%d %d\n", x, pc.ST);
						assert(c>=0);


				}else if (x==pc.ND+1){
					cur.back().ND=x;
				}else
					cur.pb(MP(x, x));



			}


		}
	}



	return c;


}

int main(){
	int t, T, n, i, x, v;
	cin>>T;

	REP(t, T){

		CLR(l);
		cin>>n;

		REP(i, n){
			cin>>x>>v;
			l.pb(MP(x, v));
		}


		printf("Case #%d: %Ld\n", t+1, solve());
	}


	return EXIT_SUCCESS;
}

