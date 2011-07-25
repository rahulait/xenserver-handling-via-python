#include <stdlib.h>
#include <stdio.h>
#include <climits>
#include "VMUtil.h"

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
	cout<<"\nEnter the username:: ";
	cin>>username;
	cout<<"\nEnter the password:: ";
	cin>>password;
	system("clear");
	cout<<"\n-------------MENU--------------\n";
	cout<<"1.Start VM.\n2.Stop VM\n3.Suspend VM\n4.Pause VM\n5.Reboot VM\n6.Migrate VM\n7.exit\nEnter your choice:: ";
	cin>>choice;
	if(choice<1||choice>7)
	{
			cout<<"\nWrong choice entered.... Program will end now.... ";
	}
	switch(choice)
	{
		case 1:
			cin.clear();
			cin.ignore(INT_MAX,'\n');
			cout<<"\nEnter the vmname which you want to start:: ";
			getline(cin,vmname,'\n');
			cout<<"VMName received is "<<vmname;
			cout.flush();
			vmname="\'"+vmname+"\'";
			VMUtil *vmutil=new VMUtil(url,username,password);
			vmutil->startVM(vmname);
	}
	return 0;
}