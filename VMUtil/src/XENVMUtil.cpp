/*********************************************************************
 * Name:      	main.cpp
 * Purpose:   	Illustrates initialization and usage of wxWidgets in
 * 				console applications.
 * Author:      Rahul Sharma
 * Created:     
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		
 *********************************************************************/
 
 #include <iostream>
 #include <stdlib.h>
 #include <stdio.h>
 #include "XENVMUtil.h"
 
 using namespace std;
 using std::string;
 
XENVMUtil::XENVMUtil(const string &url1,const string &uname,const string &pass) : VMUtil(url1, uname, pass){}

int XENVMUtil::startVM(const string &vmname){
		//char *command;
		//string combined_command;
		//combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_start" + " " + vmname;
		//command=&combined_command[0];
		//system(command);
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_start" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	}

int XENVMUtil::stopVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_stop" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}

int XENVMUtil::suspendVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_suspend" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}

int XENVMUtil::rebootVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_reboot" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}

int XENVMUtil::pauseVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_pause" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}

int XENVMUtil::migrateVM(const string &vmname,const string &destn_server){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_migrate" + " " + vmname + " " + destn_server;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}
	
int XENVMUtil::performoperation(char* command){
	FILE *op;
	char buff[512];
	if(!(op=popen(command,"r"))){
			return 1;
		}
	cout<<"\n";
	while(fgets(buff,sizeof(buff),op)!=NULL){
		cout<<buff;
	}
	pclose(op);
	return 0;
	}