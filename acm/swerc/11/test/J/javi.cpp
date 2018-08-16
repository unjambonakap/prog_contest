// O(n log log n) preprocessing + O(n) per query.
// Javier Gomez Serrano

#include <iostream>
#include <ctime>

#define MOD 1000000007
#define MAXN 10000000
#define NPR 2000000

using namespace std;

int composite[MAXN+1];
int primes[NPR];
int nprimes;

// Returns x^p mod MOD
long long power(long long x, long long p){
     if (p == 0) return 1;
     long long a = power(x,p/2);
     long long res = a*a;
     res%= MOD;
     if (p%2) res*=x;
     res%= MOD;
     return res;
}

void gen_primes(){
     for (int i=2;i<=MAXN;i++){
         if (!composite[i]){
            primes[nprimes++] = i;
            for (long long j = (long long)i*(long long)i; j<= MAXN; j+=i){
                composite[j] = 1;
            }
         }
     }
}

int main(){
    clock_t t1,t2;
    int n;
    t1 = clock();
    gen_primes();
    while (cin >> n, n){
          long long res = 1;
          for (int i = 0; i < nprimes && primes[i] <= n; i++){
              int exponent = 0;
              int r = n;
              while (r != 0){
                    exponent+=r/primes[i];
                    r/=primes[i];
              }
              if (exponent%2) exponent--;
              res*=power(primes[i],exponent);
              res%=MOD;
          }
          cout << res << endl;
    }
    t2 = clock();
    cerr << (double)(t2 - t1)/CLOCKS_PER_SEC << endl;
}
