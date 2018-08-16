#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ext/hash_map>

#include <gmp.h>
#include <gmpxx.h>

int main(){
	mpz_t a, b;
	mpz_init(a); mpz_init(b);


	mpz_set_ui(a, 13);
	mpz_set_ui(b, 71);

	printf("%d\n", mpz_jacobi(a, b));
}

