#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include "structures.h"
#include "input_handler.c"

Memoria mem;
Program nullProgram;//definir "programa nulo"

int execProgram(char* name, int size){
	/*
	if size blabla

	for (int i=0; i<256; i++){
		if (!strcmp(name, mem.programs[i].name)){
			return 0;
		}
	}
	Buscar lugar en la memoria donde poner la wea!
	for (int i=0; i<256; i++){
		if (mem.programs[i] == nullProgram){
			mem.programs[i] = initializeProgram(name, size);
			return 1;
		}
	}
	*/
}

int freeProgram(char* name){
	/*
	for (int i=0; i<256; i++){
		if (!strcmp(name, mem.programs[i].name)){
			revisar la memoria que esta utilizando y liberarla, luego
			mem.programs[i] = nullProgram;
			return 1;
		}
	}
	return 0;
	*/
}

int assignHeap(char* name, int memSize){
	/*
	if (memSize > 256){
		printf("Max heap size is 256");
		return 0;
	}
	for (int i=0; i<256; i++){
		if (!strcmp(name, mem.programs[i].name)){
			malloc(name) ??
			return 1;
		}
	}
	return 0;
	*/
}

int checkMem(char* name){
	/*
	if (program name exists in memory array){
		print memSize // ????
		return 1
	}
	else{
		return 0
	}
	*/
}

void execute(char** args){
    //ejecutar funciones
    if (!strcmp(args[0],"exec")){
        execProgram(args[1],(int)args[2]-48);
    }else if (!strcmp(args[0],"free")){
        freeProgram(args[1]);
    }else if (!strcmp(args[0],"heap")){
        assignHeap(args[1],(int)args[2]-48);
    }else if (!strcmp(args[0],"mem")){
        checkMem(args[1]);
    }else if (!strcmp(args[0],"read")){
        //
    }else if (!strcmp(args[0],"write")){
        //
    }
}

int main(){
	int memoria;

    char *line;
    char **args;

    size_t line_size,valor = 0;
    size_t *n_args = &valor;

    while(1) {
        //printf("Ingrese funcion: "); //doesn't work
        line = read_line();
        line_size = strlen(line);
        args = split_line(line, n_args);
        execute(args);
        free(line);
        break; //sacar despues
    }

    return 0;
}
