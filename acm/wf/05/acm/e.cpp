//PROG: sunlight
//LANG: C++
//ID: raveman.n2

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<memory.h>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<set>
#include<map>


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
#define ND second

const double pi=acos(-1.);
const int maxn=111;
int x[maxn]; 
int m[maxn];
int h, w;
int n;



int main(){
	freopen("sunlight.in", "r", stdin);
	freopen("sunlight.out", "w", stdout);
	int tn=0;
	while(cin>>n,n){
		if (tn) puts("");
		printf("Apartment Complex: %d\n", ++tn);
		x[0]=0;
		scanf(" %d%d", &w,&h);
		REP(i,n){
			if (i){
				int u;
				scanf(" %d", &u);
				x[i]=x[i-1]+u+w;
			}
			scanf(" %d", m+i);
		}
		while(1){
			int a; scanf(" %d", &a);
			if (!a) break;
			puts("");
			printf("Apartment %d: ", a);
			int v=a%100, u=a/100;
			--u; --v;
			if (u<0 || v<0 || v>=n || u>=m[v]){puts("Does not exist"); continue;}

			double lb=0, ub=pi;
			double xo=x[v], yo=1.*h*u;
			REP(i,v){
				double xu=x[i]+w, yu=1.*h*m[i];
				double ang=atan2(yu-yo, xu-xo);
				if (ang<0) continue;
				ub=min(ub,ang);
			}
			xo+=w;
			for (int i=v+1; i<n; ++i){
				double xu=x[i], yu=1.*h*m[i];
				double ang=atan2(yu-yo, xu-xo);
				if (ang<0) continue;
				lb=max(lb,ang);
			}
			int st=5*3600+37*60;
			int nd=18*3600+17*60;
			int A=(pi-ub)/pi*(nd-st)+st;
			int B=(pi-lb)/pi*(nd-st)+st;
			printf("%02d:%02d:%02d - %02d:%02d:%02d\n", A/3600,A/60%60,A%60,B/3600,B/60%60,B%60);
		}

	}
	return 0;
}

