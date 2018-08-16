#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

string s;
int v[52];
int a[52];
int n;

int allado (int lado, int vertice){
  if (vertice == lado) return (lado + n - 1) % n;
  else return (lado + 1) % n; 
}

int aparecenigual (int pos){
  if ((s[pos] >= 'A' && s[pos] <= 'Z' && s[a[pos]] >= 'A' && s[a[pos]] <= 'Z' ) ||
      (s[pos] >= 'a' && s[pos] <= 'z' && s[a[pos]] >= 'a' && s[a[pos]] <= 'z' )) return 0;
  return 1;
}

void procesa (int vertice, int lado, int label){   
   v[vertice] = label;
   int nlado = a[allado(lado, vertice)];
   int d = (vertice - allado(lado, vertice) + n) % n;   
   int k = aparecenigual(allado(lado, vertice));  
   int nvertice = nlado + (k + d) % 2;
   if (v[nvertice] != -1) return;
   procesa(nvertice, nlado, label);
   return;
}

int main (){
  
  for (;;){    
    cin >> s;
    if (s == "END") break;
    
    n = s.size();
    memset (a, -1, sizeof(a));
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (tolower(s[i]) == tolower(s[j])){
          a[i] = j;
          a[j] = i; 
        } 

    memset (v, -1, sizeof(v));
    int label = 0;
    for (int i = 0; i < n; i++) if (v[i] < 0){
      procesa(i, i, label);
      procesa(i, (i + n - 1) % n, label);
      label++;
    }
    
    bool orientable = true;
    for (int i = 0; orientable && i < n; i++)
      orientable = (s[i] != s[a[i]]);
      
    int eulerch = 1 - n/2 + label;    
    
    int arms = 0, legs = 0;
    if (orientable) legs = (2 - eulerch) / 2;
    else arms = 2 - eulerch;
    
    if (!arms && !legs) cout << "none" << endl;
    else if (arms) {
       cout << arms << " arm";
       if (arms > 1) cout << "s";
       cout << endl; 
    }
    else if (legs){
       cout << legs << " leg";
       if (legs > 1) cout << "s";
       cout << endl; 
    }
    
  } 
  
  return 0;
}
