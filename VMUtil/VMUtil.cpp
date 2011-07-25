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
 #include "VMUtil.h"
 
 using namespace std;
 using std::string;
 
VMUtil::VMUtil(string url1,string uname,string pass){
	path="/home/ubuntu1/Desktop/combinedtask.py";
	url=url1;
	username=uname;
	password=pass;
	}

VMUtil::startVM(string vmname){
		char *command;
		string combined_command;
		combined_command="python" + " " + path + " " + url + " " + username + " " + password + " " + "vm_start" + " " + vmname;
		command=&combined_command[0];
		system(command);
	}

VMUtil::stopVM(string vmname){
		
	}

VMUtil::suspendVM(string vmname){
		
	}

VMUtil::rebootVM(string vmname){
		
	}

VMUtil::pauseVM(string vname){
		
	}

VMUtil::migrateVM(string vmname,string destn_server){
		
	
	}