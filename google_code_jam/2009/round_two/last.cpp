#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_N 110
#define MAX_K 35
int N,K;

int curves[MAX_N][MAX_K];
int superior[MAX_N][MAX_N];
int linkedSup[MAX_N],linkedInf[MAX_N];
int in_use[MAX_N];

#define REP(i,n) for(i=0;i<n;i++)

using namespace std;


int findSup(int a){
	int i,j,k;

//if (a == -1 || a >= N) exit(0);

	//printf("%d\n", a);
	if (in_use[a] == 1)
		return 0;

	in_use[a] = 1;

	REP(i,N){
		if(i == a || in_use[i] == 1 || superior[a][i] == 0) continue;
		if(linkedSup[a] == i) continue;

		if(linkedInf[i] == -1 or findSup(linkedInf[i]) == 1){
			linkedSup[a] = i,linkedInf[i] = a;
			return 1;
		}

	}

	//in_use[a] = 0;

	return 0;

}



int main(int argc, char** argv){
	int nT,i,j,k,l;


	scanf("%d", &nT);

	for(i=0; i < nT; i++){

		scanf("%d%d", &N, &K);
		REP(j,N){
			REP(k,K)
				scanf("%d", &curves[j][k]);
		}
		REP(j,N){
			memset(superior[j],1,sizeof(int)*N);
			REP(l,N){
				if(l == j) continue;

				REP(k,K)
					if (curves[j][k] >= curves[l][k]) break;// break if curve j ge l

				if(k != K) superior[j][l] = 0;//l is not superior to j all the time
			}
		}

		int nSup=0;

		memset(linkedInf, -1, sizeof(int)*MAX_N);
		memset(linkedSup, -1, sizeof(int)*MAX_N);

		REP(j,N){
			memset(in_use,0,sizeof(in_use));
			if (findSup(j) == 1)
				nSup ++;
		}
		printf("Case #%d: %d\n", i+1, N - nSup);
	}


	return 0;

}


