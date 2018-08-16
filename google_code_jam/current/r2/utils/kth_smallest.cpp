#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <string.h>


using namespace std;
int tb[] = {1, 2, 5, 3, 10, 16, 6, 4, 9, 12, 72, 7, 74};

void swap(int *a, int *b){
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

void disp(int *tb, int l){
	for (int i = 0; i < l; i++)
		printf("%d ", tb[i]);
	printf("\n");


}

int partition(int *tb, int start, int end, int pivotIndex){
	
	if (start == end)
		return start;


	int pivot, pivotNewIndex, i;
	//swap(tb, tb + pivotIndex);
//
//	i = start + 1;
//	pivotNewIndex = end;
//	pivot = tb[start];
//
//	while (i != pivotNewIndex){
//
//		if (tb[i] > pivot){
//			swap(tb + i, tb + pivotNewIndex);
//			pivotNewIndex --;
//		}else
//			i ++;
//	}
//	if (pivot < tb[pivotNewIndex])
//		pivotNewIndex --;
//	swap(tb + pivotNewIndex, tb + start);
//	return pivotNewIndex;

	swap(tb + end, tb + pivotIndex);
	pivot = tb[end];
	pivotNewIndex = start;

	for (i = start; i < end ; i++){
		if (pivot > tb[i]){
			swap(tb + pivotNewIndex, tb + i);
			pivotNewIndex ++;
		}
	}
	swap(tb + end, tb + pivotNewIndex);


	return pivotNewIndex;


}

int selection(int *tb, int l, int k, int pivotIndex){
	int pin, start, end;
	start = 0;
	end = l - 1;

	do{
		pin = partition(tb, start, end, pivotIndex);
		if (pin == k)
			return tb[pin];

		else if(pin < k)
			start = pin + 1;
		else
			end = pin - 1;
		pivotIndex = start;
	}while(pin != k);


}

int selection_median(int *tb_orig, int l, int k){
	int *tb;
	int nC, i, nL;
	int *median;

	tb = (int*)malloc(sizeof(int) * l);
	memcpy(tb, tb_orig, sizeof(int) * l);

	if (l < 10){
		disp(tb, l);
		sort(tb, tb + l);
		return tb[k];
	}



	nC = l / 5;
	nL = nC + (l - nC * 5);
	median = (int*)malloc(sizeof(int) * nL);

	for (i = 0; i < nC; i++){
		sort(tb + i * 5, tb + i * 5 + 5);
		median[i] = tb[i * 5 + 2];
		printf("median: %d\n", median[i]);
	}

	for (i = 0; i < nL - nC; i++){
		median[nC + i] = tb[nC * 5 + i];
	}

	int m = selection_median(median, nL, nL / 2);
	int *storeL[3], iL[3];

	for (i = 0; i < 3; i++){
		iL[i] = 0;
		storeL[i] = (int*)malloc(sizeof(int) * l);
	}


	int j;

	for (i = 0; i < l; i++){
		if (tb[i] < m)
			j = 0;
		else if (tb[i] == m)
			j = 1;
		else
			j = 2;

		storeL[j][iL[j]] = tb[i];
		iL[j]++;
	}

	printf("%d %d %d %d\n", k, iL[0], iL[1], iL[2]);
	printf(">>>median of medians : %d\n", m);
	if (k < iL[0])
		m = selection_median(storeL[0], iL[0], k);
	else if (k > iL[0] + iL[1])
		m = selection_median(storeL[2], iL[2], k - iL[0] - iL[1]);

	for (i = 0; i < 3; i++)
		free(storeL[i]);
	free(tb);

	return m;



}

int main(){

	int l = sizeof(tb)/sizeof(int);
	int ta[] = {1,2};



	int r;


	r = selection_median(tb, l, l / 2);
	printf("%d\n", r);












	return EXIT_SUCCESS;
}


