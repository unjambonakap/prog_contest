#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <stack>
#include <errno.h>

#define REP(i,n) for(i = 0; i < n; i++)
#define REPV(i, n) for (i = n - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = a; i < b; i++)
#define FORV(i, a, b) for(i = b - 1; i >= a; i--)
#define MAX(a,b) ((a < b) ? b : a)
#define MIN(a,b) ((a < b) ? a : b)
#define SQRT(a,b,x,y) sqrt((a-x)*(a-x) + (b-y)*(b-y))

#define PB(s) {printf("Problem: %s\n", s); exit(EXIT_FAILURE);}



#define MAX_ITEMS 15
#define MAX_STORES 51 
#define MAX_POS 1 << MAX_ITEMS
#define MAX_BUF 2048
#define START 0

typedef struct store{
	int x, y;
	double items[MAX_ITEMS];
   	int n_items, items_id[MAX_ITEMS];
}store;

double data[MAX_STORES][MAX_POS];

class state{
	public:
		state(){};
		state(int i, int s, double c){ items = i, store = s, cost = c; }
		bool operator<(state &s){ return this->cost > s.cost; }
		int items, store;
		double cost;
};



store stores[MAX_STORES];
int n_stores, gp;
int n_items;
char i_l[MAX_ITEMS][MAX_BUF];
int perish[MAX_ITEMS];
double min_cost;



void purge(FILE *f){
	int c;
	while( (c = getc(f) != '\n') && c != EOF && c != 1);//on lit jusqu'à la fin de ligne (flush input buffer)
}

int readString(char *s, int l, FILE *f){
	//fonction pour lire proprement une chaine au clavier
	char *a;

	if ((a = fgets(s, l, f)) == NULL)//copie l'input dans la chaine de caractère s
		return -1;


	while(*a != '\0' && *a != '\n')//on recherche le dernier caractère rentrée: '\0' ou '\n'
		a ++;


	if (*a == '\0')//on a rentré plus de caractère que la chaine peut en contenir => il faut lire les caractères restants pour que les saisies suivantes soient correctes
		purge(f);
	else
		*a = '\0';// équivalent à chomp

	return 0;
}

double get_cost(int a, int b){ return SQRT(stores[a].x, stores[a].y, stores[b].x, stores[b].y) * gp; }

double solve(){
	int i, j, k, id;
	bool per;
	double cost, nc;
	state *s, *e;
	store *a;
	std::priority_queue<state*> p;


	REP(i, MAX_STORES)
		REP(j, MAX_POS)
			data[i][j] = -1;


	s = new state(0, 0, 0);

	min_cost = -1;

	s->store = 0;
	p.push(s);
	data[START][0] = 0;

	while(!p.empty()){
		s = p.top();
		p.pop();

		if (min_cost != -1 && s->cost >= min_cost){
			free(s);
			continue;
		}
		
		a = stores + s->store;

		REP(i, (1 << a->n_items)){
			if (i == 0 && s->store != START)
				continue;

			cost = s->cost;
			per = false;
			k = 0;

			
			REP(j, a->n_items){
				if (i & (1 << j)){

					id = a->items_id[j];

					k |= 1 << id;
					cost += a->items[id];
					per |= perish[id];
				}
			}
			if (k & s->items)
				continue;

			k |= s->items;
			if (min_cost != -1 && cost >= min_cost)
				continue;

			REP(j, n_stores){
				if (j == s->store || (j != START && per))
					continue;
				nc = cost + get_cost(j, s->store);
				if ((data[j][k] == -1 || nc < data[j][k]) && (min_cost == -1 || nc < min_cost)){
					e = new state(k, j, nc);

					data[j][k] = nc;
					if (j == 0 && k == ((1 << n_items) - 1))
						min_cost = nc;
					p.push(e);

				}


			}


		}
		//printf("n items: %d\n", stores[s->store].n_items);
		delete s;
	}


	return data[START][(1 << n_items) - 1];


}










int main(){

	int i, j, k, x;
	char s[MAX_BUF], *a, *b, *endptr;


	scanf("%d", &x);

	stores[START].n_items = stores[START].x = stores[START].y = 0;

	REP(i, x){
		scanf("%d %d %d", &n_items, &n_stores, &gp);

		REP(j, n_items){
			scanf("%s", i_l[j]);
			if (i_l[j][strlen(i_l[j]) - 1] == '!')
				perish[j] = 1, i_l[j][strlen(i_l[j]) - 1] = '\0';
			else
				perish[j] = 0;
		}


		FOR(j, 1, n_stores + 1){
			if (scanf("%d %d ", &stores[j].x, &stores[j].y) != 2)
				PB("format");
			if (readString(s, MAX_BUF, stdin))
				PB("format s");

			b = s;

			stores[j].n_items = 0;
			while(a = strchr(b, ':')){
				REP(k, n_items){
					if (!strncmp(i_l[k], b, (int)(a - b)))
						break;
				}

				if (k == n_items) PB("No corresponding items");

				errno = 0;
				b = a + 1;

				stores[j].items_id[stores[j].n_items] = k;
				stores[j].items[k] = strtol(b, &endptr, 10);
				if (errno != 0) PB("reading\n");
				stores[j].n_items++;

				if (*endptr != ' ')
					break;
				b = endptr + 1;

			}
		}
		n_stores++;

		printf("Case #%d: %lf\n", i + 1, solve());
	}

}

