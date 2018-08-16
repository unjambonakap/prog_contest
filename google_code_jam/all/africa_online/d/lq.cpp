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
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)
#define FEV(i,t) for (typeof(t.rbegin())i=t.rbegin();i!=t.rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ST first
#define ND second
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

#define ST first
#define ND second

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;
const int MAX_N=500;

struct Prop{
	Prop(){}
	Prop(int type, int id, int aid, int bid=-1):type(type), id(id), aid(aid), bid(bid){}
	Prop inv(){ return Prop(type^1, id, aid, bid); }



	int type;
	int id, aid, bid;
};

int n, c;
int town[MAX_N];
vector<Prop> sl;

bool checkIt(int s){

	Prop p;
	FE(it, sl){
		if (bit_set(s, it->id))
			p=*it;
		else
			p=it->inv();
		

		switch(p.type){
			case 0:
				if (!bit_set(s, p.aid))
					return false;
				break;
			case 1:
				if (bit_set(s, p.aid))return false;
				break;
			case 2:
				if (bit_set(s, p.aid) != bit_set(s, p.bid))return false;
				break;

			case 3:
				if (bit_set(s, p.aid) == bit_set(s, p.bid))return false;
				break;

		}

	}
	return true;
	

}

void solve(){

	int i, j, k;
	memset(town, -1, sizeof(town));

	REP(i, two(n)){
		if (!checkIt(i))continue;

		REP(j, n)
			town[j]&=bit_set(i, j)+1;
	}






}

int main(){
	int t, X;
	int i, j, k;
	int a, b;
	char l;


	scanf("%d", &X);
	REP(t, X){


		sl.clear();

		scanf("%d %d", &n, &c);
		REP(i, c){
			scanf("%d %c", &k, &l);
			switch(l){
				case 'T':j=0;break;
				case 'L':j=1;break;
				case 'S':j=2;break;
				case 'D':j=3;break;
			}

			if (j>=2)
				scanf("%d %d", &a, &b);
			else
				scanf("%d", &a);
			sl.pb(Prop(j, k-1, a-1, b-1));
		}

		printf("Case #%d:", t+1);

		solve();
		REP(i, n){
			if (town[i] == 0)printf(" -");
			else if (town[i] == 1)printf(" L");
			else printf(" T");
		}


		printf("\n");


	}
	return EXIT_SUCCESS;
}

