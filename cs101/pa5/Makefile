# Strother Woog
# 1618221
# CMPS 101
# 6/2/19
# Makefile for CMPS 101 Programming Assignment 4
# Makefile

# FindPath
FindComponents : FindComponents.o List.o Graph.o
	gcc -o FindComponents FindComponents.o List.o Graph.o
	
FindComponents.o : FindComponents.c List.h Graph.h
	gcc -c -std=c99 -Wall FindComponents.c

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
	rm -f FindComponents ListClient GraphClient FindComponents.o ListClient.o GraphClient.o List.o Graph.o
 