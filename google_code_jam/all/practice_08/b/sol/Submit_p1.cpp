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
#define two(X) (1<<(X))

int n,m,X[15],Y[15];
int f[two(15)];
vector<int> A;

int main()
{
//	freopen("..\\B.in","r",stdin);
//	freopen("..\\B-small-attempt1.in","r",stdin);freopen("..\\B-small-attempt1.out","w",stdout);
//	freopen("..\\B-large.in","r",stdin);freopen("..\\B-large.out","w",stdout);
	int testcase;
	scanf("%d",&testcase);
	for (int caseId=1;caseId<=testcase;caseId++)
	{
		printf("Case #%d:",caseId);
		scanf("%d%d",&n,&m);
		for (int i=0;i<n;i++) scanf("%d%d",&X[i],&Y[i]);
		int H=-1,T=100000000;
		for (;H+1<T;)
		{
			int M=H+(T-H)/2;
			A.clear();
			for (int i=0;i<n;i++) for (int j=0;j<n;j++)
			{
				int x1=X[i],y1=Y[j];
				int x2=x1+M,y2=y1+M;
				int set=0;
				for (int k=0;k<n;k++) 
					if (X[k]>=x1 && X[k]<=x2 && Y[k]>=y1 && Y[k]<=y2)
						set|=two(k);
				A.push_back(set);
			}
			sort(A.begin(),A.end());
			reverse(A.begin(),A.end());
			int size=0;
			for (int i=0;i<SIZE(A);i++)
			{
				bool fd=false;
				for (int k=0;k<size;k++)
					if ((A[k]&A[i])==A[i])
						fd=true;
				if (!fd) A[size++]=A[i];
			}
			memset(f,255,sizeof(f));
			f[0]=0;
			for (int set=0;set<two(n);set++) if (f[set]>=0)
			{
				for (int i=0;i<size;i++) 
				{
					int newset=set|A[i];
					if (newset==set) continue;
					if (f[newset]<0 || f[set]+1<f[newset])
						f[newset]=f[set]+1;
				}
			}
			if (f[two(n)-1]<=m) T=M;
			else H=M;
		}
		printf(" %d\n",T);
		fflush(stdout);
	}
	return 0;
}

