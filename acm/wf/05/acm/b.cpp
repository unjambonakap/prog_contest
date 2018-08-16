//PROG: gsm
//LANG: C++
//ID: raveman.n2

#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstdlib>
#include<memory.h>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<set>
#include<map>
#include<queue>


using namespace std;

typedef pair<int,int>		pii;
typedef pair<double,int> pdi;
typedef pair<double,double> pdd;

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define CL(a,b)			memset(a,b,sizeof a)
#define SORT(v)			sort((v).begin(),(v).end())
#define pb			push_back
#define ST first
#define ALL(a) (a).begin(),(a).end()
#define ND second
#define MP make_pair



const int maxn=55;
const double eps=1e-9;
const int maxm=555;
int B, C, R, Q;

double xa[maxn], ya[maxn], xb[maxn], yb[maxn];
int to[maxm], from[maxm], last[maxn], prev[maxm], cost[maxm];
vector<pair<double,pii> > inter[maxm];
int on[maxn];
int ne;
int dx[maxn];


double dist(double a, double b){return a*a+b*b;}
void adde(int a, int b){
	to[ne]=b; from[ne]=a; prev[ne]=last[a]; last[a]=ne; ne++;
	swap(a,b);
	to[ne]=b; from[ne]=a; prev[ne]=last[a]; last[a]=ne; ne++;
}


void proc(int ex, int a, int b){
	double R=dist(xa[a]-xa[b],ya[a]-ya[b]);
	int u=from[ex], v=to[ex];
	//printf("%d %d XX %d %d\n", u, v, a, b);
	//printf("%lf %lf\n", dist(xa[a]-xb[u],ya[a]-yb[u]), dist(xa[b]-xb[v],ya[b]-yb[v]));
	double vx=xb[v]-xb[u], vy=yb[v]-yb[u];
	double B=2*(vx*(xa[b]-xa[a])+vy*(ya[b]-ya[a]));
	double C=dist(xb[u]-xa[a],yb[u]-ya[a])-dist(xb[u]-xa[b],yb[u]-ya[b]);

	//printf("%lf %lf xxxx %lf %lf\n", xa[a], ya[a], xa[b], ya[b]);
	//printf("%lf %lf xxxx %lf %lf\n", xb[u], yb[u], xb[v], yb[v]);
	//printf("%lf %lf\n", B, C);
	if (fabs(B)<eps) return;
	assert(fabs(B)>eps);
	double ka=-C/B;

	if (ka<0 || ka>1) return;

	double xo=xb[u]+ka*vx, yo=yb[u]+ka*vy;
	//printf("%lf >> %lf %lf\n", ka, xo, yo);
	//printf("%lf %lf\n", dist(xo-xa[a],yo-ya[a]),dist(xo-xa[b],yo-ya[b]));
	double xo2=xb[u]+(ka+0.01)*vx, yo2=yb[u]+(ka+0.01)*vy;
	//assert (fabs(dist(xo-xa[a],yo-ya[a])-dist(xo-xa[b],yo-ya[b]))<eps);
	if (dist(xo2-xa[a],yo2-ya[a])<dist(xo2-xa[b],yo2-ya[b])) swap(a,b);
	inter[ex].pb(MP(ka,MP(a,b)));
}

int go(int a, int b){
	memset(dx,0x7f,sizeof(dx));
	dx[a]=0;
	priority_queue<pii> q;
	q.push(MP(0,a));
	while(!q.empty()){
		int u=q.top().ND, d=-q.top().ST; q.pop();
		if (d!=dx[u]) continue;
		if (u==b) return d;
		for (int i=last[u]; i>=0; i=prev[i]){
			int nd=d+cost[i];
			if (dx[to[i]]>nd){dx[to[i]]=nd; q.push(MP(-nd,to[i]));}
		}
	}
	return -1;
}


int main(){
	freopen("gsm.in", "r", stdin);
	freopen("gsm.out", "w", stdout);
	int tn=0;
	while(cin>>B>>C>>R>>Q,B){
		REP(i,B) scanf(" %lf%lf", xa+i, ya+i);
		REP(i,C) scanf(" %lf%lf", xb+i, yb+i);
		ne=0;
		memset(last,-1,sizeof(last));
		REP(i,R){
			int a, b; scanf(" %d%d", &a,&b);
			--a; --b;
			adde(a,b);
		}

		REP(i,maxm) inter[i].clear();

		REP(i,C){
			on[i]=0;
			REP(j,B) if (dist(xb[i]-xa[j],yb[i]-ya[j])<dist(xb[i]-xa[on[i]],yb[i]-ya[on[i]])) on[i]=j;
		}
		REP(i,ne) REP(j,B) REP(k,j) proc(i,j,k);

		

		
		REP(i,ne){
			sort(ALL(inter[i]));
			int st=on[from[i]];
			int cnt=0;
			int k=0;
			//printf("%d\n", i);
			//printf("%d %d\n", from[i], to[i]);
			//printf("%d %d\n", on[from[i]], on[to[i]]);
			while(st!=on[to[i]]){
				//printf("on %d >> %d to %d\n",k,st,on[to[i]]);
				assert(k<inter[i].size());
				if (inter[i][k].ND.ST==st){
				       	++cnt, st=inter[i][k].ND.ND;
					//printf("CHANGE AT %lf\n", inter[i][k].ND);
				}
				++k;
			}
			cost[i]=cnt;
		}


		printf("Case %d:\n", ++tn);
		REP(i,Q){
			int a, b; scanf(" %d%d", &a,&b); --a; --b;
			int res=go(a,b);
			if (res==-1) printf("Impossible\n");
			else printf("%d\n", res);
		}
		
	}
	return 0;
}



