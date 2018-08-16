#include "gen_prime.hpp"



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

#define ll long long

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

#define MAX_N 12048

char buf[MAX_N];


int jacobi_symbol(mpz_t _a, mpz_t _b){
	mpz_t a, b, c;
	int i, f;

	mpz_init_set(a, _a), mpz_init_set(b, _b);
	mpz_init(c);

	//b odd
	if (mpz_cmp_ui(b, 1) == 0){
		mpz_clear(a), mpz_clear(b), mpz_clear(c);
		return 1;
	}
	if (mpz_cmp_ui(a, 0) == 0){
		mpz_clear(a), mpz_clear(b), mpz_clear(c);
		return 0;
	}

	if (mpz_cmp_ui(a, 2) == 0){

		f=mpz_mod_ui(c, b, 8);
		if (f == 1 || f == 7)
			f=1;
		else f=-1;

		mpz_clear(a), mpz_clear(b), mpz_clear(c);
		return f;


	}
	

	if (mpz_cmp(a, b) >= 0)
		mpz_mod(c, a, b), mpz_set(a, c);

	if (mpz_cmp_ui(a, 0) == 0){
		mpz_clear(a), mpz_clear(b), mpz_clear(c);
		return 0;
	}
	

	f=1;
	if (mpz_even_p(a)){
		mpz_get_str(buf, 2, a);

		int ol=strlen(buf);
		REPV(i, strlen(buf))
			if (buf[i] == '1')break;



		buf[i+1]='\0';

		mpz_set_ui(c, 2);
		mpz_set_str(a, buf, 2);

		f=pow(jacobi_symbol(c, b), ol-1-i);
	}

	//now a odd
	mpz_t ma, mb;
	mpz_init(ma);
	mpz_init(mb);


	mpz_mod_ui(ma, a, 4);
	mpz_mod_ui(mb, b, 4);

	if (mpz_cmp_ui(ma, 3) == 0 && mpz_cmp_ui(mb, 3) == 0)
		f*=-1;
	

	f*=jacobi_symbol(b, a);

	mpz_clear(ma);
	mpz_clear(mb);
	mpz_clear(a), mpz_clear(b), mpz_clear(c);

	return f;
}


int grandom(mpz_t a, int n){

	if (n > MAX_N-1) 
		return -1;

	int i;
	buf[n]='\0';
	REP(i, n)
		buf[i]='0'+rand()%10;
	mpz_set_str(a, buf, 10);
	return 0;
}

int grandom_odd(mpz_t a, int n){

	if (n > MAX_N-1) 
		return -1;

	int i;
	buf[n]='\0';
	REP(i, n-1)
		buf[i]='0'+rand()%10;
	buf[i]='0'+2*(rand()%5)+1;
	mpz_set_str(a, buf, 10);
	return 0;
}





