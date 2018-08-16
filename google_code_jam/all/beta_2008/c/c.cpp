#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>

#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back


#define MAX_BUF 256
#define MAX_N 50
#define START 0

using namespace std;

string list[MAX_N];
int n, n_t, n_visitable;
int total_n;


typedef struct data{
	int n, v;
	int s, e;
	int id, n_used;
	
}data;
data *t[MAX_N][MAX_N];

data l_d[MAX_N];

int cost[MAX_N];
double prob[MAX_N];


void reset_count(){
	int i;

	total_n = 0;
	REP(i, n)
		l_d[i].n_used = 0;
}

void update_count(vector<int> path){
	int factor, i;

	factor = 1;
	REP(i, path.size() - 1)
		factor *= t[path[i]][path[i+1]]->n;
	

	total_n += factor;

	REP(i, path.size() - 1)
		t[path[i]][path[i+1]]->n_used += factor;
}

void update_prob(){
	int i;

	if (total_n == 0)
		return;
	REP(i, n)
		prob[i] += (double)(l_d[i].n_used) * 1. / (double)(total_n) * 1. / (double)(n_visitable);
	
}

void dfs(int act, vector<int> path, int dest, int nc){

	int i;
	if (cost[act] != -1 && cost[act] < nc)
		return;

	path.pb(act);
	if (act == dest){

		if (cost[act] == -1 || nc < cost[act]){
			reset_count();
			cost[act] = nc;
		}
		update_count(path);
	}else{

		cost[act] = nc;
		REP(i, n_t)
			if (t[act][i])
				dfs(i, path, dest, cost[act] + t[act][i]->v);
			

	}

}

void solve(){

	int i, j, nc;
	vector<int> a;
	data *d;
	int id;

	REP(i, MAX_N)
		prob[i] = 0;

	FOR(i, 1, n_t){
		memset(cost, -1, sizeof(cost));
		reset_count();
		a.clear();
		dfs(START, a, i, 0);
		update_prob();


	}
}

void set_visitable(){

	stack<int> s;
	int i, id;

	s.push(START);
	n_visitable = -1;
	memset(cost, 0, sizeof(cost));


	while(!s.empty()){

		id = s.top();
		s.pop();
		if (cost[id])
			continue;

		n_visitable++;

		cost[id] = 1;

		REP(i, n_t){
			if (t[id][i])
				s.push(i);
		}
	}

}


int main(){
	int i, j, k, x, l, a_id, b_id;
	char a[MAX_BUF], b[MAX_BUF], start[MAX_BUF];
	data *d;

	scanf("%d", &x);

	REP(i, x){

		scanf("%d %s\n", &n, start);

		REP(j, MAX_N)
			REP(k, MAX_N)
				t[j][k] = NULL;

		list[START] = start;

		n_t = 1;

		REP(j, n){

			scanf("%s %s %d", a, b, &l_d[j].v); 

			a_id = b_id = -1;
			REP(k, n_t){
				if (list[k] == a)
					a_id = k;
				else if (list[k] == b)
					b_id = k;
			}

			if (a_id == -1)
				a_id = n_t, list[n_t++] = a;
			if (b_id == -1)
				b_id = n_t, list[n_t++] = b;

			l_d[j].s = a_id, l_d[j].e = b_id;
			l_d[j].n = 1;
			l_d[j].id = j;

		}

		REP(j, n){
			d = l_d + j;
			if (t[d->s][d->e] == NULL)
				t[d->s][d->e] = d;
			else if (t[d->s][d->e]->v > d->v)
				t[d->s][d->e] = d;
			else if (t[d->s][d->e]->v == d->v)
				t[d->s][d->e]->n++;
		}


		//REP(j, n)
		//	REP(k, n)
		//		if (t[j][k])
		//			printf("%d )> %d\n", j, k);

		set_visitable();
		solve();
		printf("Case #%d: ", i + 1);

		REP(j, n){
			a_id = t[l_d[j].s][l_d[j].e]->id;
			if (l_d[j].v == l_d[a_id].v)
				printf(" %.7lf", prob[a_id] / (double)l_d[a_id].n);
			else
				printf(" %.7lf", 0.);



		}
		cout << endl;
	}
}



