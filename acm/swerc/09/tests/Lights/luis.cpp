//DP solution by Luis
#include <cstdio>
#include <iostream>
#include <ctime>
using namespace std;

#define maxm 1001
#define maxn 1001

long long p = 10567201LL;

long long exp (long long a, long long k){
   long long ret = 1LL;  
   if (k == 0) return ret;
   ret = exp(a, k / 2);
   ret = (ret * ret) % p;
   if (k % 2 == 1) ret = (ret * a) % p;  
   return ret;
}

long long inverso(int a){
   return exp((long long)a, p - 2); 
}

long long inv[maxm];
long long dos[maxn];

long long comb (int n, int m){
   long long c = dos[n];
   long long ret = 1LL;
   for (int i = 0; i < m; i++) ret = (ret * (c - i)) % p; 
   for (int i = 1; i <= m; i++) ret = (ret * inv[i]) % p;
   return ret;
}

int main (){
  clock_t start, finish;
  start = clock();
  
  dos[0] = 1LL;
  for (int i = 1; i < maxn; i++) dos[i] = (dos[i - 1] * 2) % p;
  for (int i = 1; i < maxm; i++) inv[i] = inverso(i);
  
  int n, m, v;
  
  for (;;){
   scanf("%d %d %d", &n, &m, &v);
   if (!n) break; 
   
   long long f[maxm];
   if (v) f[0] = 0LL;
   else f[0] = 1LL;
   f[1] = 1LL;
   for (int i = 2; i <= m; i++){
     f[i] = (comb(n, i - 1) - (dos[n] - i + 2) * f[i - 2] + p * p) % p;   
     f[i] = (f[i] * inv[i]) % p;
    }
    
     
   printf("%d\n", f[m]);
    
  }
  
  finish = clock();
  cerr << (double)(finish  -start) / CLOCKS_PER_SEC << endl;
  
  return 0;
}
