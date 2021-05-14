#include "Item.h"
#include "tree.h"
#include <string.h>
#include <stdlib.h>


void getinf(Info* from, Info* here) {
	//here->inf_f = from->inf_f;
	if (from->inf1 != NULL && from->inf2 != NULL) {
		here->inf1 = (char*)calloc(strlen(from->inf1) + 1, sizeof(char));
		strcpy(here->inf1, from->inf1);
		here->inf2 = (char*)calloc(strlen(from->inf2) + 1, sizeof(char));
		strcpy(here->inf2, from->inf2);
		free(from->inf2);
		free(from->inf1);
	}
	//free(from);
}

void to_int(char* str, int* re) {
	int help;
	*re = 0;
	for (int i = 0; i < strlen(str); i++) {
		help = str[i] - '0';
		(*re) = (*re) * 10 + help;
	}
}
