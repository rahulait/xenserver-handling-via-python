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
	XENVMUtil(const string &url1,const string &uname,const string &pass); //Constructor
	virtual int startVM(const string&);
	virtual int stopVM(const string&);
	virtual int rebootVM(const string&);
	virtual int suspendVM(const string&);
	virtual int pauseVM(const string&);
	virtual int migrateVM(const string&, const string&);
	virtual int performoperation(char *);
};

#endif