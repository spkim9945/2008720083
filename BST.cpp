#include "BST.h"
#include <iostream>
#include <cstring>
using namespace std;
int n = 0;
int chk_dup = 0;

BST::BST(void)
{
	root = NULL;
}


BST::~BST(void)
{
	cout<<"Test git diff\n";
	Destructor();
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool BST::Insert(FILE_IO &F, char *firstname, char *lastname, char *phone, char *address_num, char *address_str, char *keys) //insert function
{
	BST_Node *p = root; //p pointed root.
	BST_Node *q;

	//Insert Node in BST
	while(p) //loop until p moves end leaf
	{
		q = p; //q pointed p.
		if(strcmp(p->getLastName(), lastname) == 0)  //if p->lastname and lastname are same,
		{
			if(strcmp(p->getFirstname(), firstname) == 0) //if p->firstname and firstname are same,
			{
				if(strcmp(p->getPhone(), phone) == 0) //if p->phone and phone are same,
				{
					F.Write("INSERT Error - Duplicate records"); //this data is duplicate data.
					F.Write("\n");
					F.Write(keys);
					F.Write("\n\n");
					return false;
				}
				else if(strcmp(p->getPhone(), phone) == -1) //if phone is bigger than p->phone,
				{
					p = p->getRight(); //p moves to right.
				}
				else //if phone is smaller than p->phone
				{
					p = p->getLeft(); //p moves to left.
				}
			}
			else if(strcmp(p->getFirstname(), firstname) == -1) //if p->firstname is smaller than firstname,
				p = p->getRight(); //p moves to right.
			else //if p->firstname is bigger than firstname,
				p = p->getLeft(); //p moves to left.
			
		}
		else if(strcmp(p->getLastName(), lastname)  == -1) //if p->lastname is smaller than lastname
			p = p->getRight(); //p moves to right
		else //if p->lastname is bigger than lastname,
			p = p->getLeft(); //p moves to left.
	}
	BST_Node *pNode = new BST_Node; //make a new node and allocate the memory.
	pNode->setName(firstname, lastname); //input datas in node.
	pNode->setPhone(phone);
	pNode->setAddress(address_num, address_str);
	if(!root) root = pNode; //if BST is empty, root is pNode.
	else if(strcmp(q->getLastName(), lastname) == 1) q->setLeft(pNode); //if q->lastname is bigger than lastname, pNode is q's left child.
	else if(strcmp(q->getLastName(), lastname) == 0) //if q->lastname and lastname are same,
	{
		if(strcmp(q->getFirstname(), firstname) == 0) // if q->firstname and firstname are same
		{
			if(strcmp(q->getPhone(), phone)  == 1) //if q->phone is bigger than phone,
				q->setLeft(pNode); //pNode is q's left child.
			else //if q->pNode is smaller than phone
				q->setRight(pNode); //pNode is q's right child.
		}
		else if(strcmp(q->getFirstname(), firstname)  == 1) //if q->firstname is bigger than firstname, 
			q->setLeft(pNode); //pNode is q's left child.
		else //if q->firstname is smaller than firstname,
			q->setRight(pNode); //pNode is q's right child.
	}
	else q->setRight(pNode); //if q->lastname is smaller than lastname, pNode is q's right child.
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void BST::PrintAll(FILE_IO &F) //PrintAll function.
{
	BST_Node *Stack[100] = {NULL}; //to store the nodes as a stack, make array pointer size 100. 
	int n = 0; //stack count.
	BST_Node *p = root; //p pointed root
	int cnt = 0;

	if(root != NULL) //if BST is not empty,
	{
		F.Write("==================================================================");
		F.Write("\n");
		F.Write("   Name          Phone-number              Address");
		F.Write("\n");
		F.Write("==================================================================");
		F.Write("\n");
		while(1) //loop until visit all BST's nodes.
		{
			while(p) //loop until p moves end leaf.
			{
				Push(Stack, p, n); //push all left child leaf in stack.
				p = p->getLeft(); //p moves to left.
			}
			p = Pop(Stack, n); //pop the last inputted node that is smallest node in stack.
			if(!p) //if p is NULL
				break; //end loop.
			F.Writeall(p->getFirstname(), p->getLastName(), p->getPhone(), p->getAddress_num(), p->getAddress_str()); //write datas to file.
			p = p->getRight(); //p moves to right.
		}
		F.Write("\n");

	}
	else //if BST is empty
	{
		F.Write("PRINTALL error - No data"); //print BST is empty.
		F.Write("\n\n");
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int BST::search(char *firstname, char *lastname, char *phone) //search function. use when command is Update, Delete, and Print.
{
	int cnt = 0; //count the node that has same name data(firstname, lastname)
	int chk_dup = 0; //find the node that has same name data(firstname, lastname) and phone data(phone)
	BST_Node *Stack[100] = {NULL}; //to store the nodes as a stack, make array pointer size 100. 
	int n = 0; //stack count
	BST_Node *p = root; //p pointed root.
	if(root != NULL) //if BST isn't empty.
	{
		while(1) //loop until visit all nodes in BST.
		{
			while(p) //loop until p moves end node.
			{
				Push(Stack, p, n); //push all left child leaf in stack.
				p = p->getLeft(); //p moves to left.
			}
			p = Pop(Stack, n); //pop the last inputted node that is smallest node in stack
			if(!p) //if p is NULL
				break; //end loop.
			if((strcmp(p->getFirstname(), firstname) == 0) && (strcmp(p->getLastName(), lastname) == 0)) //if p's name data and inputted name data are same,
			{
				cnt++; //count
				if(strcmp(p->getPhone(), phone) == 0) //if p's phone data and phone data are same,
					chk_dup = -1; //change chk_dup to -1 (In BST, there is no duplicate node that is same all data(name, phone)
			}
			p = p->getRight(); //p moves to right.
		}
		if(strcmp(phone, "NULL") != 0) //if phone is inputted,
		{
			if(cnt == 1) //if node is not duplicate,
				return 1; // return 1;
			cnt = chk_dup; //return chk_dup
		}
			
		return cnt; //if phone isn't inputted, return cnt.
	}
	else //if BST is empty
		return 0;

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool BST::Update(FILE_IO &F, char *firstname, char *lastname, char *phone, char *phone2, char *address_num, char *address_str) //update function.
{
	BST_Node *p = root; //p pointed root
	BST_Node *q;
	int i = 0;
	while(p) //loop until p moves end leaf.
	{
		q = p; //q pointed p.
		if(strcmp(q->getLastName(), lastname) == 0) //if q->lastname and lastname are same
		{
			if(strcmp(q->getFirstname(), firstname) == 0) //if q->firstname and firstname are same
			{
				if(strcmp(phone, "NULL") != 0) //if inputted phone datas are two,
				{
					if(strcmp(q->getPhone(), phone) == 0) //if q->phone and phone are same,
					{
						q->setPhone(phone2); //change phone data to phone2.
						q->setAddress(address_num, address_str); //change address data.
						
						return true; //return
					}
					else if(strcmp(q->getPhone(), phone)  == 1) //if q->phone is bigger than phone,
					{
						p = p->getLeft(); //move p to left.
						continue; //continue loop
					}
					else //if q->phone is smaller than phone
					{
						p = p->getRight(); //p moves to right.
						continue; //continue loop
					}
				}
				else //if inputted phone data is only one,
				{
					q->setPhone(phone2); //change phone data
					q->setAddress(address_num, address_str); //change address data
					return true; //return
				}
			}

			else if(strcmp(q->getFirstname(), firstname) == 1) //if q->firstname is bigger than firstname,
			{
				p = p->getLeft(); //p moves to left
				continue; //continue loop
			}
			else //if q->firstname is smaller than firstname,
			{
				p = p->getRight(); //p moves to right
				continue; //continue loop
			}
		}
		else if(strcmp(q->getLastName(), lastname)  == -1) //if q->lastname is smaller than lastname
			p = p->getRight(); //p moves to right
		else //if q->lastname is bigger than firstname
			p = p->getLeft(); //p moves to left
	}
	return false; //if fail to find the correct node, return false.
}

///////////////////////////////////////////////////////////////////////////////////////////////


bool BST::Delete(FILE_IO &F, char *firstname, char *lastname, char *phone) //delete function.
{
	//int found = false;
	BST_Node *p, *q, *r, *s, *t;
	p = root; //p pointed root.
	q = NULL;
	while(p) //loop until p moves to end leaf or find the correct node.
	{
		if(strcmp(p->getLastName(), lastname) == 0) //if p->lastname and lastname are same,
		{
			if(strcmp(p->getFirstname(), firstname) == 0) //if p->firstname and firstname are same,
			{
				if(strcmp(phone, "NULL") != 0) //if phone is inputted,
				{
					if(strcmp(p->getPhone(), phone) == 0) //if p->phone and phone are same,
						break; //break while loop
					else if(strcmp(p->getPhone(), phone) == -1) //if p->phone is smaller than phone
					{
						q = p; //q pointed p's current address.
						p = p->getRight(); //p moves to right.
					}
					else //if p->phone is bigger than phone
					{
						q = p; //q pointed p's current address
						p = p->getLeft(); //p moves to left.
					}
				}
				else //if phone isn't inputted.
					break; //end while loop
			}

		}
		else //if p's name data and inputted name data aren't same
		{
			q = p; //q pointed current p's addrses.
			if(strcmp(lastname, p->getLastName()) == 1) //if lastname is bigger than p->lastname, 
				p = p->getRight(); //p moves to right
			else if(strcmp(lastname, p->getLastName()) == 0) //if lastname and p->lastname are same
			{
				if(strcmp(firstname, p->getFirstname()) == 1) //if firstname is bigger than p->firstname,
					p = p->getRight(); //p moves to right.
				else if(strcmp(firstname, p->getFirstname()) == 0) //if firstname and p->firstname are same,
				{
					if(strcmp(phone, p->getPhone())  == 1) //if phone is bigger than p->phone,
						p = p->getRight(); //p moves to right
					else //if phone is smaller than p->phone,
						p = p->getLeft(); //p moves to left
				}
				else //if firstname is smaller than p->firstname
					p = p->getLeft(); //p moves to left
			}
			else //if lastname is smaller than p->lastname
				p = p->getLeft(); //p moves to left.
		}
	}

	if(p->getLeft() == NULL) //if p has only right child,
		r = p->getRight(); //r pointed p's right child.
	else //if p has only left child or p has no child
	{
		if(p->getRight() == NULL) //if p has only left child,
			r = p->getLeft(); //r pointed p's left child.
		else //if p has two child
		{
			t = p; //t pointed p's current address.
			r = p->getRight(); //r pointed p's right child.
			s = r->getLeft(); //s pointed p's right child's left child.
			while(s) //move until s moves p's right child's smallest node.
			{
				t = r; //t pointed r's address
				r = s; //r pointed s' address
				s = r->getLeft(); //s moved to left.
			} //then, r has p's right child's smallest node.

			if(t != p) //if t moved at least one time,
			{
				t->setLeft(r->getRight()); //lint t's left child to r's right child.
				r->setRight(p->getRight()); //link r's right child to p's right child.
			}
			r->setLeft(p->getLeft()); //link r's left child to p's left child.
		}
	}
	if(!q) root = r; //if BST is empty, r is root.
	else if(p == q->getLeft()) //if p is q's left child,
		q->setLeft(r); //q's left child is r.
	else if(p == q->getRight()) //if p is q's right child,
		q->setRight(r); //q's right child is r.
	delete p; //delete p.

	return true; //return true.
}
void BST::Destructor() //Destructor.
{
	BST_Node *Stack[100] = {NULL};
	BST_Node *p = root;
	BST_Node *q;
	while(1) //loop until delete all nodes in BST.
	{
		while(p) //loop until p moves to end left leaf.
		{
			Push(Stack, p, n); //push p
			p = p->getLeft(); //p moves to left
		}
		p = Pop(Stack, n); //pop the last inputted node(smallest node in stack)
		if(!p) //if p is NULL
			break; //end loop
		q = p; //q pointed p's address.
		p = p->getRight(); //p moved to right
		delete q; //delete smallest node.
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////

void BST::PrintLastName(FILE_IO &F, char *lastname, char *keys) //PrintLastName function
{
	BST_Node *Stack[100] = {NULL}; //to store the nodes as a stack, make array pointer size 100. 
	int n = 0; //stack count
	BST_Node *p = root; //p pointed root
	int cnt = 0; //count the node that has same lastname data.
	while(1) //loop until vit all nodes in BST
	{
		while(p) //loop until p moves to end left leaf
		{
			Push(Stack, p, n); //push current node
			p = p->getLeft(); //p moves to left
		}
		p = Pop(Stack, n); //pop the last inputted node(smallest node in stack)
		if(!p) //if p is NULL
			break; //end loop
		if(strcmp(p->getLastName(), lastname) == 0) //if p->lastname and lastname are same,
		{
			if(cnt == 0) //if it is first found node
			{
				F.Write("==================================================================");
				F.Write("\n");
				F.Write("   Name          Phone-number              Address");
				F.Write("\n");
				F.Write("==================================================================");
				F.Write("\n");
			}
			F.Writeall(p->getFirstname(), p->getLastName(), p->getPhone(), p->getAddress_num(), p->getAddress_str()); //write datas to file.
			cnt++; //count
		}
		p = p->getRight(); //p moves to right.
	}
	if(cnt == 0) //if can't find correct node.
	{
		F.Write("PRINTNAME error - Can't Find : "); //print that can't find node.
		F.Write(lastname);
		F.Write("\n");
		F.Write(keys);
		F.Write("\n\n");
		return;
	}
	F.Write("\n");
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void BST::Print(FILE_IO &F, char *firstname, char *lastname, char *phone) //Print function.
{
	BST_Node *Stack[100] = {NULL};  //to store the nodes as a stack, make array pointer size 100.
	int n = 0; //stack count
	BST_Node *p = root; //p pointed root
	F.Write("==================================================================");
	F.Write("\n");
	F.Write("   Name          Phone-number              Address");
	F.Write("\n");
	F.Write("==================================================================");
	F.Write("\n");
	while(1) //loop until visit all nodes in BST.
	{
		while(p) //loop until p moves end left leaf
		{
			Push(Stack, p, n); //push current node in stack
			p = p->getLeft(); //p moves to left
		}
		p = Pop(Stack, n); //pop last inputted node(smallest node in stack)
		if(!p) //if visit all nodes
			break; //end loop
		if((strcmp(p->getLastName(), lastname) == 0) && (strcmp(p->getFirstname(), firstname) == 0)) //if p's name data and inputted name data are same,
			F.Writeall(p->getFirstname(), p->getLastName(), p->getPhone(), p->getAddress_num(), p->getAddress_str()); //write data to file.
		p = p->getRight(); //p moves to right.
	}
	F.Write("\n");
}
void BST::Push(BST_Node *Stack[], BST_Node *CurrentNode, int &n) //to make inorder using stack, make a push function.
{
	if(n == 100) //if stack is full, 
	{
		cout<<"Stack is Full!"<<endl;
	}
	else //if stack has enough space, 
	{
		Stack[n] = CurrentNode; //input current node in n'th stack array.
		n++; //adds stack count by 1.
	}
}
BST_Node *BST::Pop(BST_Node *Stack[], int &n) //to make inorder using stack, make a pop function.
{
	if(n == 0) //if stack is empty,
		return NULL; //return null
	else //if stack has at least one node,
	{
		n--; //decrease stack count by 1.
		return Stack[n]; //retun node in n'th stack array.
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
	
bool BST::Parsing(FILE_IO &F, char *keys, char *cmd, char *firstname, char *lastname, char *phone, char *phone2, char *address_num, char *address_str)
{
	char buf[128];
	char *token;
	int i = 0;
	strcpy(buf, keys); //copy keys to buf.
	token = strtok(buf, " \r"); //parse buf.
	strcpy(cmd, token); //store the command
	if(cmd == NULL)
		return true;
////////////////////////////////////////////////
	if(strcmp(cmd, "INSERT") == 0) //Insert : firstname, lastname, phone, address_num, address_str
	{
		if((token = strtok(NULL, " \r")) != NULL) //parsing firstname
			strcpy(firstname, token);
		else 
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing lastname
			strcpy(lastname, token);
		else 
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing phone
			strcpy(phone, token);
		else 
		{	
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing address_num
			strcpy(address_num, token);
		else
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing address_str
			strcpy(address_str, token);
		else 
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //if there is remained words in buf,
		{
			return false; //just return
		}
		strcpy(phone2, "NULL"); //in Insert command, phone2 isn't used, so store "NULL"
	}
/////////////////////////////////////////////////////////////////
	else if(strcmp(cmd, "UPDATE") == 0) //UPDATE : firstname, lastname, (phone), phone2, address_num, address_str
	{
		if((token = strtok(NULL, " \r")) != NULL) //parsing firstname
			strcpy(firstname, token);
		else 
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing lastname
			strcpy(lastname, token);
		else 
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing phone
			strcpy(phone, token);
		else 
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL)
		{
			if(((strlen(token)) > 4 ) && token[3] == '-') //if inputted phone data is two, (parsed word is phone2)
			{
				strcpy(phone2, token); //store token to phone2.
				if((token = strtok(NULL, " \r")) != NULL) //paring address_num
					strcpy(address_num, token); 
				else 
				{
					return true;
				}
			}
			else //if parsed word is address_num(inputted phone data is one)
			{
				strcpy(phone2, phone); //copy phone to phone2.
				strcpy(phone, "NULL"); //store "NULL" to phone.
				strcpy(address_num, token); //parsing address_num
			}
		}
		else 
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing address_str
			strcpy(address_str, token);
		else 
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //if there is remained word in buf,
		{
			return false; //return
		}
	}
/////////////////////////////////////////////////////////////////
	else if(strcmp(cmd, "PRINT") == 0) //PRINT : firstname, lastname, (phone)
	{
		if((token = strtok(NULL, " \r")) != NULL) //parsing firstname
			strcpy(firstname, token);
		else
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing lastname
			strcpy(lastname, token);
		else
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL)  //if phone is inputted,
		{
			strcpy(phone, token); //parsing phone
			if((token = strtok(NULL, " \r")) != NULL) //if there is remained word in buf,
			{
				return false; //return
			}
		}
		else 
			strcpy(phone, "NULL"); //if phone isn't inputted, store "NULL" to phone.
	}
///////////////////////////////////////////////////////////
	else if(strcmp(cmd, "DELETE") == 0) //DELETE : firstname, lastname, (phone)
	{
		if((token = strtok(NULL, " \r")) != NULL) //parsing firstname
			strcpy(firstname, token);
		else
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //parsing lastname
			strcpy(lastname, token);
		else
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //if phone is inputted
		{
			strcpy(phone, token); //parsing phone
			if((token = strtok(NULL, " \r")) != NULL) //if there is remained word in buf,
			{
				return false; //return
			}
		}
		else 
			strcpy(phone, "NULL"); //if phone isn't inputted, store "NULL" to phone
	}
//////////////////////////////////////////////////////////
	else if(strcmp(cmd, "PRINTNAME") == 0) //PRINTNAME : lastname
	{
		if((token = strtok(NULL, " \r")) != NULL) //parsing lastname
			strcpy(lastname, token);
		else
		{
			return true;
		}
		if((token = strtok(NULL, " \r")) != NULL) //if there is remained word in buf,
		{
			return false; //return
		}
	}
/////////////////////////////////////////////////////////
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BST::Chk_str(FILE_IO &F, char *keys, char *firstname, char *lastname, char *phone, char *phone2, char *address_num, char *address_str)
//check whether words' forms are appropriate or not
{
	int i = 0;
	int cnt = 0;
	char address[50];
	char *token;
	for(i = 0; i < strlen(firstname); i++)
	{
		if(i == 0) 
		{
			if(firstname[0] < 65 || firstname[0] > 90) //if first letter isn't capital letter,
			{
				F.Write("Input error - First name"); // print error
				F.Write("\n");
				F.Write(keys);
				F.Write("\n\n");
				return false;
			}
		}
		else 
		{
			if(!((firstname[i] >= 97 && firstname[i]  <= 122) || (firstname[i] >= 65 && firstname[i] <= 90))) //if remained letters aren't small letters or capital letters,
			{
				F.Write("Input error - First name"); // print error
				F.Write("\n");
				F.Write(keys);
				F.Write("\n\n");
				return false;
			}
		}
	}
	for(i = 0; i < strlen(lastname); i++)
	{
		if(i == 0)
		{
			if(lastname[0] < 65 || lastname[0] > 90) //if first letter isn't capital letter,
			{
				F.Write("Input error - Last name"); //print error
				F.Write("\n");
				F.Write(keys);
				F.Write("\n\n");
				return false;
			}
		}
		else
		{
			if(lastname[i] < 97 || lastname[i] > 122) //if remained letters aren't small letters,
			{
				F.Write("Input error - Last name"); //print error
				F.Write("\n");
				F.Write(keys);
				F.Write("\n\n");
				return false;
			}
		}
	}
	if(strcmp(phone, "NULL") != 0) //if phone is inputted,
	{
		if(strlen(phone) != 8) //if phone's length isn't 8,
		{
			F.Write("Input error - Phone-number"); //print error
			F.Write("\n");
			F.Write(keys);
			F.Write("\n\n");
			return false;
		}
		for(i = 0; i < 8; i++)
		{
			if(i != 3) 
			{
				if(phone[i] < 48 || phone[i] > 57) //if letters aren't numbers
				{
					F.Write("Input error - Phone-number"); //print error
					F.Write("\n"); 
					F.Write(keys);
					F.Write("\n\n");
					return false;
				}
			}
			else if(i == 3) 
			{
				if(phone[i] != 45) //if fourth letter isn't hyphen,
				{
					F.Write("Input error - Phone-number");
					F.Write("\n");
					F.Write(keys);
					F.Write("\n\n");					
					return false;
				}
			}
		}
		if(strcmp(phone2, "NULL") != 0) //if phone2 is inputted,
		{
			if(strlen(phone2) != 8) //if phone2's length isn't 8,
			{
				F.Write("Input error - Phone-number"); //print error
				F.Write("\n");
				F.Write(keys);
				F.Write("\n\n");
				return false;
			}
			for(i = 0; i < 8; i++) 
			{
				if(i != 3)
				{
					if(phone2[i] < 48 || phone2[i] > 57) //if letters aren't number, 
					{
						F.Write("Input error - Phone-number"); //print error
						F.Write("\n");
						F.Write(keys);
						F.Write("\n\n");
						return false;
					}
				}
				else if(i == 3)
				{
					if(phone2[i] != 45) //if fourth letter isn't hyphen,
					{
						F.Write("Input error - Phone-number"); //print error
						F.Write("\n");
						F.Write(keys);
						F.Write("\n\n");					
						return false;
					}
				}
			}
		}
	}
	if(strcmp(address_num, "NULL") != 0) //if address_num is inputted, 
	{
		for(i = 0; i < strlen(address_num); i++) 
		{
			if(address_num[i] < 48 || address_num[i] > 57) //if address_num's letters aren't numbers,
			{
				F.Write("Input error - Steet address"); //print error
				F.Write("\n");
				F.Write(keys);
				F.Write("\n\n");
				return false;
			}
		}
		
		for(i = 0; i < strlen(address_str); i++) 
		{
			if(address_str[i] == '-') //if address_str has hyphen
				cnt++; //count the hyphen
			else 
			{
				if(!(address_str[i] >= 97 && address_str[i] <= 122)) //if address_str's letters aren't small letters,
				{
					F.Write("Insert error - Dong address"); //print error
					F.Write("\n");
					F.Write(keys);
					F.Write("\n\n");
					return false;
				}
			}
		}
		strcpy(address, address_str); //copy address_str to address.
		if(cnt == 1) //if hyphen's number is only one,
		{
			if((token = strtok(address, "-")) != NULL) //parsing word behind the hyphen.
			{
				if((token = strtok(NULL, " \r")) != NULL)
				{
					if(strcmp(token, "dong") != 0) //if token isn't "dong"
					{
						F.Write("Input error - Dong address"); //print error
						F.Write("\n");
						F.Write(keys);
						F.Write("\n\n");
						return false;
					}
				}
				else //if fail to parse the address,
				{
					F.Write("Input error - Dong address"); //print error
					F.Write("\n");
					F.Write(keys);
					F.Write("\n\n");
					return false;
				}
			}
		}
		else // if hyphen's count is at least two,
		{
			F.Write("Insert error - Dong address"); //print error.
			F.Write("\n");
			F.Write(keys);
			F.Write("\n\n");
			return false;
		}
	}
	return true; //if words' forms are correct, return true.
}
