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

const int MAX_N=11;
const int BC=4;
const int END=8;

struct State{
	vector<int> tp;
	vector<int> tl;
	int bend, wend;
	State(int n=MAX_N, int m=MAX_N):tp(m, -1), tl(m, -1), bend(0), wend(0){}
	bool operator<(const State &s)const{
		return tp<s.tp || (tp==s.tp && (tl<s.tl || (tl==s.tl && (bend<s.bend || (bend==s.bend && wend<s.wend)))));

	}
};

map<State, int> st[MAX_N][MAX_N];
int n, m;
int used[MAX_N][MAX_N];

bool correct(int s){
	return (s&3)<=((s&END)?1:2);
}

bool finalized(int s){ return (s&3)==((s&END)?1:2); }


int solve(int x, int y, State s){
	int i, j, k;
	if (y==n-1 && x==m){
		used[n-1][y]=1;
		if (!(s.bend==2 && s.wend==2 && finalized(s.tp[x-1])))return 0;
//		printf("%d %d\n", s.wend, s.bend);
//		REP(i, n)
//			printf("%d ", s.tp[i]);
//		printf("\n");
//		REP(i, n)
//			printf("%d ", s.tl[i]);
//		printf("\n\n");
//		exit(0);
		return 1;

	}
	if (x==m){
		s.tl=s.tp;
		s.tp=vector<int>(m, 0);
		++y, x=0;
	}
	

	//printf("%d %d\n", x, y);
	//REP(i, n)
	//	printf("%d ", s.tp[i]);
	//printf("\n");
	map<State, int>::iterator itm;
	itm=st[x][y].find(s);
	if (itm!=st[x][y].end())
		return itm->ND;
	itm=st[x][y].insert(MP(s, 0)).ST;
	int &r=itm->ND;

	



	for(i=0; i<=4; i+=4){
		State ns=s;
		int nb=0;
		//if (x==2 && y==3){
		//	printf("BEFORE %d\n", i);
		//	if (x!=0)
		//		printf("left: %d\n", ns.tp[x-1]);
		//	if (y!=0)
		//		printf("below %d\n", ns.tl[x]);
		//}

		if (x!=0 && (ns.tp[x-1]&BC)==i)
			++nb, ++ns.tp[x-1];


		if (y!=0 && (ns.tl[x]&BC)==i)
			++nb, ++ns.tl[x];

		//if (x==2 && y==3){
		//	printf("AFTER\n");
		//	if (x!=0)
		//		printf("left: %d\n", ns.tp[x-1]);
		//	if (y!=0)
		//		printf("below %d\n", ns.tl[x]);

		//	printf("%d\n", nb);
		//	printf("\n\n");
		//}



		if (y!=0 && !finalized(ns.tl[x]))continue;

		if (x!=0){
			if (y==n-1)used[x-1][y]=1;
			if (y==n-1 && !finalized(ns.tp[x-1]))continue;
			if (y!=n-1 && !correct(ns.tp[x-1]))continue;
			assert((ns.tp[x-1]&3)<3);
		}

		if (y!=0)
			used[x][y-1]=1;


		if (x>0 && y>0)
			if ((ns.tp[x-1]&BC)==i && (ns.tl[x]&BC)==i && (ns.tl[x-1]&BC)==i)continue;

		
		ns.tp[x]=nb+i;
		r+=solve(x+1, y, ns);



		int &color=(i==0)?ns.wend:ns.bend;
		if (color==2)continue;
		++color;
		ns.tp[x]|=END;

		if (nb<2)r+=solve(x+1, y, ns);
	}


	return r;

}

int vx[]={0, -1, 0, 1};
int vy[]={-1, 0, 1, 0};

int solve2(){
	int i, j, k;
	int x, y;
	int r=0;

	REP(i, two(n*m)){
		int end[2];
		end[0]=end[1]=2;

		REP(x, m)
			REP(y, n){
				int act=(i&two(x*n+y))?1:0;
				int nx, ny, c, na;
				c=0;
				REP(k, 4){
					nx=x+vx[k], ny=y+vy[k];
					if (nx<0 || nx>=m || ny<0 || ny>=n)continue;
					na=(i&two(nx*n+ny))?1:0;
					if (act==na)++c;

				}
				if (x>0 && y>0){
					bool xa, xb, xc, xd;
					xa=i&two(x*n+y);
					xb=i&two((x-1)*n+y);
					xc=i&two(x*n+y-1);
					xd=i&two((x-1)*n+y-1);
					if (xa==xb && xb==xc && xc==xd)goto fail;

				}
				if (c>2 || c==0)
					goto fail;
				if (c==1){
					--end[act];
					if (end[act]<0)goto fail;
				}

			}
		if (end[0]!=0 || end[1]!=0)goto fail;

		++r;
		REP(y, n){
			REP(x, m)
				printf("%d", (i&two(x*n+y)?1:0));
			printf("\n");
		}
		printf("\n\n\n");

fail:;

	}
	return r;
}

char cl[MAX_N][MAX_N], mp[MAX_N][MAX_N];
char parent[MAX_N*MAX_N];
int xsa, xsb, xea, xeb, ysa, ysb, yea, yeb;

