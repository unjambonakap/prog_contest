#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIZE(X) ((int)(X.size()))
typedef long long int64;
#define two(X) (1<<(X))
#define contain(S,X) (((S)&two(X))!=0)
template<class T> inline int countbit(T n){return (n==0)?0:(1+countbit(n&(n-1)));}

const int _MODE=9901;

int MODE;
int n,m,P[15],Q[15];
bool G[50][50];
int father[50];
map<int,int> M;
int ID[50],PT[50];
int f[two(16)][16];

int getID(int v)
{
	if (M.find(v)==M.end()) 
	{
		int size=M.size();
		M[v]=(size+1);
	}
	return M[v];
}
int getfather(int v)
{
	return (father[v]==0)?v:(father[v]=getfather(father[v]));
}
void merge(int u,int v)
{
	u=getfather(u);
	v=getfather(v);
	if (u!=v) father[u]=v;
}
int main()
{
//	freopen("..\\C.in","r",stdin);
//	freopen("..\\C-small-attempt0.in","r",stdin);freopen("..\\C-small-attempt0.out","w",stdout);
//	freopen("..\\C-small-attempt1.in","r",stdin);freopen("..\\C-small-attempt1.out","w",stdout);
//	freopen("..\\C-small-attempt2.in","r",stdin);freopen("..\\C-small-attempt2.ans","w",stdout);
	int testcase;
	scanf("%d",&testcase);
	for (int caseId=1;caseId<=testcase;caseId++)
	{
		printf("Case #%d: ",caseId);
		scanf("%d%d",&n,&m);
		for (int i=0;i<m;i++) scanf("%d%d",&P[i],&Q[i]);
		int result=0;
		M.clear();
		for (int i=0;i<m;i++) P[i]=getID(P[i]),Q[i]=getID(Q[i]);
		int size=SIZE(M);
		MODE=_MODE*n*2;
		for (int mset=0;mset<two(m);mset++)
		{
			int total=1;
			memset(father,0,sizeof(father));
			memset(G,false,sizeof(G));
			for (int i=0;i<m;i++) if (contain(mset,i)) 
			{
				G[P[i]][Q[i]]=G[Q[i]][P[i]]=true;
				merge(P[i],Q[i]);
			}
			bool bad=false;
			int nsegs=0;
			vector<int> L;
			for (int key=1;key<=size;key++) if (father[key]==0)
			{
				nsegs++;
				int c=0;
				for (int i=1;i<=size;i++) if (getfather(i)==key) PT[c]=i,ID[i]=(c++);
				if (c>1) L.push_back(c);
				int cnt=0;
				for (int i=0;i<c;i++) for (int j=i+1;j<c;j++) if (G[PT[i]][PT[j]]) cnt++;
				if (c==n)
				{
					bad=true;
					int current=0,current2=0;
					if (cnt==c || cnt==c-1)
						for (int src=0;src<c;src++)
						{
							for (int set=0;set<two(c);set++) memset(f[set],0,sizeof(f[set]));
							f[two(src)][src]=1;
							for (int set=0;set<two(c);set++) for (int i=0;i<c;i++) if (f[set][i]>0)
								for (int j=0;j<c;j++) if (!contain(set,j) && G[PT[i]][PT[j]]) 
									f[set+two(j)][j]=(f[set+two(j)][j]+f[set][i])%MODE;
							for (int i=0;i<c;i++) 
								if (G[PT[i]][PT[src]]) 
									current=(current+f[two(c)-1][i])%MODE;
								else
									current2=(current2+f[two(c)-1][i])%MODE;
						}
					if (cnt!=c) current=0;
					if (cnt!=c-1) current2=0;
					total=(current+current2*n)%MODE;
					continue;
				}
				int current=0;
				if (cnt==c-1)
				{
					for (int set=0;set<two(c);set++) memset(f[set],0,sizeof(f[set]));
					for (int i=0;i<c;i++) f[two(i)][i]=1;
					for (int set=0;set<two(c);set++) for (int i=0;i<c;i++) if (f[set][i]>0)
						for (int j=0;j<c;j++) if (!contain(set,j) && G[PT[i]][PT[j]]) 
							f[set+two(j)][j]=(f[set+two(j)][j]+f[set][i])%MODE;
					for (int i=0;i<c;i++) current=(current+f[two(c)-1][i])%MODE;
				}
				total=(int)(((int64)total*current)%MODE);
			}
			if (!bad) 
			{
				nsegs+=(n-size);
				int total2=1;
				for (int i=1;i<=nsegs;i++) total2=(int)((int64)total2*i%MODE);
				int total3=1;
				for (int i=1;i<=nsegs-1;i++) total3=(int)((int64)total3*i%MODE);
				int total4=0;
				for (int i=0;i<SIZE(L);i++) total4+=(L[i]-1);
				total3=(int)((int64)total3*total4%MODE);
				total=(int)((int64)total*(total2+total3)%MODE);
			}
			if (countbit(mset)%2==0) result=(result+total)%MODE;
			else result=(result+MODE-total)%MODE;
		}
		result=result/(n*2);
		printf("%d\n",result);
		fflush(stdout);
	}
	return 0;
}

