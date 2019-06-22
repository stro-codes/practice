Strother Woog
1618221
CMPS 101
6/2/19
Table of contents for the program and its files.
README

FILES:

List.c
	- List ADT in C
	
List.h
	- Header/Interface for the List ADT

Graph.c
	- Graph ADT in C
	
Graph.h
	- Header/Interface for the Graph ADT
	
GraphTest.c
	- Does some basic tests of the Graph ADT
	
FindComponents.c
	- Runs the Depth-First Search Algorithim on a Graph
	
Makefile
	- Utility to compile and run FindPath, as well as debug and clean up the mess
	
README
	- Bibilical texts related to this very project
	
Notes:

	- The List ADT and Header/Interface files were reused from previous programming assignments(pa2, pa4) of 
	mine. I modified them while working on pa4 to succesfully pass the List test script on github. Otherwise 
	the code remains mostly unchanged. The error fixed was an issue with the index() access function, an upper 
	bound for the range of what the List index could be was not correctly set.
	
	-  The Graph ADT and Header/Interface file were taken from my pa4 and repurposed for the Depth-First Search
	Algorithim. Made slight modifications to the access functions that were relatively similar, and major 
	overhaul to the manipulation functions as well helper functions to match the algorithm. 
	
	- FindComponents is very similar to FindPath in pa4 with a few changes to how it builds the Graph. Rather than
	building an Undirected Graph for BFS, it builds a Directed Graph for DFS from the input files. Then, it uses DFS
	to find the Strongly Connected Components of the Graph.
	
	- GraphTest does some basic test cases to make sure the Graph can be built and maipulated properly, and be used
	to check whether whatever values you plug into it are gone over by the algorithm by using the access functions.
	