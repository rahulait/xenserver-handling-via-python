/*********************************************************************
 * Name:      	VMUtil.h
 * Purpose:   	provides declaration for VMUtil class.....
 * Author:      Rahul Sharma
 * Created:     
 * Copyright: 
 * License:   	
 *********************************************************************/

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
	
	//Constructor
	VMUtil(){
		m_path="/home/ubuntu1/Desktop/combinedtask.py";
	}
	
	//**** Pure virtual functions defined below......
	virtual void seturl(const string &)=0;
	virtual void setusername(const string &)=0;
	virtual void setpassword(const string &)=0;
	virtual int startVM(const string&)=0;      
	virtual int stopVM(const string&)=0;
	virtual int rebootVM(const string&)=0;
	virtual int suspendVM(const string&)=0;
	virtual int pauseVM(const string&)=0;
	virtual int migrateVM(const string&, const string&)=0;
	virtual int snapshotVM(const string&,const string&)=0;
	virtual int cloneVM(const string&,const string&)=0;
	virtual int vmfromTemplate(const string &,const string &)=0;
	virtual int vmtoTemplate(const string &)=0;
	
	//Variables which can be used by other files which inherit this file.....
protected:
	string m_path;
	string m_url;
	string m_username;
	string m_password;
};

class VMUtilexception {
public:
	VMUtilexception(std::string msg){
		message=msg;
	}
	
	std::string getMessage(){
		return message;
	}
	
private:
	std::string message;
};

#endif