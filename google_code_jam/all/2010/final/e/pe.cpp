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

#include "cg.hpp"


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

const double PI=2.*asin(1);
const double INF=1e20;
const double EPS=10e-6;
const int MAX_N=1010;

int n, r;
vector<pii> pl;

map<double, int> data[MAX_N][MAX_N];
double angTb[MAX_N][MAX_N];
double distTb[MAX_N][MAX_N];
double proced[MAX_N][MAX_N];
int seen[MAX_N][MAX_N];
map<double, int>  store[MAX_N][MAX_N];
set<double> inproc[MAX_N][MAX_N];

struct cmpA{ bool operator()(const pii& a, const pii& b)const{return a.ND<b.ND;} };

int procMax(int &a, int b){ return a=(b>a)?b:a; }

int procIt(double maxl, int a, int b){
	//printf("\n\n");
	//printf("=================%d %d %lf\n", a, b, maxl);
	if (maxl<=EPS)return INT_MIN;
	//printf("xxxxxxxxxxxxxxxxxxxxxxx %d\n", SZ(inproc[a][b]));


	map<double, int>::iterator itc;
	set<double>::iterator its;



	vi order;
   	vector<double> dista;
	int oa, ob, na, nb;
	int ra=0;
	double mb;
	double d=0.;
	oa=a, ob=b;

	itc=store[oa][ob].find(maxl);
	if (itc!=store[oa][ob].end())
		return itc->ND;
	its=inproc[oa][ob].find(maxl);
	assert(its==inproc[oa][ob].end());
	its=inproc[oa][ob].insert(maxl).ST;



	memset(seen, 0, sizeof(seen));
	map<double, int> *mr;

	while(1){
		dista.pb(d);
		order.pb(b);
		//printf("on %d with %lf\n", b, d);

		mr=&data[a][b];

		if (seen[a][b])
			break;

		itc=mr->upper_bound(maxl-d-EPS);
		if (itc==mr->begin())
			break;
		seen[a][b]=1;

		--itc;
		a=b, b=itc->ND;
		d+=itc->ST;

	}

	int i, j, pad, cycleN, pathN;
	double da, db, cycleC, pathToC;
	int startC;
	pathToC=cycleC=0.;
	startC=MAX_N;
	cycleN=0, pathN=0;


	if (seen[a][b]){
		if (a==oa && b==ob)
			cycleC=dista.back(), startC=0, cycleN=SZ(order)-1;
		else
			REP(i, SZ(order)-1)
				if (order[i]==a && order[i+1]==b){
					cycleC=dista.back()-dista[i+1], pathToC=dista[i+1], startC=i+1;
					cycleN=SZ(order)-i-2, pathN=i+1;
					break;
				}
		pad=(maxl-pathToC)/cycleC;
		ra=pathN+pad*cycleN;
		if (fabs(maxl-pathToC-pad*cycleC)<EPS)--ra;
	}else
		ra=SZ(order)-1;

	//printf("path: ");
	//FE(itz, order)
	//	printf(" %d", *itz);
	//printf("\n");

	//printf("<<<<<<<%d %lf %lf\n\n\n", startC, cycleC, pathToC);
	REP(i, SZ(order)){
		na=(i==0)?oa:order[i-1];
		nb=order[i];

		mr=&data[na][nb];

		if (i<startC){
			da=((i==SZ(order)-1)?maxl:dista[i+1])-dista[i];
	//		printf("la %d, cur %lf, remain %lf\n", nb, da, maxl-dista[i]);

			FE(it, *mr){
				itc=it;
				++itc;
				if (min((itc==mr->end())?da:itc->ST, da)-it->ST<EPS)break;
				//printf("%d>> %d at %lf/%lf>> %d /// %d\n", nb, it->ND, it->ST, min((itc==mr->end())?da:itc->ST, da)-it->ST, ra, i);
				assert(min((itc==mr->end())?da:itc->ST, maxl)-it->ST<maxl);
				procMax(ra, procIt(min((itc==mr->end())?da:itc->ST, maxl)-it->ST, nb, it->ND)+i+1);
			}
			//if (na==3 && nb==4)exit(0);
			//printf("======================\n\n");
		}else{
			if (i==SZ(order)-1)continue;
//			printf("yyyyyyyyyyyyyyyyyyyyyyyyyyy %d %d => %d:%d\n", i, startC, na, nb);
			
//			printf("can do %d cycles of %d => %lf: rope for cycle: %lf, before %d, remains after cycle: %lf\n", pad, cycleN, cycleC, maxl-pathToC, pathN, maxl-pathToC-pad*cycleC);
//			printf("BREAK BETWEEN %d and %d\n", nb, order[i+1]);
			FE(it, *mr){
				itc=it;
				++itc;

				if (itc==mr->end())
					da=dista[i+1];
				else da=dista[i]+itc->ST;


			//	printf("try (%d) %d %lf %lf with %lf from %d %d %d\n", i, it->ND, it->ST, da, maxl, oa, ob, pad);
			//	printf("%d %d %d ask %lf have %lf remove %lf\n", pad, cycleN, pathN, da+pad*cycleC, maxl, -pad*cycleC-dista[i]-it->ST);
			//	printf("call %lf %d %d add %d\n", min(maxl, da+pad*cycleC)-pad*cycleC-dista[i]-it->ST, nb, it->ND, pad*cycleN+pathN);
				assert(min(maxl, da+pad*cycleC)-pad*cycleC-dista[i]-it->ST<maxl);
//				printf("call a\n");
				procMax(ra, procIt(min(maxl, da+pad*cycleC)-pad*cycleC-dista[i]-it->ST, nb, it->ND)+pad*cycleN+i+1);
				--pad;
			//	printf("call %lf %d %d add %d\n", min(maxl, da+pad*cycleC)-pad*cycleC-dista[i]-it->ST, nb, it->ND, pad*cycleN+pathN);
				assert(min(maxl, da+pad*cycleC)-pad*cycleC-dista[i]-it->ST<maxl);
//				printf("call b\n");
				if (pad>=0)
					procMax(ra, procIt(min(maxl, da+pad*cycleC)-pad*cycleC-dista[i]-it->ST, nb, it->ND)+pad*cycleN+i+1);
				++pad;
			}
	//		printf("\n\n\n");


		}


	}
	//printf("ret %d\n", ra);
	//if (startC!=MAX_N)exit(0);

	inproc[oa][ob].erase(its);
	store[oa][ob].insert(MP(maxl, ra));
	return ra;
}

