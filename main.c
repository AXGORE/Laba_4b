#include "Item.h"
#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include "dialog.h"
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

int main() {
	Info* inf = (Info*)calloc(1, sizeof(Info));
	Item* tree = (Item*)calloc(1, sizeof(Item));
	int release, key;
	char* name;
	int a, f1 = 0, f2 = 0, n;
	int vsp;
	//_crtBreakAlloc = 100;
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
			n=AddItem(&tree, inf, key);
		}
		if (a == 2) {
		    Delete(key, tree, &tree);
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
	} while (a != 7);
	free_tree(tree);
	free(inf);
	_CrtDumpMemoryLeaks();
	return 0;
}