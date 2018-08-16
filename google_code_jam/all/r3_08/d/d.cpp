#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <assert.h>


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define SWAPG(a,b,c) c = a, a = b, b = c;
#define pb push_back
#define ll long long


#define MAX_H 100000000
#define MAX_W 100000000
#define MAX_R 15
#define MOD 10007

class Point{
	public: 
		Point(){};
		bool operator<(const Point &p) const{return (this->y < p.y || (this->y == p.y && this->x < p.x));}
		int x, y;
};

int h, w, r;
int ret;
int tb[MOD][MOD];
int inv[MOD];
/*
   A * 2 + B * 1 = x
   A * 1 + B * 2 = y

   A =  (y - 2 x) / -3
   b = x - 2 A
*/
Point rock[MAX_R];

int comb(int n, int k){

	int s, i;

	if (k > n)
		return 0;

	if (tb[n][k] != -1)
		return tb[n][k];

	s = 1;
	REP(i, n)
		s = (s * (i + 1)) % MOD;
	REP(i, k)
		s = (s * inv[i + 1]) % MOD;
	REP(i, n - k)
		s = (s * inv[i + 1]) % MOD;
	return tb[n][k] = s;


}
int comb_mod(int x, int y){
	int s, p;

	if (x < 0 || y < 0)
		return 0;
	s = x + y;

	p = 1;
	while(s > 0){
		p = (p * comb(s % MOD, x % MOD)) % MOD;
		s /= MOD, x /= MOD;
	}
	//printf("here: %d %d =>>>> %d\n", x, y, p);
	return p;

}

void solve(){

	int s;
	int i, j, sgn;
	int prevx, prevy;

	//printf("%d %d\n", w, h);


	ret = 0;
	REP(i, 1 << r){
		s = 1;
		sgn = 1;
		prevx = prevy = 0;
		REP(j, r){
			if (i & 1 << j){
				sgn *= -1;
				s = (comb_mod(rock[j].x - prevx, rock[j].y - prevy) * s) % MOD;
				prevx = rock[j].x, prevy = rock[j].y;
				if (s == 0)
					break;
			}
		}
		if (s != 0)
			s = (comb_mod(w - prevx, h - prevy) * s) % MOD;

		ret = (sgn * s + ret) % MOD;
	}
	ret = (ret + MOD) % MOD;


	
}

int eul(int ro, int uo, int vo, int ra, int ua, int va){

	int nr, nu, nv;

	assert(ra != 0);
	nr = ro % ra;
	nu = uo - ro / ra * ua;
	nv = vo - ro / ra * va;

	if (nr == 1)
		return nu;
	return eul(ra, ua, va, nr, nu, nv);
}


void set_inv(){
	int i;
	inv[0] = 0;
	inv[1] = 1;

	FOR(i, 2, MOD){
		inv[i] = (MOD + eul(MOD, 0, 1, i, 1, 0)) % MOD;
		assert(i * inv[i] % MOD == 1);
	}

}

int main(){
	int i, j, x;
	int a, b;

	REP(i, MOD)
		REP(j, MOD)
			tb[i][j] = -1;
	set_inv();

	scanf("%d", &x);
	REP(i, x){
		scanf("%d %d %d", &b, &a, &r);
		b--, a--;

		if ((b - 2 * a) % (-3) != 0)
			w = -1;
		else
			w = (b - 2 * a) / (-3);
		h = a - 2 * w;

		REP(j, r){
			scanf("%d %d", &b, &a);
			b--, a--;
			if ((b - 2 * a) % (-3) != 0)
				rock[j].x = -1;
			else
				rock[j].x = (b - 2 * a) / (-3);
			rock[j].y = a - 2 * rock[j].x;

		}
		std::sort(rock, rock + r);

		
		
		solve();
		printf("Case #%d: %d\n", i + 1, ret);






	}


	return EXIT_SUCCESS;
}

