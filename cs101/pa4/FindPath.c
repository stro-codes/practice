// Strother Woog
// 1618221
// CMPS 101
// 5/28/19
// Header file for Graph ADT
// FindPath.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
   
	FILE *in, *out;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	Graph G;
	int xero = 0;
	int x, y;

	// loop through input file
	while(fscanf(in, "%d", &x) != EOF) {
		if(xero == 0) { // initialize graph
			xero++;
			G = newGraph(x);
		}
		else if(xero == 1) { // add adjacent vertex to graph
			fscanf(in, "%d", &y);
			if(x == 0 && y == 0) { // skip to next function
				xero++;
				printGraph(out, G);
				fprintf(out, "\n");
			}
			else {
				addEdge(G, x, y);
			}
		}
		else if(xero == 2) { // find path and distance
			fscanf(in, "%d", &y);
			if(x == 0 && y == 0) { // end function
				xero++;
			}
			else {
				BFS(G, x);
				List L = newList();
				getPath(L, G, y);
				if(x == y) {
					fprintf(out, "The distance from %d to %d is %d\n", x, y, 0);
					fprintf(out, "A shortest %d-%d path is: ", x, y);
					printList(out, L);
				}
				else if(front(L) == NIL) {
					fprintf(out, "The distance from %d to %d is infinity\n", x, y);
					fprintf(out, "No %d-%d path exists", x, y);
				}
				else {
					fprintf(out, "The distance from %d to %d is %d\n", x, y, getDist(G, y));
					fprintf(out, "A shortest %d-%d path is: ", x, y);
					printList(out, L);
				}
				fprintf(out, "\n");
			}
		}
		else { // end loop
			break;
		}	
	}

	// close all input and output files
	fclose(in);
	fclose(out);
   
	return(0);
}