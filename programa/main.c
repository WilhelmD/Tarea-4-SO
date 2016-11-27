#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"

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
	//encontrar cantidad de pags a asignar
	//luego buscar pags desocupadas en la memoria y asignarlas
}

Program *initializeProgram(char *name, int size){

	Program *prog = malloc(sizeof(Program));

	strcpy(prog->name, name);
	prog->code = size;
	prog->data = 0;
	prog->heap = 0;
	prog->stack = 256; //falta address stuff

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

	for (int i=0; i<255; i++){
		if (!strcmp(name, mem->programs[i].name)){
			return 0;
		}
	}

	for (int i=0; i<255; i++){
		if (programCmp(mem->programs[i], *null)){
			mem->programs[i] = *initializeProgram(name, size);
			return 1;
		}
	}
	return 0;
}

int freeProgram(char* name, Memory *mem, Program *null){
	for (int i=0; i<255; i++){
		if (!strcmp(name, mem->programs[i].name)){
			//revisar la memoria que esta utilizando y liberarla, luego
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
	for (int i=0; i<255; i++){
		if (!strcmp(name, mem->programs[i].name)){
			mem->programs[i].heap = size;
			return 1;
		}
	}
	return 0;
}

int checkMem(char* name, Memory *mem){
	for (int i=0; i<255; i++){
		if (!strcmp(name, mem->programs[i].name)){
			//print total mem used by program + addresses.
			int total = mem->programs[i].code + mem->programs[i].data + mem->programs[i].stack + mem->programs[i].heap;
			printf("El total de memoria utilizada por el programa es %d.\n", total);
			return 1;
		}
	}
	return 0;
}

int readData(char *name, int address, Memory *mem){
	/*
	if (address belongs to program){
		if (permissions are ok){
			printf("Se ha leido con exito\n");
			return 1;
		}
		printf("No tiene los permisos para realizar esa accion\n");
		return 0;
	}
	else{
		printf("No tiene los permisos para realizar esa accion\n");
		return 0;
	}
	*/
	return 0;
}

int writeData(char *name, int address, Memory *mem){
	/*
	if (address belongs to program){
		if (permissions are ok){
			printf("Se ha escrito con exito\n");
			return 1;
		}
		printf("No tiene los permisos para realizar esa accion\n");
		return 0;
	}
	else{
		printf("No tiene los permisos para realizar esa accion\n");
		return 0;
	}
	*/
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
    	a = readData(args[1], atoi(args[2]), mem);//convertir de binaro a dec?
    	if (a == 0){
        	printf("No se pudo leer la memoria del programa\n");
        }
        return 1;
    }else if (!strcmp(args[0],"write")){
    	a = writeData(args[1], atoi(args[2]), mem);//convertir de binario a dec?
    	if (a){
        	printf("Escritura realizada con exito\n");
        }
        else{
        	printf("No se pudo escribir en la memoria del programa\n");
        }
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
	null = &nullProgram;
	mem = &memoria;

	
	strcpy(nullProgram.name, "NULLNAME");//definir "programa nulo". falta address stuff
	nullProgram.code = 0;
	nullProgram.data = 0;
	nullProgram.heap = 0;
	nullProgram.stack = 0;

	for (int i=0; i<255; i++){
		mem->programs[i] = nullProgram;
	}

	for (int i=0; i<511; i++){
		mem->memArray[i] = 128*i;
	}


	/*for (int i=0; i<15; i++){
		mem->segments[i].permission = 0;
		mem->segments[i].base = (512*i);
		for (int j=0; j<31; j++){
			mem->segments[i].pages[j] = 128*j;
		}
	}*/

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
