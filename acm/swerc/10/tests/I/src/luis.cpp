//Solution to Locks and Keys
#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

#define maxv 1500

typedef struct vertex {
  int par, door;
  vector <int> ch, key;
};

int v, c, root, finish;
int wdoor[maxv + 2], wkey[maxv + 2];
int adj[maxv][maxv];
vertex g[maxv];
vector <int> path;

void buildtree (int vert, int parent){
  g[vert].par = parent;
  for (int i = 0; i < v; i++)
   if (adj[vert][i] >= 0 && i != parent){
     g[vert].ch.push_back(i);
     buildtree(i, vert);
     if (adj[vert][i] >= 1) {
       g[i].door = adj[vert][i] - 1;
       wdoor[g[i].door] = i;
     }
   }  
 return;
}

vector <int> build_path (int ver){
  vector <int> w;
  while (ver != root){
    w.push_back(ver);
    ver = g[ver].par;
  }
  w.push_back(root);
  return w;
}

void add_path (vector <int>& ret, int start, int end){
  vector <int> first, second;
  first = build_path(start);
  second = build_path(end);
  reverse(second.begin(), second.end());
  for (int i = 1; i < first.size(); i++) ret.push_back(first[i]);
  for (int i = 1; i < second.size(); i++) ret.push_back(second[i]);
}

int main (){
 clock_t starttime, fintime;
 starttime = clock();

 int aux, maxtampath = 0;
 for (;;) {
   cin >> v >> c >> root >> finish;
   if (!v) break;
   for (int i = 0; i < v; i++) {
     g[i].par = -1;
     g[i].ch.clear();
     g[i].door = -1;
     g[i].key.clear();
   }
   for (int i = 0; i < maxv + 2; i++){
     wdoor[i] = -1;
     wkey[i] = -1;
   }
   for (int i = 0; i < c; i++) {
     cin >> aux;
     g[aux].key.push_back(i);
     wkey[i] = aux;
   }
   fill(&adj[0][0], &adj[v][0], -1);
   for (int i = 0; i < v - 1; i++) {
     int ea, eb, el;
     cin >> ea >> eb >> aux;
     adj[ea][eb] = aux + 1;
     adj[eb][ea] = aux + 1;
   }

   buildtree(root, -1);
   wkey[maxv + 1] = finish;
   wdoor[maxv + 1] = finish;

//cout << v << " " << c << " " << root << " " << finish << endl;

   path.clear();
   stack <int> pila; //en la pila guardare las puertas que me vaya encontrando
   int now = root;
   pila.push(maxv + 1);
   while (!pila.empty() && pila.size() < v + 2){
     int a = pila.top();
//cout <<"procesando puerta: " << a << endl;
     vector <int> c, d;
     int pos = wkey[a];
     int x = pos;
//cout << "desde la posicion " << pos << endl;
     while (x != root){      
       if (g[x].door != -1) d.push_back(g[x].door);
       x = g[x].par;
     }
     if (d.size() == 0) { //no door between a and root
//cout << "no hay problema para la puerta: " << a << endl;
       add_path(path, now, pos);
       add_path(path, pos, wdoor[a]);
       pila.pop();
       now = wdoor[a];
       if (a < maxv) g[now].door = -1;
     }
     else {
       for (int i = 0; i < d.size(); i++)
         pila.push(d[i]);
     }
   }

   if (pila.size() >= v + 2) puts("Impossible");
   else {
     printf("%u: %u", path.size(), root);
     for (int i = 0; i < path.size(); i++) printf(" %u", path[i]);
     puts("");
   }

  if (path.size() > maxtampath) maxtampath = path.size();

 }

 cerr << "El camino mas tocho es de: " << maxtampath << endl;
 fintime = clock();
 cerr << "Time: " << (double)(fintime - starttime) / CLOCKS_PER_SEC << endl;


return 0;
}
