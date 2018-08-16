#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>

#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PB push_back


#define MAX_N 2000
#define MAX_C 2000

int n, c;
int client[MAX_C][MAX_N];
int c_c[MAX_C];

int m[MAX_N];
int m_id[MAX_C];


int solve(){
	int found;
	int i, j, k;

	while(1){
		found = 0;

		REP(i, c){
			if (c_c[i] == 0){
				found = 1;
				if (m_id[i] == -1)
					return -1;

				m[m_id[i]] = 1;

				c_c[i] = -1;
				REP(j, c){
					if (c_c[j] == -1)
						continue;

					if (client[j][m_id[i]] == 0)
						--c_c[j];
					else if (client[j][m_id[i]] == 1)
						c_c[j] = -1;
					
				}
				break;

			}

		}

		
	


		if (found == 0)
			break;
	}
	return 0;
}



int main(){
	int x, i, j, k, malt, n_m, id;

	scanf("%d", &x);
	REP(i, x){
		scanf("%d", &n);
		scanf("%d", &c);

		memset(m, 0, sizeof(m));
		REP(j, c){
			memset(client[j], -1, sizeof(int) * n);
			c_c[j] = 0;

			scanf("%d", &n_m);
			m_id[j] = -1;
			REP(k, n_m){

				scanf("%d %d", &id, &malt);
				--id;

				if (!malt) 
					++c_c[j];
				else
					 m_id[j] = id;


				client[j][id] = malt;

			}
		}
		printf("Case #%d:", i + 1);
		if (solve() == -1)
			printf(" IMPOSSIBLE");
		else
			REP(j, n)
				printf(" %d", m[j]);

		printf("\n");

	}


	return EXIT_SUCCESS;
}

