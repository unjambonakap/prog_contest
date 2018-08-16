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

#define MAX_N 50

int n;
int tb[MAX_N];

int solve(){
	int i, j, k, s;
	int c;

	c=0;

	REP(i, n){
		if (tb[i] <= i)continue;
		FOR(j, i, n-1)
			if (tb[j] <= i)
				break;
		assert(j < n);
		s=tb[j];
		c+=j-i;
		FORV(k, j, i+1)
			tb[k]=tb[k-1];
		tb[i]=s;

	}
	return c;


}


int main(){
	int i, j, k, T;
	char c;

	scanf("%d\n", &T);
	REP(i, T){
		scanf("%d\n", &n);
		REP(j, n){
			tb[j]=0;

			REP(k, n){
				cin >> c;
				if (c == '1')
					tb[j]=k;
			}
			scanf("\n");
		}

		printf("Case #%d: %d\n", i+1, solve());

	}



	return EXIT_SUCCESS;
}

