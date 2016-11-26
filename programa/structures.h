#ifndef PROGRAMA_STRUCTURES_H
#define PROGRAMA_STRUCTURES_H

struct Program{
	char* name;
	int code; //Memoria para el codigo
	int data; //Datos
	int heap = 0;
	int stack = 256;
	//direcciones de memoria que esta utilizando?
};

struct Segment{
	int pages[32] = {0}; //32 pags de 128 bits
};

struct Memoria{
	Segment segments[16];
	Program programs[256];
};

#endif //PROGRAMA_STRUCTURES_H
