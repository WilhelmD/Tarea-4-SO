#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include "input_handler.h"

int execProgram(char* name, int size){
	/*
	if (program name exists in memory array){
		return 0
	}
	else{
		array[unused slot] = open(filename, etc) //???
		return 1
	}
	*/
}

int freeProgram(char* name){
	/*
	if (program name exists in memory array){
		free(name) // ????
		return 1
	}
	else{
		return 0
	}
	*/
}

int assignHeap(char* name, int memSize){
	/*
	if (program name exists in memory array){
		malloc() // ????
		return 1
	}
	else{
		return 0
	}
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
	int memArray[32];

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
