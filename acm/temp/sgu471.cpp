#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

#define bit(n) (1<<(n))
#define inf 1000000000
#define eps 1e-9
#define pb push_back
#define sz size()
#define mp make_pair
#define cl clear()
#define all(a) a.begin(),a.end()
#define fill(ar,val) memset(ar,val,sizeof ar)
#define MIN(a,b) if(a>b) a=b
#define MAX(a,b) if(a<b) a=b
#define sqr(x) ((x)*(x))
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

typedef vector<int> VI;
typedef pair<int,int> PII;
//typedef long long LL;

#define N 55

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n,t=0;
	while(scanf("%d",&n)>0)
	{
		if(n==1){printf("Case #%d: -1/1\n",++t);continue;}
		int i,j;
		int r1[N],r2[N],c1[N],c2[N];
		int markr[N]={0},markc[N]={0};
		for(i=0;i<n;i++) c1[i]=r1[i]=i-1,c2[i]=r2[i]=i+1<n?i+1:-1;
		for(;;)
		{
			bool exist=false;
			for(i=0;i<n;i++)
				for(j=0;j<n;j++) if(i!=j)
					if(!markr[i] && !markr[j])
					{
						if((r1[i]<0 || (r1[j]==r1[i] || r2[j]==r1[i])) &&
							(r2[i]<0 || (r1[j]==r2[i] || r2[j]==r2[i])))
						{
							exist=true;
							markr[i]=1;
							if(r1[i]>=0)
							{
								if(c1[r1[i]]==i) c1[r1[i]]=-1;
								if(c2[r1[i]]==i) c2[r1[i]]=-1;
							}
							if(r2[i]>=0)
							{
								if(c1[r2[i]]==i) c1[r2[i]]=-1;
								if(c2[r2[i]]==i) c2[r2[i]]=-1;
							}
						}
					}
			for(i=0;i<n;i++)
				for(j=0;j<n;j++) if(i!=j)
					if(!markc[i] && !markc[j])
					{
						if((c1[i]<0 || (c1[j]==c1[i] || c2[j]==c1[i])) &&
							(c2[i]<0 || (c1[j]==c2[i] || c2[j]==c2[i])))
						{
							exist=true;
							markc[j]=1;
							if(c1[j]>=0)
							{
								if(r1[c1[j]]==j) r1[c1[j]]=-1;
								if(r2[c1[j]]==j) r2[c1[j]]=-1;
							}
							if(c2[j]>=0)
							{
								if(r1[c2[j]]==j) r1[c2[j]]=-1;
								if(r2[c2[j]]==j) r2[c2[j]]=-1;
							}
						}
					}
			if(!exist) break;
		}
		int ans=0;
		for(i=0;i<n;i++) ans+=!markr[i];
		//printf("%d\n",ans);
		//for(i=0;i<n;i++) printf("%d",!markr[i]);
		//printf("\n");
		//for(i=0;i<n;i++) printf("%d",!markc[i]);
		//printf("\n");
		int d=2-ans%2;
		printf("Case #%d: %d/%d\n",++t,(2-ans)/d,ans/d);
	}
	return 0;
}
