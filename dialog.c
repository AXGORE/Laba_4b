#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "tree.h"
#include "dialog.h"
#include "time.h"



int Get_double(double* a) {
	int n;
	do {
		n = scanf("%lf", a);
		if (n == -1) { return -1; }
		if (n == 0) {
			printf("Error, try something else ");
			scanf("%*s");
		}
	} while (n == 0);
	return 1;
}
int Get_key(int* a) {
	int x;
	do {
		x = scanf("%d", a);
		if (x == 0) {
			printf("%s\n", "Error, try again ");
			scanf("%*s");
		}
		if (x == -1) { return -1; }
	} while (x == 0);
}


void Get_int(int* a) {
	int x;
	do {
		do {
			x = scanf("%d", a);
			if (x == 0) {
				printf("%s\n", "Error, try again ");
				scanf("%*s");
			}
			if (x == -1) { *a = -1; return; }
		} while (x == 0);
		if (*a < 1) {
			printf("%s\n", "Error, try again ");
			scanf("%*s");
		}
	} while (*a < 1);
}
char* Get_str() {
	int a = 1, size = 80;
	char help_str[81];
	int n = 1;
	char* osn_str;
	osn_str = (char*)calloc(1, sizeof(char));
	while (1 == 1) {
		n = scanf("%80[^\n]s", &help_str);
		if (n == -1) { return NULL; }
		if (n == 0) { return osn_str; }
		//size += 80;
		osn_str = (char*)realloc(osn_str, (size + a) * sizeof(char));
		strcpy((osn_str)+(a - 1), help_str);
		a += 80;
	}
}
void No_Key() {
	printf("\nNo elements with this key or number\n");
}
void Empty() {
	printf("\ntree is empty\n");
}

void show_tree(Item* tree) {
	Item* start = tree;
	if (start == NULL) { return; }
	show_tree(start->left);
	printf("\nBalance: %d\n", start->balance);
	show_inf(start);
	show_tree(start->right);
}

int dialog(int* key, Info** info, int* num) {
	char* options[] = { "1. Add Item","2.Delete Items with specefied key and number","3.Find Items with specefied keys", "4.Show the most different element(s)","5.Timing","6.Show tree","7.Exit" };
	int flag, vsp, n;
	printf("Choose one option:\n");
	for (int i = 0; i < 7; i++) {
		printf("%s\n", options[i]);
	}
	do {
		Get_int(&vsp);
		if (vsp > 7) { printf("%s\n", "Error, try again "); }
	} while (vsp > 7);
	if (vsp == -1) { return 7; }
	printf("\n");
	if (vsp == 1) {
		printf("Enter key -->\n");
		flag = Get_key(key);
		if (flag == -1) { return 7; }
		printf("Enter information 1 (string) -->\n");
		while (getchar() != '\n');
		(*info)->inf1 = Get_str();
		if ((*info)->inf1 == NULL) { return 7; }
		printf("Enter information 2 (string) -->\n");
		while (getchar() != '\n');
		(*info)->inf2 = Get_str();
		if ((*info)->inf2 == NULL) { return 7; }
		return 1;
	}
	if (vsp == 2) {
		printf("Enter key -->\n");
		while (getchar() != '\n');
		flag = Get_key(key);
		if (flag == -1) { return 7; }
		return 2;
	}
	if (vsp == 3) {

		printf("Enter key -->\n");
		flag = Get_key(key);
		if (flag == -1) { return 7; }
		return 3;
	}

	if (vsp == 4) {
		printf("Enter key -->\n");
		while (getchar() != '\n');
		flag = Get_key(key);
		if (flag == -1) { return 7; }
		return 4;
	}
	if (vsp == 5) {
		return 5;
	}
	if (vsp == 6) {
		return 6;
	}
	if (vsp == 7) {
		return 7;
	}
}
void show_inf(Item* tree) {
	if (tree->inf == NULL) {
		printf("\nTree is empty\n");
		return;
	}
	printf("Key--> %d \nInformation:\n%s\n%s\n", tree->key, tree->inf->inf1, tree->inf->inf2);
}
void No_Elements() {
	printf("\nNo elements in this range\n");
}
void No_File() {
	printf("\nNo file with this name\n");
}

int D_Timing() {
	Item* tree = (Item*)calloc(1, sizeof(Item));
	Info* inf = (Info*)calloc(1, sizeof(Info));
	Item* next;
	int n = 10, key[10000], k, cnt = 10000, i, m;
	clock_t first, last;
	srand(time(NULL));
	while (n-- > 0) {
		for (i = 0; i < 10000; ++i)
			key[i] = rand() * rand();
		for (i = 0; i < cnt; ) {
			k = rand() * rand();
			AddItem(&tree, inf, k);
			++i;
		}
		m = 0;
		first = clock();
		for (i = 0; i < 10000; ++i) {
			Item* start = tree;
			next= find(key[i],tree);
			if (next != NULL) {
				++m;
			}
		}
		last = clock();
		printf("%d items was found\n", m);
		printf("test #%d, number of nodes = %d, time = %d\n", 10 - n, (10 - n) * cnt, last - first);
	}
	free_tree(tree);
	free(inf);
	return 1;
}