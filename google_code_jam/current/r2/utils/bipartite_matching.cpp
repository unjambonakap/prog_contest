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


#define MAX_K 25
#define MAX_N 100

int store[MAX_N][MAX_K];
int edge[MAX_N][MAX_N];
int visited[MAX_N], match[MAX_N][2];

int n, nk;

int dfs(int a){
	int i;

	if (visited[a])return 0;
	visited[a]=1;

	REP(i, n){
		if (edge[a][i] == 0)continue;
		
		if (match[i][1] == -1 || dfs(match[i][1])){
			match[a][0]=i, match[i][1]=a;
			return 1;
		}
	}

	
			

	return 0;

}


int solve(){
	int i, j, k;

	memset(edge, 0, sizeof(edge));

	REP(i, n)
		REP(j, n){
			REP(k, nk)
				if (store[i][k] <= store[j][k])break;
			edge[i][j]=(k == nk)?1:0;
		}


	int c=0;
	memset(match, -1, sizeof(match));
	REP(i, n){
		memset(visited, 0, sizeof(visited));

		if (!dfs(i))c++;
	}

	return c;



}

int main(){

	int i, j, k, T;
	cin >> T;
	REP(i, T){

		cin >> n >> nk;
		REP(j, n)
			REP(k, nk)
				cin >> store[j][k];

		printf("Case #%d: %d\n", i+1, solve());


		

	}

	return EXIT_SUCCESS;
}





