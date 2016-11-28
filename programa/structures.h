#ifndef PROGRAMA_STRUCTURES_H
#define PROGRAMA_STRUCTURES_H

#include <stdlib.h>

typedef struct{
	int *array;
	size_t used;
	size_t size;
} Array;

typedef struct{
	char name[20];
	int code;
	int data;
	int heap;
	int stack;
	int pageCount;
	Array pages;
} Program;

typedef struct{
	int memArray[512];
	int usedPages[512];
	Program programs[128];
} Memory;

#endif
