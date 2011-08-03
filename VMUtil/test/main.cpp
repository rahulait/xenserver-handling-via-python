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
	string url, username, password,vmname,destn_server,snapshot_name,newvm_name,templatename;
	
	//**** choice for the operation to be performed on the VM.....
	int choice=0;			
	
	//**** getting the choice of platform on which operations will be performed...
	int platform_choice=0;  
	
	//**** getting the URL of the server....
	cout<<"Enter the url of the XenServer:: ";
	cin>>url;               
	
	//**** getting the username of the server....
	cout<<"Enter the username:: ";
	cin>>username;          
	
	//**** getting the password of the server....
	cout<<"Enter the password:: ";
	cin>>password;  
	
	//**** getting the platform choice from the User....
	cout<<"Choose platform as specified below:: \n1. XEN\n2. ESX(No support yet....)\n3. HYPERV(No support yet....)\nEnter Choice number:: ";
	cin>>platform_choice;   
	if(platform_choice>0 && platform_choice<VMUtilfactory::INVALID)
	{
		//Create new VMUtilfactory object....
		VMUtilfactory *vmfactory=new VMUtilfactory();  
		VMUtil *vmutil;
		
		if(platform_choice==1){
			//Create new object of required platform's class....
			vmutil=vmfactory->createVMUtil(VMUtilfactory::XEN); 
		}
		
		vmutil->seturl(url);
		vmutil->setusername(username);
		vmutil->setpassword(password);
		
		while(1)
		{
			system("clear");
			cout<<"-------------MENU--------------\n";
			cout<<" 1.Start VM.\n 2.Stop VM\n 3.Suspend VM\n 4.Pause VM\n 5.Reboot VM\n 6.Migrate VM\n";
			cout<<" 7.Snapshot VM\n 8.Clone VM\n 9.VM from Template\n 10.VM to Template\n 11.Exit\n";
			cout<<"-------------------------------\n";
			cout<<"Enter your choice:: ";
			cin>>choice;
			if(choice<1||choice>11)
			{
					cout<<"\nWrong choice entered.... Program will end now.... \n";
					//Freeing the memory....
					delete vmutil;      
					delete vmfactory;   
					exit(0);
			}
			
			system("clear");
			
			switch(choice)
			{
				//Starting a particular VM.....
				case 1:                 
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to start:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->startVM(vmname);
					break;
				
				//Stopping a particular VM.....
				case 2:                
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to stop:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->stopVM(vmname);
					break;
				
				//Suspending a particular VM.....
				case 3:				   
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to suspend:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->suspendVM(vmname);	
					break;
				
				//Pausing a particular VM.....
				case 4:               
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to pause:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->pauseVM(vmname);
					break;
					
				//Rebooting a particular VM.....
				case 5:              
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to reboot:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->rebootVM(vmname);
					break;
					
				//Migrating a particular VM.....
				case 6:				
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
					
				//Snapshot a particular VM.....
				case 7:				
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname whose shapshot you want to take:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					cout<<"\nEnter the snapshot_name:: ";
					getline(cin,snapshot_name,'\n');
					cout<<"\nSnapshot name is:: "<<snapshot_name<<std::endl;
					cout.flush();
					snapshot_name="\'"+snapshot_name+"\'";
					vmutil->snapshotVM(vmname,snapshot_name);
					break;
				
				//Clones a particular VM.....
				case 8:				
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname whome you want to clone:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					cout<<"\nEnter the name for new VM to be generated:: ";
					getline(cin,newvm_name,'\n');
					cout<<"New VM's name is:: "<<newvm_name<<std::endl;
					cout.flush();
					newvm_name="\'"+newvm_name+"\'";
					vmutil->cloneVM(vmname,newvm_name);
					break;
				
				//VM from a particular Template.....
				case 9:				
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the Template_name whose VM you want to create:: ";
					getline(cin,templatename,'\n');
					cout<<"Template_Name received is "<<templatename;
					cout.flush();
					templatename="\'"+templatename+"\'";
					cout<<"\nEnter the name for new VM to be generated:: ";
					getline(cin,newvm_name,'\n');
					cout<<"New VM's name is:: "<<newvm_name<<std::endl;
					cout.flush();
					newvm_name="\'"+newvm_name+"\'";
					vmutil->vmfromTemplate(templatename,newvm_name);
					break;
				
				//Converting VM to Template.....
				case 10:              
					cin.clear();
					cin.ignore(INT_MAX,'\n');
					cout<<"Enter the vmname which you want to convert to template:: ";
					getline(cin,vmname,'\n');
					cout<<"VMName received is "<<vmname;
					cout.flush();
					vmname="\'"+vmname+"\'";
					vmutil->vmtoTemplate(vmname);
					break;
				
				//Exiting from the program.....
				case 11:
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