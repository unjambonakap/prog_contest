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


int q, p;


int solve(int p, vi ql){

	int i, j, bm, m;

	if (ql.size() == 0)
		return 0;

	bm=-1;
	m=-1;

	REP(j, ql.size()){
		bm=ql[j];

		vi al, bl;
		REP(i, ql.size()){
			if (ql[i] < bm)
				al.pb(ql[i]);
			else if (ql[i] > bm)
				bl.pb(ql[i]-bm-1);
		}
		if (m == -1)
			m=solve(bm, al)+solve(p-bm-1, bl);
		else
			m=MIN(m, solve(bm, al)+solve(p-bm-1, bl));
	}

	return m+p-1;

}

int main(){

	int i, j, T, a;
	cin >> T;
	REP(i, T){

	
		vi ql;
		cin >> p >> q;

		REP(j, q){
			cin >> a;
			a--;
			ql.pb(a);
		}

		printf("Case #%d: %d\n", i+1, solve(p, ql));

	}

	return EXIT_SUCCESS;
}

