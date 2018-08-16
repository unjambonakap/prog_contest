#include"crypto.h"


gmp_randstate_t randstate;

void initcrypto(){
    gmp_randinit_default(randstate);
}
