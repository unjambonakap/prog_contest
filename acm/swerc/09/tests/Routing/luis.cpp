//Código para el problema routing propuesto por David Garcia Soriano
//Autor: Luis Hernandez Corbato
//Comentarios: La solución es básicamente la misma que David pero implementada
//de manera más ineficiente, sin usar variables globales.
//Cuidado, he dejado un cerr al final que saca el tiempo que ha tardado

#include <cstdio>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstring>
using namespace std;

vector <int> bicolorea (vector <vector <int> > g, int n){
 //cada vertice solo tiene dos adyacentes
 bool vis[(1 << n)]; 
 memset (vis, 0, sizeof(vis));    
 vector <int> ret((1 << n));
 for (int i = 0; i < (1 << n); i++) if (!vis[i]){
     ret[i] = 0;
     vis[i] = true;
     int v = i, vant;
     while(1){
        vant = v;
        for (int j = 0; j < 2; j++) if (!vis[g[vant][j]]) v = g[vant][j];
        if (v == vant) break;
        vis[v] = true;        
        ret[v] = 1 - ret[vant];         
      }       
  }
  return ret;
}

vector <vector <int> > haz (vector <int> p, int n){ 
   
  if (n == 1){
     vector <vector <int> > ret;
     vector <int> v(1);
     if (p[0] == 0) v[0] = 0;
     else v[0] = 1;
     ret.push_back(v);
     return ret;
  }
  
 vector <vector <int> > g(1 << n);
 for (int i = 0; i < (1 << n); i++) 
   if (i % 2 == 1) g[i].push_back(i - 1);
   else g[i].push_back(i + 1);
 for (int i = 0; i < (1 << n); i++) 
   if (i % 2 == 1) g[p[i]].push_back(p[i - 1]);
   else g[p[i]].push_back(p[i + 1]);
 vector <int> color = bicolorea(g, n);
 //color = 0 va a la izda
 vector <int> a[2][2]; 
 for (int i = 0; i < (1 << n); i++)
   a[0][color[i]].push_back(i);
   
 for (int i = 0; i < (1 << n); i++) 
   a[1][color[p[i]]].push_back(p[i]);    
     
 vector <int> sini(1 << (n - 1)), sfin(1 << (n - 1));
 for (int i = 0; i < (1 << (n - 1)); i++) sini[i] = color[2 * i];
 for (int i = 0; i < (1 << (n - 1)); i++) sfin[i] = color[p[2 * i]];
 
 //ahora hay que hallar las permutaciones perm[lado] correspondientes a a[0][lado]->a[1][lado]
 int b[(1 << n)];
 vector <int> perm[2];
 for (int lado = 0; lado < 2; lado++){
   for (int i = 0; i < (1 << (n - 1)); i++) b[a[0][lado][i]] = i;
   for (int i = 0; i < (1 << (n - 1)); i++) perm[lado].push_back(b[a[1][lado][i]]);
  }
  
 vector <vector <int> > v[2], ret;
 for (int lado = 0; lado < 2; lado++)
   v[lado] = haz(perm[lado], n - 1);
   
 ret.push_back(sini);
 for (int i = 0; i < v[0].size(); i++){
   ret.push_back(v[0][i]);    
   for (int j = 0; j < v[1][i].size(); j++) ret[i + 1].push_back(v[1][i][j]); 
  }
 ret.push_back(sfin);
 return ret;
}


int main (){
  clock_t start, finish;
  start = clock();
  int n;
  bool primero = true;
  while ((cin >> n) && n > 0){
    
    if (!primero) cout << endl;
    else primero = false;
    
    vector <int> p(1 << n);
    for (int i = 0; i < (1 << n); i++) cin >> p[i];
    
    vector <vector <int> > ret = haz(p, n);
    
    for (int i = 0; i < ret.size(); i++){
       for (int j = 0; j < ret[i].size(); j++) cout << ret[i][j];
       cout << endl; 
    }
    
  }
  finish = clock();
  cerr << (double)(finish - start) / CLOCKS_PER_SEC << endl;
  return 0;
}
