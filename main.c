#include "Item.h"
#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dialog.h"
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

int main() {
	Info* inf = (Info*)calloc(1, sizeof(Info));
	Item* tree = (Item*)calloc(1, sizeof(Item));
	Item* help1;
	FILE* f;
	int release, key;
	char* name;
	//char* fname ;
	int a, f1 = 0, f2 = 0, n;
	int vsp;
	//_crtBreakAlloc = 1356;
	do {
		printf("Use file?\n1. Yes\n2. No\n");
		Get_int(&n);
		if (n > 2) { printf("%s\n", "Error, try again "); }
		if (n == 1) {
			printf("\nEnter File name-->\n");
			while (getchar() != '\n');
			name = Get_str();
			if (name == NULL) { break; }
			a = load(tree, name);
			if (a == -1) {
				No_File();
			}
			else {
				free(name);
				break;
			}
			free(name);
		}
		if (n == 2) { break; }
		if (n == -1) { break; }
	} while (1 == 1);
	do {
		Item* start = tree;
		Item* help;
		a = dialog(&key, &inf, &release);
		if (a == 1) {
			help1=AddItem(&tree, inf, key);
			if (help1->inf != NULL) {
				show_inf(help1);
				free_info(help1);
			}
			free(help1->inf);
			free(help1);
		}
		if (a == 2) {
		   n = Delete(key, tree, &tree);
		   if (n == -1) { No_Elements(); }
			Balance(tree,&tree,key);
		}
		if (a == 3) {
			help = find(key,tree);
			if (help == NULL) { No_Key(); }
			else { show_inf(help); }
		}
		if (a == 4) {
			find_dif(key, tree);
		}
		if (a == 5) {
			D_Timing();
		}
		if (a == 6) {
			show_tree(tree);
			print_tree(start, 0);
		}
		if (a == 8) {
			//fname = Get_str();
			f = fopen("output.txt", "w+b");
			fprintf(f,"digraph G{\n");
			dop_1(tree, f);
			fprintf(f, "\n}\n");
			fclose(f);
			//free(fname);
		}
		if (a == 9) {
			dop_2();
		}
	} while (a != 7);
	while (getchar() != '\n');
	/*fname = Get_str();
	f=fopen(fname,"w+b");
	dop_1(tree,f);
	fclose(f);
	free(fname);*/
	free_tree(tree);
	free(inf);
	_CrtDumpMemoryLeaks();
	return 0;
}