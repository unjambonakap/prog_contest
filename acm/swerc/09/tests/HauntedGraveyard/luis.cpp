#include <cstdio>
#include <ctime>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
#define maxtam 50
#define PB push_back
#define MP make_pair
#define infinito 100000000

int w, h;
int map[maxtam][maxtam];
int d[maxtam][maxtam];
int t[maxtam * maxtam];
int sx[maxtam * maxtam], sy[maxtam * maxtam];
int fx[maxtam * maxtam], fy[maxtam * maxtam];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int saltos;
int trap[maxtam * maxtam];

void concatenate(){
  int x, y;
  int time[maxtam * maxtam];
  memset (trap, -1, sizeof(trap));
   for (int i = 1; i <= saltos; i++){
      x = sx[i];
      y = sy[i];
      fill (&time[0], &time[maxtam * maxtam], infinito);
      int timetravel = 0;
      int saltoactual = i;
      while (saltoactual && time[saltoactual] == infinito){
        time[saltoactual] = timetravel;
        timetravel += t[saltoactual];
        x = fx[saltoactual];
        y = fy[saltoactual];        
        saltoactual = map[x][y];
      }
     if (time[saltoactual] < infinito){
       //hay un bucle de saltos 
       if (timetravel < time[saltoactual]) trap[i] = 1; //si el bucle es negativo
       else trap[i] = 0;
      } 
     else {
       fx[i] = x;
       fy[i] = y;
       t[i] =  timetravel;
      }
    }
  return;
}

int main (){
  clock_t start, finish;
  start = clock();
  
  for (;;){
    scanf("%u %u", &w, &h);
    if (!w) break;
    memset (map, 0, sizeof(map));
    
    int x, y, tumbas, nx, ny, time;
    scanf("%u", &tumbas);
    while (tumbas--){
       scanf("%u %u", &x, &y);
       map[x][y] = -1;
    } 
    
    scanf("%u", &saltos);
    for (int i = 1; i <= saltos; i++){
       scanf("%u %u %d %d %d", &x, &y, &nx, &ny, &time);
       map[x][y] = i;
       t[i] = time;
       sx[i] = x;
       sy[i] = y;
       fx[i] = nx;
       fy[i] = ny;      
    }
    
    concatenate();
    
    fill (&d[0][0], &d[maxtam][0], infinito);
    d[0][0] = 0;
    vector <pair <int, int> > v, nv;
    v.PB(MP(0, 0));
    bool ciclosnegativos = false;
    for (int pasos = 0; !ciclosnegativos && pasos < w * h; pasos++){
      for (int i = 0; i < v.size(); i++){
        y = v[i].first / w;
        x = v[i].first % w; 
        if (x < w - 1 || y < h - 1)
        for (int j = 0; j < 4; j++) 
          if (x + dx[j] >= 0 && x + dx[j] < w && y + dy[j] >= 0 && y + dy[j] < h)
          if (map[x + dx[j]][y + dy[j]] >= 0){            
            nx = x + dx[j];
            ny = y + dy[j];
            int numsalto = map[nx][ny];
            int dtime = 1;
            if (numsalto != 0) {nx = fx[numsalto]; ny = fy[numsalto]; dtime += t[numsalto];}
            if ((numsalto == 0 || trap[numsalto] == -1) && d[nx][ny] > v[i].second + dtime){
               d[nx][ny] = v[i].second + dtime;
               nv.PB(MP(w * ny + nx, d[nx][ny])); 
            }
            else if (numsalto != 0 && trap[numsalto] == 1) ciclosnegativos = true;
          }        
      }    
      v = nv;
      nv.clear();  
    }
    
           
      for (int pasos = 0; !ciclosnegativos && pasos < w * h; pasos++){
      for (int i = 0; i < v.size(); i++){
        y = v[i].first / w;
        x = v[i].first % w; 
        if (x < w - 1 || y < h - 1)
        for (int j = 0; j < 4; j++) 
          if (x + dx[j] >= 0 && x + dx[j] < w && y + dy[j] >= 0 && y + dy[j] < h)
          if (map[x + dx[j]][y + dy[j]] >= 0){            
            nx = x + dx[j];
            ny = y + dy[j];
            int numsalto = map[nx][ny];
            int dtime = 1;
            if (numsalto != 0) {nx = fx[numsalto]; ny = fy[numsalto]; dtime = t[numsalto];}
            if (d[nx][ny] > d[x][y] + dtime){
               ciclosnegativos = true;
               d[nx][ny] = d[x][y] + dtime;
               nv.PB(MP(w * ny + nx, d[nx][ny])); 
            }
          }        
      }    
      v = nv;
      nv.clear();  
    }              
    
    if (ciclosnegativos) puts("Never");
    else if (d[w - 1][h - 1] == infinito) puts("Impossible");
    else printf("%d\n", d[w - 1][h - 1]);
    
  }
  
  finish = clock();
  cerr << (double)(finish - start) / CLOCKS_PER_SEC << endl;
  return 0;
}
