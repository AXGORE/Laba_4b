#ifndef ITEM_H
#define ITEM_H

typedef struct Info Info;
typedef struct Info {
	char* inf1;
	char* inf2;
	int help;
}Info;
void getinf(Info* from, Info* here);
void to_int(char* str, int* re);








#endif // !1
