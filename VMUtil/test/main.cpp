#include <stdlib.h>
#include <stdio.h>
#include <climits>
#include "XENVMUtil.h"

using namespace std;
using std::string;
using std::cout;
using std::cin;

int main()
{
	string url, username, password,vmname,destn_server;
	int choice=0;
	cout<<"Enter the url of the XenServer:: ";
	cin>>url;
	cout<<"Enter the username:: ";
	cin>>username;
	cout<<"Enter the password:: ";
	cin>>password;
	XENVMUtil *xenvmutil=new XENVMUtil(url,username,password);
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
				exit(0);
		}
		system("clear");
		switch(choice)
		{
			case 1:
				cin.clear();
				cin.ignore(INT_MAX,'\n');
				cout<<"Enter the vmname which you want to start:: ";
				getline(cin,vmname,'\n');
				cout<<"VMName received is "<<vmname;
				cout.flush();
				vmname="\'"+vmname+"\'";
				xenvmutil->startVM(vmname);
				break;
			case 2:
				cin.clear();
				cin.ignore(INT_MAX,'\n');
				cout<<"Enter the vmname which you want to stop:: ";
				getline(cin,vmname,'\n');
				cout<<"VMName received is "<<vmname;
				cout.flush();
				vmname="\'"+vmname+"\'";
				xenvmutil->stopVM(vmname);
				break;
			case 3:
				cin.clear();
				cin.ignore(INT_MAX,'\n');
				cout<<"Enter the vmname which you want to suspend:: ";
				getline(cin,vmname,'\n');
				cout<<"VMName received is "<<vmname;
				cout.flush();
				vmname="\'"+vmname+"\'";
				xenvmutil->suspendVM(vmname);	
				break;
			case 4:
				cin.clear();
				cin.ignore(INT_MAX,'\n');
				cout<<"Enter the vmname which you want to pause:: ";
				getline(cin,vmname,'\n');
				cout<<"VMName received is "<<vmname;
				cout.flush();
				vmname="\'"+vmname+"\'";
				xenvmutil->pauseVM(vmname);
				break;
			case 5:
				cin.clear();
				cin.ignore(INT_MAX,'\n');
				cout<<"Enter the vmname which you want to reboot:: ";
				getline(cin,vmname,'\n');
				cout<<"VMName received is "<<vmname;
				cout.flush();
				vmname="\'"+vmname+"\'";
				xenvmutil->rebootVM(vmname);
				break;
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
				xenvmutil->migrateVM(vmname,destn_server);
				break;
			case 7:
				exit(1);
		}
		cout<<"\nPress a key to continue.......";
		getchar();
	}
	return 0;
}