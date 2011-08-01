#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <climits>
#include "VMUtilfactory.h"  //**** including VMUtilfactory here as it would be used to create an object of required class.....

using namespace std;
using std::string;
using std::cout;
using std::cin;

int main()
{
	string url, username, password,vmname,destn_server;
	int choice=0;			//**** choice for the operation to be performed on the VM.....
	int platform_choice=0;  //**** getting the choice of platform on which operations will be performed...
	cout<<"Enter the url of the XenServer:: ";
	cin>>url;               //**** getting the URL of the server....
	cout<<"Enter the username:: ";
	cin>>username;          //**** getting the username of the server....
	cout<<"Enter the password:: ";
	cin>>password;          //**** getting the password of the server....
	cout<<"Choose platform as specified below:: \n1. XEN\n2. ESX(Not supported now....)\n3. HYPERV(Not supported now....)\nEnter Choice number:: ";
	cin>>platform_choice;   //**** getting the platform choice from the User....
	if(platform_choice>0 && platform_choice<VMUtilfactory::INVALID)
	{
		VMUtilfactory *vmfactory=new VMUtilfactory();  //Create new VMUtilfactory object....
		VMUtil *vmutil;
		if(platform_choice==1){
		vmutil=vmfactory->createVMUtil(VMUtilfactory::XEN); //Create new object of required platform's class....
		}
		vmutil->seturl(url);
		vmutil->setusername(username);
		vmutil->setpassword(password);
		while(1)
		{
			system("clear");
			cout<<"-------------MENU--------------\n";
			cout<<" 1.Start VM.\n 2.Stop VM\n 3.Suspend VM\n 4.Pause VM\n 5.Reboot VM\n 6.Migrate VM\n 7.exit\n";
			cout<<"-------------------------------\n";
			cout<<"Enter your choice:: ";
			cin>>choice;
			if(choice<1||choice>7)
			{
					cout<<"\nWrong choice entered.... Program will end now.... \n";
					delete vmutil;      //Freeing the memory....
					delete vmfactory;   //Freeing the memory....
					exit(0);
			}
			system("clear");
			switch(choice)
			{
				case 1:                 //Starting a particular VM.....
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to start:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->startVM(vmname);
					break;
				case 2:                //Stopping a particular VM.....
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to stop:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->stopVM(vmname);
					break;
				case 3:				   //Suspending a particular VM.....
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to suspend:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->suspendVM(vmname);	
					break;
				case 4:               //Pausing a particular VM.....
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to pause:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->pauseVM(vmname);
					break;
				case 5:              //Rebooting a particular VM.....
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to reboot:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->rebootVM(vmname);
					break;
				case 6:				//Migrating a particular VM.....
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to migrate:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					cout<<"\nEnter the destination server name:: ";
					getline(cin,destn_server,'\n');
					cout<<"\nDestination server name received is:: "<<destn_server<<std::endl;
					cout.flush();
					destn_server="\'"+destn_server+"\'";
					vmutil->migrateVM(vmname,destn_server);
					break;
				case 7:
					delete vmutil;
					delete vmfactory;
					exit(1);
			}
			cout<<"\nPress a key to continue.......";
			getchar();
		}
	}
	else{
		std::cout<<"Invalid platform choice!!! Please check it......";
		exit(1);
	}
	return 0;
}