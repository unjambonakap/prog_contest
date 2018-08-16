#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int data[100][25];

typedef struct conflict{
	int withId[100];
	int nC,done,id;
}conflict;

conflict dataConflict[100];
conflict *p[100];

int cross( int *a, int *b, int point){
	int infI=0, infIPlus=0;

	if(a[point-1] < b[point-1])
		infI = 1;
	if(a[point] < b[point])
		infIPlus = 1;

	if (infI != infIPlus || a[point-1] == b[point-1] || a[point] == b[point]) return 1;
	return 0;

	


}

int cmpConf( conflict *a, conflict *b){
	return a->nC < b->nC;
}

int solve( int n, int k ){

	int i,j,l;
	for (i=0;i<n;i++){
		dataConflict[i].done = dataConflict[i].nC = 0;
		dataConflict[i].id = i;
		memset(dataConflict[i].withId,0,sizeof(int)*100);
		p[i] = dataConflict+i;
	}



	for (i=0;i<n-1;i++){
		for(l=i+1;l<n;l++){

			for (j=1;j<k;j++){
				if (cross(data[i],data[l],j) == 1){

					dataConflict[i].withId[l] = 1;
					dataConflict[l].withId[i] = 1;
				

					dataConflict[i].nC ++;
					dataConflict[l].nC ++;
					j = k;
				}

			}
		}
	}
	sort(p,p+n,cmpConf);



	int ret = 0;
	vector<int> chart;
	vector<int>::iterator it;
	vector<int>::reverse_iterator rit;

	for (i=n-1;i>=0;i--){
//		printf("i => %d %d %dl\n", i,p[i]->done, p[i]->nC);
		if(p[i]->done == 1) continue;

		if(p[i]->nC == 0) return ret+1;


		chart.push_back(p[i]->id);

		rit = chart.rbegin();

		dataConflict[*rit].done = 1;

//		printf("%d\n", *rit);
		for(l=0;l<i;l++){
			if (p[l]->done == 0 && p[l]->withId[*rit] == 1){
				p[l]->nC --;
//p[l]->withId[*rit] = 0;
			}
		}

		sort(p,p+i,cmpConf);
		for(j=i-1;j>=0;j--){

			if (p[j]->done == 1) continue;
			int ok = 1;
			for (it=chart.begin();it < chart.end();it++){
				if(p[j]->withId[*it] == 1){
					ok = 0;
					break;
				}
			}

			if (ok == 1){ 
				chart.push_back(p[j]->id);
				rit = chart.rbegin();

				dataConflict[*rit].done = 1;

				for(l=0;l<j;l++){
					if (p[l]->done == 0 && p[l]->withId[*rit] == 1){
						p[l]->nC --;
//						p[l]->withId[*rit] = 0;
					}
				}
sort(p,p+j,cmpConf);
			}

		}

//for (it=chart.begin();it < chart.end();it++){
//			dataConflict[*it].done = 1;
//			printf("chart %d\n", *it);
//			for(j=0;j<i;j++){
//
//				if (p[j]->done == 0 && p[j]->withId[*it] == 1){
//					p[j]->nC --;
//					p[j]->withId[*it] = 0;
//				}
//			}
//		}
//		printf("\n\n");
		chart.clear();
		ret ++;




	}

	return ret;

}
int main(int argc, char **argv){
	int nTestCases;


	scanf("%d\n",&nTestCases);

	for(int i = 1; i <= nTestCases; i ++){
		int n,k;
		scanf("%d%d",&n,&k);
		for(int j = 0; j < n; j ++){
			for(int l = 0; l < k; l ++)
				scanf("%d", &data[j][l]);
		}


		printf("Case #%d: %d\n", i,solve(n,k));

	}

	return EXIT_SUCCESS;
}
