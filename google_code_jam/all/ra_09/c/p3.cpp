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

int n, c;

#define MAX_C 41

double store[MAX_C];
long double fact[MAX_C];

long double comb(int a, int b){
	if (a > b)return 0;
	return fact[b]/(fact[a]*fact[b-a]);

}

double prob(int k){
	int i;
	long double p, coeff, cp;
	if (store[k] != -1)
		return store[k];

	if (k == c)return 0;

	cp=comb(n, c);
	p=cp, coeff=1;
	FOR(i, k+1, c+1){
		if (i-k > n)break;
		p+=prob(i)*comb(i-k, c-k)*comb(n-(i-k), k);
	}
	p/=cp;
	coeff-=(long double)comb(0, c-k)*comb(n, k)/cp;
	assert(coeff != 0);

	
	return (store[k]=p/coeff);



}

int main(){
	int i, j, T;
	cin >> T;
	fact[0]=1;
	FOR(i, 1, MAX_C)
		fact[i]=fact[i-1]*i;
	

	REP(i, T){
		cin >> c >> n;
		REP(j, MAX_C)
			store[j]=-1;
		printf("Case #%d: %lf\n", i+1, prob(0));

	}


	return EXIT_SUCCESS;
}

