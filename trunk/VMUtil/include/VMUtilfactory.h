/*********************************************************************
 * Name:      	VMUtilfactory.h
 * Purpose:   	provides declaration of VMUtilfactory class....
 * Author:      Rahul Sharma
 * Created:     
 * Copyright: 
 * License:   	
 *********************************************************************/

//Declaration of VMUtilfactory Header file
//Function Definitions are in VMUtilfactory.cpp file

//prevent multiple inclusions of header files
#ifndef VMUTILFACTORY_H
#define VMUTILFACTORY_H

#include <iostream>
#include <string>
#include "VMUtil.h"                //*****need to include VMUtil.h as we need to create an object of it and pass back to the calling function.

//VMUtilfactory class declaration
class VMUtilfactory
{
public:
	enum Platform{XEN=1,INVALID=2};         //***** More platforms can be added in future like ESX, HYPERV.......
	virtual VMUtil* createVMUtil(Platform); //***** This method creates an object of the required platform and then returns it back....
};

#endif