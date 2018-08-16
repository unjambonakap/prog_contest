#include <cassert>
#include <cstring>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <vector>
#include <list>
#include <cstdio>
#include <complex>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <iostream>

#define X real()
#define Y imag()
#define PB push_back
#define MP make_pair
#define FR(i,n) for( long long i = 0; i < n; i ++ )
#define FOR(i,a,n) for(long long i = a; i < n; i ++)
#define FREACH(it,v) for( typeof(v.end()) it = v.begin(); it != v.end(); it ++ )
#define EPS 1e-9
using namespace std;

typedef long double ld;
typedef long long ll;
typedef pair<int,int> pii;

const int inf=100000000;

int dr[4]={-1,1,0,0};
int dc[4]={0,0,-1,1};
bool vis[30][30];
int dist[30][30];
bool forb[30][30];

vector<int> adyx[30][30];
vector<int> adyy[30][30];
vector<int> cst[30][30];

int nr,nc;

bool okpos(int r,int c)
{
    return (r>-1&&r<nr&&c>-1&&c<nc);
}

bool ok(int r,int c)
{
    return (r>-1&&r<nr&&c>-1&&c<nc&&!vis[r][c]&&!forb[r][c]);
}
int ncas=0;

void ffill(int r,int c)
{
    if(!ok(r,c)) return;
    
 //   if(r==27&&c==3&&nr==30&&nc==30) cerr << "ncas: " << ncas << "fsf " << " " << adyx[r][c].size() <<  endl;
    vis[r][c]=1;
    if(r==nr-1&&c==nc-1) return;
    if(adyx[r][c].size()==0) FR(k,4) ffill(r+dr[k],c+dc[k]);
    FR(k,adyx[r][c].size()) ffill(adyx[r][c][k],adyy[r][c][k]);
}

int main()
{
    while(cin>>nc>>nr&&(nc|nr)) {
        ncas++;
      //  cerr << ncas << endl;
       // cout << nc << " " << nr << endl;
        memset(vis,false,sizeof(vis));
        FR(i,nr) FR(j,nc) dist[i][j]=inf;
        dist[0][0]=0;
        

        FR(i,nr) FR(j,nc) { adyx[i][j].clear(); adyy[i][j].clear(); cst[i][j].clear(); }
        memset(forb,false,sizeof(forb)); // no forbiddden positons
        int g;
        cin >> g;
        FR(i,g) {
            int x,y;
            scanf("%d %d",&x,&y);
            forb[y][x]=true;
        }
        int e;
        cin >> e;
        FR(i,e) {
            int x,y,x2,y2,e;
            scanf("%d %d %d %d %d",&x,&y,&x2,&y2,&e);
            adyx[y][x].PB(y2);
            adyy[y][x].PB(x2);
            cst[y][x].PB(e);
        }
        
        ffill(0,0);

        FR(i,nr) FR(j,nc) if(!vis[i][j]) forb[i][j]=true; // forbid all unreachable positions
                

        
        int nit=0;
        for(;;)
        {
            bool prv=false;
            int r,c;

            if(nit>=nr*nc+1) goto NEGLOOP;            
            FR(i,nr) FR(j,nc) {
            //    cerr << "ncas: " << ncas << " " << forb[27][3] << endl;
                r=i;c=j;

                if(forb[i][j]) continue;
                if(i==nr-1&&j==nc-1) continue;
                if(adyx[r][c].size()==0)
                FR(k,4) {
                    int ni=i+dr[k],nj=j+dc[k];
                    if(!okpos(ni,nj)) continue;
                    if(!forb[ni][nj])
                    {
                        if(dist[ni][nj]>dist[i][j]+1)
                        {
                            prv=true;
                            dist[ni][nj]=dist[i][j]+1;
                        }
                    }
                }
                FR(k,adyx[r][c].size()) 
                {
                    
                    int ni=adyx[r][c][k],nj=adyy[r][c][k];
                    if(!okpos(ni,nj)) continue;
                    
                    if(!forb[ni][nj])
                    if(dist[ni][nj]>dist[i][j]+cst[r][c][k])
                    {
                        prv=true;
                        dist[ni][nj]=dist[i][j]+cst[r][c][k];
                    }                                        
                }
            }    
            if(!prv) break;
            nit++;
        }
 
      //  cerr << nr << " " << nc << endl;
        /*
        FR(i,nr)
        {
            FR(j,nc) cerr << dist[i][j] << " ";
            cerr << endl;
        }*/
        
        
        if(forb[nr-1][nc-1]) {
            cout << "Impossible" << endl;
            continue;
        }
        
        cout << dist[nr-1][nc-1] << endl;
        
        continue;
    NEGLOOP:
     //   cerr << ncas << " " << nr-1 << " " << nc-1 << endl;

        
        /*
        if(dist[nr-1][nc-1]==inf)  cerr << nr << " " << nc << endl;
        if(dist[nr-1][nc-1]==inf) FR(i,nr)
        {
            FR(j,nc) cerr << dist[i][j] << " ";
            cerr << endl;
        }*/
        //assert(dist[nr-1][nc-1]<inf); // In this case, we say Impossible!!!!
        cout << "Never" << endl;
    }
}
