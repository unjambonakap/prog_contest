#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <math.h>

int c;
#define SWAP(a,b) c = a, a = b, b = c;


#define MAX(a,b) (a < b)? b : a;
#define MIN_LVL(a,b) (level[a] < level[b]) ? a : b;
#define MAX_LEN 10

int tb[] = {2, 4, 3, 1, 6, 7, 8, 9, 1, 7};
int tree[MAX_LEN];
int stack[MAX_LEN];

void to_lca(){
	int stack_l = -1;
	int k;

	for (int i = 0; i < MAX_LEN; i ++){
		for (k = stack_l; k >= 0 && tb[i] < tb[stack[k]]; k --);

		if (k != -1)
			tree[i] = stack[k];

		if (k < stack_l)
			tree[stack[k+1]] = i;
		printf("%d => next lower: %d %d, over %d  ( %d ===== %d)\n", i, k, stack[k], stack_l, tree[i], tree[stack[k]]);

		stack_l = k + 1;
		stack[stack_l] = i;
	}
	tree[stack[0]] = -1;
	for (int i = 0; i < MAX_LEN; i ++)
		printf("%d => %d\n", i, tree[i]);
		

}

int main(int argc, char **argv){
	to_lca();


















	return EXIT_SUCCESS;
}



