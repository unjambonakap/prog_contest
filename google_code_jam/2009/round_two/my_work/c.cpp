#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>

#include <cmath>

using namespace std;
#define MAX_S 50
#define REP(i,n) for(int i = 0;i < (int)(n); i ++)

int n, t, k;

int charts[110][30];
int relation[110][110];
int visited[110];
int prev[110];

int findDfs(int a){
	int i;
	if (a == -1)
		return 1;

	if (visited[a])
		return 0;

	visited[a] = 1;
	for (i = 0; i < n; i++){
		if (relation[a][i]){
			if (findDfs(prev[i])){
				prev[i] = a;
				return 1;
			}
		}
	}

	return 0;

}

int solve(){
	int ret, i;

	ret = 0;
	for (i = 0; i < n; i++){
		memset(visited, 0, sizeof(visited));
		if (!findDfs(i)) ret++;
	}

	return ret;
}

int main(){
	int i, j, l, m;
	int ret;

	scanf("%d", &t);

	for(i = 0; i < t; i++){
		scanf("%d %d", &n, &k);
		REP(j, n){
			REP(l, k)
				scanf("%d", &charts[j][l]);
			memset(relation[j], 0, 110 * sizeof(int));
		}
		REP(j, n){


			REP(l, n){
				if (l == j)
					continue;

				relation[j][l] = 1;
				REP(m, k){
					if (charts[j][m] <= charts[l][m]){
						relation[j][l] = 0;
						break;
					}
				}
			}
		}

		memset(prev, -1, sizeof(prev));

		ret = solve();
		
		printf("Case #%d: %d\n", i + 1, ret);

	}

}
