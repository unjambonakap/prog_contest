//PROG: workshops
//LANG: C++
//ID: raveman.n2

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<memory.h>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int,int>		pii;

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define CL(a,b)			memset(a,b,sizeof a)
#define SORT(v)			sort((v).begin(),(v).end())
#define pb			push_back

int n,m;
int p[1111],d[1111];
int c[1111],t[1111];

int main(){
	
	freopen("workshops.in","r",stdin);
	freopen("workshops.out","w",stdout);
	int tc=0;
	while(cin>>n,n){
		vector<pii> v;
		REP(i,n) scanf("%d %d",p+i,d+i),v.pb(pii(p[i],d[i]));
		cin>>m;
		REP(i,m){
			int x,y;
			scanf("%d %d:%d",c+i,&x,&y);
			t[i]=x*60+y-14*60;
		}
		int resa=0,resb=0;
		SORT(v);
		while(v.size()){
			int need_p = v.back().first;
			int need_d = v.back().second;
			v.pop_back();
			int best=-1;
			REP(i,m)if(t[i]>=need_d && c[i]>=need_p)
				if(best==-1 || t[i]<t[best])
					best = i;
			if(best==-1) resa++,resb+=need_p;
			else t[best] = -1;
		}
		printf("Trial %d:  %d %d\n\n",++tc,resa,resb);
		
	}
	return 0;
}