void setList(int a, int b, double maxl){
	int i, j;
	double ma, mb;
	double sAngle;
	map<double, int> &mr=data[a][b];
	map<double, int>::iterator it, ita, itb;
	if (proced[a][b]>=maxl)return;

	CLR(mr);
	proced[a][b]=maxl;

	sAngle=angTb[b][a]+PI;
	if (sAngle>=2*PI)
		sAngle-=2*PI;

	//if (a!=0 || b!=3)return;

	REP(i, n){
		if (i==b)continue;
		if (distTb[b][i]+EPS>=maxl)continue;

		ma=angTb[b][i];
		if (ma<=sAngle+EPS)ma+=2*PI;
		//printf("%d => %lf %lf\n", i, sAngle, ma);


		it=mr.upper_bound(distTb[b][i]);

		if (it==mr.begin()){
			mr.insert(MP(distTb[b][i], i));
			it=mr.begin();
			++it;
			while(it!=mr.end()){
				ita=it;
				++it;
				mb=angTb[b][ita->ND];
				if (mb<=sAngle+EPS)mb+=2*PI;

				if (ma<mb) mr.erase(ita);
				else break;
			}

		}
		else{
			if (it==mr.end()){
				--it;
				assert(it!=mr.end());

				mb=angTb[b][it->ND];
				if (mb<=sAngle+EPS)mb+=2*PI;

				if (ma<=mb){
					if (it->ST==distTb[b][i])
						mr.erase(it);
					mr.insert(mr.end(), MP(distTb[b][i], i));
				}
			}else{
				ita=it;
				--ita;
				mb=angTb[b][ita->ND];
				if (mb<=sAngle+EPS)mb+=2*PI;

				if (fabs(distTb[b][i]-distTb[b][ita->ND])<EPS){
					if (ma>mb)continue;
					itb=ita;
					--ita;
					mr.erase(itb);
				}

				mb=angTb[b][ita->ND];
				if (mb<=sAngle+EPS)mb+=2*PI;

				if (ma<=mb){
					mr.insert(it, MP(distTb[b][i], i));

					while(it!=mr.end()){
						ita=it;
						++it;
						mb=angTb[b][ita->ND];
						if (mb<=sAngle+EPS)mb+=2*PI;

						if (ma<mb) mr.erase(ita);
						else break;
					}
				}
			}

		}

	}
	//printf("%d %d %lf\n", a, b, maxl);
	//FE(itz, mr)
	//	printf(">>%d %lf\n", itz->ND, itz->ST);
	//exit(0);
	FE(itz, mr){
		it=itz; ++it;
		setList(b, itz->ND, (it==mr.end())?maxl:it->ST);
	}



}


void setData(){

	int i, j, k;

	REP(i, n)
		REP(j, n){
			if (i==j)continue;
			distTb[i][j]=distTb[j][i]=sqrt(sqr(pl[i].ST-pl[j].ST)+sqr(pl[i].ND-pl[j].ND));
			angTb[i][j]=(Point(pl[j])-Point(pl[i])).angle();//i to j
			angTb[j][i]=(Point(pl[i])-Point(pl[j])).angle();//j to i
		}
	angTb[0][n]=0;

	REP(i, n+1)
		REP(j, n+1)
		proced[i][j]=0.;

	setList(n, 0, r);
	j=n, i=0;
	//printf("%d ====> %d\n", j, i);
	//FE(it, data[j][i])
	//	printf("%lf %d\n", it->ST, it->ND);
	//printf("\n");

	//	REP(i, n){
	//		REP(j, n){
	//			if (i==j)continue;
	//			setList(j, i);
	//					printf("%d ====> %d\n", j, i);
	//					FE(it, data[j][i])
	//						printf("%lf %d\n", it->ST, it->ND);
	//					printf("\n");
	//
	//		}
	//	}
}

int solve(){

	setData();
	int i, j;
	REP(i, n)
		REP(j, n)
			CLR(inproc[i][j]), CLR(store[i][j]);

			

	return procIt((double)r, n, 0);
}

int main(){
	int t, tn;
	pii p;
	int i;

	cin>>tn;

	FOR(t, 1, tn){
		CLR(pl);
		cin>>n>>r;
		REP(i, n){
			cin>>p.ST>>p.ND;
			pl.pb(p);
		}

//		if (t!=77)continue;
//		printf("%d %d\n", n, r);
//		FE(it, pl)
//			printf("%d %d\n", it->ST, it->ND);
		fprintf(stderr, "Case #%d: %d\n", t, solve());
	}


	return EXIT_SUCCESS;
}

