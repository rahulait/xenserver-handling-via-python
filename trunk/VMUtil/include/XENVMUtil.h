/*********************************************************************
 * Name:      	XENVMUtil.h
 * Purpose:   	provides declaration of XENVMUtil class.....
 * Author:      Rahul Sharma
 * Created:     
 * Copyright: 
 * License:   	
 *********************************************************************/

//Declaration of XENVMUtil Header file
//Function Definitions are in XENVMUtil.cpp file

//prevent multiple inclusions of header files
#ifndef XENVMUTIL_H
#define XENVMUTIL_H

#include <iostream>
#include <string>
#include "VMUtil.h"                  //**** This file is included because XENVMUtil extends VMUtil. 

using std::string;

//VMUtil class declaration
class XENVMUtil : public VMUtil      //**** Inheriting VMUtil here.......
{
public:
	XENVMUtil(); //Constructor
	virtual void seturl(const string &);       //***** Pure virtual functions in VMUtil used here as virtual functions......
	virtual void setusername(const string &);
	virtual void setpassword(const string &);
	virtual int startVM(const string &);
	virtual int stopVM(const string &);
	virtual int rebootVM(const string &);
	virtual int suspendVM(const string &);
	virtual int pauseVM(const string &);
	virtual int migrateVM(const string &, const string &);
private:
	int performoperation(char *);             //***** This function performs the operation by taking input the command and then executing it...
};

#endif