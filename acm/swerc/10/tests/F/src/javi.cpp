// O(n^3 2^n) solution to monkey
// Javier Gómez Serrano
// Should it pass?
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int q[1 << 21], prev[1 << 21], shot[1 << 21];

int main(){
    int n,m;
    while (cin >> n >> m, n+m){
          memset(prev,-1,sizeof(prev));
          vector<vector<int> > L(n);
          for (int i=0;i<m;i++){
              int x,y; cin >> x >> y;
              L[x].push_back(y);
              L[y].push_back(x);
          }
          int begin,end;
          begin = end = 0;
          q[end++]=(1<<n)-1;
          prev[(1<<n)-1]=-2;
          while (begin != end){
                int top = q[begin++];
                for (int i=0;i<n;i++){
                    int a = top;
                    if (a & (1<<i)){
                       //Shoot at position i
                       a = a^(1<<i);
                       int b = 0;
                       for (int j=0;j<n;j++){
                           if (a & (1<<j)){
                              for (int k=0;k<L[j].size();k++) b |= (1<<(L[j][k]));
                           }
                       }
                       if (prev[b] == -1){
                          prev[b] = top;
                          shot[b] = i;
                          q[end++] = b;
                       }
                    }
                }
          }
          if (prev[0] == -1) cout << "Impossible" << endl;
          else {
               vector<int> V;
               int path = 0;
               while (path != ((1<<n)-1)){
                     V.push_back(shot[path]);
                     path = prev[path];
               }
               cout << V.size() << ":";
               for (int i=V.size()-1;i>=0;i--)
                   cout << " " << V[i];
               cout << endl;
          }
    }
    return 0;
}
