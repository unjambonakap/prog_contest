//Problem Slalom:
//O(n^2) solution by Luis Hernandez Corbato
#include <cstdio>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
using namespace std;
#define PB push_back
#define MP make_pair
#define eps 1e-8

double dist (double x1, double y1, double x2, double y2){
   return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); 
}

int main (){
  clock_t start, finish;
  start = clock();
 
 vector <double> y;
 vector <pair <double, double> > x;
 int n;
 double px, py;
 
 while (scanf("%u", &n) == 1 && n != 0){
   scanf("%lf %lf", &px, &py);
   
   double yy, x1, x2;
   x.clear();
   y.clear();
   for (int i = 0; i < n; i++){
     scanf("%lf %lf %lf", &yy, &x1, &x2);
     x.PB(MP(x1, x2));
     y.PB(yy);
    }
    
    int puerta = -1;  
    double distancia = 0.0;
    int totalpuertas = 0;
    
    while (puerta < n - 1){
      totalpuertas++;
      int i = puerta + 1;
      double tanizda = (x[i].first - px) / (py - y[i]), tandcha = (x[i].second - px) / (py - y[i]);
      int maxizda = i, maxdcha = i;
      int giro = -1; //0 si el camino se desplaza a la izda, 1 a la dcha
   //   cout << px << " " << py << endl;
      while (++i < n && tanizda < tandcha + eps){//nunca me meto en los dos if's
         if (tanizda < (x[i].first - px) / (py - y[i])){
             maxizda = i;
             tanizda = (x[i].first - px) / (py - y[i]);
             giro = 1;
          }
         if (tandcha > (x[i].second - px) / (py - y[i])){
             maxdcha = i;
             tandcha = (x[i].second - px) / (py - y[i]);
             giro = 0;
          }
      //   cout << i << ": " << maxizda << "- " << tanizda << " " << maxdcha <<" - " << tandcha<< endl;              
      }
      if (tanizda < tandcha + eps) {//podria terminar pero igual no es optimo
      //termino verticalmente
        if (tanizda < eps && tandcha > - eps){
          distancia += fabs(py - y[n - 1]);
          puerta = n - 1;       
        }
      //si voy al extremo de la izquierda
        else if (tanizda > -eps && (puerta == -1 || x[maxizda].first > px - eps)){
          distancia += dist(px, py, x[maxizda].first, y[maxizda]);
          px = x[maxizda].first;
          py = y[maxizda];
          puerta = maxizda;        
        }
        //si voy al de la derecha
        else {          
          distancia += dist(px, py, x[maxdcha].second, y[maxdcha]);
          px = x[maxdcha].second;
          py = y[maxdcha];
          puerta = maxdcha;
        }
      }
      else {        
        if (giro == 0) {
          distancia += dist(px, py, x[maxizda].first, y[maxizda]);
          px = x[maxizda].first;
          py = y[maxizda];
          puerta = maxizda;        
        }
        else {
          distancia += dist(px, py, x[maxdcha].second, y[maxdcha]);
          px = x[maxdcha].second;
          py = y[maxdcha];
          puerta = maxdcha;
        }       
      }    
    //  cout << "llego a la puerta " << puerta << " " << distancia << endl;
    }//while puerta pequeña    
     
    printf("%lf\n", distancia);
 //   printf("%.11lf  %lf\n", distancia, (double)totalpuertas/n);
    
  }  
  
  finish = clock();
  cerr << (double)(finish - start) / CLOCKS_PER_SEC << endl;
  return 0;
}
