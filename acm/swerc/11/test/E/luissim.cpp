// Solution to 'Game, Set and Match'.
// Luis Hernandez Corbato

//Same as luis.cpp but using simulation to obtain
//the winning probability in case of tie
//MAX indicates the maximum number of ties we consider
//a game/set will have
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAX 20

double simula(double p){
  double w = 0.0;
  double e = 1.0;
  for (int i = 0; i < MAX; i++){
    w += p * p * e;
    e = e * 2 * p * (1 - p);
  }
  
  return w;
}

pair <double, double> calc (double p, int n){
 double a[20][20];       
 for (int i = 0; i <= n; i++)
   for (int j = 0; j <= n; j++) {      
      if (i + j == 0) a[i][j] = 1.0;
      else a[i][j] = 0.0;
      if (i > 0 && j < n) a[i][j] += (1 - p) * a[i-1][j];      
      if (j > 0 && i < n) a[i][j] += p * a[i][j-1];      
    }
 double w = 0.0;
 for (int i = 0; i < n - 1; i++)
   w += a[i][n];
 return make_pair(w, a[n-1][n-1]);
}

//probability of winning a game where you need at least n points to win
double game (double p, int n){
  pair <double, double> b = calc(p, n);
  return b.first + b.second * simula(p);       
}

double set (double p){
  double c = game(p, 4);
  pair <double, double> b = calc(c, 6);
  double t = game (p, 7);
  return b.first + b.second * (c * c + 2 * c * (1 - c) * t);
}

double match (double p){
  double b = set(p);
  return b * b * (1 + 2 * (1 - b));       
}

int main (){
 
  for (;;){
     double p;
     cin >> p;
     if (p < 0) break;
     cout << game(p, 4) << " " << set(p) << " " << match(p) << endl;    
  }
    
  return 0;
}
