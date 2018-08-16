#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i < (b)) && (c); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define FORVC(i, a, b, c) for(i = (b) - 1; (i >= (a)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;


#define MAX_W 120

int vx[]={0,-1,1,0};
int vy[]={-1,0,0,1};

int parent[MAX_W*MAX_W];
int map[MAX_W][MAX_W];
int remap[MAX_W*MAX_W];
char label[MAX_W*MAX_W];



int w, h;
int root(int a){
	if (parent[a] == -1)return a;
	return parent[a]=root(parent[a]);
}

void solve(){
	int i, j, k, nx, ny;
	char curc;
	int lc;

	memset(parent, -1, sizeof(parent));

	REP(j, h){
		REP(i, w){
			lc=-1;
			REP(k, 4){
				nx=i+vx[k], ny=j+vy[k];
				if (nx >= 0 && ny >= 0 && nx < w && ny < h)
					if (map[nx][ny] < map[i][j] && (lc == -1 || map[lc%w][lc/w] > map[nx][ny]))
						lc=nx+ny*w;
				
			}
			if (lc != -1)
				parent[root(i+j*w)]=root(lc);

		}
	}

	curc='a';
	memset(label, -1, sizeof(label));
	REP(i, w*h){
		if (label[root(i)] == -1)
			label[root(i)]=curc++;
		label[i]=label[root(i)];
	}


}


int main(){
	int i, j, k, T;

	cin >> T;
	REP(i, T){
		cin >> h >> w;
		REP(j, h)
			REP(k, w)
				cin >> map[k][j];

		printf("Case #%d: \n", i+1);
		solve();
		REP(j, h){
			REP(k, w-1)
				printf("%c ", label[k+j*w]);
			printf("%c", label[k+j*w]);
			printf("\n");
		}

		



	}


	return EXIT_SUCCESS;
}

