// Strother Woog
// 1618221
// CMPS 101
// 6/4/19
// Graph ADT for Breadth-First Search on Adjacent Vertices
// Graph.c

#include<stdio.h>
#include<stdlib.h>

#include "Graph.h"
#include "List.h"

#define UNDEF 1
#define NIL -1

#define white 1
#define gray 2
#define black 3

// structs

typedef struct GraphObj {
	int order;
	int size;
	List* vertex;
	int* color;
	int* discover;
	int* finish;
	int* parent;
} GraphObj;

typedef GraphObj* Graph;

// constructor-destructor

Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->vertex = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->discover = calloc(n + 1, sizeof(int));
	G->finish = calloc(n + 1, sizeof(int));
	G->parent = calloc(n + 1, sizeof(int));
	for(int x = 0; x < n + 1; x++) {
		List L = newList();
		G->vertex[x] = L;
		G->color[x] = white;
		G->discover[x] = UNDEF;
		G->finish[x] = UNDEF;
		G->parent[x] = NIL;
	}	
	return G;
}

void freeGraph(Graph* pG) {
	if(pG != NULL && *pG != NULL) { 
		makeNull(*pG);
		free(*pG);
		*pG = NULL;
	}
}

// Access functions 

int getOrder(Graph G) {
	if(G == NULL) {
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(1);
	}
	
	return G->order;
}

int getSize(Graph G) {
	if(G == NULL) {
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	
	return G->size;
}

int getParent(Graph G, int u) {
	if(G == NULL) {
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(1);
	}
	if(!(u <= getOrder(G) && 1 <= u)) {
		printf("Graph Error: calling getParent() on invalid vertex\n");
		exit(1);
	}
	
	return G->parent[u];
}

int getDiscover(Graph G, int u) {
	if(G == NULL) {
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(1);
	}
	if(!(u <= getOrder(G) && 1 <= u)) {
		printf("Graph Error: calling getDist() on invalid vertex\n");
		exit(1);
	}
	
	return G->discover[u];
}

int getFinish(Graph G, int u) {
	if(G == NULL) {
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(1);
	}
	if(!( (u <= getOrder(G) && 1 <= u) || u == NIL )) {
		printf("Graph Error: calling getPath() on invalid vertex\n");
		exit(1);
	}

	return G->finish[u];
}

// Manipulation procedures 

void makeNull(Graph G) {
	if(G == NULL) {
		printf("Graph Error: calling makeNull() on NULL Graph reference\n");
		exit(1);
	}
	
	for(int x = 0; x <= getOrder(G); x++) {
		freeList(&(G->vertex[x]));
	}
	free(G->vertex);
	free(G->color);
	free(G->discover);
	free(G->finish);
	free(G->parent);
}

void addEdge(Graph G, int u, int v) {
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

void addArc(Graph G, int u, int v) {
	if(G == NULL) {
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
		exit(1);
	}
	if(!(1 <= u && u <= getOrder(G))) {
		printf("Graph Error: calling addArc() on vertex out of bounds\n");
		exit(1);
	}

	List temp = G->vertex[u];
	if(isEmpty(temp)) {
		prepend(temp, v);
	}
	else if(!isEmpty(temp)) { 
		moveFront(temp);
		for(int x = 1; x <= length(temp); x++) {
			if(get(temp) < v) {
				moveNext(temp);
			}
			else if(get(temp) > v) {
				insertBefore(temp, v);
				break;
			}
		}
		//- iteration ends
		if(back(temp) < v) {
			append(temp, v);
		}
	}
	G->size++;
}

void visit(Graph G, List S, int x, int *time) { 
	(*time)++;
	G->discover[x] = *time;
	G->color[x] = gray;	
	
	if(!isEmpty(G->vertex[x]))
		moveFront(G->vertex[x]);	
	while(index(G->vertex[x]) != -1) {
		int y = get(G->vertex[x]);
		if(G->color[y] == white) {
			G->parent[y] = x;
			visit(G, S, y, time); // pointer to the address where time is stored
		}
		moveNext(G->vertex[x]);
	}
	
	G->color[x] = black;
	(*time)++;
	G->finish[x] = *time;
	prepend(S, x);
}

void DFS(Graph G, List S) {
	if(G == NULL) {
		printf("Graph Error: calling DFS() on NULL Graph reference\n");
		exit(1);
	}
	if(length(S) != getOrder(G)) {
		printf("Graph Error: calling DFS() on List without proper order\n");
		exit(1);
	}
	
	List iterate = copyList(S);
	clear(S);
	for(int x = 1; x <= getOrder(G); x++) {
		G->color[x] = white;
		G->parent[x] = NIL;
	}
	int time = 0;
	/*
	for(int i = 1; i <= length(iterate); i++) {
		int x = front(iterate);
		deleteFront(iterate);
		if(G->color[x] == white) {
			visit(G, S, x, time);
		}
	}
	*/
	if(!isEmpty(iterate))
		moveFront(iterate);	
	while(index(iterate) != -1) {
		int x = get(iterate);
		if(G->color[x] == white) {
			visit(G, S, x, &time); // address to where time is stored
		}
		moveNext(iterate);
	}
	freeList(&iterate);
}

// Other operations 

Graph transpose(Graph G) {
	Graph temp = newGraph(getOrder(G));
	for(int x = 1; x <= getOrder(G); x++) {
		if(!isEmpty(G->vertex[x]))
			moveFront(G->vertex[x]);
		
		while(index(G->vertex[x]) != -1) {
			addArc(temp, get(G->vertex[x]), x);
			moveNext(G->vertex[x]);
		}
	}
	return temp;
}

Graph copyGraph(Graph G) {
	Graph temp = newGraph(getOrder(G));
	for(int x = 1; x <= getOrder(G); x++) {
		if(!isEmpty(G->vertex[x]))
			moveFront(G->vertex[x]);
		
		while(index(G->vertex[x]) != -1) {
			addArc(temp, x, get(G->vertex[x]));
			moveNext(G->vertex[x]);
		}
	}
	return temp;
}

void printGraph(FILE* out, Graph G) {
	if(G == NULL) {
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
		exit(1);
	}
	
	for(int x = 1; x <= getOrder(G); x++) {
		fprintf(out, "%d: ", x);
		if(G->vertex[x] != NULL)
			printList(out, G->vertex[x]);
		else
			printf("\n");
	}	
}
