//Solution by
//Luis Hernandez Corbato
//Compares <x,A^2y> = <x,By> for random vectors in {0,1}^n
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define maxtam 1000

int a[maxtam][maxtam], b[maxtam][maxtam];
int col[maxtam][maxtam + 1], row[maxtam][maxtam + 1];
int sb[maxtam + 1][maxtam + 1];
int n;

void permute (int i, int j){
//swaps columns i and j and rows i and j
 if (i == j) return;
 for (int k = 0; k < n; k++) {
   swap(a[i][k], a[j][k]);
   swap(b[i][k], b[j][k]);
 }
 for (int k = 0; k < n; k++) {
   swap(a[k][i], a[k][j]);
   swap(b[k][i], b[k][j]);
 }
 return;
}

void mix (int times){
//swaps randomly two rows and columns times times
  while (times--){
    permute(rand() % n, rand() % n);
  }
  return;
}

bool checksubmatrix (int x, int dx, int y, int dy){
//compares the sum of the entries in B(x..x+dx,y..y+dy) 
//and in the same submatrix of A^2
 int sum = 0;
 for (int i = 0; i < n; i++)
    sum += (row[i][y + dy] - row[i][y]) * (col[i][x + dx] - col[i][x]);  
 return (sum == sb[x + dx][y + dy] - sb[x][y + dy] - sb[x + dx][y] + sb[x][y]);  
}

bool heuristics (){
//return YES if for some random submatrices the sum of their entries in both
//B and A^2 are equal
 int times = maxtam;
 int x, y, dx, dy;
 
 while (times--){
   x = rand() % n;
   y = rand() % n;
   dx = 1 + rand() % (n - x);
   dy = 1 + rand() % (n - y);

   if (!checksubmatrix (x, dx, y, dy)) return false;  
 }
 return true;
}

int main (){
clock_t s, f;
s = clock();	

 for (;;){
   scanf("%u", &n);
   if(!n) break;
   for (int i = 0; i < n; i++)
     for (int j = 0; j < n; j++)
      scanf("%d", &a[i][j]);
   for (int i = 0; i < n; i++)
     for (int j = 0; j < n; j++)
      scanf("%d", &b[i][j]);
   
   mix(n);

   for (int i = 0; i < n; i++){
     row[i][0] = 0;
     col[i][0] = 0;
     for (int j = 0; j < n; j++){
       row[i][j + 1] = row[i][j] + a[i][j];
       col[i][j + 1] = col[i][j] + a[j][i];
     }
   }

   for (int i = 0; i <= n; i++) {
    sb[i][0] = 0;
    sb[0][i] = 0;
   }

   for (int i = 1; i <= n; i++)
     for (int j = 1; j <= n; j++)
      sb[i][j] = sb[i][j - 1] + sb[i - 1][j] - sb[i - 1][j - 1] + b[i - 1][j - 1];

   bool ret = heuristics();
   if (ret) printf("YES\n");
   else printf("NO\n");

 }

f = clock();
cerr << "Tiempo total: " << (double)(f - s)/CLOCKS_PER_SEC << endl;

 return 0;
}
