#pragma once
#include "Child_Node.h"
class Child_Node;
class BST_Node
{
private:
	Child_Node *leftchild;
public:
	BST_Node(void);
	~BST_Node(void);
	char BST_firstname[20]; //node's data.
	char BST_lastname[20];
	char BST_phone[20];
	char BST_address_str[30];
	char BST_address_num[10];
	void setLeft(BST_Node *pNode); //set the left child.
	void setRight(BST_Node *pNode); //set the right child.
	BST_Node *getLeft(); //return the left child's address.
	BST_Node *getRight(); //return the right child's address.
	void setName(char *firstname, char *lastname); //set the name
	void setPhone(char *phone); //set the phone
	void setAddress(char *address_num, char *address_str); //set the address
	char *getFirstname(); //get the node's firstname
	char *getLastName(); //get the node's lastname
	char *getPhone(); //get the node's phone
	char *getAddress_num(); //get the node's address_num
	char *getAddress_str(); //get the node's address_str
};

