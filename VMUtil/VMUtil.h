//Declaration of VMUtil Header file
//Function Definitions are in VMUtil.cpp file

//prevent multiple inclusions of header files
#ifndef VMUTIL_H
#define VMUTIL_H

#include <iostream>
#include <string>

using std::string;

//VMUtil class declaration
class VMUtil
{
public:
	VMUtil(string,string,string);  //Constructor
	int startVM(string);
	int stopVM(string);
	int rebootVM(string);
	int suspendVM(string);
	int pauseVM(string);
	int migrateVM(string,string);
	
private:
	string path;
	string url;
	string username;
	string password;
	string vmname;
	string destn_server;
	
}

#endif