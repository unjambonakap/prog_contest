#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>

#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PB push_back


using namespace std;

#define MAX_E 500

class event{
	public: 

		event(){};

		bool operator<(const event &s)const { return (this->time < s.time || (this->time == s.time && this->start < s.start)) ; }

		bool a, start;
		int time;



};


event e[MAX_E];
int n, na, nb;


void solve(){
	int ia, ib, i, j, *pi, *pn;


	ia = ib = 0;
	na = nb = 0;
	sort(e, e + n);
	REP(i, n){
		if (e[i].a)
			pi = &ia, pn = &na;
		else
			pi = &ib, pn = &nb;

		if (e[i].start){
			if (*pi == 0)
				++(*pn);
			else
				--(*pi);

		}else
			++(*pi);
	}


	


}

int main(){
	int i, j, x, h, m, t, l;

	scanf("%d", &x);
	REP(i, x){
		scanf("%d", &l);
		scanf("%d %d", &na, &nb);

		n = 2 * (na + nb);
		REP(j, 2 * na){
			scanf("%d:%d", &h, &m);
			t = h * 60 + m;
			e[j].a = 1, e[j].start = 1, e[j].time = t;

			++j;

			scanf("%d:%d", &h, &m);
			t = h * 60 + m + l;
			e[j].a = 0, e[j].start = 0, e[j].time = t;
		}


		FOR(j, 2 * na, n){
			scanf("%d:%d", &h, &m);
			t = h * 60 + m;
			e[j].a = 0, e[j].start = 1, e[j].time = t;

			++j;

			scanf("%d:%d", &h, &m);
			t = h * 60 + m + l;
			e[j].a = 1, e[j].start = 0, e[j].time = t;
		}
			

		solve();
		printf("Case #%d: %d %d\n", i + 1, na, nb);

	}


}

