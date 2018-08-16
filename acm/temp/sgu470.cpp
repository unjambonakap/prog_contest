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
typedef long long LL;

int main()
{
	freopen("deathcube.in","r",stdin);
	freopen("deathcube.out","w",stdout);
	LL x,y,z;
	int t=0;
	//while(scanf("%lld%lld%lld",&x,&y,&z)>0)
	while(cin >> x >> y >> z)
	{
		if(x>y) swap(x,y);
		if(y>z) swap(z,y);
		if(x>y) swap(x,y);
		LL ans=3*x*y*z-x*y-x*z-z*y;
		if(x==1)
		{
			if(y==1) ans+=0; else
			if(y==2) ans+=max(z-3,0); else
			{
				LL s=y%2+z%2;
				ans+=(z-2)/2*2+(y-2)/2*2;
				if(s==2) ans+=2; else
				if(s==1) ans+=0; else ans+=-1;
			}
		}
		else
		{
			if(x==2) ans+=3+(y-2)*(z-2); else
			if(x==3)
			{
				if(y==3)
				{
					ans+=(z-2)/2*4;
					if(z%2==0) ans+=8; else	ans+=12;
				}
				else
				{
					LL s=y%2+z%2;
					ans+=(y-2)*(z-2)/2*2+(y-2)/2*2+(z-2)/2*2;
					if(s==2) ans+=12; else
					if(s==1) ans+=8; else ans+=6;
				}
			}
			else
			{
				LL s=x%2+y%2+z%2;
				ans+=(y-2)*(z-2)/2*2+(x-2)*(y-2)/2*2+(x-2)*(z-2)/2*2;
				if(s==3) ans+=12; else
				if(s==2) ans+=10; else ans+=9;
			}
		}
		//printf("Case #%d: %lld\n",++t,ans);
		cout << "Case #" << ++t << ": " << ans << "\n";
	}
	return 0;
}
