#include "Child_Node.h"
#include <iostream>
#include <cstring>


Child_Node::Child_Node(void)
{
	childNode = NULL; //initialize to NULL.
	rightchild = NULL;
}


Child_Node::~Child_Node(void)
{
	delete rightchild; //when program ends, delete rightchild
}

void Child_Node::setChild(BST_Node *pNode)
{
	childNode = pNode; //set the pNode to childNode
}

void Child_Node::setRightNode()
{
	rightchild = new Child_Node; //make a new Child_node
}

Child_Node *Child_Node::getRightNode()
{
	return rightchild; //return right's address
}

BST_Node *Child_Node::getChild()
{
	return childNode; //return child node's address
}
