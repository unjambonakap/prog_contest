#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 10000
#define maxm 100

int main (){
  
  int n, m;
  for (;;){
    scanf("%d %d", &n, &m);
    if (!n && !m) break;
    
    int source, dest, s[maxn], l[maxn], st, len;
    for (int i = 0; i < n; i++)
      scanf("%d %d %d %d", &source, &dest, &s[i], &l[i]);
      
    for (int i = 0; i < m; i++){
      scanf("%d %d", &st, &len);
      int overlaps = 0;
      for (int j = 0; j < n; j++)
        if (st + len > s[j] && st < s[j] + l[j]) overlaps++; 
      printf("%d\n", overlaps);
    }             
  }
  
  return 0;
}
