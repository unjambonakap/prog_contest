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

#define MAX_N 62

char buf[MAX_N];
char seen[256];
int cor[256];
int base;
int used[MAX_N];




int main(){
	int i, j, k, T, ns;
	char c;

	scanf("%d\n", &T);

	REP(i, T){

		ns=0;
		while((c=getchar()) != '\n')
			buf[ns++]=c;

		base=0;
		memset(seen, 0, sizeof(seen));
		REP(j, ns)
			if (seen[buf[j]] == 0)
				base++, seen[buf[j]]=1;
		if (base == 1)base=2;
		
		memset(cor, -1, sizeof(cor));
		memset(used, 0, sizeof(used));
		REP(j, ns){
			if (cor[buf[j]] == -1){
				FOR(k, (j == 0)?1:0, base)
					if (!used[k]){
						used[k]=1, cor[buf[j]]=k;
						break;
					}
			}
		}

		ll ret=0;
		REP(j, ns)
			ret=ret*base+cor[buf[j]];
		printf("Case #%d: %Ld\n", i+1, ret);

	}


	return EXIT_SUCCESS;
}

