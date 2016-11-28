#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"

void initArray(Array *a, size_t initialSize){
	a->array = (int *)malloc(initialSize * sizeof(int));
	a->used = 0;
	a->size = initialSize;
}

void insertArray(Array *a, int element){
	if (a->used == a->size){
		a->size *= 2;
		a->array = (int *)realloc(a->array, a->size * sizeof(int));
	}
	a->array[a->used++] = element;
}

void freeArray(Array *a){
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

char **split(char *phrase, const size_t length, const char delimiter, size_t *n_tokens){
    int words = 1;

    size_t n;
    for (n = 0; n < length; n++)
        words += phrase[n] == delimiter;

    char **input = malloc(sizeof(char*) * words);

    int j = 0;
    char *token = strtok(phrase, &delimiter);
    while (token != NULL) {
        input[j] = malloc(sizeof(char) * strlen(token) + sizeof(char));
        strcpy(input[j++], token);
        token = strtok(NULL, &delimiter);
    }

    *n_tokens = words;
    return input;
}

char **split_line(char *phrase, size_t *n_tokens){
    const size_t length = sizeof(phrase);
    const char delimiter = ' ';

    return split(phrase, length, delimiter, n_tokens);
}

char *read_line() {
    size_t bufsize = 1024;
    int position = 0;
    char c,*buffer = malloc(sizeof(char) * bufsize);

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += 1024;
            buffer = realloc(buffer, bufsize);
        }
    }
}

void assignMemory(char *name, int size, Memory *mem){

	Program *prog;
	int pagesToAssign = 4 + size/128;

	if (size % 128 != 0){
		pagesToAssign += 1;
	}

	for (int i=0; i<127;i++){
		if (!strcmp(mem->programs[i].name, name)){
			prog = &mem->programs[i];
		}
	}
	
	while(pagesToAssign > 0){
		for (int i=0; i<511; i++){
			if (mem->usedPages[i] == 0){
				prog->pageCount += 1;
				insertArray(&prog->pages, i);
				mem->usedPages[i] = 1;
				pagesToAssign -= 1;
				break;
			}
		}
	}
}

void reassignMemory(char *name, int size, Memory *mem){

	Program *prog;
	int pagesToAssign = size/128;

	if (size % 128 != 0){
		pagesToAssign += 1;
	}

	for (int i=0; i<127;i++){
		if (!strcmp(mem->programs[i].name, name)){
			prog = &mem->programs[i];
		}
	}
	
	while(pagesToAssign > 0){
		for (int i=0; i<511; i++){
			if (mem->usedPages[i] == 0){
				prog->pageCount += 1;
				insertArray(&prog->pages, i);
				mem->usedPages[i] = 1;
				pagesToAssign -= 1;
				break;
			}
		}
	}
}

Program *initializeProgram(char *name, int size){

	Program *prog = malloc(sizeof(Program));
	Array pages;

	strcpy(prog->name, name);
	prog->code = size;
	prog->data = 256;
	prog->heap = 0;
	prog->stack = 256;
	initArray(&prog->pages, 5);

	return prog;
}

int programCmp(Program p1, Program p2){
	int sameProgram = 1;
	if (strcmp(p1.name,p2.name)){
		sameProgram = 0;
	}
	else if (p1.code != p2.code){
		sameProgram = 0;
	}
	else if (p1.data != p2.data){
		sameProgram = 0;
	}
	else if (p1.heap != p2.heap){
		sameProgram = 0;
	}
	else if (p1.stack != p2.stack){
		sameProgram = 0;
	}
	return sameProgram;
}

int execProgram(char* name, int size, Memory *mem, Program *null){

	for (int i=0; i<127; i++){
		if (!strcmp(name, mem->programs[i].name)){
			return 0;
		}
	}

	for (int i=0; i<127; i++){
		if (programCmp(mem->programs[i], *null)){
			mem->programs[i] = *initializeProgram(name, size);
			assignMemory(name, 128*4 + size, mem);
			return 1;
		}
	}
	return 0;
}

int freeProgram(char* name, Memory *mem, Program *null){
	for (int i=0; i<127; i++){
		if (!strcmp(name, mem->programs[i].name)){
			for (int j = 0; j < mem->programs[i].pageCount; j++){
				int pageIndex = mem->programs[i].pages.array[j];
				mem->usedPages[pageIndex] = 0; 
			}
			mem->programs[i] = *null;
			return 1;
		}
	}
	return 0;
}

int assignHeap(char* name, int size, Memory *mem){
	if (size > 256){
		printf("El tamaño maximo del heap es 256\n");
		return 0;
	}
	for (int i=0; i<127; i++){
		if (!strcmp(name, mem->programs[i].name)){
			reassignMemory(name, size, mem);
			mem->programs[i].heap = size;
			return 1;
		}
	}
	return 0;
}

