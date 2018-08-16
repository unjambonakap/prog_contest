#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ext/hash_map>

#include <gmp.h>

using namespace std;
using namespace __gnu_cxx;

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
#define FEV(i,t) for (typeof(t.rbegin())i=t.rbegin();i!=t.rend();i++)

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
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second

#define ll unsigned long long

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;


#define MAX_D 10000
#define MAX_M 50
#define MAX_T 50



int m[MAX_T];
int dm[MAX_T][MAX_M];
ll t, n;
ll A, B, K;

ll d[MAX_T][MAX_D];


ll pgcd(ll a, ll b){
	ll c;
	if (b > a)
		SWAP(a, b, c);
	if (a%b == 0)
		return b;
	return pgcd(b, a%b);
}


void simple_frac(){
	ll p;

	K+=A/B;
	A%=B;
	if (A == 0)
		B=1;
	else
		while((p=pgcd(A, B)) != 1)
			A/=p, B/=p;
}


int solve(){

	int i, j, k, l;
	ll lv;

	A=K=0;
	B=(ll)n*(ll)n;

	REP(i, t){
		k=0;
		REP(j, MAX_D){
			if (k != m[i] && dm[i][k] == j)
				k++;
			d[i][j]=k;
		}
	}


	
	ll ink;
	REP(i, MIN(MAX_D, n)){
		ink=lv=0;

		REP(j, t){
			lv+=d[j][i]*n;
			ink+=lv/B;
			lv%=B;
		}
		REP(j, t)
			FOR(k, j+1, t-1){
				lv+=2*d[j][i]*d[k][i];
				ink+=lv/B;
				lv%=B;
			}
		A+=lv;
		K+=A/B+ink;
		A%=B;
	}

	mpz_t na, nb, nc;
	mpz_init(na);
	mpz_init(nb);
	mpz_init(nc);

	char buf[255];
	sprintf(buf, "%Ld", lv);
	mpz_set_str(na, buf, 10);
	sprintf(buf, "%Ld", B);
	mpz_set_str(nc, buf, 10);

	mpz_mul_ui(nb, na, (n-i));
	mpz_set(na, nb);
	mpz_fdiv_q(nb, na, nc);
	K+=ink*(n-i)+mpz_get_ui(nb);
	mpz_fdiv_r(nb, na, nc);

	mpz_get_str(buf, 10, nb);
	sscanf(buf, "%Ld", &lv);
	A+=lv;

	K+=A/B;
	A%=B;



	
	mpz_clear(na);
	mpz_clear(nb);
	
	assert(A < B);

	simple_frac();

}



int main(){
	int i, j, k, T;
	ll d;
	
	scanf("%d", &T);
	REP(i, T){
		scanf("%Ld %Ld", &n, &t);

		REP(j, t){
			scanf("%d", m+j);

			dm[j][0]=0;
			REP(k, m[j]-1){
				scanf("%d", &dm[j][1+k]);
				dm[j][1+k]--;
			}

		}
		solve();
		printf("Case #%d: %Ld+%Ld/%Ld\n", i+1, K, A, B);


	}


	return EXIT_SUCCESS;
}

