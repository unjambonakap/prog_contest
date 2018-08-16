#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 10000;

bool ret;
vector <int> g[MAXN];
int n;
int cad[MAXN];

int letra (char c){
  if (c == 'A') return 0;
  if (c == 'G') return 1;
  if (c == 'T') return 2;
  if (c == 'C') return 3;
  puts("error leyendo");
  return -3;
}

int m[MAXN];

int yaestaria[MAXN], ya[MAXN];
vector <int> vere;
bool sepodra;

void dfs (int v, int label){
 if (!sepodra) return;
 if ((yaestaria[v] == 0) && !ya[v]) {vere.push_back(v); yaestaria[v] = 1;}
 if (m[v] >= 0){
  sepodra = sepodra && (m[v] == label);
 }
 else {
   if (label == (cad[v] + 2) % 4) {sepodra = false; return;}
   m[v] = label;
   for (int i = 0; i < g[v].size(); i++)
     dfs(g[v][i], label);
   if (label != cad[v]){
     if (v > 0) dfs(v - 1, cad[v - 1]);
     if (v + 1 < n) dfs(v + 1, cad[v + 1]);
   }
 }
 return;
}

void haz (int x){

 if (ret) return;
 if (x == n) {ret = true; return;}
 if (m[x] >= 0 || g[x].size() == 0) {
   haz(x + 1); 
   return;
  }

 for (int c = 0; !ret && c < 4; c++) if (c != (cad[x] + 2) % 4){
   vere.clear();
   memset (yaestaria, 0, sizeof(yaestaria));
   sepodra = true;
   dfs(x, c);
   if (sepodra) {
     for (int i = 0; i < vere.size(); i++) ya[vere[i]] = 1;
     haz(x + 1);
   }
   for (int i = 0; i < vere.size(); i++) {ya[vere[i]] = 0; m[vere[i]] = -1;}
 }

 return;  
}

int main (){
clock_t start, finish;

start = clock();

 int t, taml;

 for (;;){
   cin >> n >> t;
   if (n == 0) break;
   string s;
   cin >> s;
   for (int i = 0; i < n; i++) cad[i] = letra(s[i]);
   for (int i = 0; i < n; i++) g[i].clear();
   while (t--){
     scanf("%i:", &taml);
     vector <int> v(taml);
     for (int i = 0; i < taml; i++)
       cin >> v[i];
     for (int i = 0; i < taml - 1 - i; i++){
       g[v[i]].push_back(v[taml - 1 - i]);
       g[v[taml - 1 - i]].push_back(v[i]);
     }       
   }

  ret = false;   
  for (int i = 0; i < n; i++) {m[i] = -1; ya[i] = 0;}
  haz(0);

  if (ret) puts("YES");
  else puts("NO");

 }

finish = clock();

cerr << "Tiempo: " << (double)(finish-start)/CLOCKS_PER_SEC << endl;


 return 0;
}
