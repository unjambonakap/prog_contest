//Solution to Locks and Keys
//Idea: do BFS and unlock as much as you
//can at every step

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

void add_simple_path (vector <int>& ret, int goal){
  vector <int> p;
  int pos = goal;
  do {
    p.push_back(pos);
    pos = g[pos].par;
  } while (pos != -1);
  for (int i = p.size() - 2; i >= 0; i--) ret.push_back(p[i]);
}

void add_round_path (vector <int>& ret, int goal){
  vector <int> p;
  int pos = goal;
  do {
    p.push_back(pos);
    pos = g[pos].par;
  } while (pos != -1);
  for (int i = p.size() - 2; i >= 0; i--) ret.push_back(p[i]);
  for (int i = 1; i < p.size(); i++) ret.push_back(p[i]);
}

vector <int> doorsfound;
bool reachable, newkey, viskey[maxv], visdoors[maxv];

void dfs (int x){
  if (x == finish) reachable = true;
  for (int i = 0; i < g[x].key.size(); i++)
    if (!viskey[g[x].key[i]]){
      newkey = true;
      viskey[g[x].key[i]] = true;
    }
  for (int i = 0; i < g[x].ch.size(); i++)
    if (g[g[x].ch[i]].door == -1)
      dfs(g[x].ch[i]);
    else doorsfound.push_back(g[g[x].ch[i]].door);
  return;
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

   path.clear();
   bool newdoor;
   fill(&viskey[0], &viskey[c], false);
   fill(&visdoors[0], &visdoors[c], false);
   do {
     reachable = false;
     doorsfound.clear();
     newkey = false;
     dfs(root);
     if (reachable) {
       add_simple_path(path, finish);
       break;
     }
     newdoor = false;
     for (int i = 0; i < doorsfound.size(); i++){
        int k = doorsfound[i];
        if (!visdoors[k]){
          visdoors[k] = true;
          newdoor = true;
        }
        if (viskey[k]) {        
          add_round_path(path, wkey[k]);
          add_round_path(path, wdoor[k]);
          g[wdoor[k]].door = -1;
        }
      }    
   } while (newdoor || newkey);


   if (!reachable) puts("Impossible");
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
