#include <iostream>
#include <fstream>
#include "BST.h"
#include "BST_Node.h"
#include "FILE_IO.h"
//#include <crtdbg.h>
#include <cstring>

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif
using namespace std;

int main()
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); //check memory leakage.

	BST B;
	FILE_IO F;
	if(F.InputFileOpen("input_data.in") == true)
	{
		cout<<"Open Input file : input_data.in"<<endl;
	}
	else
	{
		cout<<"Fail to open file : input_data.in"<<endl;
		return 0;
	}
	if(F.OutputFileOpen("result.out") == true)
	{
		cout<<"Open Output file : result.out"<<endl;
	}
	else
	{
		cout<<"Fail to open file : result.out"<<endl;
		return 0;
	}
	char ch_value;
	char *command = new char[20];
	char buf[128];
	char *token;
	char *firstname = new char[20];
	char *lastname = new char[20];
	char *phone = new char[20];
	char *address_num = new char[20];
	char *address_str = new char[30];
	char *keys = new char[128];
	char *phone2 = new char[20];
	int i, chk_dup;
	chk_dup = 0;
	int n_menu = 0;
	cout<<"###### Make Phone Adress #####\n";
	cout<<"1. Load text file\n";
	cout<<"2. Make Phone address file\n";
	cout<<"3. Read Phone address file\n";
	cout<<"4. Exit\n";
	cout<<"Modified at github\n";
	while(F.ReadCommand(keys)) //read file's one line. If read all line, end while loop
	{
		if(strcmp(keys, "") == 0) //if readed line has no keys
		{
			//F.Write("\n");
			continue; //read next line
		}
		B.Parsing(F, keys, command, firstname, lastname, phone, phone2, address_num, address_str); //Parse the current line.

		if(strcmp(command, "INSERT") == 0) //if command is "INSERT"
		{
			if(B.Chk_str(F, keys, firstname, lastname, phone, "NULL", address_num, address_str) != false) //check whether parsed words are appropriate or not.
				B.Insert(F, firstname, lastname, phone, address_num, address_str, keys); //if words are fine, call Insert function.
		}
		else if(strcmp(command, "UPDATE") == 0) //If command is "Update"
		{
			if(B.Chk_str(F, keys, firstname, lastname, phone, phone2, address_num, address_str) != false) //check whether parsed words are appropriate or not
			{
				chk_dup = B.search(firstname, lastname, phone);
				if(chk_dup == 1) //if BST has only one node that has name data{firstname, lastname}
					B.Update(F, firstname, lastname, phone, phone2, address_num, address_str);
				else
				{
					if(strcmp(phone, "NULL") == 0) //If inputted phone number is one,
					{
						//if(B.search(firstname, lastname, phone) == 1) //search the BST tree, then if find only one node that has name data(firstname, lastname)
						//B.Update(F, firstname, lastname, phone, phone2, address_num, address_str, keys); //Update appropriate node's data.
						if(B.search(firstname, lastname, phone) > 1) //if find more than two nodes that has same name data
						{
							F.Write("UPDATE Error - Require Phone_Number (Duplicate records)"); //print that this name is duplicated.
							F.Write("\n");
							F.Write(keys);
							F.Write("\n\n");
						}
						else //if BST doesn't have node that has name data(firstname, lastname)
						{
							F.Write("UPDATE error - Can't find : "); //print that can't find node.
							F.Write(lastname);
							F.Write(" ");
							F.Write(firstname);
							F.Write("\n");
							F.Write(keys);
							F.Write("\n\n");
						}
					}
					else //if inputted phone numbers are two,
					{
						if(B.search(firstname, lastname, phone) == -1) //search the BST, then if find one node that has name data(firstname, lastname) and phone data(phone)
						{
							//B.Update(F, firstname, lastname, phone, phone2, address_num, address_str, keys); //update appropriate nodes' data.
							B.Delete(F, firstname, lastname, phone);
							B.Insert(F, firstname, lastname, phone2, address_num, address_str, keys);
						}
						else if(B.search(firstname, lastname, phone) == 0) //if BST doesn't have node that has name data(firstname, lastname) and phone data(phone)
						{
							F.Write("UPDATE error - Can't find : "); //print that can't find node.
							F.Write(lastname);
							F.Write(" ");
							F.Write(firstname);
							F.Write(" ");
							F.Write(phone);
							F.Write("\n");
							F.Write(keys);
							F.Write("\n\n");
						}
					}
				}
			}
		}
		else if(strcmp(command, "DELETE") == 0)	//If command is "DELETE"
		{
			if(B.Chk_str(F, keys, firstname, lastname, phone, "NULL", "NULL", "NULL") != false)  //check whether parsed words are appropriate or not.
			{
				if(strcmp(phone, "NULL") == 0) //if there is no inputted phone data
				{
					if(B.search(firstname, lastname, phone) > 1) //search the BST, then if find more than two nodes that has name data(firstname, lastname)
					{
						F.Write("DELETE error - Require Phone_number (Duplicate records)"); //print that this name is duplicated.
						F.Write("\n");
						F.Write(keys);
						F.Write("\n\n");
					}
					else if(B.search(firstname, lastname, phone) == 1) //if find only one node that has name data(firstname, lastname)
					{
						B.Delete(F, firstname, lastname, phone); //delete appropriate node.
					}
					else //if BST doesn't have node that has name data(firstname, lastname)
					{
						F.Write("DELETE error - Can't find : "); //print that can't find node.
						F.Write(lastname);
						F.Write(" ");
						F.Write(firstname);
						F.Write("\n\n");
					}

				}
				else //if phone is inputted.
				{				
					if(B.search(firstname, lastname, phone) == -1) //search the BST, then if find one node that has name data(firstname, lastname) and phone data(phone)
						B.Delete(F, firstname, lastname, phone); //delete appropriate node
					else if(B.search(firstname, lastname, phone) == 0) //if BST doesn't have node that has name data(firstname, lastname) and phone data(phone)
					{
						F.Write("DELETE error - Can't find : "); //print that can't find node
						F.Write(lastname);
						F.Write(" ");
						F.Write(firstname);
						F.Write(" ");
						F.Write(phone);
						F.Write("\n");
						F.Write(keys);
						F.Write("\n\n");
					}
				}
			}
		}
		else if(strcmp(command, "PRINTALL") == 0) //If command is "PRINTALL"
			B.PrintAll(F); //call PrintAll function
		else if(strcmp(command, "PRINTNAME") == 0) //If command is "PRINTNAME"
		{
			if(B.Chk_str(F, keys, "NULL", lastname, "NULL", "NULL", "NULL", "NULL") != false) //check whether parsed words are appropriate or not.
				B.PrintLastName(F, lastname, keys); //if words are fine, call PrintLastName function.
		}
		else if(strcmp(command, "PRINT") == 0) //if command is "PRINT"
		{
			if(B.Chk_str(F, keys, firstname, lastname, phone, "NULL", "NULL", "NULL")  != false) //check whether parsed words are appropriate or not
			{				  
				if(strcmp(phone, "NULL") == 0) //if there is no inputted phone data
				{ 
					if(B.search(firstname, lastname, "NULL") == 1) //search the BST, then if find one node that has name data(firstname, lastname)
					{
						B.Print(F, firstname, lastname, phone); //call Print Function
					}
					else if(B.search(firstname, lastname, "NULL") > 1) //if find more tha two node that has name data(firstname, lastname)
					{
						F.Write("PRINT error - Require Phone_number (Duplicate records)"); //print that this name is duplicated.
						F.Write("\n");
						F.Write(keys);
						F.Write("\n\n");
					}
					else //if BST doesn't have node that has name data(firstname, lastname)
					{
						F.Write("PRINT error - Can't find : "); //print that can't find node.
						F.Write(lastname);
						F.Write(" ");
						F.Write(firstname);
						F.Write("\n");
						F.Write(keys);
						F.Write("\n\n");
					}
				}
				else //if phone is inputted.
				{
					if(B.search(firstname, lastname, phone) == -1) //search the BST, then if find one node that has name data(firstname, lastname) and phone data(phone)
						B.Print(F, firstname, lastname, phone); //call Print function.
					else  //if BST doesn't have node that has name data(firstname, lastname) and phone data(phone)
					{
						F.Write("PRINT error - Can't find : "); //print that can't find node.
						F.Write(lastname);
						F.Write(" ");
						F.Write(firstname);
						F.Write(" ");
						F.Write(phone);
						F.Write("\n");
						F.Write(keys);
						F.Write("\n\n");
					}
				}

			}
		}
		else //if command is not appropriate word,
		{
			F.Write("Command error"); //print command error.
			F.Write("\n");
			F.Write(keys);
			F.Write("\n\n");
		}
		chk_dup = 0;
	}
	delete []firstname; //delete to prevent memory leaks.
	delete []lastname;
	delete []phone;
	delete []phone2;
	delete []address_num;
	delete []address_str;
	delete []keys;
	delete []command;
	F.InputFileClose();
	F.OutputFileClose();
	return 0;
}
