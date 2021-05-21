#ifndef TREE_H
#define TREE_H
#include <stdio.h>
typedef struct Info Info;
typedef struct Item Item;
typedef struct Item {
	int key;
	int balance;
	Info* inf;
	Item* right;
	Item* left;
}Item;
void* AddItem(Item**tree, Info* inf, int key);
void print_tree(Item* tree, int i);
void free_tree(Item* tree);
void* find(int key, Item* tree);
void find_dif(int key, Item* tree);
int tree_h(Item* tree);
int Balance(Item* tree, Item** root, int key);
void free_info(Item* start);
void* find_par(Item* start, Item* tree);
void rotate_l(Item* start, Item* par, Item** root);
void rotate_r(Item* start, Item* par, Item** root);
void Cp_Item(Item* from, Item* here);
int Delete(int key, Item* tree, Item** root);
int Del(Item* start, Item* prev_h, Item* tree);
void free_item(Item* start);
int dop_1(Item* tree, FILE* output);
void dop_2();
#endif // !TREE_H#pragma once
