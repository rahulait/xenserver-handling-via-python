
#ifndef VMUTILFACTORY_H
#define VMUTILFACTORY_H

#include <iostream>
#include <string>
#include "VMUtil.h"

//VMUtilfactory class declaration
class VMUtilfactory
{
public:
	enum Platform{XEN=1,ESX=2,HYPERV=3};
	virtual VMUtil* createVMUtil(Platform);
};

#endif