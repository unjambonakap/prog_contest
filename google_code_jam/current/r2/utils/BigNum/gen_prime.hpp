#ifndef MT10_GENPRIME
#define MT10_GENPRIME
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ext/hash_map>

#include <gmp.h>
#include <gmpxx.h>



int jacobi_symbol(mpz_t a, mpz_t b);
int grandom_odd(mpz_t a, int n);
int grandom(mpz_t a, int n);


#endif

