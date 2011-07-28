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
	VMUtil(const string &url1,const string &uname,const string &pass)  //Constructor
	{
		m_path="/home/ubuntu1/Desktop/combinedtask.py";
		m_url=url1;
		m_username=uname;
		m_password=pass;
	}
	virtual int startVM(const string&)=0;
	virtual int stopVM(const string&)=0;
	virtual int rebootVM(const string&)=0;
	virtual int suspendVM(const string&)=0;
	virtual int pauseVM(const string&)=0;
	virtual int migrateVM(const string&, const string&)=0;
	virtual int performoperation(char *)=0;
	
protected:
	string m_path;
	string m_url;
	string m_username;
	string m_password;
};

#endif