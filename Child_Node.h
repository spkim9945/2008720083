#pragma once
//#include "BST_Node.h"
class BST_Node;
class Child_Node
{
private:
	Child_Node *rightchild; //leftchild's right child.
	BST_Node *childNode; //child node.
public:
	Child_Node(void);
	~Child_Node(void);
	void setChild(BST_Node *pNode); //set left or right child.
	void setRightNode(); //set the right. 
	BST_Node *getChild(); //return left or right child
	Child_Node *getRightNode(); //return right address.
};

