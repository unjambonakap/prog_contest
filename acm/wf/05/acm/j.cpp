//PROG: zones
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

int nb[1<<20];
int n,m,k;
int r[11],s[11];
int a[22];

int main(){
	FOR(i,1,1<<20) nb[i] = nb[i/2] + (i%2);
	
	freopen("zones.in","r",stdin);
	freopen("zones.out","w",stdout);
	int tc=0;
	while(cin>>n>>m,n||m){
		REP(i,n) scanf("%d",&a[n-1-i]);
		cin>>k;
		REP(i,k){
			int c;
			cin>>c;
			int mask = 0;
			REP(j,c){
				int x;
				scanf("%d",&x);
				x--;
				mask|=(1<<(n-1-x));
			}
			r[i] = mask;
			scanf("%d",s+i);
		}
		int best = -1;
		int mask = 0;
		REP(i,1<<n)if(nb[i]==m){
			int sum = 0;
			REP(j,n)if(i&(1<<j)) sum += a[j];
			REP(j,k){
				int t = i&r[j];
				if(t){
					sum -= (nb[t]-1)*s[j];
				}
			}
			if(sum >= best){ // ?
				best = sum;
				mask = i;
			}
		}
		printf("Case Number  %d\n",++tc);
		printf("Number of Customers: %d\n",best);
		printf("Locations recommended:");
		for(int i=n-1;i>=0;i--)if(mask&(1<<i))
			printf(" %d",n-i);
		puts("");puts("");
	}
	return 0;
}
