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
#define SWAPI(a,b) (a^=b, b^=a, a^=b)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;


#define MAX_D 21
int tb[MAX_D];
int od[MAX_D];

void solve(){
	int i, j, k;
	int b, sid;
	char c;
	memset(tb, 0, sizeof(tb));
	memset(od, 0, sizeof(od));

	i=0;
	while(1){

		scanf("%c", &c);
		if (c == '\n')break;
		od[i++]=c-'0';

	}
	reverse(od, od+i);

	FOR(j, 1, i){
		sid=-1;
		REP(k, j){
			if (od[k] > od[j] && (sid == -1 || od[k] < od[sid]))
				sid=k;
		}
		if (sid != -1)break;
	}
	
	assert(sid != -1);
	SWAPI(od[j], od[sid]);
	sort(od, od+j, greater<int>());


	if (od[i] != 0)
		i++;
	REPV(j, i)
		printf("%c", od[j]+'0');

	
	printf("\n");


	


}


int main(){
	int i, T;
	scanf("%d\n", &T);
	REP(i, T){

		printf("Case #%d: ", i+1);
		solve();
	}


	return EXIT_SUCCESS;
}

