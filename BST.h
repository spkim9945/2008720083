#pragma once
#include "BST_Node.h"
#include "Child_Node.h"
#include "FILE_IO.h"
class BST
{
private:
	BST_Node *root;
public:
	BST(void);
	~BST(void);
	bool Insert(FILE_IO &F, char *firstname, char *lastname, char *phone, char *address_num, char *address_str, char *keys); //command : insert
	void PrintAll(FILE_IO &F); //command : PRINTALL    
	void PrintLastName(FILE_IO &F, char *lastname, char *keys);  //command : PRINTNAME
	void Print(FILE_IO &F, char *firstname, char *lastname, char *phone); //command : PRINT
	void Push(BST_Node *Stack[], BST_Node *CurrentNode, int &n); //to make inorder using stack, use this function.
	BST_Node *Pop(BST_Node *Stack[], int &n); //to amake inorder using stack, use this function.
	int search(char *firstname, char *lastname, char *phone); //use it to check if duplicate records are exist or not
	bool Update(FILE_IO &F, char *firstname, char *lastname, char *phone, char *phone2, char *address_num, char *address_str); //command : update
	//void Delete(FILE_IO &F, char *firstname, char *lastname, char *phone, char *keys); //command : delete, call Delete function.
	bool Delete(FILE_IO &F, char *firstname, char *lastname, char *phone); //command : delete
	void Destructor(); //delete all nodes in BST when program ends.
	bool Parsing(FILE_IO &F, char *keys, char *cmd, char *firstname, char *lastname, char *phone, char *phone2, char *address_num, char *address_str); //parsing the file's one line.
	bool Chk_str(FILE_IO &F, char *keys, char *firstname, char *lastname, char *phone, char *phone2, char *address_num, char *address_str); //check whether words' forms are appropriate or not.
};

