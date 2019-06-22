// Strother Woog
// 1618221
// CMPS 101
// 5/28/19
// Graph ADT for Breadth-First Search on Adjacent Vertices
// Graph.c

#include<stdio.h>
#include<stdlib.h>

#include "Graph.h"
#include "List.h"

#define INF 1
#define NIL -1

#define white 1
#define gray 2
#define black 3

// structs

typedef struct GraphObj {
	int order;
	int size;
	int source;
	List* vertex;
	int* color;
	int* parent;
	int* distance;
	
} GraphObj;

typedef GraphObj* Graph;

// constructor-destructor

Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	G->vertex = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->parent = calloc(n + 1, sizeof(int));
	G->distance = calloc(n + 1, sizeof(int));
	for(int x = 0; x < n + 1; x++) {
		List L = newList();
		G->vertex[x] = L;
		G->color[x] = white;
		G->parent[x] = NIL;
		G->distance[x] = INF;
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

int getSource(Graph G) {
	if(G == NULL) {
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
		exit(1);
	}
	
	return G->source;
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
int getDist(Graph G, int u) {
	if(G == NULL) {
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(1);
	}
	if(!(u <= getOrder(G) && 1 <= u)) {
		printf("Graph Error: calling getDist() on invalid vertex\n");
		exit(1);
	}
	
	return G->distance[u];
}

void getPath(List L, Graph G, int u) {
	if(G == NULL) {
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(1);
	}
	if(!( (u <= getOrder(G) && 1 <= u) || u == NIL )) {
		printf("Graph Error: calling getPath() on invalid vertex\n");
		exit(1);
	}
	if(getSource(G) == NIL) {
		printf("Graph Error: calling getPath() without a source vertex \n");
		exit(1);
	}
	
	if(u == getSource(G)) {
		append(L, u);
	}
	else if(u == NIL) {
		append(L, NIL);
	}
	else if(G->color[u] == white) {
		append(L, NIL);
	}
	else {
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
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
	free(G->distance);
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

void BFS(Graph G, int s) {
	G->source = s;
	for(int x = 0; x <= getOrder(G); x++) {
		G->color[x] = white;
		G->distance[x] = INF;
		G->parent[x] = NIL;
	}
	G->color[s] = gray; // discover the source s
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List queue = newList(); // construct a new queue
	prepend(queue, s);
	while(!isEmpty(queue)) {
		int x = front(queue);
		deleteFront(queue);
		if(!isEmpty(G->vertex[x])) {
			moveFront(G->vertex[x]);
		}
		for(int z = 0; z < length(G->vertex[x]); z++) {
			int y = get(G->vertex[x]);
			if(G->color[y] == white) { // y is undiscovered
				G->color[y] = gray; // discover y
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(queue, y);
			}
			if(index(G->vertex[x]) != length(G->vertex[x])) {
				moveNext(G->vertex[x]);
			}
		}
		G->color[x] = black; // finish x
	}
	freeList(&queue);
}


// Other operations 

void printGraph(FILE* out, Graph G) {
	if(G == NULL) {
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
		exit(1);
	}
	
	for(int x = 1; x <= getOrder(G); x++) {
		fprintf(out, "%d: ", x);
		printList(out, G->vertex[x]);
	}
}