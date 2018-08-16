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

#define MAX_N 10000000
#define MAX_B 11
vi base;
int hp[MAX_N][MAX_B];
bool seen[100000];



int happy(int a, int b){
	int na, oa;

	

	if (a < MAX_N && hp[a][b] != -1)return hp[a][b];
	if (a < 10000 && seen[a])return 0;
	if (a < 10000)
	seen[a]=1;
	

	oa=a;

	na=0;
	while(a != 0){
		na+=SQR(a%b);
		a/=b;
	}
	if (oa >= MAX_N)
		return happy(na, b);

	hp[oa][b]=happy(na, b);
	if (oa < 10000)
	   	seen[oa]=0;
	return hp[oa][b];
}
int solve(){
	int i, j, k;
	bool ok=false;

	i=1;
	while(!ok){
		ok=true;
		i++;



		REP(j, SZ(base)){
			if (happy(i, base[j])==0){
				ok=false;
				break;
			}
		}





	}
	return i;


}



int main(){

	int i, j, T;
	char c;
	cin >> T;
	scanf("\n");

	memset(hp, -1, sizeof(hp));
	REP(i, MAX_B)
		hp[1][i]=1, hp[0][i]=0;

	REP(i, T){

		base.clear();

		while(1){
			scanf("%c", &c);

			if (c == '\n')break;
			if (c == ' ' || c == '0')continue;
			if (c == '1')
				c='0'+10;

			base.pb(c-'0');

		}
		printf("Case #%d: %d\n", i+1, solve());
	}
	return 0;
}




