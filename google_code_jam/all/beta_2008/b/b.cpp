#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <math.h>

#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)

#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

using namespace std;

#define MAX_N 64
#define MAX_LEN 256
#define MAX_BUF 2048

string list[MAX_N];
int cost[MAX_N];
bool u[MAX_N];
int n;



char isAlpha(char c){
	c |= 0x20;//convertit c de uppercase a lowercase (c codé sur 1 octet, le 5ème bit diffère pour uppercase/lowercase, cf table ASCII)
	return c >= 'a' && c <= 'z';
}

char isNum(char c){
	return c >= '0' && c <= '9';
}
char isAlNum(char c){
	return isNum(c) || isAlpha(c) || c == '_';
}




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
char *nextWord(char *s){
	int blank = 0;

	//recupere l'addresse du prochaine mot ou NUL/ si c'est le dernier mot


	while(*s != '\0'){//tant qu'on a pas parcouru toute la chaine de caractère

		if (blank == 0 && isAlNum(*s) == 0) blank = 1;//s est à la fin du mot actuel (premier caractère non alphanumérique)
		else if (blank == 1 && isAlNum(*s) == 1) return s;//on attend le prochain caractère alnum qui représente le début du prochain mot
		s++;

	}
	return NULL;

}


int calc(){
	int i, j, r;

	int d[MAX_N];

	r = 0;
	REP(i, n){
		d[i] = 1;
		if (!u[i])
			REP(j, i)
				if (!u[j] && cost[j] < cost[i])
					d[i] = MAX(d[i], d[j] + 1);

		r = MAX(r, d[i]);
	}
	return r;



}

void solve(){
	int i, j, r, id, k;

	r = calc();

	k = 0;
	while(1){
		id = -1;

		if (k == n - 1)
			break;

		REP(i, n){

			if (u[i]) continue;

			u[i] = 1;
			if (calc() == r)
				if (id == -1 || list[i] < list[id])
					id = i;

			u[i] = 0;
		}

		if (id == -1) break;

		u[id] = 1;
		++k;

		cout << " " << list[id];
	}
}

int main(){

	int i, j, k, x;
	char buf[MAX_BUF], *s, *a, w[MAX_LEN];

	scanf("%d\n", &x);
	REP(i, x){

		if (readString(buf, MAX_BUF - 1, stdin))
			exit(0);

		s = buf;
		n = 0;
		while(a = nextWord(s)){
			strncpy(w, s, (int)(a - s - 1));
			w[a - s - 1] = '\0';

			list[n] = w;
			s = a;
			++n;
		}
		strcpy(w, s);
		list[n] = w;

		++n;


		REP(j, n - 1)
			scanf("%d", cost + j);
		scanf("%d\n", cost + j);

		REP(j, n)
			u[j] = 0;

		printf("Case #%d:", i + 1);
		solve();
		cout << endl;
	}
}



