// Javier Gomez Serrano
//
// O(n^2) solution for slalom.
// DP minimizing the path from the start to each of the endpoints of the gates.
// Then, 'meet-in-the-middle' to get the minimum between the sum of the DP and 
// the straight path starting on any interval and ending at the last gate.

#include <iostream>
#include <vector>
#include <cmath>

#define infinity 1000000000
using namespace std;

typedef pair<double,double> interval;

int n;

double dist2(double x, double y){
       return sqrt(x*x+y*y);
}

double startx,starty;

// Returns the intersection of two intervals. isempty returns false if the intersection is empty 
interval intersection(interval i, interval j, bool& isempty){
         interval k;
         k.first = max(i.first, j.first);
         k.second = min(i.second, j.second);
         if (k.first > k.second) isempty = true;
         return k;
}

// Returns the distance between (px,py) and (vx,vy) or -1 if vx is not contained in curr
double in_intersection(interval curr_i,double vx, double vy,double px,double py){
       if (vx < curr_i.first or vx > curr_i.second) return -1;
       return dist2(vx-px,vy-py);
}

// What is the minimum distance from (px,py) to the goal(curr_i,vy) in a straight line?
double reach_goal(interval curr_i, double vy, double px, double py){
       double distmin = infinity;
       double d1,d2,d3;
       d1 = in_intersection(curr_i,curr_i.first,vy,startx,starty);
       d2 = in_intersection(curr_i,curr_i.second,vy,startx,starty);
       d3 = in_intersection(curr_i,startx,vy,startx,starty);
       if (d1 > -0.5) distmin = min(distmin, d1);
       if (d2 > -0.5) distmin = min(distmin, d2);
       if (d3 > -0.5) distmin = min(distmin, d3);
       return distmin;
}


// Distance between endpoints. -1 if it is not possible to reach it
double dist[1000][2][1000][2];

int main(){
    cout.setf(ios::fixed);
    cout.precision(9);
    while (cin >> n,n){
          vector<pair<double,double> > vx;
          vector<double> vy;
          cin >> startx >> starty;
          for (int i=0;i<n;i++){
              double a,b,c;
              cin >> c >> a >> b;
              vx.push_back(make_pair(a,b));
              vy.push_back(c);
          }
          // Can I reach the i-th endpoint from the start in a straight line?
          // -1 for not reaching, != -1 with the distance
          double achieve_start[n][2];
          // Can I reach the goal from the i-th endpoint in a straight line?
          // -1 for not reaching, != -1 with the distance
          double achieve_goal[n][2];
          // Best path from the start to the gate, possibly zigzagging
          double dp[n][2];
          // Initialization
          for (int i=0;i<n;i++) for (int j=0;j<2;j++) for (int k=0;k<n;k++) for (int l=0;l<2;l++) dist[i][j][k][l]=-1;
          for (int i=0;i<n;i++) achieve_start[i][0] = achieve_start[i][1] = achieve_goal[i][0] = achieve_goal[i][1] = -1;
          
          double distmin = infinity;
          // We calculate the points reachable from the starting point
          interval curr_i = vx[0];
          double curr_y = vy[0];
          achieve_start[0][0] = dist2(startx-vx[0].first,starty-vy[0]);
          achieve_start[0][1] = dist2(startx-vx[0].second,starty-vy[0]);
          for (int i=1;i<n;i++){
              // We calculate the interval that we can reach in a straight line
              curr_i.first = startx + (curr_i.first - startx)*(starty-vy[i]) / (starty-curr_y);
              curr_i.second = startx + (curr_i.second - startx)*(starty-vy[i]) / (starty-curr_y);
              curr_y = vy[i];
              bool empty = false;
              curr_i = intersection(curr_i,vx[i],empty);
              if (empty) break;
              achieve_start[i][0] = in_intersection(curr_i,vx[i].first,vy[i],startx,starty);
              achieve_start[i][1] = in_intersection(curr_i,vx[i].second,vy[i],startx,starty);
              if (i == n-1){
                 // We can reach the goal from the start
                 distmin = reach_goal(curr_i,vy[n-1],startx,starty);
              }
          }
          // Very important. Don't forget this special case.
          if (n == 1){
             distmin = min(distmin,reach_goal(vx[0],vy[0],startx,starty));
          }
          // Distance between endpoints of the gates and gate->end
          for (int i=0;i<n-1;i++){
              for (int j=0;j<2;j++){
                  if (j == 0) startx = vx[i].first; else startx = vx[i].second;
                  starty = vy[i];
                  interval curr_i = vx[i+1];
                  double curr_y = vy[i+1];
                  dist[i][j][i+1][0] = dist2(startx-vx[i+1].first,starty-vy[i+1]);
                  dist[i][j][i+1][1] = dist2(startx-vx[i+1].second,starty-vy[i+1]);
                  for (int k=i+1;k<n;k++){
                      curr_i.first = startx + (curr_i.first - startx)*(starty-vy[k]) / (starty-curr_y);
                      curr_i.second = startx + (curr_i.second - startx)*(starty-vy[k]) / (starty-curr_y);
                      curr_y = vy[k];
                      bool empty = false;
                      curr_i = intersection(curr_i,vx[k],empty);
                      if (empty) break;
                      dist[i][j][k][0] = in_intersection(curr_i,vx[k].first,vy[k],startx,starty);
                      dist[i][j][k][1] = in_intersection(curr_i,vx[k].second,vy[k],startx,starty);
                      if (k == n-1){
                         // We can reach the goal (last interval) straight from this point
                         achieve_goal[i][j] = reach_goal(curr_i,vy[n-1],startx,starty);
                      }
                  }
              }
          }
          
          for (int i=0;i<n;i++) for (int j=0;j<2;j++) dp[i][j] = infinity;
          
          // min distance from the start in a straight line
          for (int i=0;i<n;i++) for (int j=0;j<2;j++){
              if (achieve_start[i][j] > -0.5) dp[i][j] = achieve_start[i][j];
          }
          
          // DP: min. distance from the start possibly zigzagging
          for (int i=0;i<n;i++){
              for (int j=0;j<2;j++){
                  for (int k=0;k<i;k++){
                      for (int l=0;l<2;l++){
                          if (dist[k][l][i][j] > -0.5){
                             dp[i][j] = min(dp[i][j], dp[k][l] + dist[k][l][i][j]);
                          }
                      }
                  }
              }
          }
          
          // We search over the minimum of the sum start->gate + gate->end
          for (int i=0;i<n;i++){
              for (int j=0;j<2;j++){
                  if (achieve_goal[i][j] > -0.5){
                     distmin = min(distmin, achieve_goal[i][j] + dp[i][j]);
                  }
              }
          }
          cout << distmin << endl;
    }
    return 0;
}