int getParent(int a){return (parent[a]==-1)?a:(parent[a]=getParent(parent[a]));}

bool connected(){
	memset(parent, -1, sizeof(parent));
	int np=m*n;
	int i;
	int x, y;
	REP(i, m*n){

		x=i/n, y=i%n;
		if (x<m && mp[x][y]==mp[x+1][y] && getParent(i)!=getParent(i+n)){
			//printf("merge %d %d >>%d %d (%d %d\n", x, y, x+1, y, getParent(i), getParent(i+n));
			parent[getParent(i+n)]=getParent(i), --np;
		}
		if (y<n && mp[x][y]==mp[x][y+1] && getParent(i)!=getParent(i+1)){
			//printf("merge %d %d >>%d %d (%d %d\n", x, y, x, y+1, getParent(i), getParent(i+1));
			parent[getParent(i+1)]=getParent(i), --np;
		}
	}
	//printf("connected\n");
	//REPV(y, n){
	//	REP(x, n)
	//		printf("%d", mp[x][y]);
	//	printf("\n");
	//}
	//printf("\n\n");

	//printf("%d\n", np);
	return np==2;
}

int procMap(){
	int i, j, k, c;
	int r=0;
	REP(i, two(n)){
		//if (i!=7)continue;
		memset(cl, 2, sizeof(cl));
		memset(mp, -1, sizeof(mp));
		cl[xsa][ysa]=cl[xea][yea]=cl[xsb][ysb]=cl[xeb][yeb]=1;
		mp[xsa][ysa]=mp[xea][yea]=1;
		mp[xsb][ysb]=mp[xeb][yeb]=0;

		REP(j, n){
			c=(i&two(j))>>j;
			assert(c==0||c==1);
			if (mp[0][j]!=-1 && mp[0][j]!=c)goto fail;
			mp[0][j]=c;
			//printf("%d %d=> %d\n", 0, j, c);
		}

		FOR(j, 1, n-1){
			if (mp[0][j]==mp[0][j-1])
				--cl[0][j], --cl[0][j-1];
		}
		REP(j, n)
			if (cl[0][j]<0 || cl[0][j]==2)goto fail;

		FOR(j, 1, m-1){
			REP(k, n){
				if (cl[j-1][k]==0){
					if (mp[j][k]!=-1 && 1-mp[j-1][k]!=mp[j][k])goto fail;
					mp[j][k]=1-mp[j-1][k];
				} else{
					assert(cl[j-1][k]==1);
					if (mp[j][k]!=-1 && mp[j-1][k]!=mp[j][k])goto fail;
					mp[j][k]=mp[j-1][k], --cl[j][k];
				}
				//printf("%d %d=> %d %d\n", j, k, mp[j][k], cl[j][k]);
				if (k!=0){
					if (mp[j][k]==mp[j][k-1])--cl[j][k], --cl[j][k-1];
					if (cl[j][k-1]<0 || cl[j][k-1]==2)goto fail;
				}
			}
			if (cl[j][n-1]<0 || cl[j][n-1]==2)goto fail;
		}


		if (connected())
			++r;
fail:;

	}
	return r;


}


int solve3(){
	int r;
	int sa, sb, ea, eb;

	r=0;
	REP(sa, n*m){//sa=x*n+y
		xsa=sa/n, ysa=sa%n;
		FOR(ea, sa+1, n*m-1){
			xea=ea/n, yea=ea%n;
			REP(sb, n*m){
				xsb=sb/n, ysb=sb%n;
				if (sb==sa || sb==ea)continue;
				FOR(eb, sb+1, n*m-1){
					xeb=eb/n, yeb=eb%n;
					if (eb==sa || eb==ea)continue;


					//printf("%d %d %d %d => %d %d, %d %d, %d %d, %d %d\n", sa, ea, sb, eb, xsa, ysa, xea, yea, xsb, ysb, xeb, yeb);
					r+=procMap();


				}
			}
		}
	}

	return r;
	//0000
	//1110
	//1010
	//1000

}

int main(){
	int t, tn;
	cin>>tn;
	int i, j;
	//	n=m=4;
	//	vector<int> a, b;
	//	a.pb(2);
	//	a.pb(2);
	//	a.pb(1);
	//	a.pb(0);
	//
	//	b.pb(2);
	//	b.pb(5+8);
	//	b.pb(6);
	//	b.pb(6);
	//	State s;
	//	s.tp=a, s.tl=b, s.wend=1, s.bend=2;
	//	printf("%d\n", solve(3, 3, s));
	//	exit(0);


	FOR(t, 1, tn){
		memset(used, 0, sizeof(used));
		REP(i, n)
			REP(j, m)
			CLR(st[i][j]);
		cin>>n>>m;
		if (m<n)swap(n, m);

		//printf("Case #%d: %d\n", t, solve(0, 0, State(n, m)));
		printf("Case #%d: %d\n", t, solve2());
		//printf("Case #%d: %d\n", t, solve3());
		break;
	}


	return EXIT_SUCCESS;
}


