#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>


int pos[70];
int n, t;


int solve(){
	int i, j, c, temp, k;




	c = 0;
	for (i = 0; i < t - 1; i++){
		if (pos[i] > i){
			for (j = i + 1; j < t; j++){
				if (pos[j] <= i){
					c += j - i;
					temp = pos[j];

					for (k = j - 1; k >= i; k--)
						pos[k + 1] = pos[k];
					pos[i] = temp;

					break;
				}
			}

		}

	}
	return c;



}

int main(){
	int i, j, k, last, d, ret;

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &t);

		last = 0;
		for (j = 0; j < t; j++){
			last = 0;
			for (k = 0; k < t; k++){
				scanf("%1d", &d);

				if (d == 1)
					last = k;
			}
			pos[j] = last;
		}


		ret = solve();
		printf("Case #%d: %d\n", i + 1, ret);

	}

}
