#include "BST_Node.h"
#include <iostream>
#include <fstream>
#include <cstring>

BST_Node::BST_Node(void)
{
	leftchild = new Child_Node; //allocate new Child_Node

	leftchild->setRightNode(); //link left and right as a linked list.
}


BST_Node::~BST_Node(void)
{
	delete leftchild; //when program ends, delete leftchild.
}

void BST_Node::setLeft(BST_Node *pNode)
{
	leftchild->setChild(pNode); //set pNode to left child.
}

void BST_Node::setRight(BST_Node *pNode)
{
	leftchild->getRightNode()->setChild(pNode); //set pNode to right child.
}

BST_Node *BST_Node::getLeft()
{
	return leftchild->getChild(); //return left child's address.
}

BST_Node *BST_Node::getRight()
{
	return leftchild->getRightNode()->getChild(); //return right child's address.
}

void BST_Node::setName(char *firstname, char *lastname)
{
	strcpy(BST_firstname, firstname); //set the current node's name data.
	strcpy(BST_lastname, lastname);
}

void BST_Node::setPhone(char *phone)
{
	strcpy(BST_phone, phone); //set the current node's phone.
}

void BST_Node::setAddress(char *address_num, char *address_str)
{
	strcpy(BST_address_num, address_num); //set the current node's address data.
	strcpy(BST_address_str, address_str);
}

char *BST_Node::getFirstname()
{
	return BST_firstname; //return firstname
}

char *BST_Node::getLastName()
{
	return BST_lastname; //return lastname
}

char *BST_Node::getPhone()
{
	return BST_phone; //return phone
}

char *BST_Node::getAddress_num()
{
	return BST_address_num; //return address_num
}

char *BST_Node::getAddress_str()
{
	return BST_address_str; //return address_str
}
