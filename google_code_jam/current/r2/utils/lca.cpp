#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <math.h>

#define LEN 14
int c;
#define SWAP(a,b) c = a; a = b; b = c;
int tree[LEN] = {0, 0, 0, 1, 1, 1, 4, 4, 5, 5, 8, 8};
int level[LEN] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4};
int store[LEN][5];

void init_lca(){
	int i, j;

	for (i = 0; i < LEN; i ++){
		for (j = 0; (1 << j) < LEN; j ++)
			store[i][j] = -1;
		store[i][0] = tree[i];
	}
	for (j = 1; (1 << j) < LEN; j ++){

		for (i = 0; i < LEN; i ++){
			if (store[i][j - 1] != -1)
				store[i][j] = store[store[i][j - 1]][j - 1];
		}

	}

}

int request_lca(int a, int b){
	int c;
	if (level[a] < level[b]){
		c = a; a = b; b = c;
	}

	while(level[a] > level[b]){

		printf("%d\n", (int)floor(log(level[a] - level[b]) / log(2)));
		a = store[a][(int)floor(log(level[a] - level[b]) / log(2))];
	}
	printf("level a %d %d (%d %d)\n", level[a], level[b], a, b);
	int l = floor(log(level[a]) / log(2));
	if (a == b)
		return a;

	for(l; l >= 0; l --){
		printf("%d %d %d\n", a, l, store[a][l]);
		printf("%d %d %d\n", b, l, store[b][l]);
		if (store[a][l] != store[b][l]){
			a = store[a][l - 1];
			b = store[b][l - 1];
		}
	}

	return store[a][0];



}


int main(int argc, char **argv){
	init_lca();
	int a = request_lca(11, 9);
	printf("return: %d\n", a);








	return EXIT_SUCCESS;

}

