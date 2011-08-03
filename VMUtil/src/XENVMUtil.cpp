/*********************************************************************
 * Name:      	XENVMUtil.cpp
 * Purpose:   	Provides definition to the methods inherited from 
 * 				VMUtil class and also defines its own methods.....
 * Author:      Rahul Sharma
 * Created:     
 * Copyright: 
 * License:   	
 *********************************************************************/
 
 #include <iostream>
 #include <stdlib.h>
 #include <stdio.h>
 #include "XENVMUtil.h"  //XENVMUtil.h included here to provide definition to its functions....
 
 using namespace std;
 using std::string;
 
XENVMUtil::XENVMUtil(){
	
	}

void XENVMUtil::seturl(const string &url1){
	m_url=url1;
	}
	
void XENVMUtil::setusername(const string &uname){
	m_username=uname;
	}
	
void XENVMUtil::setpassword(const string &pass){
	m_password=pass;
	}

int XENVMUtil::startVM(const string &vmname){
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
	}

int XENVMUtil::suspendVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_suspend" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	}

int XENVMUtil::rebootVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_reboot" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	}

int XENVMUtil::pauseVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_pause" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	}

int XENVMUtil::migrateVM(const string &vmname,const string &destn_server){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_migrate" + " " + vmname + " " + destn_server;
		command=&combined_command[0];
		return performoperation(command);
	}
	
int XENVMUtil::snapshotVM(const string &vmname,const string &snapshot_name){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_snapshot" + " " + vmname + " " + snapshot_name;
		command=&combined_command[0];
		return performoperation(command);
	}
	
int XENVMUtil::cloneVM(const string &vmname,const string &newvm_name){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_clone" + " " + vmname + " " + newvm_name;
		command=&combined_command[0];
		return performoperation(command);
	}
	
int XENVMUtil::vmfromTemplate(const string &templatename,const string &newvm_name){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_from_template" + " " + templatename + " " + newvm_name;
		command=&combined_command[0];
		return performoperation(command);
	}
	
int XENVMUtil::vmtoTemplate(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + m_path + " " + m_url + " " + m_username + " " + m_password + " " + "vm_to_template" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
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