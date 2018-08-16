#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

typedef std::pair<int,int> pii;

#define MAX_N 500
#define MAX_K 100
#define MOD 1000000009

int n, k;
int root;

int edges[MAX_N][MAX_N];
int count[MAX_N][MAX_N];
int adj[MAX_N];
int parent[MAX_N];


int solve(){
	int i, j;
	std::queue<int> q;
	int nd, c;

	q.push(root);
	memset(count, -1, sizeof(count));
	memset(adj, 0, sizeof(adj));
	memset(parent, -1, sizeof(parent));
	parent[root]=-2;
	
	while(!q.empty()){
		nd=q.front();
		q.pop();

		int a, b;

		if (parent[nd] == -2)
			a=b=0;
		else if (parent[parent[nd]] == -2)
			a=1, b=adj[parent[nd]]-1;
		else
			a=1, b=adj[parent[nd]];

		c=0;
		REP(i, n)
			if (edges[nd][i] && parent[i] == -1){

				parent[i]=nd;
				q.push(i);

				count[nd][i]=count[i][nd]=k-c-a-b;
				if (count[nd][i] <= 0)
					return 0;
				c++;
					
			}
		adj[nd]=c;
	}

	ll m=1;
	REP(i, n)
		REP(j, i+1)
			if (edges[i][j])
				m=(m*count[i][j])%MOD;

	return ((m+MOD)%MOD);


}

int main(){
	int i, j, T;
	int a, b;

	scanf("%d", &T);
	REP(i, T){

		scanf("%d %d", &n, &k);

		memset(edges, 0, sizeof(edges));
		REP(j, n-1){
			scanf("%d %d", &a, &b);
			
			a--, b--;
			if (j == 0)
				root=a;
			edges[a][b]=edges[b][a]=1;
		}
		printf("Case #%d: %d\n", i+1, solve());


	}



	return EXIT_SUCCESS;
}

