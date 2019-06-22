// Strother Woog
// 1618221
// CMPS 101
// 6/2/19
// Header file for Graph ADT
// FindComponents.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
   
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
		else if(xero == 1) { // add directed vertex to graph
			fscanf(in, "%d", &y);
			if(x == 0 && y == 0) { // skip to next function
				xero++;
				fprintf(out, "Adjacency list representation of G: \n");
				printGraph(out, G);
				fprintf(out, "\n");
			}
			else {
				addArc(G, x, y);
			}
		}
	}
	
	// build List of size getOrder(G) to be modified by DFS
	List L = newList();
	for(int i = 1; i <= getOrder(G); i++) {
		append(L, i);
	}
	
	// run DFS on Graph G, then on its Transpose
	Graph trans = transpose(G);
	DFS(G, L);
	DFS(trans, L);
	printf("List:\n");
	printList(stdout, L);
	
	// determine strongly connected components
	int scc = 0;
	
	// find the # of SCC
	if(!isEmpty(L))
		moveFront(L);
	while(index(L) != -1) {
		if(getParent(trans, get(L)) == NIL)
			scc++;
		moveNext(L);
	}
	
	// initialize List for each SCC
	List *componenets = calloc(scc + 1, sizeof(List));
	for(int i = 1; i <= scc; i++) {
		componenets[i] = newList();
	}
	
	// counter for SCC
	int c = 1;
	
	// build List of each SCC
	if(!isEmpty(L))
		moveBack(L);
	while(index(L) != -1) {
		if(getParent(trans, get(L)) == NIL) {
			prepend(componenets[c], get(L));
			c++;
		}
		else
			prepend(componenets[c], get(L));
		movePrev(L);
	}
	
	// print strongly connected componenets to outfile
	fprintf(out, "G contains %d strongly connected components:\n", scc);
	for(int i = 1; i <= scc; i++) {
		fprintf(out, "Component %d: ", i);
		printList(out, componenets[i]);
	}

	// close all input and output files
	fclose(in);
	fclose(out);
   
	// close program
	return(0);
}