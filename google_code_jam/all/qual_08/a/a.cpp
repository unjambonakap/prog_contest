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
#define PB push_back


#define MAX_Q 1000
#define MAX_S 100
#define BUF_LEN 120

using namespace std;

string q[MAX_Q];
string s[MAX_S];
bool used[MAX_S];

int ns, nq;

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
int find_id(string a){
	int i;
	REP(i, ns)
		if (s[i] == a)
			return i;

	return -1;
}
int solve(){
	int i, j, c, nu, id;

	c = 0;

	nu = 0;
	REP(i, ns)
		used[i] = 0;

	REP(i, nq){

		
		id = find_id(q[i]);
		if (id != -1 && used[id] == 0){
		   if (nu == ns - 1){
			   ++c, nu = 1;
			   REP(j, ns)
				   used[j] = 0;
			   used[id] = 1;
		   }else
			   used[id] = 1, ++nu;
		}
	}

	return c;


}
int main(){
	int i, j, x;
	char buf[BUF_LEN];


	scanf("%d", &x);

	REP(i, x){

		scanf("%d\n", &ns);
		REP(j, ns){
			if (readString(buf, BUF_LEN, stdin))
				exit(-1);
			s[j] = buf;
			
		}

		scanf("%d\n", &nq);
		REP(j, nq){
			if (readString(buf, BUF_LEN, stdin))
				exit(-1);
			q[j] = buf;
		}
		
		printf("Case #%d: %d\n", i + 1, solve());


	}


}

