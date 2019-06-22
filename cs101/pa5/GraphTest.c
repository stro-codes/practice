// Strother Woog
// 1618221
// CMPS 101
// 6/4/19
// Test file for Graph ADT
// GraphTest.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
   
	FILE *in;

	// check command line for correct number of arguments
	if( argc != 2 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	if(in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
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
				//printGraph(stdout, G);
				//fprintf(out, "\n");
			}
			else {
				addEdge(G, x, y);
			}
		}
		else { // end loop
			break;
		}	
	}

	// close all input and output files
	fclose(in);
   
	// testing the graph	// Test Cases:
	printGraph(stdout , G); // 0
	printf("\n");

	
	printf("%d\n", getOrder(G));
	printf("%d\n", getSize(G));
	
	// begin tests
	
	addArc(G, 4, 6);
	addArc(G, 6, 4);
	addArc(G, 5, 7);
	
	printGraph(stdout , G); // 1
	printf("\n");

	
	
	printGraph(stdout , G); // 2
	printf("\n");
	
	List L = newList();
	for(int i = 1; i <= getOrder(G); i++) {
		append(L, i);
	}
	
	DFS(G, L);
	printList(stdout, L);
	
	Graph T = transpose(G);
	
	printGraph(stdout , T); // 3
	printf("\n");
	
	DFS(T, L);
	printList(stdout, L);
	
	printGraph(stdout , G); // 4
	printf("\n");

	makeNull(G);

	printGraph(stdout , G); // N
	printf("\n");

	
	// close test program
	return(0);
}