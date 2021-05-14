#include "Item.h"
#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include "dialog.h"
#include <stdio.h>

int AddItem(Item** tree, Info* inf, int key) {
	Item* start = *tree;
	Item* p = NULL;
	Item* par;
	while (start->inf != NULL) {
		if (key > start->key) {
			if (start->right == NULL) {
				start->right = (Item*)calloc(1, sizeof(Item));
			}
			p = start;
			start = start->right;
		}
		if (key < start->key) {
			if (start->left == NULL) {
				start->left = (Item*)calloc(1, sizeof(Item));
			}
			p = start;
			start = start->left;
			//AddItem(start, inf, key, next);
			//start = tree;
		}
		if (start->inf == NULL) { break; }
		if (key == start->key) {
			if (start->inf->inf1 != NULL) {
				show_inf(start);
			}
			if (start->inf->inf1 != NULL && start->inf->inf2 != NULL) {
				free(start->inf->inf1);
				free(start->inf->inf2);
			}
			free(start->inf);
			start->inf = (Info*)calloc(1, sizeof(Info));
			getinf(inf,start->inf);
			break;
		}
	}
	if (start->inf == NULL) {
		start->balance = 0;
		start->inf = (Info*)calloc(1, sizeof(Info));
		getinf(inf, start->inf);
		start->key = key;
	}
	Balance(*tree, tree,key);
}
void print_tree(Item* tree, int i) {
	if (tree == NULL) { return; }
	print_tree(tree->right, i + 1);
	for (int j = 0; j < i; j++) {
		printf("\t");
	}
	printf("%d\n", tree->key);
	print_tree(tree->left, i + 1);
}
void free_tree(Item* tree) {
	if (tree == NULL) { return; }
	free_tree(tree->right);
	if (tree->inf != NULL) {
		if (tree->inf->inf1 != NULL) {
			free(tree->inf->inf1);
		}
		if (tree->inf->inf2 != NULL) {
			free(tree->inf->inf2);
		}
		free(tree->inf);
	}
	free_tree(tree->left);
	free(tree);
}
int tree_h(Item* tree) {
	int a, b,h;
	if (tree == NULL) { return 0; }
	if (tree->inf == NULL) {
		return 0;
	}
	h = 1;
	a = 0;
	b = 0;
	Item* start = tree;
	if (start->right != NULL) {
		a = tree_h(start->right);
	}
	if (start->left != NULL) {
		b = tree_h(start->left);
	}
	if (a > b) {
		h  += a; 
	}
	else {
		h += b;
	}
	return h;
}

int Balance(Item* tree, Item** root,int key) {
	int a=1;
	int b = tree->balance;
	Item* par;
	Item* help = *root;
	if (tree == NULL) { return 1; }
	if (tree->right != NULL && key>tree->key) {
		a=Balance(tree->right, root,key);
	}
	if (tree->left != NULL && tree->key > key) {
		a=Balance(tree->left, root,key);
	}
	if (a == 0 && tree->balance !=2 && tree->balance != -2) { return 0; }
	tree->balance = (tree_h(tree->right) - tree_h(tree->left));
	if (tree->balance == b && (tree->left!=NULL || tree->right!=NULL)&& tree->balance !=2 && tree->balance !=-2 ) { return 0; }
	if (tree->balance == -2) { 
		par = find_par(tree,help);
		rotate_r(tree, par, root);
	}
	else if (tree->balance == 2) { 
		par = find_par(tree,help);
		rotate_l(tree, par, root);
	}
	else { return 1;}
}

void* find_par(Item* start,Item* tree) {
	Item* par = tree;
	if (start == tree) { return NULL; }
	while (1 == 1) {
		while (start->key > tree->key) {
			if (tree->right == start) {
				par = tree;
				return par;
			}
			tree = tree->right;
		}
		while (start->key < tree->key) {
			if (tree->left == start) {
				par = tree;
				return par;
			}
			tree = tree->left;
		}
	}
}
void rotate_l(Item* start,Item* par, Item** root) {
	if (start->right != NULL) {
		if (start->right->balance == -1) {
			rotate_r(start->right, start, root);
			return;
		}
	}
	if (par != NULL) {
		if (par->right == start) {
			par->right = start->right;
			start->right = start->right->left;
			par->right->left = start;
			Balance(par, root, par->right->left->key);
			return;
		}
		if (par->left == start) {
			par->left = start->right;
			start->right = start->right->left;
			par->left->left = start;
			Balance(par,root,par->left->left->key);
			return;
		}
	}
	else {
		*root = start->right;
		start->right = (*root)->left;
		(*root)->left = start;
		Balance(*root, root,(*root)->left->key);
		return;
	}
}

