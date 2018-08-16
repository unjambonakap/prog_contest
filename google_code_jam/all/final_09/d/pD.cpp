#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;

#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)
#define FEV(i,t) for (typeof(t.rbegin())i=t.rbegin();i!=t.rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ST first
#define ND second
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second

#define ll long long

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;


#define MAX_N 502
#define INFTY 1e9
#define MAX_S 30000


class WT{
	public:
		WT(){}
		//WT(int _x, int _y, int _c, int _r){x=_x, y=_y, c=_c, r=_r;}
		int x, y, c, r;

};
WT wl[MAX_N];
vi edge[MAX_N];

int n;
int used[MAX_N];
int score[MAX_N];
int visited[MAX_N];

int c[MAX_N][MAX_N];
int net[MAX_N][MAX_N];
int parent[MAX_N];
int flow;

int bfs(){
	int i, j, p, au;
	qi q;


	memset(parent, -1, sizeof(parent));

	q.push(n);
	parent[n]=-2;
	while(!q.empty()){
		p=q.front(); q.pop();
		REP(i, n+2){
			if (c[p][i]-net[p][i] > 0 && parent[i] == -1){
				parent[i]=p;
				if (i == n+1){
					au=MAX_S;
					j=i;
					while(parent[j] != -2)
						au=std::min(au, c[parent[j]][j]-net[parent[j]][j]), j=parent[j];
					

					j=i;
					while(parent[j] != -2)
						net[parent[j]][j]+=au, net[j][parent[j]]-=au, j=parent[j];
					
					
					
					return au;
					

				}else{
					q.push(i);
				}


			}
		}
	}

	return 0;


}

int solve(){
	int i, j, k, au;

	flow=0;
	memset(c, 0, sizeof(c));
	memset(net, 0, sizeof(net));

	REP(i, n){
		if (wl[i].c < 0)
			c[n][i]=-wl[i].c;
		else if (wl[i].c > 0)
			c[i][n+1]=wl[i].c;

		FE(it, edge[i])
			c[*it][i]=MAX_S;
	}

	while(1){

		au=bfs();
		if (au == 0)
			break;
		flow+=au;
	}
	flow=-flow;
	REP(i, n)
		if (wl[i].c > 0)
			flow+=wl[i].c;
		


	return flow;

}


int main(){
	int i, j, k, T;


	scanf("%d", &T);

	REP(i, T){
		scanf("%d", &n);
		REP(j, n)
			scanf("%d %d %d %d", &wl[j].x, &wl[j].y, &wl[j].r, &wl[j].c);
		
		REP(j, n+2)
			edge[j].clear();


		REP(j, n){
			CLR(edge[j]);

			REP(k, n)
				if (j!=k && DIST(wl[k].x-wl[j].x, wl[k].y-wl[j].y) <= SQR(wl[j].r))
					edge[j].pb(k);
				
		}
			
		printf("Case #%d: %d\n", i+1, solve());



	}


	return EXIT_SUCCESS;
}

