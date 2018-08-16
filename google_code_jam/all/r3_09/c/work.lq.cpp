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
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

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
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)


#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;


#define MAX_X 1100
#define MAX_Y 35
#define MAX_N 1100
#define MAX_C 3

vector<pii> pl;
vector<vi> edges;
vector<vi> Y;
int map[MAX_X][MAX_Y];
int n;
int yseen[MAX_Y];
vi yl;

int color[MAX_N];

int tb[MAX_Y];

int rec(int y, int my, int nc){
	int i, j, k;
	if (y == my){

		int used[MAX_C];
		memset(color, -1, sizeof(color));

		REP(i, my)
			color[map[Y[yl[i]].back()][yl[i]]]=tb[i];

		FEV(it, pl){
			int t=map[it->ST][it->ND];
			if (color[t] != -1){
				FE(ita, edges[t])
					if (color[*ita] == color[t])
						return 0;
				continue;	
			}
			memset(used, 0, sizeof(used));
			FE(ita, edges[t])
				if (color[*ita] != -1)
					used[color[*ita]]=1;


			REP(i, nc)
				if (!used[i])break;

			if (i == nc)
				return 0;
			
			color[t]=i;
		}

		return 1;
	}else{

		REP(i, nc){
			tb[y]=i;
			if (rec(y+1, my, nc))
				return 1;
		}

	}
	return 0;
}

int solve(){
	int i, j, k, l, x, y;

	edges=vector<vi>(SZ(pl), vi());



	FE(it, pl){
		x=it->ST, y=it->ND;

		FOR(j, -1, 1){
			if (y+j < 0 || y+j >= MAX_Y)continue;
			FOR(i, x+1, MAX_X-1)
				if (map[i][y+j] != -1){
					edges[map[x][y]].pb(map[i][y+j]), edges[map[i][y+j]].pb(map[x][y]);
					break;
				}

		}
	}

	REP(i, 3)
		if (rec(0, SZ(yl), i+1))
			return i+1;

	return 4;

}

int main(){
	int i, j, k, T;
	int x, y;

	cin >> T;
	REP(i, T){
		cin >> n;

		CLR(pl);

		Y=vector<vi>(MAX_Y, vi());
		memset(yseen, 0, sizeof(yseen));
		CLR(yl);

		memset(map, -1, sizeof(map));
		REP(j, n){
			cin >> x >> y;
			pl.pb(pii(x, y)), map[x][y]=pl.size()-1; 
			Y[y].pb(x);
			if (!yseen[y])
				yl.pb(y), yseen[y]=1;

		}


		sort(ALL(pl));
		REP(j, MAX_Y)
			sort(ALL(Y[j]));


//		if (i!=9)continue;
//		REP(j, MAX_Y){
//			REP(k, SZ(pl))
//				printf("%c", (map[k][j] != -1)?'.':' ');
//			printf("\n");
//
//
//		}

		printf("Case #%d: %d\n", i+1, solve());


	}


	return EXIT_SUCCESS;
}

