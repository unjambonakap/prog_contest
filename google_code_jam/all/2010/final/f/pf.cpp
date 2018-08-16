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
const int MAX_N=100;
const int MAX_P=4*MAX_N-2;

int mp[MAX_N][MAX_N];
int xmap[MAX_P], ymap[MAX_P];
char cl[MAX_N][MAX_N];
int smap[MAX_N][MAX_N];
int parent[MAX_N*MAX_N];
int xsa, xsb, xea, xeb, ysa, ysb, yea, yeb;
set<pii> bused, wused;
set<pii>::iterator itsa, itsb;

int n, m;

int getParent(int a){return (parent[a]==-1)?a:(parent[a]=getParent(parent[a]));}


//bool correct(){
//	memset(parent, -1, sizeof(parent));
//	int np=m*n;
//	int i, j;
//	int x, y, nx, ny;
//	REP(i, m*n){
//		x=i/n, y=i%n;
//		if (x<m && mp[x][y]==mp[x+1][y] && getParent(i)!=getParent(i+n))
//			parent[getParent(i+n)]=getParent(i), --np;
//		if (y<n && mp[x][y]==mp[x][y+1] && getParent(i)!=getParent(i+1))
//			parent[getParent(i+1)]=getParent(i), --np;
//
//	}
//	//if (np==2){
//	//	printf("found\n");
//	//	REPV(i, n){
//	//		REP(j, m)
//	//			printf("%d", mp[j][i]);
//	//		printf("\n");
//
//	//	}
//	//	printf("\n\n");
//
//	//}
//	return np==2;
//}


int procMap(){
	int i, j, k, c;
	REP(i, n)
		REP(j, m)
		cl[j][i]=2, mp[j][i]=smap[j][i], parent[j*n+i]=-1;

	if (mp[xsa][ysa]!=-1 && mp[xsa][ysa]!=1)return 0;
	if (mp[xea][yea]!=-1 && mp[xea][yea]!=1)return 0;
	if (mp[xsb][ysb]!=-1 && mp[xsb][ysb]!=0)return 0;
	if (mp[xeb][yeb]!=-1 && mp[xeb][yeb]!=0)return 0;

	cl[xsa][ysa]=cl[xea][yea]=cl[xsb][ysb]=cl[xeb][yeb]=1;
	mp[xsa][ysa]=mp[xea][yea]=1;
	mp[xsb][ysb]=mp[xeb][yeb]=0;
	int np=n*m;

	FOR(j, 1, n-1){
		if (mp[0][j]==mp[0][j-1])
			--cl[0][j], --cl[0][j-1], parent[getParent(j)]=getParent(j-1), --np;
		if (cl[0][j-1]<0 || cl[0][j-1]==2)return 0;
	}
	if (cl[0][n-1]==2)return 0;

	FOR(j, 1, m-1){
		REP(k, n){
			if (cl[j-1][k]==0){
				if (mp[j][k]!=-1 && 1-mp[j-1][k]!=mp[j][k])return 0;
				mp[j][k]=1-mp[j-1][k];
			} else{
				if (mp[j][k]!=-1 && mp[j-1][k]!=mp[j][k])return 0;
				mp[j][k]=mp[j-1][k], --cl[j][k];
				parent[getParent(j*n+k)]=getParent(j*n-n+k), --np;
			}
			//printf("%d %d=> %d %d\n", j, k, mp[j][k], cl[j][k]);
			if (k!=0){
				if (mp[j][k]==mp[j][k-1]){
					--cl[j][k], --cl[j][k-1];
					if (getParent(j*n+k)!=getParent(j*n+k-1))
						parent[getParent(j*n+k)]=getParent(j*n+k-1), --np;
				}
				if (cl[j][k-1]<0 || cl[j][k-1]==2)return 0;

			}
		}
		if (cl[j][n-1]<0 || cl[j][n-1]==2)return 0;
	}
	//return correct();
	return np==2;
}

int getX(int a){
	if (a<m)return a;
	if (a<m+n-1)return m-1;
	if (a<m+n-1+m-1)return m+n-1+m-a-2;
	return 0;
}
int getY(int a){
	if (a<m)return 0;
	if (a<m+n-1)return a-m+1;
	if (a<m+n-1+m-1)return n-1;
	return m+n-1+m-1+n-a-2;
}
struct Ray{
	Ray(int x, int y, int vx, int vy):x(x), y(y), vx(vx), vy(vy){}
	/*
	   ray of the form (x, y)+k(vx, vy)
	   (1) xa+ka*vxa=xb+kb*vxb
	   (2) ya+ka*vya=yb+kb*vyb

	   vya*(1)-vxa*(2)=>
	   vya*xa-vxa*ya=xb*vya-yb*vxa+kb*(vxb*vya-vyb*vxa)
	   =>>> kb=(vya*(xa-xb)-vxa*(ya-yb))/(vxb*vya-vyb*vxa)
	 */

	bool intersect(const Ray &r, int &_x, int &_y)const{
		int kb, d, e;
		if ((d=r.vx*vy-r.vy*vx)==0)return false;
		e=vy*(x-r.x)-vx*(y-r.y);
		kb=e/d;
		if (e!=kb*d)return false;
		_x=r.x+kb*r.vx, _y=r.y+kb*r.vy;
		return true;
	}