int checkMem(char* name, Memory *mem){
	Program prog;
	for (int i=0; i<127; i++){
		if (!strcmp(mem->programs[i].name, name)){
			prog = mem->programs[i];
			break;
		}
		else{
			return 0;
		}
	}

	int total = prog.code + prog.data + prog.stack + prog.heap;
	printf("El total de memoria utilizada por el programa es %d\n", total);
	printf("Las direcciones utilizadas son:\n");

	for (int i=0; i<prog.pageCount; i++){
		int pageIndex = prog.pages.array[i];
		int segmento = mem->memArray[pageIndex]/4096;
		printf("%d: %d, del segmento %d\n", i+1, mem->memArray[pageIndex], segmento);
	}
	return 1;
}

int readData(char *name, int address, Memory *mem){
	Program prog;
	int addressCheck = 0;

	for (int i=0; i<127;i++){
		if (!strcmp(mem->programs[i].name, name)){
			prog = mem->programs[i];
			break;
		}
		else{
			return 0;
		}
	}

	for (int i=0; i<prog.pageCount; i++){
		int pageIndex = prog.pages.array[i];
		if (mem->memArray[pageIndex] == address){
			addressCheck = 1;
		}
	}

	if (addressCheck){
		printf("Se ha leido con exito\n");
		return 1;
		/*if (permissions are ok){
			printf("Se ha leido con exito\n");
			return 1;
		}
		printf("No tiene los permisos para realizar esa accion\n");
		return 0;*/
	}
	else{
		printf("No tiene los permisos para realizar esa accion\n");
		return 0;
	}
	
	return 0;
}

int writeData(char *name, int address, Memory *mem){
	Program prog;
	int addressCheck = 0;

	for (int i=0; i<127;i++){
		if (!strcmp(mem->programs[i].name, name)){
			prog = mem->programs[i];
			break;
		}
		else{
			return 0;
		}
	}
	
	for (int i=0; i<prog.pageCount; i++){
		int pageIndex = prog.pages.array[i];
		if (mem->memArray[pageIndex] == address){
			addressCheck = 1;
		}
	}

	if (addressCheck){
		//if (permissions are ok){
			printf("Se ha escrito con exito\n");
			return 1;
		/*/}
		printf("No tiene los permisos para realizar esa accion\n");
		return 0;*/
	}
	else{
		printf("No tiene los permisos para realizar esa accion\n");
		return 0;
	}
	
	return 0;
}

int execute(char** args, Memory *mem, Program *null){
    int a;
    if (!strcmp(args[0],"exec")){
        a = execProgram(args[1],atoi(args[2]), mem, null);
        if (a){
        	printf("Programa ejecutado correctamente\n");
        }
        else{
        	printf("No se pudo ejecutar el programa\n");
        }
        return 1;
    }else if (!strcmp(args[0],"free")){
        a = freeProgram(args[1], mem, null);
        if (a){
        	printf("Programa eliminado de la memoria\n");
        }
        else{
        	printf("No se pudo eliminar el programa de la memoria\n");
        }
        return 1;
    }else if (!strcmp(args[0],"heap")){
        a = assignHeap(args[1],atoi(args[2]), mem);
        if (a){
        	printf("Heap asignado correctamente\n");
        }
        else{
        	printf("No se pudo asignar el heap\n");
        }
        return 1;
    }else if (!strcmp(args[0],"mem")){
        a = checkMem(args[1], mem);
        if (a == 0){
        	printf("No se pudo checkear la memoria\n");
        }
        return 1;
    }else if (!strcmp(args[0],"read")){
    	readData(args[1], atoi(args[2]), mem);//convertir de binaro a dec?
        return 1;
    }else if (!strcmp(args[0],"write")){
    	writeData(args[1], atoi(args[2]), mem);//convertir de binario a dec?
        return 1;
    }
    else if (!strcmp(args[0], "exit")){
    	return 0;
    }
    else{
    	printf("Comando no existente\n");
    	return 1;
    }
}

int main(){

	Program nullProgram, *null;
	Memory memoria, *mem;
	Array Null;

	null = &nullProgram;
	mem = &memoria;

	Null.array = NULL;
	Null.size = 0;
	Null.used = 0;

	strcpy(nullProgram.name, "NULLNAME");
	nullProgram.code = 0;
	nullProgram.data = 0;
	nullProgram.heap = 0;
	nullProgram.stack = 0;
	nullProgram.pageCount = 0;
	nullProgram.pages = Null;

	for (int i=0; i<127; i++){
		mem->programs[i] = nullProgram;
	}

	for (int i=0; i<511; i++){
		mem->memArray[i] = 128*i;
	}

    char *line;
    char **args;

    size_t line_size,valor = 0;
    size_t *n_args = &valor;

    while(1) {
        line = read_line();
        line_size = strlen(line);
        args = split_line(line, n_args);
        int a = execute(args, mem, null);
        free(line);
        if (a == 0) break;
    }

    return 0;
}
