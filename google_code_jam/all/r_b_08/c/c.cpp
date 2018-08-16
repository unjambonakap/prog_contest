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
#define PB push_back


#define MAX_K 1000110
#define MAX_N 101

typedef struct node{
	int c, s, e;
	node *l, *r, *p;
}node;

int t, n;
int card[MAX_K];
int ask[MAX_N];
int use_id;
node counter[MAX_K * 2];


node *set_node(int s, int e, node *p){

	node *n = counter + use_id;
	int m;

	if (s > e)
		return NULL;

	n->s = s, n->e = e, n->c = e - s + 1;
	n->p = p;

	if (s == e)
		return n;
	

	m = (s + e) / 2;

	++use_id;
	n->l = set_node(s, m, n);
	++use_id;
	n->r = set_node(m + 1, e, n);
	return n;


}

node *find_card(node *r, int pos){
	if (r->e == r->s)
		return r;
	if (pos > r->l->c)
		return find_card(r->r, pos - r->l->c);
	else
		return find_card(r->l, pos);

}

void update(node *n){
	if (n == NULL)
		return;

	--n->c;
	update(n->p);

}


void solve(){
	
	int i, j, pos, h, s;
	node *r, *e;

	use_id = 0;
	r = set_node(0, t - 1, NULL);
	pos = 1;
	REP(i, t){
		pos = (pos + i - 1) % r->c + 1;
		e = find_card(r, pos);
		card[e->s] = i;
		update(e);


	}


	
}

int main(){
	int i, j, x;


	scanf("%d", &x);
	REP(i, x){
		scanf("%d", &t);
		scanf("%d", &n);
		REP(j, n)
			scanf("%d", ask + j);

		solve();
		printf("Case #%d:", i + 1);
		REP(j, n)
			printf(" %d", card[ask[j] - 1] + 1);
		printf("\n");
	}
	return 0;


}

