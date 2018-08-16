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


#define MAX_Q 110
int q, p, il;

vi ql;
int dp[MAX_Q][MAX_Q];
int solve(int s, int t){
	int i, m, r;

	if (dp[s][t] != -1)
		return dp[s][t];

	if (s == t-1)
		return 0;

	m=-1;
	FOR(i, s+1, t-1){
		r=solve(s, i)+solve(i, t)+ql[t]-ql[s]-2;
		if (m == -1 || m > r)
			m=r;
	}
	return dp[s][t]=m;
	
}

int main(){

	int i, j, T, a;
	cin >> T;
	REP(i, T){

		ql.clear();
		
		cin >> p >> q;

		ql.pb(0);
		REP(j, q){
			cin >> a;
			a;
			ql.pb(a);
		}
		ql.pb(p+1);


		sort(ALL(ql));

		memset(dp, -1, sizeof(dp));
		printf("Case #%d: %d\n", i+1, solve(0, SZ(ql)-1));

	}

	return EXIT_SUCCESS;
}