	int x, y, vx, vy;
};

Ray getRay(int a, int s){
	if (xmap[a]==0)
		return Ray(xmap[a], ymap[a], 1, -s);
	else if (xmap[a]==m-1)
		return Ray(xmap[a], ymap[a], -1, s);
	else if (ymap[a]==0)
		return Ray(xmap[a], ymap[a], s, 1);
	return Ray(xmap[a], ymap[a], -s, -1);
}

int solve(){
	int i, j, k;
	int a, b, c, d;
	int x, y;
	int r=0;
	int p=2*n+2*(m-2);
	REP(i, p)
		xmap[i]=getX(i), ymap[i]=getY(i);

	vector<Ray> diag;
	diag.pb(Ray(0, 0, 1, 1));
	diag.pb(Ray(m-1, 0, -1, 1));
	diag.pb(Ray(0, n-1, 1, -1));
	diag.pb(Ray(m-1, n-1, -1, -1));

//0111
//0101
//0001
//1111
//
//1000
//1010
//1110
//0000



	REP(a, p){
		FOR(b, a, p-2){
			//fprintf(stderr,  "%d %d\n", a, b);
			//if (a!=9 || b!=11)continue;
			REP(i, n)
				REP(j, m)
					smap[j][i]=-1;
			c=(b+1)%p, d=(p+a-1)%p;
			FOR(i, a, b)
				smap[xmap[i]][ymap[i]]=1;


			FOR(i, b+1, a-1+p)
				smap[xmap[i%p]][ymap[i%p]]=0;
			//REPV(i, n){
			//	REP(j, m)
			//		printf("%d", smap[j][i]);
			//	printf("\n");
			//}
			//printf("\n\n");
			vector<Ray> rays=diag;
			//printf("range %d %d to %d %d\n", xmap[a], ymap[a], xmap[b], ymap[b]);
			rays.pb(getRay(a, 1));
			rays.pb(getRay(b, -1));
			rays.pb(getRay(c, 1));
			rays.pb(getRay(d, -1));

			CLR(bused);
			CLR(wused);
			if (a==0 || a==m-1|| a==m-1+n-1 || a==m-1+n-1+m-1)
				wused.insert(MP(xmap[a], ymap[a]));
			if (b==0 || b==m-1|| b==m-1+n-1 || b==m-1+n-1+m-1)
				wused.insert(MP(xmap[b], ymap[b]));
			if (c==0 || c==m-1|| c==m-1+n-1 || c==m-1+n-1+m-1)
				bused.insert(MP(xmap[c], ymap[c]));
			if (d==0 || d==m-1|| d==m-1+n-1 || d==m-1+n-1+m-1)
				bused.insert(MP(xmap[d], ymap[d]));
			REP(i, SZ(rays)){
				//printf("ray: %d %d v (%d %d)\n", rays[i].x, rays[i].y, rays[i].vx, rays[i].vy);
				FOR(j, i+1, SZ(rays)-1){
					//		if (i!=2 ||j!=5)continue;
					//			printf("try ray: %d %d v (%d %d)\n", rays[i].x, rays[i].y, rays[i].vx, rays[i].vy);
					//			printf("try ray: %d %d v (%d %d)\n", rays[j].x, rays[j].y, rays[j].vx, rays[j].vy);
					if (!rays[i].intersect(rays[j], x, y))continue;
					if (x<0 || y<0 || x>m-1 || y>n-1)continue;
					if ((k=(abs(rays[i].x-x)+smap[rays[i].x][rays[i].y])%2)==(abs(rays[j].x-x)+smap[rays[j].x][rays[j].y])%2){
						if (k==1)
							wused.insert(MP(x, y));
						else
							bused.insert(MP(x, y));
					//	printf("intersect at %d %d in color %d\n", x, y, k);
					}
				}
            }

			if (SZ(wused)<2 || SZ(bused)<2)continue;
			//fprintf(stderr, "<< %d %d\n", SZ(wused), SZ(bused));

			FE(ita, wused){
				itsa=ita; ++itsa;
				for(; itsa!=wused.end(); ++itsa){
					FE(itb, bused){
						if (*itb==*ita || *itb==*itsa)continue;
						itsb=itb; ++itsb;
						for(; itsb!=bused.end(); ++itsb){
							if (*itsb==*ita || *itsb==*itsa)continue;
							xsa=ita->ST, ysa=ita->ND;
							xea=itsa->ST, yea=itsa->ND;
							xsb=itb->ST, ysb=itb->ND;
							xeb=itsb->ST, yeb=itsb->ND;
							//fprintf(stderr, "try %d %d === %d %d /////////// %d %d ==== %d %d\n", xsa, ysa, xea, yea, xsb, ysb, xeb, yeb);
							r+=procMap();
							//printf("%d\n", r);

						}
					}
				}
			}
			//break;
		}
	}

	return 2*r;

}

int main(){
	int t, tn, a;
	cin>>tn;

	FOR(t, 1, tn){
		cin>>m>>n;
		//fprintf(stderr, "Board: %d %d\n", n, m);
		//fprintf(stderr, "Case #%d: %d\n", t, a=solve());
		printf("Case #%d: %d\n", t, a=solve());
	}


	return EXIT_SUCCESS;
}

