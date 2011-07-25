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
 
 #include <stdlib.h>
 #include "VMUtil.h"
 
 using namespace std;
 using std::string;
 
VMUtil::VMUtil(string url1,string uname,string pass){
	path="/home/ubuntu1/Desktop/combinedtask.py";
	url=url1;
	username=uname;
	password=pass;
	}

int VMUtil::startVM(string vmname){
		char *command;
		string combined_command;
		combined_command="python " + path + " " + url + " " + username + " " + password + " " + "vm_start" + " " + vmname;
		command=&combined_command[0];
		system(command);
		return 0;
	}

int VMUtil::stopVM(string vmname){
		
	return 0;
	}

int VMUtil::suspendVM(string vmname){
		
	return 0;
	}

int VMUtil::rebootVM(string vmname){
		
	return 0;
	}

int VMUtil::pauseVM(string vname){
	
	return 0;
	}

int VMUtil::migrateVM(string vmname,string destn_server){
		
	return 0;
	}