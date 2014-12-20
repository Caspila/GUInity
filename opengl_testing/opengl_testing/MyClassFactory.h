#pragma once

#include "MyClass.h"

class MyClassFactory
{
public:
	MyClassFactory();
	~MyClassFactory();

	static MyClass  CreateInstance();
	static void ReleaseInstance(MyClass myClass);
	
	
	static MyClass*  CreateInstancePTR();
	static void ReleaseInstancePTR(MyClass* myClass);

};

