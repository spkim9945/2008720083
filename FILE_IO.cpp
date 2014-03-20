#include "FILE_IO.h"
#include <iomanip>
#include <cstring>
#include <iostream>

using namespace std;


FILE_IO::FILE_IO(void)
{
}


FILE_IO::~FILE_IO(void)
{
	
}

bool FILE_IO::InputFileOpen(char *fname) //open the input file.
{
	m_fin.open(fname);
	if(!m_fin) //if fail to open file
		return false; //return false.
	else
		return true;
}

bool FILE_IO::OutputFileOpen(char *fname) //open the output file.
{
	m_fout.open(fname); //when the file is exist, adds the data.
	if(!m_fout) //if fail to open file,
		return false;
	else
		return true;
}

bool FILE_IO::ReadCommand(char *keys) //read file's one line.
{

	char buf[128];
	char *token;
	int i = 0;
	if(!m_fin.eof()) //if file has lines, 
	{
		if(m_fin.getline(buf, 128) == NULL) //if file's line has no data
			return false;
		strcpy(keys, buf); //copy file's one line to keys.
		if(keys == NULL) //if key has no data, 
			return true;
		return true;
	}
	else
		return false;
}
	
bool FILE_IO::Write(char *str) //write str to output file.
{
	m_fout<<str;
	return true;
}

bool FILE_IO::Writeall(char *firstname, char *lastname, char *phone, char *address_num, char *address_str) //overloading. write variables to output file.
{
	char address[50];
	char name[20];
	strcpy(address, address_num); //make 'address_num address_str'
	strcat(address, " ");
	strcat(address, address_str);
	strcpy(name, lastname); //make 'lastname firstname'
	strcat(name, " ");
	strcat(name, firstname);
	m_fout.setf(ios::left); //dress to the left.
	m_fout<<setw(17)<<name<<setw(23)<<phone<<setw(18)<<address<<endl;
	return true;
}

void FILE_IO::OutputFileClose() //close the output file
{
	m_fout.close();
}

void FILE_IO::InputFileClose() //close the input file
{
	m_fin.close();
}