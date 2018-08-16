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
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;

struct node{
	map<string, node*> f;

	~node(){
		FE(it, f)
			delete it->ND;
	}
};

deque<string> split(string a){
	int i;
	string c;
	deque<string> l;
	REP(i, a.length()){
		if (a[i]=='/'){
			if (c!="")l.pb(c);
			c="";
		}else
			c+=a[i];
	}
	l.pb(c);
	return l;
}

int add(node *a, deque<string> l){
	if (SZ(l)==0)return 0;
	string s=l.front();
	l.pop_front();
	node *n;

	int r=0;

	if (a->f.find(s)==a->f.end()){
		++r;
		a->f.insert(MP(s, n=new node));
	}else
		n=a->f.find(s)->ND;
	r+=add(n, l);
	return r;
}

int main(){
	int T, t;
	int i, j, k;
	int r, n, m;
	string s;
	deque<string> l;


	scanf("%d", &T);
	REP(t, T){
		scanf("%d %d\n", &n, &m);
		node root;

		r=0;
		REP(i, n){
			cin>>s;
			l=split(s);
			add(&root, l);
		}

		REP(j, m){
			cin>>s;
			l=split(s);
			r+=add(&root, l);
		}
		


		printf("Case #%d: %d\n", t+1, r);
	}


	return EXIT_SUCCESS;
}

