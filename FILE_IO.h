#pragma once
#include <fstream>
#include <iostream>
#include "BST_Node.h"
using namespace std;
class FILE_IO
{
private:
	ifstream m_fin;
	ofstream m_fout;
public:
	bool InputFileOpen(char *fname); //open input file
	bool OutputFileOpen(char *fname); //open output file
	bool ReadCommand(char *keys); //read one line in file.
	bool Write(char *str); //write str to file.
	bool Writeall(char *firstname, char *lastname, char *phone, char *address_num, char *address_str); //overloading write. 
	void InputFileClose();
	void OutputFileClose();
	FILE_IO(void);
	~FILE_IO(void);
};

