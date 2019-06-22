# Strother Woog
# 1618221
# CMPS 101
# 5/28/19
# Makefile for CMPS 101 Programming Assignment 4
# Makefile

# FindPath
FindPath : FindPath.o List.o Graph.o
	gcc -o FindPath FindPath.o List.o Graph.o
	
FindPath.o : FindPath.c List.h Graph.h
	gcc -c -std=c99 -Wall FindPath.c

# ListClient
ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

# GraphClient
GraphClient: GraphClient.o List.o Graph.o
	gcc -o GraphClient GraphClient.o List.o Graph.o

GraphClient.o : GraphClient.c List.h Graph.h
	gcc -c -std=c99 -Wall GraphClient.c

# GraphTest
GraphTest: GraphTest.o List.o Graph.o
	gcc -o GraphTest GraphTest.o List.o Graph.o

GraphTest.o : GraphTest.c List.h Graph.h
	gcc -c -std=c99 -Wall GraphTest.c

# List
List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c
	
# Graph
Graph.o : Graph.c Graph.h 
	gcc -c -std=c99 -Wall Graph.c

# Clean
clean :
	rm -f FindPath ListClient GraphClient FindPath.o ListClient.o GraphClient.o List.o Graph.o
 