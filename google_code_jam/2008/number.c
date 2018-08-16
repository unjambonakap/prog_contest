#include <stdio.h>
#include <stdlib.h>


unsigned long solve(unsigned long l){
	unsigned long a,b,c,i;

	a = 2;
	b = 6;
	for (i = 2; i <= l;i ++){
		c = b%1000;
		
	
		b = 1000+(6*b-4*a) % 1000;
		a = c;
	}

	return (b-1)%1000;

}


int main(){
	unsigned long n,i,l,r;


	scanf("%ld\n",&n);
	for(i = 0; i < n; i ++){
		scanf("%ld\n",&l);
		r = solve(l);

		if (r < 10)
			printf("Case #%ld: 00%ld\n", i+1,r);
		else if (r < 100)
			printf("Case #%ld: 0%ld\n", i+1,r);
		else
			printf("Case #%ld: %ld\n", i+1,r);
	}


	return EXIT_SUCCESS;

}
