// Strother Woog
// 1618221
// CMPS 101
// 4/22/19
// Runs InsertSort on a List of indicies based on a String Array
// Lex.c


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 256

int main(int argc, char* argv[]){
   
	int n, count = 0;
	FILE *in, *in2, *out;
	char line[MAX_LEN];
	char *token;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	in2 = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	
	// check if files are available
	if(in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	// grab number of lines from input file
	while( fgets(line, MAX_LEN, in2) != NULL) {
		count++;
	}
	
	// initialize array of strings for the lines from input file
	char tokenlist[count][MAX_LEN];
	
	// store each line from input file in array
	while( fgets(line, MAX_LEN, in) != NULL) {
		token = strtok(line, "\n");
		while(token != NULL) {
			strcpy(tokenlist[n], line);
			token = strtok(NULL, "\n");
			n++;
		}
	}
	
	// insert sort algorithm
	List L = newList();
	prepend(L, 0);
	moveFront(L);
	for(int j = 1; j < count; j++) {
		strcpy(line, tokenlist[j]);
		moveFront(L);
		while(index(L) < j - 1){
			moveNext(L);
		}
		while(strcmp(tokenlist[get(L)], line) > 0) {
			if(index(L) != 0)
				movePrev(L);
			else if(index(L) == 0)
				break;
		}
		if(strcmp(tokenlist[get(L)], line) < 0 ) {
			insertAfter(L, j);
		}
		else if(strcmp(tokenlist[get(L)], line) > 0 ) {
			insertBefore(L, j);
		}
		else {
			insertAfter(L, j);
		}
		moveBack(L);
	}
	
	// print list to output file
	moveFront(L);
	for(int i = 0; i < count; i++){
		fprintf(out, "%s\n", tokenlist[get(L)]);
		if(i != count - 1)
			moveNext(L);
	}
	
	// free heap memory
	freeList(&L);
	
	// close all input and output files
	fclose(in);
	fclose(in2);
	fclose(out);
   
	return(0);
}
