//PROG: streets
//LANG: C++
//ID: raveman.n2

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<memory.h>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

typedef pair<int,int>		pii;
typedef vector<int>		vi;

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define CL(a,b)			memset(a,b,sizeof a)
#define SORT(v)			sort((v).begin(),(v).end())
#define UN(v)			SORT(v),(v).erase(unique((v).begin(),(v).end()),(v).end())
#define pb			push_back

int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int  V[]={1,2,4,8};

int m[1111][1111];
int d[1111][1111];

int n;
int x[555],X[555];
int y[555],Y[555];

int main(){	
	freopen("streets.in","r",stdin);
	freopen("streets.out","w",stdout);
	int tc=0;
	while(cin>>n,n){
		vi xx,yy;
		REP(i,n){
			scanf("%d %d %d %d",&x[i],&y[i],&X[i],&Y[i]);
			xx.pb(x[i]);
			xx.pb(X[i]);
			yy.pb(y[i]);
			yy.pb(Y[i]);
		}
		
		int fx,fy,tx,ty;
		scanf("%d %d %d %d",&fx,&fy,&tx,&ty);
		xx.pb(fx);xx.pb(tx);
		yy.pb(fy);yy.pb(ty);
		
		UN(xx),UN(yy);
		
		fx = lower_bound(xx.begin(),xx.end(),fx)-xx.begin();
		tx = lower_bound(xx.begin(),xx.end(),tx)-xx.begin();
		fy = lower_bound(yy.begin(),yy.end(),fy)-yy.begin();
		ty = lower_bound(yy.begin(),yy.end(),ty)-yy.begin();
		REP(i,n){
			x[i] = lower_bound(xx.begin(),xx.end(),x[i])-xx.begin();
			X[i] = lower_bound(xx.begin(),xx.end(),X[i])-xx.begin();
			y[i] = lower_bound(yy.begin(),yy.end(),y[i])-yy.begin();
			Y[i] = lower_bound(yy.begin(),yy.end(),Y[i])-yy.begin();
		}
		
		int N = max(xx.size(),yy.size())+10;
		REP(i,N)REP(j,N)m[i][j]=0,d[i][j]=-1;
		REP(i,n)
			if(x[i]==X[i]){
				if(y[i]>Y[i]) swap(y[i],Y[i]);
				for(int j=y[i]+1;j<=Y[i];j++)
					m[x[i]][j]|=1,
					m[x[i]+1][j]|=2;
			}else{
				if(x[i]>X[i]) swap(x[i],X[i]);
				for(int j=x[i]+1;j<=X[i];j++)
					m[j][y[i]]|=4,
					m[j][y[i]+1]|=8;
			}
		d[fx][fy]=0;
		deque<pii> q;
		q.pb(pii(fx,fy));
		while(!q.empty()){
			int x = q.front().first;
			int y = q.front().second;
			q.pop_front();
			
			if(x==tx && y==ty){
				printf("City %d\n",++tc);
				printf("Peter has to cross %d streets\n",d[x][y]);
				break;
			}
			
			REP(dd,4){
				int nx = x + dx[dd];
				int ny = y + dy[dd];
				if(nx>=0 && ny>=0 && nx<N && ny<N){
					if(!(m[x][y]&V[dd])){
						if(d[nx][ny]==-1 || d[nx][ny] > d[x][y]){
							d[nx][ny] = d[x][y];
							q.push_front(pii(nx,ny));
						}
					}
					if((m[x][y]&V[dd])){
						if(d[nx][ny]==-1 || d[nx][ny] > d[x][y] + 1){
							d[nx][ny] = d[x][y] + 1;
							q.pb(pii(nx,ny));
						}
					}
				}
			}
		}
	}
	return 0;
}
