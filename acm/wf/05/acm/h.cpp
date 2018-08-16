//PROG: wall
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

int x[22],y[22];
int n;

int a[22];

int d[20][1<<15];

int diag(){
	CL(d,-1);
	d[0][0]=0;
	REP(i,n)REP(j,1<<n)if(d[i][j]!=-1){
		REP(k,n)if(!(j&(1<<k))){
			int nval = d[i][j] + abs(i+1-x[k])+abs(i+1-y[k]);
			if(d[i+1][j|(1<<k)]==-1 || d[i+1][j|(1<<k)] > nval)
				d[i+1][j|(1<<k)] = nval;
		}
	}
	return d[n][(1<<n)-1];
}

int solve(){
	int res = diag();
	FOR(i,1,n+1){
		int moves = 0;
		CL(a,0);
		REP(j,n){
			moves += abs(x[j]-i);
			a[y[j]]++;
		}
		FOR(j,1,n+1)if(a[j]==0){
			FOR(pos,1,n+1)if(a[pos]>1){
				a[pos]--;
				a[j]++;
				moves += abs(pos-j);
				break;
			}
		}
		res = min(res, moves);
	}
	return res;
}

int main(){
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
	int tc=0;
	while(cin>>n,n){
		REP(i,n) cin>>x[i]>>y[i];
		int best = solve();
		
		REP(i,n) swap(x[i],y[i]);
		best = min(best, solve());
		
		REP(i,n) x[i]=n+1-x[i];
		best = min(best, solve());
		

		printf("Board %d: %d moves required.\n",++tc,best);		
		puts("");
	}
	return 0;
}
