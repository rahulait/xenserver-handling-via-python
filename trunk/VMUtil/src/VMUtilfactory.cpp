/*********************************************************************
 * Name:      	VMUtilfactory.cpp
 * Purpose:   	returns an object of the platform which is specified
 * 				by the user.
 * Author:      Rahul Sharma
 * Created:     
 * Copyright: 
 * License:   	
 *********************************************************************/
 
/*********************************************************************
 * XENVMUtil file included here as we need to return an object of it
 * in one of the method/fuunction......
 * VMUtilfactory file included here as it contains the class 
 * declaration.......
*********************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "VMUtil.h"
#include "XENVMUtil.h"         
#include "VMUtilfactory.h"     

using namespace std;

//This method returns an object of the specified platform as entered by the user.....
VMUtil* VMUtilfactory::createVMUtil(Platform platfrm){
	try{
		switch(platfrm)
		{
			case XEN:                      //**** If the platform specified is XEN, then return an object of XENVMUtil class.....
				return new XENVMUtil();
				break;
			default:                       //**** In case the platform entered doesn't match, display the error message and exit....
				throw VMUtilexception("Platform out of scope......");
				exit(1);
		}
	}
	catch(VMUtilexception ex){
		std::cout<<"\nError occured!! "+ ex.getMessage();
	}
}