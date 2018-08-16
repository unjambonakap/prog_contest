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

#include <map>

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
using namespace __gnu_cxx;

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;


#define MAX_X 1100
#define MAX_Y 35
#define MAX_N 1100
#define MAX_C 4

vector<pii> pl;
vector<int> ply[MAX_Y];
vector<vi> edges;



int mmap[MAX_X][MAX_Y];
int n;
int cover[MAX_N];
int cedge[MAX_Y];

int solve(){
	int i, j, k, l, x, y;

	int md;

	edges.clear();

	
	REP(i, SZ(pl))
		edges.pb(vi());

	memset(cover, 0, sizeof(cover));
	memset(cedge, 0, sizeof(cedge));
	FE(it, pl){
		x=it->ST, y=it->ND;

		FOR(j, -1, 1){
			if (y+j < 0 || y+j >= MAX_Y)continue;

			FOR(i, x+1, MAX_X-1){
				if (mmap[i][y+j] != -1){
					cover[mmap[x][y]]|=two(j+1);
					if (j == 0)
						cover[mmap[i][y+j]]|=two((j+1+2)%4);
					if (j != 0)
						cedge[MIN(y, y+j)]++;

					edges[mmap[x][y]].pb(mmap[i][y+j]), edges[mmap[i][y+j]].pb(mmap[x][y]);
					break;
				}
			}
		}
	}

	md=0;
	REP(i, SZ(pl))
		md=MAX(md, SZ(edges[i]));
	
	if (md == 0)return 1;
	REP(j, MAX_Y)
		if (cedge[j] >= 2)
			break;
	if (j == MAX_Y)
		return 2;



	FE(it, pl){
		j=mmap[it->ST][it->ND];
		if (cover[j] == two(4)-1 && (SZ(edges[j])&1))
			return 4;
		
	}
	
	return 3;

}

int main(){
	int i, j, k, T;
	int x, y;

	cin >> T;
	REP(i, T){
		cin >> n;

		CLR(pl);
		REP(j, MAX_Y)
			CLR(ply[j]);

		memset(mmap, -1, sizeof(mmap));
		REP(j, n){
			cin >> x >> y;
			pl.pb(pii(x, y)), mmap[x][y]=pl.size()-1; 
			ply[y].pb(x);
		}
//		if (i!=98)continue;
//		FE(it, pl)
//			printf("%d %d\n", it->ST, it->ND);
		//REP(j, MAX_Y)
		//	sort(ALL(pl[j]));

		printf("Case #%d: %d\n", i+1, solve());


	}


	return EXIT_SUCCESS;
}

