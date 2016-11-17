#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

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

int main(){
	int memArray[32];
}
