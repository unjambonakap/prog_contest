#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int map[1000000];
int ask[100];
int list[1000000];

void solve(int K,int u,int c){
	int i;

	if (u == K) 
		return;
	i = (c+u)%(K-u);
	map[list[i]] = u+1;
	memcpy(&list[i],&list[i+1],sizeof(int)*(K-i-1));
	solve(K,u+1,i);
	



}

int main(){
	int t,K,s,i,c,j;

	scanf("%d",&t);
	for(i=0;i<t;i++){
		scanf("%d",&K);



		for (j=0;j<K;j++)
			list[j] = j;

		solve(K,0,0);
		printf("Case #%d:",i+1);

		
		scanf("%d",&s);
		for (j=0;j<s;j++){
			scanf("%d",&c);
			printf( " %d",map[c-1]);

		}
		printf("\n");





	}




}
