//Genetics:
//Algoritmo que usa cortes aleatorios
//para reducir la cadena
//Luis Hernandez Corbato
#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

bool igual(char a, char b){
   return (tolower(a) == tolower(b)); 
}

string reverso(string s){
 int n = s.size();
 string ret = "";
 for (int i = n - 1; i >= 0; i--) 
  if ((s[i] - 'a') >= 0) ret += s[i] + 'A' - 'a';
  else ret += s[i] - 'A' + 'a';
 return ret;
}

string rota(string s, int n){
  string ret = s.substr(n); 
  return ret + s.substr(0, n);
}

string cortapega (string s, int corte, int pega1, int pega2){
  //corte es la posicion de la letra siguiente a donde se hace el corte
  //[0, 1, ...., pega1, ...., corte - 1, corte, ..., pega2, ..., n-1]
  
   string s1 = s.substr(0, pega1);
   string s2 = s.substr(pega1 + 1, corte - 1 - pega1);
   string s3 = s.substr(corte, pega2 - corte);
   string s4 = s.substr(pega2 + 1);
   char letra = tolower(s[pega1]);
   
   string ret1 = s2 + letra + s1;
   string ret2 = s4 + (char)toupper(letra) + s3;
   
   if (s[pega1] == s[pega2]) ret2 = reverso(ret2); 
   return ret1 + ret2;
}

string eliminaesferas (string s){
  int n = s.size();
  for (int i = 0; i < n - 1; i++)
    if (s[i] != s[i+1] && igual(s[i], s[i+1])){
      return eliminaesferas(s.substr(0, i) + s.substr(i + 2));
    }
  if (n && s[0] != s[n-1] && igual (s[0], s[n-1])) return eliminaesferas(s.substr(1, n - 2));
  return s;
}

int p2, toros;

string eliminap2 (string s){
   int n = s.size();
   for (int i = 0; i < n - 1; i++)
    if (s[i] == s[i+1] ){
      p2++;
      return eliminap2(s.substr(0, i) + s.substr(i + 2));
    }
  if (n && (s[0] == s[n-1])) {
    p2++;
    return eliminap2(s.substr(1, n - 2));
  }
  return s;    
}

string eliminatoros (string s){
   int n = s.size();
   if (n < 4) return s;
   
   string aux = s + s.substr(0, 3);
   for (int i = 0; i < n; i++)
     if (aux[i] != aux[i+2] && igual(aux[i], aux[i+2]))
     if (aux[i+1] != aux[i+3] && igual(aux[i+1], aux[i+3])){
       s = rota(s, i);       
       s = s.substr(4);
       toros++;
       return eliminatoros(s);
      }
  return s;
}

//BACKTRACKING
//CUANDO NO ME ENCUENTRO CON BRAZOS O PIERNAS (P2 O TOROS)
//SELECCIONO UN NUCLEOTIDO AL AZAR Y UN PUNTO DE CORTE Y ZAS
//ME METO EN EL BACKTRACKING

string procesa (string s){
   return eliminatoros(eliminap2(eliminaesferas(s))); 
}

int pasosbk;

void bk (string s){
  pasosbk++;
//  cout << s << endl;
 int n = s.size();
 if (!n) return; 
  
 s = procesa(s);
 if (s.size() < n) {bk(s); return;}
 
 int pos1 = rand() % n, pos2; 
 for (int i = 0; i < n; i++) if (i != pos1 && igual(s[pos1], s[i])) pos2 = i;
 if (pos1 > pos2) swap(pos1, pos2);
 int k = rand() % (pos2 - pos1) ; 
 s = cortapega(s, pos1 + k + 1, pos1, pos2);
 bk(s);
 return;
  
}

int main (){
  
  clock_t start, finish;
  start = clock();
 
  while (1){
   string s;
   cin >> s;
   if (s == "END") break;
   
   p2 = 0; toros = 0;
   pasosbk = 0;
   bk(s);   
   if (!p2 && !toros) cout << "none" << endl;
   else if (p2 == 0){
     cout << toros << " leg";
     if (toros > 1) cout << "s";
     cout << endl;
   }
   else {
     int total = p2 + 2 * toros;
     cout << total << " arm";
     if (total > 1) cout << "s";
     cout << endl;
   }
  // cout << s.size() << " " << pasosbk << endl;
  }
  
  finish = clock();
//  cerr << (double)(finish - start) / CLOCKS_PER_SEC << endl;
    
  return 0;
}
