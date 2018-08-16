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

#define MAX_N 520
#define MOD 10000

char s[MAX_N];
char cs[]="welcome to code jam";
int dp[MAX_N][25];
int sl, csl;

int doit(int a, int b){
	int r;

	if (dp[a][b] != -1)
		return dp[a][b];

	if (b == csl)
		r=1;
	else if (a == sl)
		r=0;
	else{
		r=doit(a+1, b);
		if (s[a] == cs[b])
			r+=doit(a+1,b+1);
		
	}

	//printf("%d %d => %d\n", a, b, r);
	return dp[a][b]=(r%MOD);

}
int solve(){
	memset(dp, -1, sizeof(dp));
	return doit(0, 0);


}



int main(){
	int i, j, a, T;
	cin >> T;

	scanf("\n");

	csl=strlen(cs);
	REP(i, T){
		cin.getline(s, MAX_N);
		sl=strlen(s);
		a=solve();


		printf("Case #%d: ", i+1);

		j=10000;
		while((j/=10)>1)
			if (a<j)
				printf("0");
		
		printf("%d\n", a);
		


	}


	return EXIT_SUCCESS;
}

