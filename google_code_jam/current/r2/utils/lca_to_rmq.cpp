#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <math.h>

#define LEN 14
int c;
#define SWAP(a,b) c = a, a = b, b = c;


#define MAX(a,b) (a < b)? b : a;
#define MIN_LVL(a,b) (level[a] < level[b]) ? a : b;
int tree[LEN] = {-1, 0, 1, 1, 1, 3, 3, 3, 6, 6, 7, 7, 10, 10};
int level[LEN] = {-1, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4};
int store[LEN][5];
int euler_tour[2 * LEN];


int build_euler_tour(int start, int parent_id, int startPos){
	int i, found;

	euler_tour[start++] = parent_id;
	found = 0;

	for(i = startPos; i < LEN; i ++){
		if (tree[i] == parent_id){
			start = build_euler_tour(start, i, i + 1);
			euler_tour[start++] = parent_id;
			found = 1;
		}else if (found)
			break;
	}
	return start;

}

int rmq(int a, int b){
	
	int start = 0;
	int lower;
	lower = -1;
	for (int i = 1; i < 2 * LEN; i ++){

		if (start == 0){
			if (euler_tour[i] == b)
				SWAP(a,b);
			
		
			if(euler_tour[i] == a){
			

				start = 1;
				lower = a;
			}

		}else{
			lower = MIN_LVL(lower,euler_tour[i]);

			if (euler_tour[i] == b)
				break;

		}


	}
	return lower;


}

int main(int argc, char **argv){

	memset(euler_tour, -1, sizeof(euler_tour) * 2 * LEN);
	build_euler_tour(0, 1, 2);

	for (int i = 0; i < 2 * LEN; i ++)
		printf("%d\n", euler_tour[i]);
	printf("=>>>>>>>> %d\n", rmq(7, 10));

	return EXIT_SUCCESS;

}

