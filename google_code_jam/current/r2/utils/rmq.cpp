#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <math.h>



int **store;
int tb[] = {2, 4, 3, 1, 6, 7, 8, 9, 1, 7};
int *m;
int n = sizeof(tb) / sizeof(int);
void trivial_sol_preprocess();

void trivial_sol_preprocess(){
	int i, j, s;

	s = n;
	for (i = 0; i < n; i++)
		store[i] = (int*)malloc(sizeof(int) * s);

	for (i = 0; i < n; i++){
		store[i][i] = i;
		for (j = i+ 1; j < s; j++){
			store[i][j] = (tb[j] < tb[store[i][j - 1]]) ? j : store[i][j - 1];
		}
	}
}
int trivial_sol_query(int a, int b){
	return store[a][b];
}

void trivial_sol_postprocess(){
	for (int i = 0; i < n; i++)
		free(store[i]);
}





void sqrt_sol_preprocess(){
	int i, j, s, t;

	s = floor(sqrt(n));
	m = (int*)malloc(sizeof(int) * s);

	t = -1;
	for (i = 0; i < n; i++){

		if (t == -1 || tb[i] < tb[t]){ t = i; }


		if ((i+ 1) % s == 0){ m[(i+ 1) / s - 1] = t; t = -1;  }
	}



}

int sqrt_sol_query(int a, int b){
	int i, e, enter;
	float s = floor(sqrt(n));
	e = -1;
	for (i = ceil(a / s); i <= floor(b / s); i++){
		
		if (e == -1 || tb[m[i]] <  tb[e]) e = m[i];
		printf("ici %d %d =< %d // %d\n", i, e, tb[e], tb[m[i]]);
	}


	for (i = a; i < ceil(a / s) * s;i++)
		printf("check a for %d\n", i);
		if (e == -1 || tb[i] <  tb[e]) e = i;

	for (i = (floor(b / s) + 1) * s; i <= b;i++){


		printf("check for %d\n", i);
		if (e == -1 || tb[i] <  tb[e]) e = i;
	}


	return e;


}
void sqrt_sol_postprocess(){
	free(m);

}

void sparse_tree_preprocess(){
	int i, j, s, e;

	s = ceil(log(n));
	for (i = 0; i < n; i++){
		store[i] = (int*)malloc(sizeof(int) * s);
		store[i][0] = i;
	}

	for (j = 1; (1 << j) < n; j++ ){
		for (i = 1; i < n && i + (1 << j) - 1 < n; i++){
			store[i][j] = (tb[store[i + ( 1 << (j - 1))][j - 1]] < tb[store[i][j - 1]]) ? store[i + (1 << (j - 1))][j - 1] : store[i][j - 1];
			printf("%d %d %d \n", i, j, store[i][j]);
		}
	}

}
int sparse_tree_query(int a, int b){
	b++;
	int p = floor(log(b - a) / log(2));

	return (store[a][p] < store[b - (1 << p)][p]) ? store[a][p] : store[b - (1 << p)][p];


}
void sparse_tree_postprocess(){

	for (int i = 0; i < n; i++)
		free(store[i]);
}


int main(int argc, char **argv){

	int s;


	store = (int**)malloc(sizeof(int*) * n);

	if (store == NULL){ fprintf(stderr, "Could not malloc() for store\n"); exit(EXIT_FAILURE); }

//	sqrt_sol_preprocess();
//	s = sqrt_sol_query(4,8);
//	printf("Ret => %d\n", s);
//	sqrt_sol_postprocess();
	sparse_tree_preprocess();
	s = sparse_tree_query(5,8);
	printf("Ret => %d\n", s);
	sparse_tree_postprocess();







	return EXIT_SUCCESS;
}
