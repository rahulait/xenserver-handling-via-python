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
	VMUtil()  //Constructor
	{
		m_path="/home/ubuntu1/Desktop/combinedtask.py";
	}
	
	void seturl(const string &url1)
	{
		m_url=url1;
	}
	
	void setusername(const string &uname)
	{
		m_username=uname;
	}
	
	void setpassword(const string &pass)
	{
		m_password=pass;
	}
	
	virtual int startVM(const string&)=0;
	virtual int stopVM(const string&)=0;
	virtual int rebootVM(const string&)=0;
	virtual int suspendVM(const string&)=0;
	virtual int pauseVM(const string&)=0;
	virtual int migrateVM(const string&, const string&)=0;
	
protected:
	string m_path;
	string m_url;
	string m_username;
	string m_password;
};

#endif