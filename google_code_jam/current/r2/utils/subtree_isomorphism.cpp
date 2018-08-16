#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <assert.h>


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, b, a) for(i = (b); i > (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define SZ(a) (a).size()
#define pb push_back
#define ll long long

using namespace std;
typedef pair<int,int> pii;
#define MAX_N 110


int n, m;
int edgea[MAX_N][MAX_N], edgeb[MAX_N][MAX_N];
vector<vector<int> > deptha, depthb;

int edge[2 * MAX_N][2 * MAX_N];
int visited[2 * MAX_N];
int used[2 * MAX_N];
int fit[2 * MAX_N][2*MAX_N];
int U;


void set_depthb(int a, int d){

	int i;
	visited[a] = 1;

	if (depthb.size() <= d)
		depthb.pb(vector<int>());

	depthb[d].pb(a);

	REP(i, m)
		if (edgeb[i][a] && !visited[i])
			set_depthb(i, d + 1);

}

void set_deptha(int a, int d){

	int i;
	visited[a] = 1;

	if (deptha.size() <= d)
		deptha.pb(vector<int>());

	deptha[d].pb(a);

	REP(i, n)
		if (edgea[i][a] && !visited[i])
			set_deptha(i, d + 1);

}

int dfs(int a, int length){
	int i;

	if (visited[a] == U)
		return 0;
	visited[a] = U;

	REP(i, length)
		if (edge[a][i] && (used[i] == -1 || dfs(used[i], length))){
			used[i] = a, used[a] = i;
			return 1;
		}


	
	return 0;
	

}
void solve(){
	int i, j, k, l;
	int T;
	int ca, cb;
	int u, v;

	memset(visited, 0, sizeof(visited));
	depthb.clear();
	set_depthb(0, 0);

	REP(i, n){

		memset(visited, 0, sizeof(visited));
		deptha.clear();
		set_deptha(i, 0);


		int d=depthb.size()-1;

		memset(fit, 0, sizeof(fit));
		if (deptha.size() < depthb.size())
			continue;
		

		assert(deptha[d].size() > 0 && depthb[d].size()>0);
		REP(j, deptha[d].size())
			REP(k, depthb[d].size())
				fit[deptha[d][j]][depthb[d][k]+n]=fit[depthb[d][k]+n][deptha[d][j]]=1;
			
			
	


		//REP(j, n)
		//	printf("DEPTH A : %d => %d\n", j, deptha[j]);
		//REP(j, m)
		//	printf("DEPTH B : %d => %d\n", j, depthb[j]);


		REPV(j, d){
			int la, lb;
			la=deptha[j+1].size(), lb=depthb[j+1].size();
			if (la < lb)
				break;
			REP(l, depthb[j].size()){
				REP(k, deptha[j].size()){


					memset(edge, 0, sizeof(edge));
					REP(v, lb)
						REP(u, la)
							if (edgea[deptha[j][k]][deptha[j+1][u]] && edgeb[depthb[j][l]][depthb[j+1][v]] && fit[deptha[j+1][u]][depthb[j+1][v]+n])
								edge[u+lb][v]=edge[v][u+lb]=1;

					int cb=0;
					REP(v, lb)
						if (edgeb[depthb[j][l]][depthb[j+1][v]])
							cb++;

						

					int c = 0;
					memset(used, -1, sizeof(used));
					memset(visited, -1, sizeof(visited));
					REP(u, lb){
						U = u;
						if (dfs(u, lb+la))
							c++;
					}

					//printf("test fit %d(%d) %d(%d) matching: %d\n", k, deptha[k], l, depthb[l], c);
					if (c == cb)
						fit[deptha[j][k]][n+depthb[j][l]] = fit[n+depthb[j][l]][deptha[j][k]] = 1;
				}
		
			}
		}

		if (fit[n][i]){
			printf("YES\n");
			return;

		}

	}
	printf("NO\n");


}



int main(){
	int i, j, k;
	int T;
	int a, b;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d", &n);

		memset(edgea, 0, sizeof(edgea));
		memset(edgeb, 0, sizeof(edgeb));

		REP(j, n - 1){
			scanf("%d %d", &a, &b);
			a--, b--;
			edgea[a][b] = edgea[b][a] = 1;
		}

		scanf("%d", &m);
		REP(j, m - 1){
			scanf("%d %d", &a, &b);
			a--, b--;
			edgeb[a][b] = edgeb[b][a] = 1;
		}
		printf("Case #%d: ", i + 1);
		solve();

	}


	return EXIT_SUCCESS;
}

