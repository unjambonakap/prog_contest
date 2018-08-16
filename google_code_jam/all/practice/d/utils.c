
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LEN 255

char buffer[MAX_LEN];

void purge(FILE *f){
	int c;
	while( (c = getc(f) != '\n') && c != EOF && c != 1);//on lit jusqu'à la fin de ligne (flush input buffer)
}

void clear_screen(){
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n");

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

int readInt(int *a, FILE *f){
	//cette fonction lit une chaine de caractère, et le convertit en entier
	if(readString(buffer, MAX_LEN, f) == -1) return -1;

	char *endptr;
	errno = 0;
	*a = strtol(buffer, &endptr, 10);
	if (errno != 0 || endptr == buffer)
		return -1;

	return 0;



}
char isAlpha(char c){
	c |= 0x20;//convertit c de uppercase a lowercase (c codé sur 1 octet, le 5ème bit diffère pour uppercase/lowercase, cf table ASCII)
	return c >= 'a' && c <= 'z';
}

char isNum(char c){
	return c >= '0' && c <= '9';
}
char isAlNum(char c){
	return isNum(c) || isAlpha(c);
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


