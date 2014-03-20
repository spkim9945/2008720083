Project:BST.o BST_Node.o Child_Node.o FILE_IO.o main.o
	g++ -o Project BST.o BST_Node.o Child_Node.o FILE_IO.o main.o

BST.o : BST.cpp BST.h
	g++ -c BST.cpp

BST_Node.o : BST_Node.cpp BST_Node.h
	g++ -c BST_Node.cpp

Child_Node.o : Child_Node.cpp Child_Node.h
	g++ -c Child_Node.cpp

FILE_IO.o : FILE_IO.cpp FILE_IO.h
	g++ -c FILE_IO.cpp

main.o : main.cpp
	g++ -pg -c main.cpp
clean:
	rm BST_Node.o BST.o Child_Node.o FILE_IO.o main.o Project
