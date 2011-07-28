#include <iostream>
#include "XENVMUtil.h"
#include "VMUtilfactory.h"

using namespace std;

VMUtil* VMUtilfactory::createVMUtil(Platform platfrm){
		switch(platfrm)
		{
			case XEN:
				return new XENVMUtil();
				break;
			case ESX:
				
			case HYPERV:
				
			default:
				throw("\nError!!! Platform out of scope......");
		}
}