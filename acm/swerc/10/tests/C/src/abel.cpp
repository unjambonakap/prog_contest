#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <vector>
#include <cstdio>
#include <complex>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <iostream>

#define X real()
#define Y imag()
#define PB push_back
#define MP make_pair
#define FR(i,n) for( long long i = 0; i < n; i ++ )
#define FOR(i,a,n) for(long long i = a; i < n; i ++)
#define FREACH(it,v) for( typeof(v.end()) it = v.begin(); it != v.end(); it ++ )
#define EPS 1e-9
using namespace std;

int mat1[1000][1000];
int mat2[1000][1000];

int ans1[1000], ans2[1000], ans3[1000];

int mult(bool fl, int * c, int * ans, int n) {
	FR(i,n) {
		int val=0;
		FR(j,n) val+= c[j]*(fl?mat1[i][j]:mat2[i][j]);
		ans[i]=val;
	}
}

int main() {
	
	int n;
	for(;;) {
		
		scanf("%d",&n);
		if(n==0) break;
		
		FR(i,n) FR(j,n) {
			scanf("%d",&mat1[i][j]);
		}
		
		
		FR(i,n) FR(j,n) {
			scanf("%d",&mat2[i][j]);
		}
		
		
		FR(rep,10) {
			FR(i,n) ans1[i]=(1+rand()%2);
			
			mult(1,ans1,ans2,n);
			mult(1,ans2,ans3,n);		
			mult(0,ans1,ans2,n);
			FR(i,n) if(ans3[i]!=ans2[i]) {
				goto NO;
			}			
		}
		
	
		printf("YES\n");
		continue;
		
	NO:;		
		
		printf("NO\n");		
		
		
	}
	
	
	
}