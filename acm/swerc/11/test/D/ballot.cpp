// Solution to 'Distributing Ballot Boxes'.
// Luis Hernandez Corbato.
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define max 500000
#define maxpop 5000000
int a[max];
int N, B;

bool ok (int x){
  int c = 0;
  for (int i = 0; i < N && c <= B; i++)
    c += (a[i] + x - 1) / x;
  return (c <= B);
}

int busca (){
  int x = 1;
  int y = maxpop;
  while (y - x > 1){
    int z = (x + y) / 2;
    if (ok(z)) y = z;
    else x = z;      
  }  
  if (ok(x)) return x;
  else return y;
}

int main (){
 
 for (;;){
   cin >> N >> B;
   if (N < 0) break;    
   for (int i = 0; i < N; i++) cin >> a[i];
   int ret = busca();
   cout << ret << endl;
 }        
  return 0;
}
