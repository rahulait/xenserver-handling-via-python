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
 #include "VMUtil.h"
 #include "XENVMUtil.h"
 
 using namespace std;
 using std::string;
 
VMUtil::VMUtil(string url1,string uname,string pass){
	path="/home/ubuntu1/Desktop/combinedtask.py";
	url=url1;
	username=uname;
	password=pass;
	}

int VMUtil::startVM(const string &vmname){
		//char *command;
		//string combined_command;
		//combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_start" + " " + vmname;
		//command=&combined_command[0];
		//system(command);
		char *command;
		string combined_command;
		combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_start" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	}

int VMUtil::stopVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_stop" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}

int VMUtil::suspendVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_suspend" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}

int VMUtil::rebootVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_reboot" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}

int VMUtil::pauseVM(const string &vmname){
		char *command;
		string combined_command;
		combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_pause" + " " + vmname;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}

int VMUtil::migrateVM(const string &vmname,const string &destn_server){
		char *command;
		string combined_command;
		combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_migrate" + " " + vmname + " " + destn_server;
		command=&combined_command[0];
		return performoperation(command);
	return 0;
	}
	
int VMUtil::performoperation(char* command){
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