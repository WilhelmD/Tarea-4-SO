#ifndef PROGRAMA_STRUCTURES_H
#define PROGRAMA_STRUCTURES_H

typedef struct{
	char name[20];
	int code; //Memoria para el codigo
	int data;
	int heap;
	int stack;
	int *pages;
} Program;

typedef struct{
	int memArray[512];
	int usedPages[512];
	Program programs[256];
} Memory;

#endif