void rotate_r(Item* start, Item* par, Item** root) {
	if (start->left != NULL) {
		if (start->left->balance == 1) {
			rotate_l(start->left, start, root);
			return;
		}
	}
	if (par != NULL) {
		if (par->right == start) {
			par->right = start->left;
			start->left = start->left->right;
			par->right->right = start;
			Balance(par,root,par->right->right->key);
			return;
		}
		if (par->left == start) {
			par->left = start->left;
			start->left = start->left->right;
			par->left->right = start;
			Balance(par, root, par->left->right->key);
			return;
		}
	}
	else {
		*root = start->left;
		start->left = (*root)->right;
		(*root)->right = start;
		Balance(*root, root,(*root)->right->key);
		return;
	}
}

void* find(int key, Item* tree) {
	while (1 == 1) {
		if (key == tree->key) { return tree; }
		while (key > tree->key) {
			tree = tree->right;
			if (tree == NULL) { return tree; }
		}
		while (key < tree->key) {
			tree = tree->left;
			if (tree == NULL) { return tree; }
		}
	}
}

void find_dif(int key, Item* tree) {
	int a, b;
	Item* start = tree;
	while (tree->left!=NULL) {
		tree = tree->left;
	}
	a = abs(tree->key - key);
	while (start->right != NULL) {
		start = start->right;
	}
	b = abs(start->key-key);
	if (a > b) {
		show_inf(tree);
		return;
	}
	if (a < b) {
		show_inf(start);
		return;
	}
	if (a == b) {
		show_inf(tree);
		show_inf(start);
		return;
	}
}
void Delete(int key, Item* tree, Item** root) {
	Item* start = find(key,tree);
	Item* help;
	if (start == NULL) { 
		No_Elements();
		return;
	}
	Item* par = find_par(start,tree);
	if (start->left != NULL && start->right != NULL) {
		help = start->right;
		while (help->left != NULL) { help = help->left; }
		free(start->inf->inf1);
		free(start->inf->inf2);
		free(start->inf);
		par = find_par(help, tree);
		Cp_Item(help, start);
		Del(help,par,tree);
		return;
	}
	if (par == NULL) {
		if (start->left == NULL && start->right == NULL) {
			free_item(start);
			(*root) = (Item*)calloc(1, sizeof(Item));
			return;
		}
		if (start->left != NULL) {
			(*root) = start->left;
			free_item(start);
			return;
		}
		if (start->right != NULL) {
			(*root) = start->right;
			free_item(start);
			return;
		}
	}
	free_info(start);
	free(start->inf);
	Del(start, par, tree);
	return;
}
int Del(Item* start, Item* prev_h, Item* tree) {
	if (start->left == NULL && start->right == NULL) {
		if (prev_h->right == start) {
			prev_h->right = NULL;
			prev_h->balance--;
		}
		if (prev_h->left == start) {
			prev_h->balance++;
			prev_h->left = NULL;
		}
		free(start);
		return 0;
	}
	if (start->left == NULL) {
		if (prev_h->right == start) {
			prev_h->right = start->right;
			prev_h->balance--;
		}
		if (prev_h->left == start) {
			prev_h->balance++;
			prev_h->left = start->right;
			
		}
		free(start);
		return 0;
	}
	if (start->left != NULL) {
		if (prev_h->right == start) {
			prev_h->right = start->left;
			prev_h->balance--;
		}
		if (prev_h->left == start) {
			prev_h->left = start->left;
			prev_h->balance++;
		}
		free(start);
		return 0;
	}
}
void Cp_Item(Item* from, Item* here) {
	here->inf = from->inf;
	here->key = from->key;
}
void free_item(Item* start) {
	free(start->inf->inf1);
	free(start->inf->inf2);
	free(start->inf);
	free(start);
}
void free_info(Item* start) {
	free(start->inf->inf1);
	free(start->inf->inf2);
}

int load(Item* tree, char* name) {
	FILE* f = NULL;
	char** inf;
	char** inf_help;
	Item* next = NULL;
	char* prov;
	int key;
	int flag;
	double inf2;
	f = fopen(name, "r+b");
	if (f == NULL) {
		return -1;
	}
	Info* help = (Info*)calloc(1, sizeof(Info));
	inf = (char**)calloc(3, sizeof(char*));
	for (int i = 0; i < 3; i++) {
		inf[i] = (char*)calloc(255, sizeof(char));
	}
	flag = 1;
	inf_help = (char**)calloc(3, sizeof(char*));
	while (flag == 1) {
		for (int i = 0; i < 3; i++) {
			inf_help[i] = (char*)calloc(255, sizeof(char));
		}
		for (int i = 0; i < 3; i++) {
			prov = fgets(inf[i], 255, f);
			if (prov == NULL) {
				flag = 0;
				break;
			}
			strncpy(inf_help[i], inf[i], strlen(inf[i]) - 2);

		}
		if (flag == 0) {
			for (int i = 0; i < 3; i++) {
				free(inf_help[i]);
			}
			break;
		}
		to_int(inf_help[0], &key);
		help->inf1 = inf_help[1];
		help->inf2 = inf_help[2];
		AddItem(&tree, help, key);
			free(inf_help[0]);
	}
	for (int i = 0; i < 3; i++) {
		free(inf[i]);
	}
	free(inf);
	free(inf_help);
	free(help);
	fclose(f);
	return 0;
}