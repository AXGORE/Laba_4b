#ifndef DIALOG_H
#define DIALOG_H
typedef struct Info Info;
typedef struct Item Item;
int Get_double(double* a);
void Get_int(int* a);
char* Get_str();
int dialog(int* key, Info** info, int* num);
void show_tree(Item* tree);
void show_inf(Item* tree);
void No_Elements();
void No_Key();
void Empty();
int Get_key(int* a);
void No_File();
int D_Timing();


#endif // !DIALOG_H
