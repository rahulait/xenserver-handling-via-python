//Declaration of VMUtil Header file
//Function Definitions are in VMUtil.cpp file

//prevent multiple inclusions of header files
#ifndef XENVMUTIL_H
#define XENVMUTIL_H

#include <iostream>
#include <string>
#include "VMUtil.h"

using std::string;

//VMUtil class declaration
class XENVMUtil : public VMUtil
{
public:
	XENVMUtil(); //Constructor
	virtual void seturl(const string &);
	virtual void setusername(const string &);
	virtual void setpassword(const string &);
	virtual int startVM(const string&);
	virtual int stopVM(const string&);
	virtual int rebootVM(const string&);
	virtual int suspendVM(const string&);
	virtual int pauseVM(const string&);
	virtual int migrateVM(const string&, const string&);
private:
	int performoperation(char *);
};

#endif