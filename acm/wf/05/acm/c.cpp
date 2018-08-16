//PROG: judges
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
typedef vector<int>		vi;

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define CL(a,b)			memset(a,b,sizeof a)
#define SORT(v)			sort((v).begin(),(v).end())
#define pb			push_back

typedef pair<int, pii>  	p3;

p3 e[1111];
int n;
int p[22],dc;
int P(int x){return p[x]==x?x:p[x]=P(p[x]);}

vi sm[22];
vi xx;
bool go(int ver,int par=-1){
	if(ver==dc) {xx.pb(ver);return 1;}
	REP(i,sm[ver].size()) if(sm[ver][i]!=par)
		if(go(sm[ver][i],ver)){
			xx.pb(ver);
			return 1;
		}
	return 0;
}

int main(){	
	freopen("judges.in","r",stdin);
	freopen("judges.out","w",stdout);
	int tc=0;
	while(cin>>n,n!=-1){
		int m;
		scanf(" %d %d",&dc,&m);
		dc--;
		REP(i,m){
			int x,y,z;
			scanf("%d %d %d",&x,&y,&z);
			x--,y--;
			e[i] = p3(z,pii(x,y));
		}
		sort(e,e+m);
		int k;
		scanf(" %d",&k);
		int mask = 0;
		vi jd;
		REP(i,k){
			int x;
			scanf("%d",&x);
			x--;
			jd.pb(x);
			mask|=(1<<x);
		}
		mask |= (1<<dc);
		int best = 1011111111,btmask;
		vi best_ct;
		int iter_mask = ((1<<n)-1)^mask;
		for(int i = ((1<<n)-1)&iter_mask;;i=(i-1)&iter_mask){
			int ii = i | mask;
			
			vi cities;
			REP(j,n){
				p[j] = j;
				if(ii&(1<<j)) cities.pb(j);
			}
			
			int num = 0;
			int mst = 0;
			REP(j,m)if(ii&(1<<e[j].second.first))
				if(ii&(1<<e[j].second.second)){
					int p1 = P(e[j].second.first);
					int p2 = P(e[j].second.second);
					if(p1!=p2){
						num++;	
						mst += e[j].first;
						p[p1] = p2;
					}
				}
			
			if(num == cities.size() -1)if(best > mst || best == mst && (cities.size() < best_ct.size() || cities.size()==best_ct.size() && cities < best_ct)){
				best = mst;
				best_ct = cities;
				btmask = ii;
			}
			if(i==0) break;
		}
		
		printf("Case %d: distance = %d\n",++tc,best);
		REP(j,n) p[j] = j,sm[j].clear();
		REP(j,m)if(btmask&(1<<e[j].second.first))
			if(btmask&(1<<e[j].second.second)){
				int p1 = P(e[j].second.first);
				int p2 = P(e[j].second.second);
				if(p1!=p2){
					p[p1] = p2;
					sm[e[j].second.first].pb(e[j].second.second);
					sm[e[j].second.second].pb(e[j].second.first);
				}
			}
		REP(i,k){
			xx.clear();
			printf("   ");
			go(jd[i]);
			reverse(xx.begin(),xx.end());
			REP(j,xx.size()){
				if(j) printf("-");
				printf("%d",xx[j]+1);
			}
			puts("");
		}
		
			
		puts("");
	}
	return 0;
}
